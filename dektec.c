/* -*- c-file-style: "bsd"; indent-tabs-mode: t; -*- */

/*-
 * Copyright (c) 2012 Giacomo Olgeni. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/bus.h>
#include <sys/uio.h>
#include <sys/poll.h>
#include <sys/selinfo.h>
#include <sys/rman.h>
#include <machine/bus.h>

#include <dev/pci/pcivar.h>
#include <dev/pci/pcireg.h>

#include "Dta1xxRegs.h"
#include "Dta1xxCodes.h"
#include "Plx905x.h"

#include "dektec.h"

#define TX_TIMEOUT (3 * hz)
#define RX_TIMEOUT (3 * hz)

#define DEKTEC_STATE_READ  "dekrd"
#define DEKTEC_STATE_WRITE "dekwr"

#define BOARD_MODEL_140   140
#define BOARD_MODEL_145   145
#define BOARD_MODEL_2145 2145

#define PLX_PCI_VENDOR_ID     0x10B5
#define PLX_PCI_DEVICE_ID     0x9056
#define DTA1XX_PCI_VENDOR_ID  0x1A0E

#define DTA100_PCI_DEVICE_ID  0xD100
#define DTA102_PCI_DEVICE_ID  0xD102
#define DTA105_PCI_DEVICE_ID  0x0069
#define DTA107_PCI_DEVICE_ID  0xD107
#define DTA110_PCI_DEVICE_ID  0xD10A
#define DTA115_PCI_DEVICE_ID  0x0073
#define DTA116_PCI_DEVICE_ID  0x0074
#define DTA120_PCI_DEVICE_ID  0xD114
#define DTA122_PCI_DEVICE_ID  0xD116
#define DTA124_PCI_DEVICE_ID  0xD118
#define DTA140_PCI_DEVICE_ID  0xD128
#define DTA145_PCI_DEVICE_ID  0x0091
#define DTA2145_PCI_DEVICE_ID 0x0861
#define DTA160_PCI_DEVICE_ID  0x00A0
#define DTA545_PCI_DEVICE_ID  0xD2BD

#define REG_DMA_DESC 0x04
#define REG_CMD_STAT 0x08

#define ASI_PLX_DESCRIPTOR_ALIGN 16
#define ASI_PLX_SEGMENT_ALIGN     4

#define TX_BUFFER_SIZE 65536
#define RX_BUFFER_SIZE 65536

#define BUFFER_MAX_DMA_SIZE         65536
#define BUFFER_MAX_DMA_SEGMENTS       256
#define BUFFER_MAX_DMA_SEGMENT_SIZE 65536
#define DESC_MAX_DMA_SIZE           65536
#define DESC_MAX_DMA_SEGMENTS         256
#define DESC_MAX_DMA_SEGMENT_SIZE   65536

#define DMA_BUSY 0x01

static d_open_t      dektec_open;
static d_close_t     dektec_close;
static d_ioctl_t     dektec_ioctl;
static d_read_t      dektec_read;
static d_write_t     dektec_write;
static d_poll_t      dektec_poll;
static driver_intr_t dektec_intr;

static struct cdevsw dektec_cdevsw = {
	.d_version = D_VERSION,
	.d_flags   = D_NEEDGIANT, /* FIXME do we really need GIANT? */
	.d_open    = dektec_open,
	.d_close   = dektec_close,
	.d_read    = dektec_read,
	.d_write   = dektec_write,
	.d_ioctl   = dektec_ioctl,
	.d_poll    = dektec_poll,
	.d_name    = "dektec",
};

static devclass_t dektec_devclass;

/*
 * PLX 9080 DMA descriptor
 */

struct plx_dma_desc {
	uint32_t	pci_addr;
	uint32_t	local_addr;
	uint32_t	bytes;
	uint32_t	next_desc;
};

struct plx_dma_buffer {
	struct dektec_sc	*sc;

	bus_dmamap_t		buffer_dmamap;
	bus_dmamap_t		desc_dmamap;
	int			segment_count;
	bus_addr_t		desc_ds_addr;

	uint32_t		flags;

	uint8_t			*buffer;

	struct plx_dma_desc	*desc_list;
};

struct dektec_sc {
	device_t		dev;
	struct cdev		*cdev;

	int			fw_rev_gen;
	int			fw_rev_tx;
	int			fw_rev_rx;

	int			model;
	int			legacy_plx;

	uint32_t		gen_base, tx_base, rx_base;
	uint32_t		dma_base0, dma_base1;

	int			plx_base_id;
	struct resource		*plx_base_res;
	bus_space_tag_t		plx_base_bt;
	bus_space_handle_t	plx_base_bh;

	int			dta_base_id;
	struct resource		*dta_base_res;
	bus_space_tag_t		dta_base_bt;
	bus_space_handle_t	dta_base_bh;

	int			irq_id;
	struct resource		*irq_res;
	bus_space_tag_t		irq_bt;
	bus_space_handle_t	irq_bh;
	void			*irq_cookie;

	bus_dma_tag_t		buffer_dma_tag;
	bus_dma_tag_t		desc_dma_tag;

	struct plx_dma_buffer	tx_buffer;
	struct plx_dma_buffer	rx_buffer;

	int			tx_watermark, rx_watermark;

	struct selinfo		selinfo;
	struct mtx		mutex; /* FIXME actually use the mutex */
};

// {{{ get_device_model

static int
get_device_model (device_t dev)
{
	uint32_t vendor_id = pci_get_vendor (dev);
	uint32_t device_id = pci_get_device (dev);

	if (vendor_id == PLX_PCI_VENDOR_ID && device_id == PLX_PCI_DEVICE_ID)
		return BOARD_MODEL_140;

	if (vendor_id == DTA1XX_PCI_VENDOR_ID) {
		if (device_id == DTA145_PCI_DEVICE_ID)
			return BOARD_MODEL_145;

		if (device_id == DTA2145_PCI_DEVICE_ID)
			return BOARD_MODEL_2145;
	}

	return 0;
}

