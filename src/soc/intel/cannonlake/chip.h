/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2008 coresystems GmbH
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2017 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _SOC_CHIP_H_
#define _SOC_CHIP_H_

#include <intelblocks/gspi.h>
#include <stdint.h>
#include <soc/usb.h>
#include <soc/vr_config.h>

struct soc_intel_cannonlake_config {
	/* GSPI */
	struct gspi_cfg gspi[CONFIG_SOC_INTEL_COMMON_BLOCK_GSPI_MAX];

	/* Interrupt Routing configuration.
	 * If bit7 is 1, the interrupt is disabled. */
	uint8_t pirqa_routing;
	uint8_t pirqb_routing;
	uint8_t pirqc_routing;
	uint8_t pirqd_routing;
	uint8_t pirqe_routing;
	uint8_t pirqf_routing;
	uint8_t pirqg_routing;
	uint8_t pirqh_routing;

	/* GPE configuration */
	uint32_t gpe0_en_1; /* GPE0_EN_31_0 */
	uint32_t gpe0_en_2; /* GPE0_EN_63_32 */
	uint32_t gpe0_en_3; /* GPE0_EN_95_64 */
	uint32_t gpe0_en_4; /* GPE0_EN_127_96 / GPE_STD */

	/* Gpio group routed to each dword of the GPE0 block. Values are
	 * of the form GPP_[A:G] or GPD. */
	uint8_t gpe0_dw0; /* GPE0_31_0 STS/EN */
	uint8_t gpe0_dw1; /* GPE0_63_32 STS/EN */
	uint8_t gpe0_dw2; /* GPE0_95_64 STS/EN */

	/* Generic IO decode ranges */
	uint32_t gen1_dec;
	uint32_t gen2_dec;
	uint32_t gen3_dec;
	uint32_t gen4_dec;

	/* Enable S0iX support */
	int s0ix_enable;
	/* Enable DPTF support */
	int dptf_enable;

	/* Deep SX enable for both AC and DC */
	int deep_s3_enable;
	int deep_s5_enable;

	/* Deep Sx Configuration
	 *  DSX_EN_WAKE_PIN       - Enable WAKE# pin
	 *  DSX_EN_LAN_WAKE_PIN   - Enable LAN_WAKE# pin
	 *  DSX_EN_AC_PRESENT_PIN - Enable AC_PRESENT pin */
	uint32_t deep_sx_config;

	/* TCC activation offset */
	uint32_t tcc_offset;

	uint64_t PlatformMemorySize;
	uint8_t SmramMask;
	uint8_t MrcFastBoot;
	uint32_t TsegSize;
	uint16_t MmioSize;

	/* DDR Frequency Limit. Maximum Memory Frequency Selections in Mhz.
	 * Options : 1067, 1333, 1600, 1867, 2133, 2400, 2667, 2933, 0(Auto) */
	uint16_t DdrFreqLimit;

	/* SAGV Low Frequency Selections in Mhz.
	 * Options : 1067, 1333, 1600, 1867, 2133, 2400, 2667, 2933, 0(Auto) */
	uint16_t FreqSaGvLow;

	/* SAGV Mid Frequency Selections in Mhz.
	 * Options : 1067, 1333, 1600, 1867, 2133, 2400, 2667, 2933, 0(Auto) */
	uint16_t FreqSaGvMid;

	/* System Agent dynamic frequency support. Only effects ULX/ULT CPUs.
	 * When enabled memory will be training at two different frequencies.
	 * 0:Disabled, 1:FixedLow, 2:FixedMid, 3:FixedHigh, 4:Enabled */
	uint8_t SaGv;

	/* Rank Margin Tool. 1:Enable, 0:Disable */
	uint8_t RMT;

	/* LAN controller. 1:Enable, 0:Disable */
	uint8_t PchLanEnable;

	/* USB related */
	struct usb2_port_config usb2_ports[16];
	struct usb3_port_config usb3_ports[10];
	uint8_t XdciEnable;
	uint8_t SsicPortEnable;

	/* SATA related */
	uint8_t SataEnable;
	uint8_t SataMode;
	uint8_t SataSalpSupport;
	uint8_t SataPortsEnable[8];
	uint8_t SataPortsDevSlp[8];

	/* Audio related */
	uint8_t PchHdaEnable;
	uint8_t PchHdaDspEnable;

	/* Enable/Disable HD Audio Link. Muxed with SSP0/SSP1/SNDW1 */
	uint8_t PchHdaAudioLinkHda;

	/* Pcie Root Ports */
	uint8_t PcieRpEnable[CONFIG_MAX_ROOT_PORTS];
	uint8_t PcieRpClkReqSupport[CONFIG_MAX_ROOT_PORTS];
	uint8_t PcieRpClkReqNumber[CONFIG_MAX_ROOT_PORTS];

	/* SMBus */
	uint8_t SmbusEnable;

	/* eMMC and SD */
	uint8_t ScsEmmcEnabled;
	uint8_t ScsEmmcHs400Enabled;
	uint8_t PchScsEmmcHs400TuningRequired;
	uint8_t ScsSdCardEnabled;
	uint8_t ScsUfsEnabled;

	/* Integrated Sensor */
	uint8_t PchIshEnable;

	/* Heci related */
	uint8_t Heci3Enabled;

	/* Gfx related */
	uint8_t IgdDvmt50PreAlloc;
	uint8_t InternalGfx;
	uint8_t SkipExtGfxScan;

	uint32_t GraphicsConfigPtr;
	uint8_t Device4Enable;

	/* GPIO IRQ Select. The valid value is 14 or 15 */
	uint8_t GpioIrqRoute;
	/* SCI IRQ Select. The valid value is 9, 10, 11, 20, 21, 22, 23 */
	uint8_t SciIrqSelect;
	/* TCO IRQ Select. The valid value is 9, 10, 11, 20, 21, 22, 23 */
	uint8_t TcoIrqSelect;
	uint8_t TcoIrqEnable;

	enum {
		CHIPSET_LOCKDOWN_FSP = 0, /* FSP handles locking per UPDs */
		CHIPSET_LOCKDOWN_COREBOOT, /* coreboot handles locking */
	} chipset_lockdown;

	uint8_t SkipMpInit;
	/* VrConfig Settings for 5 domains
	 * 0 = System Agent, 1 = IA Core, 2 = Ring,
	 * 3 = GT unsliced,  4 = GT sliced */
	struct vr_config domain_vr_config[NUM_VR_DOMAINS];
	/* HeciEnabled decides the state of Heci1 at end of boot
	 * Setting to 0 (default) disables Heci1 and hides the device from OS */
	uint8_t HeciEnabled;
	/* PL2 Override value in Watts */
	uint32_t tdp_pl2_override;
	/* Intel Speed Shift Technology */
	uint8_t speed_shift_enable;
	/* Enable VR specific mailbox command
	 * 00b - no VR specific cmd sent
	 * 01b - VR mailbox cmd specifically for the MPS IMPV8 VR will be sent
	 * 10b - VR specific cmd sent for PS4 exit issue
	 * 11b - Reserved */
	uint8_t SendVrMbxCmd;

	/* Enable/Disable EIST. 1b:Enabled, 0b:Disabled */
	uint8_t eist_enable;
};

typedef struct soc_intel_cannonlake_config config_t;

#endif