// }}}
// {{{ desc_dmamap_cb

static void
desc_dmamap_cb (void *arg, bus_dma_segment_t *segments, int nseg, int error_flag)
{
	if (error_flag)
		return;

	struct plx_dma_buffer *dma_buffer = (struct plx_dma_buffer *) arg;

	/* sanity check for clang */

	if (dma_buffer == NULL || dma_buffer->desc_list == NULL)
		return;

	struct plx_dma_desc *desc = dma_buffer->desc_list;
	struct plx_dma_desc *prev_desc = NULL;

	dma_buffer->segment_count = nseg;

	int index = 0;

	bus_addr_t ds_addr = segments[index].ds_addr;
	bus_size_t ds_len = segments[index].ds_len;

	dma_buffer->desc_ds_addr = ds_addr;

	/* FIXME check again */

	for (;;) {
		if (prev_desc != NULL)
			prev_desc->next_desc = ds_addr;

		prev_desc = desc;

		ds_addr += sizeof (struct plx_dma_desc);
		ds_len -= sizeof (struct plx_dma_desc);

		if (ds_len == 0) {
			index++;

			if (index == nseg)
				break;
		}

		desc++;
	}

	desc->next_desc = PCI905X_DMADPR_ENDOFCHAIN | PCI905X_DMADPR_INTAFTERTC;
}

// }}}
// {{{ buffer_dmamap_cb

static void
buffer_dmamap_cb (void *arg, bus_dma_segment_t *segments, int nseg, int error_flag)
{
	if (error_flag)
		goto error_flag;

	int error = 0;

	struct plx_dma_buffer *dma_buffer = (struct plx_dma_buffer *) arg;

	error = bus_dmamem_alloc (dma_buffer->sc->desc_dma_tag,
				  (void **) &dma_buffer->desc_list,
				  BUS_DMA_WAITOK | BUS_DMA_ZERO,
				  &dma_buffer->desc_dmamap);

	if (error)
		goto bus_dmamem_alloc;

	error = bus_dmamap_load (dma_buffer->sc->desc_dma_tag, dma_buffer->desc_dmamap,
				 dma_buffer->desc_list, nseg * sizeof (struct plx_dma_desc),
				 desc_dmamap_cb, dma_buffer, 0);

	if (error)
		goto bus_dmamap_load;

	for (int i = 0; i < nseg; i++) {
		struct plx_dma_desc *desc = (struct plx_dma_desc *) &(dma_buffer->desc_list[i]);

		desc->pci_addr = segments[i].ds_addr;
		desc->bytes = segments[i].ds_len;
	}

	goto done;

bus_dmamap_load:
	bus_dmamem_free (dma_buffer->sc->buffer_dma_tag, dma_buffer->buffer, dma_buffer->buffer_dmamap);

bus_dmamem_alloc:
error_flag:
done:
	return;
}

// }}}
// {{{ allocate_buffer

static int
allocate_buffer (device_t dev, struct dektec_sc *sc, struct plx_dma_buffer *dma_buffer)
{
	int error = 0;

	dma_buffer->sc = sc;
	dma_buffer->segment_count = 0;
	dma_buffer->desc_ds_addr = 0;
	dma_buffer->flags = 0;
	dma_buffer->desc_list = NULL;

	error = bus_dmamap_create (sc->buffer_dma_tag, 0, &dma_buffer->buffer_dmamap);

	if (error)
		goto bus_dmamap_create0;

	error = bus_dmamap_create (sc->desc_dma_tag, 0, &dma_buffer->desc_dmamap);

	if (error)
		goto bus_dmamap_create1;

	error = bus_dmamem_alloc (sc->buffer_dma_tag,
				  (void **) &dma_buffer->buffer,
				  BUS_DMA_WAITOK | BUS_DMA_ZERO,
				  &(dma_buffer->buffer_dmamap));

	if (error)
		goto bus_dmamem_alloc;

	goto done;

bus_dmamem_alloc:
	bus_dmamap_destroy (sc->desc_dma_tag, dma_buffer->desc_dmamap);

bus_dmamap_create1:
	bus_dmamap_destroy (sc->buffer_dma_tag, dma_buffer->buffer_dmamap);

bus_dmamap_create0:
done:
	return error;
}

// }}}
// {{{ free_buffer

static int
free_buffer (device_t dev, struct dektec_sc *sc, struct plx_dma_buffer *dma_buffer)
{
	bus_dmamem_free (sc->buffer_dma_tag, dma_buffer->buffer, dma_buffer->buffer_dmamap);

	bus_dmamap_destroy (sc->buffer_dma_tag, dma_buffer->buffer_dmamap);
	bus_dmamap_destroy (sc->desc_dma_tag, dma_buffer->desc_dmamap);

	return 0;
}

// }}}
// {{{ tx_fifo_available

static int
tx_fifo_available (struct dektec_sc *sc)
{
	int tx_fifo_size = dta1xx_tx_get_fifo_size_reg (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
	int tx_fifo_load = dta1xx_tx_get_fifo_load_reg (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);

	int tx_fifo_available = tx_fifo_size - tx_fifo_load;

	return (tx_fifo_available > 0) && (tx_fifo_available >= sc->tx_watermark);
}

// }}}
// {{{ rx_data_available

static int
rx_data_available (struct dektec_sc *sc)
{
	int rx_fifo_load = dta1xx_rx_get_fifo_load_reg (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);

	return (rx_fifo_load > 0) && (rx_fifo_load >= sc->rx_watermark);
}

// }}}
// {{{ reset_plx

static void
reset_plx (device_t dev)
{
	struct dektec_sc *sc = (struct dektec_sc *) device_get_softc (dev);

	uint32_t cntrl = bus_space_read_4 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_EEPROM_CTRL_STAT);

	WRITE_LONG (cntrl | PCI905X_CNTRL_RESET, sc->plx_base_bt, sc->plx_base_bh,
		    PCI905X_EEPROM_CTRL_STAT);
	bus_space_read_4 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_EEPROM_CTRL_STAT);
	DELAY (100L);

	WRITE_LONG (cntrl, sc->plx_base_bt, sc->plx_base_bh, PCI905X_EEPROM_CTRL_STAT);
	bus_space_read_4 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_EEPROM_CTRL_STAT);
	DELAY (100L);

	WRITE_LONG (cntrl | PCI905X_CNTRL_RECONFIG, sc->plx_base_bt, sc->plx_base_bh,
		    PCI905X_EEPROM_CTRL_STAT);
	bus_space_read_4 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_EEPROM_CTRL_STAT);
	DELAY (6000); /* 6 Kus */

	WRITE_LONG (cntrl, sc->plx_base_bt, sc->plx_base_bh, PCI905X_EEPROM_CTRL_STAT);
	bus_space_read_4 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_EEPROM_CTRL_STAT);

	/* FIXME remove/refactor */
	dta1xx_gen_ctrl_reg_reset (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base);
	DELAY (6000); /* 6 Kus */

	WRITE_BYTE (PCI905X_DMACSR_CLEARINT, sc->plx_base_bt, sc->plx_base_bh,
		    PCI905X_DMA0_COMMAND_STAT);
	bus_space_read_1 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA0_COMMAND_STAT);

	WRITE_BYTE (PCI905X_DMACSR_CLEARINT, sc->plx_base_bt, sc->plx_base_bh,
		    PCI905X_DMA1_COMMAND_STAT);
	bus_space_read_1 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA1_COMMAND_STAT);
}

// }}}
// {{{ enable_plx

static void
enable_plx (device_t dev)
{
	struct dektec_sc *sc = (struct dektec_sc *) device_get_softc (dev);

	WRITE_LONG (PCI905X_INTCSR_PCI_INTEN   |
		    PCI905X_INTCSR_LOCAL_INTEN |
		    PCI905X_INTCSR_DMA0_INTEN  |
		    PCI905X_INTCSR_DMA1_INTEN,
		    sc->plx_base_bt, sc->plx_base_bh, PCI905X_INT_CTRL_STAT);

	bus_space_read_4 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_INT_CTRL_STAT);

	WRITE_LONG (PCI905X_DMAMODE_BUSWIDTH_32 |
		    PCI905X_DMAMODE_READY_INPEN |
		    PCI905X_DMAMODE_LOCALBURST  |
		    PCI905X_DMAMODE_SCATGATH    |
		    PCI905X_DMAMODE_DONE_INTEN  |
		    PCI905X_DMAMODE_LOC_CONST   |
		    PCI905X_DMAMODE_DEMAND      |
		    PCI905X_DMAMODE_INT2PCI,
		    sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA0_MODE);

	bus_space_read_4 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA0_MODE);

	WRITE_LONG (PCI905X_DMAMODE_BUSWIDTH_32 |
		    PCI905X_DMAMODE_READY_INPEN |
		    PCI905X_DMAMODE_LOCALBURST  |
		    PCI905X_DMAMODE_SCATGATH    |
		    PCI905X_DMAMODE_DONE_INTEN  |
		    PCI905X_DMAMODE_LOC_CONST   |
		    PCI905X_DMAMODE_DEMAND      |
		    PCI905X_DMAMODE_INT2PCI,
		    sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA1_MODE);

	bus_space_read_4 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA1_MODE);
}

// }}}
// {{{ dektec_probe

static int
dektec_probe (device_t dev)
{
	switch (get_device_model (dev)) {
	case BOARD_MODEL_140:
		device_set_desc (dev, "DekTek DTA-140");
		return BUS_PROBE_SPECIFIC;

	case BOARD_MODEL_145:
		device_set_desc (dev, "DekTek DTA-145");
		return BUS_PROBE_SPECIFIC;

	case BOARD_MODEL_2145:
		device_set_desc (dev, "DekTek DTA-2145");
		return BUS_PROBE_SPECIFIC;

	default:
		return ENXIO;
	}
}

// }}}
// {{{ dektec_attach

static int
dektec_attach (device_t dev)
{
	int error = 0;

	struct dektec_sc *sc = (struct dektec_sc *) device_get_softc (dev);

	sc->dev = dev;

	sc->model = get_device_model (dev);

	int unit = device_get_unit (dev);

	if ((sc->cdev = make_dev (&dektec_cdevsw, unit, UID_ROOT, GID_OPERATOR, 0666, "dektec%d", unit)) == NULL)
		goto make_dev;

	sc->cdev->si_drv1 = sc;

	uint32_t vendor_id = pci_get_vendor (dev);

	sc->legacy_plx = vendor_id == PLX_PCI_VENDOR_ID;

	if (sc->legacy_plx) {
		sc->plx_base_id = PCIR_BAR (0);
		sc->plx_base_res = bus_alloc_resource_any (dev, SYS_RES_MEMORY, &(sc->plx_base_id), RF_ACTIVE);

		if (sc->plx_base_res == NULL)
			goto bus_alloc_resource_any_plx_reg;

		sc->plx_base_bt = rman_get_bustag (sc->plx_base_res);
		sc->plx_base_bh = rman_get_bushandle (sc->plx_base_res);

		/* FIXME refactor dta_base */
		sc->dta_base_id = PCIR_BAR (2);
		sc->dta_base_res = bus_alloc_resource_any (dev, SYS_RES_MEMORY, &(sc->dta_base_id), RF_ACTIVE);

		if (sc->dta_base_res == NULL)
			goto bus_alloc_resource_any_dta_base;

		sc->dta_base_bt = rman_get_bustag (sc->dta_base_res);
		sc->dta_base_bh = rman_get_bushandle (sc->dta_base_res);

		/* DTA-140 */
		sc->gen_base = 0x0000; /* FIXME make constant */
		sc->tx_base = 0x0080;
		sc->rx_base = 0x0100;
		sc->dma_base0 = 0x0000;
		sc->dma_base1 = 0x0000;
	} else {
		/* pCh->m_Dma.m_pRegBase = pBase; */
		/* pCh->m_Dma.m_pRegDmaDesc = pBase + 0x4; */
		/* pCh->m_Dma.m_pRegCmdStat = pBase + 0x8; */

		/* FIXME refactor dta_base */
		sc->dta_base_id = PCIR_BAR (0);
		sc->dta_base_res = bus_alloc_resource_any (dev, SYS_RES_MEMORY, &(sc->dta_base_id), RF_ACTIVE);

		if (sc->dta_base_res == NULL)
			goto bus_alloc_resource_any_dta_base;

		sc->dta_base_bt = rman_get_bustag (sc->dta_base_res);
		sc->dta_base_bh = rman_get_bushandle (sc->dta_base_res);

		/* DTA-145 */
		sc->gen_base = 0x0000; /* FIXME make constant */
		/* program configurable channel */
		// sc->tx_base = 0x0180; /* pFdo->m_TsTx[ti]->m_pRegBase = (char*)(pRegBase + 0x180 + (0x200*i)) */
		sc->tx_base = 0x0380; /* pFdo->m_TsTx[ti]->m_pRegBase = (char*)(pRegBase + 0x180 + (0x200*i)) */
		sc->rx_base = 0x0100; /* pFdo->m_TsRx[i]->m_pRegBase = (char*)(pRegBase + 0x100 + (0x200*i)) */
		sc->dma_base0 = 0x0200;
		sc->dma_base1 = 0x0400;
	}

	sc->irq_id = 0x0;
	sc->irq_res = bus_alloc_resource_any (dev, SYS_RES_IRQ, &(sc->irq_id), RF_SHAREABLE | RF_ACTIVE);

	if (sc->irq_res == NULL)
		goto bus_alloc_resource_any_irq;

	error = bus_setup_intr (dev, sc->irq_res, INTR_TYPE_MISC, NULL, dektec_intr, sc, &(sc->irq_cookie));

	if (error)
		goto bus_setup_intr;

	error = bus_dma_tag_create (NULL, ASI_PLX_SEGMENT_ALIGN, 0, BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR,
				    NULL, NULL, BUFFER_MAX_DMA_SIZE, BUFFER_MAX_DMA_SEGMENTS, BUFFER_MAX_DMA_SEGMENT_SIZE,
				    BUS_DMA_ALLOCNOW, NULL, NULL, &sc->buffer_dma_tag);

	if (error)
		goto bus_dma_tag_create_buffer;

	error = bus_dma_tag_create (NULL, ASI_PLX_DESCRIPTOR_ALIGN, 0, BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR,
				    NULL, NULL, DESC_MAX_DMA_SIZE, DESC_MAX_DMA_SEGMENTS, DESC_MAX_DMA_SEGMENT_SIZE,
				    BUS_DMA_ALLOCNOW, NULL, NULL, &sc->desc_dma_tag);

	if (error)
		goto bus_dma_tag_create_desc;

	error = allocate_buffer (dev, sc, &sc->tx_buffer);

	if (error)
		goto allocate_tx_buffer;

	error = allocate_buffer (dev, sc, &sc->rx_buffer);

	if (error)
		goto allocate_rx_buffer;

	if (sc->legacy_plx) {
		reset_plx (dev);
		enable_plx (dev);
	}

	sc->fw_rev_gen = dta1xx_gen_ctrl_reg_get_firmware_rev (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base);
	sc->fw_rev_tx = dta1xx_tx_gen_ctrl_reg_get_firmware_rev (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
	sc->fw_rev_rx = dta1xx_rx_gen_ctrl_reg_get_firmware_rev (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);

	mtx_init (&sc->mutex, "dektec", NULL, MTX_DEF);

	device_printf (dev, "board model %d, firmware version %d (tx: %d, rx: %d), tx fifo %d MB\n",
		       dta1xx_rx_gen_ctrl_reg_get_type_number (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base),
		       sc->fw_rev_gen, sc->fw_rev_tx, sc->fw_rev_rx,
		       dta1xx_tx_get_fifo_size_reg (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base) / 1024);

	goto done;

allocate_rx_buffer:
	free_buffer (dev, sc, &sc->tx_buffer);

allocate_tx_buffer:
	bus_dma_tag_destroy (sc->desc_dma_tag);

bus_dma_tag_create_desc:
	bus_dma_tag_destroy (sc->buffer_dma_tag);

bus_dma_tag_create_buffer:
	bus_teardown_intr (dev, sc->irq_res, sc->irq_cookie);

bus_setup_intr:
	bus_release_resource (dev, SYS_RES_IRQ, sc->irq_id, sc->irq_res);

bus_alloc_resource_any_irq:
	bus_release_resource (dev, SYS_RES_MEMORY, sc->dta_base_id, sc->dta_base_res);

bus_alloc_resource_any_dta_base:
	bus_release_resource (dev, SYS_RES_MEMORY, sc->plx_base_id, sc->plx_base_res);

bus_alloc_resource_any_plx_reg:
	destroy_dev (sc->cdev);

make_dev:
done:
	return error;
}

// }}}
// {{{ dektec_detach

static int
dektec_detach (device_t dev)
{
	struct dektec_sc *sc = (struct dektec_sc *) device_get_softc (dev);

	if (sc->legacy_plx)
		reset_plx (dev);

	free_buffer (dev, sc, &sc->rx_buffer);
	free_buffer (dev, sc, &sc->tx_buffer);

	bus_dma_tag_destroy (sc->desc_dma_tag);
	bus_dma_tag_destroy (sc->buffer_dma_tag);

	bus_teardown_intr (dev, sc->irq_res, sc->irq_cookie);

	bus_release_resource (dev, SYS_RES_IRQ, sc->irq_id, sc->irq_res);

	if (sc->legacy_plx) {
		bus_release_resource (dev, SYS_RES_MEMORY, sc->dta_base_id, sc->dta_base_res);
		bus_release_resource (dev, SYS_RES_MEMORY, sc->plx_base_id, sc->plx_base_res);
	} else {
		bus_release_resource (dev, SYS_RES_MEMORY, sc->dta_base_id, sc->dta_base_res);
	}

	destroy_dev (sc->cdev);

	mtx_destroy (&sc->mutex);

	return 0;
}

// }}}
// {{{ dektec_open

static int
dektec_open (struct cdev *cdev, int flag, int otyp, struct thread *td)
{
	struct dektec_sc *sc = cdev->si_drv1;

	device_busy (sc->dev);

	sc->tx_watermark = 0;
	sc->rx_watermark = 0;

	dta1xx_gen_ctrl_reg_reset (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base);
	dta1xx_gen_ctrl_reg_set_per_int_val (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base, 4); /* 145 */
	dta1xx_gen_ctrl_reg_set_per_int_en (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base, 1);

	switch (sc->model) {
	case BOARD_MODEL_140:
		break;

	case BOARD_MODEL_145:
	case BOARD_MODEL_2145:
		/* ASI/SDI Transmit (Tx) channel 0 at 0x180 (rx_base + 0x80) */
		dta1xx_tx_ctrl_reg_set_output_en (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base + 0x80, 0);
		dta1xx_tx_ctrl_reg_set_output_en (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base, 1);
		dta1xx_dma_timeout_set (sc->dta_base_bt, sc->dta_base_bh, sc->dma_base0, 0);
		dta1xx_dma_timeout_set (sc->dta_base_bt, sc->dta_base_bh, sc->dma_base1, 0);
		break;
	}

	return 0;
}

// }}}
// {{{ dektec_close

static int
dektec_close (struct cdev *cdev, int flag, int otyp, struct thread *td)
{
	struct dektec_sc *sc = cdev->si_drv1;

	sc->tx_watermark = 0;
	sc->rx_watermark = 0;

	dta1xx_gen_ctrl_reg_set_per_int_en (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base, 0);
	dta1xx_gen_ctrl_reg_reset (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base);

	device_unbusy (sc->dev);

	return 0;
}

// }}}
// {{{ unload_tx_buffer

static void
unload_tx_buffer (struct dektec_sc *sc)
{
	bus_dmamap_unload (sc->desc_dma_tag, sc->tx_buffer.desc_dmamap);
	bus_dmamem_free (sc->desc_dma_tag, sc->tx_buffer.desc_list, sc->tx_buffer.desc_dmamap);
	bus_dmamap_unload (sc->buffer_dma_tag, sc->tx_buffer.buffer_dmamap);
}

// }}}
// {{{ unload_rx_buffer

static void
unload_rx_buffer (struct dektec_sc *sc)
{
	bus_dmamap_unload (sc->desc_dma_tag, sc->rx_buffer.desc_dmamap);
	bus_dmamem_free (sc->desc_dma_tag, sc->rx_buffer.desc_list, sc->rx_buffer.desc_dmamap);
	bus_dmamap_unload (sc->buffer_dma_tag, sc->rx_buffer.buffer_dmamap);
}

// }}}
// {{{ dektec_read

static int
dektec_read (struct cdev *cdev, struct uio *uio, int ioflag)
{
	int error = 0;

	struct dektec_sc *sc = cdev->si_drv1;

	while (uio->uio_resid > 0) {
		struct plx_dma_buffer *dma_buffer = &sc->rx_buffer;

		int amount = MIN (RX_BUFFER_SIZE, uio->uio_resid);

		error = bus_dmamap_load (sc->buffer_dma_tag, sc->rx_buffer.buffer_dmamap,
					 sc->rx_buffer.buffer, amount, buffer_dmamap_cb, dma_buffer, 0);

		if (error)
			goto bus_dmamap_load;

		for (int i = 0; i < sc->rx_buffer.segment_count; i++) {
			struct plx_dma_desc *desc = (struct plx_dma_desc *) &(sc->rx_buffer.desc_list[i]);

			desc->local_addr = sc->rx_base + DTA1XX_RX_REG_FIFO_FIRST;
			desc->next_desc |= PCI905X_DMADPR_DIROFTFR;
		}

		error = uiomove (sc->rx_buffer.buffer, amount, uio);

		if (error)
			goto uiomove;

		bus_dmamap_sync (sc->desc_dma_tag, sc->rx_buffer.desc_dmamap, BUS_DMASYNC_PREREAD);
		bus_dmamap_sync (sc->buffer_dma_tag, sc->rx_buffer.buffer_dmamap, BUS_DMASYNC_PREREAD);

		if (sc->legacy_plx) {
			/* DMA1 is used for reading */
			WRITE_LONG (sc->rx_buffer.desc_ds_addr | PCI905X_DMADPR_DESCLOC_PCI,
				    sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA1_DESC_PTR);

			bus_space_read_4 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA1_DESC_PTR);

			WRITE_BYTE (PCI905X_DMACSR_ENABLE | PCI905X_DMACSR_START,
				    sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA1_COMMAND_STAT);

			bus_space_read_1 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA1_COMMAND_STAT);
		} else {
			/* DMA0 is used for reading */
			WRITE_LONG (sc->rx_buffer.desc_ds_addr | PCI905X_DMADPR_DESCLOC_PCI,
				    sc->dta_base_bt, sc->dta_base_bh, sc->dma_base0 + REG_DMA_DESC);

			bus_space_read_4 (sc->dta_base_bt, sc->dta_base_bh, sc->dma_base0 + REG_DMA_DESC);

			WRITE_BYTE (PCI905X_DMACSR_ENABLE | PCI905X_DMACSR_START,
				    sc->dta_base_bt, sc->dta_base_bh, sc->dma_base0 + REG_CMD_STAT);

			bus_space_read_1 (sc->dta_base_bt, sc->dta_base_bh, sc->dma_base0 + REG_CMD_STAT);
		}

		sc->rx_buffer.flags |= DMA_BUSY;

		if (tsleep (&sc->rx_buffer, PRIBIO, DEKTEC_STATE_READ, RX_TIMEOUT) == EWOULDBLOCK) {
			error = EIO;

			goto tsleep;
		}

		unload_rx_buffer (sc);
	}

	goto done;

tsleep:
uiomove:
	unload_rx_buffer (sc);

bus_dmamap_load:
done:
	return error;
}

// }}}
// {{{ dektec_write

static int
dektec_write (struct cdev *cdev, struct uio *uio, int ioflag)
{
	int error = 0;

	struct dektec_sc *sc = cdev->si_drv1;

	while (uio->uio_resid > 0) {
		struct plx_dma_buffer *dma_buffer = &sc->tx_buffer;

		int amount = MIN (TX_BUFFER_SIZE, uio->uio_resid);

		error = bus_dmamap_load (sc->buffer_dma_tag, sc->tx_buffer.buffer_dmamap,
					 sc->tx_buffer.buffer, amount, buffer_dmamap_cb, dma_buffer, 0);

		if (error)
			goto bus_dmamap_load;

		for (int i = 0; i < sc->tx_buffer.segment_count; i++) {
			struct plx_dma_desc *desc = (struct plx_dma_desc *) &(sc->tx_buffer.desc_list[i]);

			desc->local_addr = sc->tx_base + DTA1XX_TX_REG_FIFO_FIRST;
			desc->next_desc &= ~PCI905X_DMADPR_DIROFTFR;
		}

		error = uiomove (sc->tx_buffer.buffer, amount, uio);

		if (error)
			goto uiomove;

		bus_dmamap_sync (sc->desc_dma_tag, sc->tx_buffer.desc_dmamap, BUS_DMASYNC_PREREAD);
		bus_dmamap_sync (sc->buffer_dma_tag, sc->tx_buffer.buffer_dmamap, BUS_DMASYNC_PREREAD);

		if (sc->legacy_plx) {
			/* DMA0 is used for writing */
			WRITE_LONG (sc->tx_buffer.desc_ds_addr | PCI905X_DMADPR_DESCLOC_PCI,
				    sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA0_DESC_PTR);

			bus_space_read_4 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA0_DESC_PTR);

			WRITE_BYTE (PCI905X_DMACSR_ENABLE | PCI905X_DMACSR_START,
				    sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA0_COMMAND_STAT);

			bus_space_read_1 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA0_COMMAND_STAT);
		} else {
			/* DMA1 is used for writing */
			WRITE_LONG (sc->tx_buffer.desc_ds_addr | PCI905X_DMADPR_DESCLOC_PCI,
				    sc->dta_base_bt, sc->dta_base_bh, sc->dma_base1 + REG_DMA_DESC);

			bus_space_read_4 (sc->dta_base_bt, sc->dta_base_bh, sc->dma_base1 + REG_DMA_DESC);

			WRITE_BYTE (PCI905X_DMACSR_ENABLE | PCI905X_DMACSR_START,
				    sc->dta_base_bt, sc->dta_base_bh, sc->dma_base1 + REG_CMD_STAT);

			bus_space_read_1 (sc->dta_base_bt, sc->dta_base_bh, sc->dma_base1 + REG_CMD_STAT);
		}

		sc->tx_buffer.flags |= DMA_BUSY;

		if (tsleep (&sc->tx_buffer, PRIBIO, DEKTEC_STATE_WRITE, TX_TIMEOUT) == EWOULDBLOCK) {
			printf ("dektec_write: EIO (fifo size: %d, load: %d, watermark: %d)\n",
				dta1xx_tx_get_fifo_size_reg (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base),
				dta1xx_tx_get_fifo_load_reg (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base),
				sc->tx_watermark);

			error = EIO;

			goto tsleep;
		}

		unload_tx_buffer (sc);
	}

	goto done;

tsleep:
uiomove:
	unload_tx_buffer (sc);

bus_dmamap_load:
done:
	return error;
}

// }}}
// {{{ dektec_ioctl

static int
dektec_ioctl (struct cdev *cdev, u_long cmd, caddr_t arg, int mode, struct thread *td)
{
	struct dektec_sc *sc = cdev->si_drv1;

	int error = 0;

	switch (cmd) {

		/* Gen */

	case IOCTL_Dta1xxGenCtrlRegReset:
		dta1xx_gen_ctrl_reg_reset (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base);
		break;
	case IOCTL_Dta1xxGenCtrlRegGetFirmwareRev:
		*(int *) arg = dta1xx_gen_ctrl_reg_get_firmware_rev (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base);
		break;

		/* RX */

	case IOCTL_Dta1xxRxGenCtrlRegGetFirmwareRev:
		*(int *) arg = dta1xx_rx_gen_ctrl_reg_get_firmware_rev (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxGenCtrlRegGetTypeNumber:
		*(int *) arg = dta1xx_rx_gen_ctrl_reg_get_type_number (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxCtrlRegGetRxMode:
		*(int *) arg = dta1xx_rx_ctrl_reg_get_rx_mode (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxCtrlRegSetRxMode:
		dta1xx_rx_ctrl_reg_set_rx_mode (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxRxCtrlRegGetRxCtrl:
		*(int *) arg = dta1xx_rx_ctrl_reg_get_rx_ctrl (sc->dta_base_bt, sc->rx_base, sc->dta_base_bh);
		break;
	case IOCTL_Dta1xxRxCtrlRegSetRxCtrl:
		dta1xx_rx_ctrl_reg_set_rx_ctrl (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxRxCtrlRegGetAsiInv:
		*(int *) arg = dta1xx_rx_ctrl_reg_get_asi_inv (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxCtrlRegSetAsiInv:
		dta1xx_rx_ctrl_reg_set_asi_inv (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxRxCtrlRegGetEqualise:
		*(int *) arg = dta1xx_rx_ctrl_reg_get_equalise (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxCtrlRegSetEqualise:
		dta1xx_rx_ctrl_reg_set_equalise (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxRxCtrlRegGetEnaPwr:
		*(int *) arg = dta1xx_rx_ctrl_reg_get_ena_pwr (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxCtrlRegSetEnaPwr:
		dta1xx_rx_ctrl_reg_set_ena_pwr (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxRxClrFifo:
		dta1xx_rx_clr_fifo (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxStatusRegGetPckSize:
		*(int *) arg = dta1xx_rx_status_reg_get_pck_size (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxStatusRegGetNumInv:
		*(int *) arg = dta1xx_rx_status_reg_get_num_inv (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxStatusRegGetSdramSize:
		*(int *) arg = dta1xx_rx_status_reg_get_sdram_size (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxStatusRegGetAsiCD:
		*(int *) arg = dta1xx_rx_status_reg_get_asi_cd (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxStatusRegGetAsiLock:
		*(int *) arg = dta1xx_rx_status_reg_get_asi_lock (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxStatusRegGetRateOk:
		*(int *) arg = dta1xx_rx_status_reg_get_rate_ok (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxStatusRegGetAsiInv:
		*(int *) arg = dta1xx_rx_status_reg_get_asi_inv (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;
	case IOCTL_Dta1xxRxGetFifoLoadReg:
		*(int *) arg = dta1xx_rx_get_fifo_load_reg (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base);
		break;

		/* TX */

	case IOCTL_Dta1xxTxGenCtrlRegGetFirmwareRev:
		*(int *) arg = dta1xx_tx_gen_ctrl_reg_get_firmware_rev (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;
	case IOCTL_Dta1xxTxGenCtrlRegGetTypeNumber:
		*(int *) arg = dta1xx_tx_gen_ctrl_reg_get_type_number (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;
	case IOCTL_Dta1xxTxCtrlRegGetTxMode:
		*(int *) arg = dta1xx_tx_ctrl_reg_get_tx_mode (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;
	case IOCTL_Dta1xxTxCtrlRegSetTxMode:
		dta1xx_tx_ctrl_reg_set_tx_mode (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxTxCtrlRegGetBurstMode:
		*(int *) arg = dta1xx_tx_ctrl_reg_get_burst_mode (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;
	case IOCTL_Dta1xxTxCtrlRegSetBurstMode:
		dta1xx_tx_ctrl_reg_set_burst_mode (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxTxCtrlRegGetPckStuff:
		*(int *) arg = dta1xx_tx_ctrl_reg_get_pck_stuff (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;
	case IOCTL_Dta1xxTxCtrlRegSetPckStuff:
		dta1xx_tx_ctrl_reg_set_pck_stuff (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxTxCtrlRegGetTxCtrl:
		*(int *) arg = dta1xx_tx_ctrl_reg_get_tx_ctrl (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;
	case IOCTL_Dta1xxTxCtrlRegSetTxCtrl:
		dta1xx_tx_ctrl_reg_set_tx_ctrl (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxTxCtrlRegSetEnaPwr:
		dta1xx_tx_ctrl_reg_set_ena_pwr (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxTxClrFifo:
		dta1xx_tx_clr_fifo (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;
	case IOCTL_Dta1xxTxCtrlSetTxAsiInv:
		dta1xx_tx_ctrl_set_tx_asi_inv (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxTxStatusRegGetFifoFilled:
		*(int *) arg = dta1xx_tx_status_reg_get_fifo_filled (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;
	case IOCTL_Dta1xxTxStatusRegGetSdramSize:
		*(int *) arg = dta1xx_tx_status_reg_get_sdram_size (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;
	case IOCTL_Dta1xxTxGetTxClockReg:
		*(int *) arg = dta1xx_tx_get_tx_clock_reg (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;
	case IOCTL_Dta1xxTxSetTxClockReg:
		dta1xx_tx_set_tx_clock_reg (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxTxGetFifoSizeReg:
		*(int *) arg = dta1xx_tx_get_fifo_size_reg (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;
	case IOCTL_Dta1xxTxSetFifoSizeReg:
		dta1xx_tx_set_fifo_size_reg (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base, *(int *) arg);
		break;
	case IOCTL_Dta1xxTxGetFifoLoadReg:
		*(int *) arg = dta1xx_tx_get_fifo_load_reg (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base);
		break;

		/* Fifo */

	case IOCTL_Dta1xxTxSetWatermark:
		sc->tx_watermark = *(int *) arg;
		break;
	case IOCTL_Dta1xxTxGetWatermark:
		*(int *) arg = sc->tx_watermark;
		break;
	case IOCTL_Dta1xxRxSetWatermark:
		sc->rx_watermark = *(int *) arg;
		break;
	case IOCTL_Dta1xxRxGetWatermark:
		*(int *) arg = sc->rx_watermark;
		break;

	default:
		error = EINVAL;
		break;
	}

	return error;
}

// }}}
// {{{ dektec_poll

static int
dektec_poll (struct cdev *cdev, int events, struct thread *td)
{
	struct dektec_sc *sc = cdev->si_drv1;

	int mask = 0;

	if ((events & (POLLOUT | POLLWRNORM)) && (tx_fifo_available (sc)))
		mask |= (POLLOUT | POLLWRNORM);

	if ((events & (POLLIN | POLLRDNORM)) && (rx_data_available (sc)))
		mask |= (POLLIN | POLLRDNORM);

	if (mask != 0)
		return events & mask;

	selrecord (td, &sc->selinfo);

	return 0;
}

// }}}
// {{{ dektec_intr

static void
dektec_intr (void *parameter)
{
	struct dektec_sc *sc = (struct dektec_sc *) parameter;

	uint32_t status, select_wakeup = 0;

	if (dta1xx_gen_status_reg_get_per_int (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base)) {
		dta1xx_gen_status_reg_clr_per_int (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base);

		if (sc->model == BOARD_MODEL_145 || sc->model == BOARD_MODEL_2145)
			dta1xx_gen_pulse_watchdog (sc->dta_base_bt, sc->dta_base_bh, sc->gen_base);

		if (tx_fifo_available (sc) || rx_data_available (sc))
			select_wakeup = 1;
	}

	/* FIXME use PCI905X_INTCSR_DMA0_INTACT / PCI905X_INTCSR_DMA1_INTACT */

	if (sc->legacy_plx) {
		/* DMA0 is used for writing */
		status = bus_space_read_1 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA0_COMMAND_STAT);

		if ((status & PCI905X_DMACSR_DONE) == PCI905X_DMACSR_DONE) {
			if ((sc->tx_buffer.flags & DMA_BUSY) == DMA_BUSY) {
				WRITE_BYTE (PCI905X_DMACSR_ENABLE | PCI905X_DMACSR_CLEARINT,
					    sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA0_COMMAND_STAT);
				bus_space_read_1 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA0_COMMAND_STAT);
				sc->tx_buffer.flags &= ~DMA_BUSY;
				wakeup (&sc->tx_buffer);
			}
		}

		/* DMA1 is used for reading */
		status = bus_space_read_1 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA1_COMMAND_STAT);

		if ((status & PCI905X_DMACSR_DONE) == PCI905X_DMACSR_DONE) {
			if ((sc->rx_buffer.flags & DMA_BUSY) == DMA_BUSY) {
				WRITE_BYTE (PCI905X_DMACSR_ENABLE | PCI905X_DMACSR_CLEARINT,
					    sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA1_COMMAND_STAT);
				bus_space_read_1 (sc->plx_base_bt, sc->plx_base_bh, PCI905X_DMA1_COMMAND_STAT);
				sc->rx_buffer.flags &= ~DMA_BUSY;
				wakeup (&sc->rx_buffer);
			}
		}
	} else {
		/* DMA1 is used for writing */
		status = bus_space_read_1 (sc->dta_base_bt, sc->dta_base_bh, sc->dma_base1 + REG_CMD_STAT);

		/* PCI905X_DMACSR_DONE */

		if ((status & DTA1XX_DMACSR_INTACT) != 0) {
			WRITE_BYTE (PCI905X_DMACSR_ENABLE | PCI905X_DMACSR_CLEARINT,
				    sc->dta_base_bt, sc->dta_base_bh, sc->dma_base1 + REG_CMD_STAT);
			bus_space_read_1 (sc->dta_base_bt, sc->dta_base_bh, sc->dma_base1 + REG_CMD_STAT);
			sc->tx_buffer.flags &= ~DMA_BUSY;
			wakeup (&sc->tx_buffer);
		}

		/* DMA0 is used for reading */
		status = bus_space_read_1 (sc->dta_base_bt, sc->dta_base_bh, sc->dma_base0 + REG_CMD_STAT);

		if ((status & DTA1XX_DMACSR_INTACT) != 0) {
			WRITE_BYTE (PCI905X_DMACSR_ENABLE | PCI905X_DMACSR_CLEARINT,
				    sc->dta_base_bt, sc->dta_base_bh, sc->dma_base0 + REG_CMD_STAT);
			bus_space_read_1 (sc->dta_base_bt, sc->dta_base_bh, sc->dma_base0 + REG_CMD_STAT);
			sc->rx_buffer.flags &= ~DMA_BUSY;
			wakeup (&sc->rx_buffer);
		}
	}

	dta1xx_rx_set_rx_status_reg (sc->dta_base_bt, sc->dta_base_bh, sc->rx_base,
				     DTA1XX_RXSTAT_PERINT  |
				     DTA1XX_RXSTAT_OVFINT  |
				     DTA1XX_RXSTAT_SYNCINT |
				     DTA1XX_RXSTAT_THRINT  |
				     DTA1XX_RXSTAT_RATEOVFINT);

	dta1xx_tx_set_tx_status_reg (sc->dta_base_bt, sc->dta_base_bh, sc->tx_base,
				     DTA1XX_TXSTAT_PERINT  |
				     DTA1XX_TXSTAT_UFLINT  |
				     DTA1XX_TXSTAT_SYNCINT |
				     DTA1XX_TXSTAT_THRINT  |
				     DTA1XX_TXSTAT_SHORTINT);

	if (select_wakeup && SEL_WAITING (&sc->selinfo))
		selwakeup (&sc->selinfo);
}

// }}}

static device_method_t dektec_methods[] = {
	/* Device interface */
	DEVMETHOD (device_probe,  dektec_probe),
	DEVMETHOD (device_attach, dektec_attach),
	DEVMETHOD (device_detach, dektec_detach),
#if __FreeBSD__ >= 900000
	DEVMETHOD_END
#else
	{ NULL, NULL }
#endif
};

static driver_t dektec_driver = {
	"dektec",
	dektec_methods,
	sizeof (struct dektec_sc),
};

DRIVER_MODULE (dektec, pci, dektec_driver, dektec_devclass, NULL, NULL);
