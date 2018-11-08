/* ==========================================================
 * configSigfox.h - SDK Configuration file for Sigfox communication
 * Project : IngeniousThings SDK
 * ----------------------------------------------------------
 * Created on: 4 nov. 2018
 *     Author: Paul Pinault aka Disk91
 * ----------------------------------------------------------
 * Copyright (C) 2018  IngeniousThings and Disk91
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU LESSER General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------
 * S2LP:
 *    In cube MX declare the CSn and SDN pin as output.
 *      CSn is pullup set to High initially
 *      SDN is set to low initially (no shutdown)
 *    Declare SPI. default configuration normally match.
 *
 * ==========================================================
 */

#ifndef IT_SDK_CONFIG_SIGFOX_H_
#define IT_SDK_CONFIG_SIGFOX_H_

#include <it_sdk/config_defines.h>
#if ITSDK_SIGFOX_LIB == __SIGFOX_S2LP
	#include "spi.h"
#endif

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// | SDK SETTING                   | USER SELECTED VALUE                  | SETTING DESCRIPTION                   |
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +---------COMMON SETTINGS-------|--------------------------------------|---------------------------------------|


// +---------------S2LP------------|--------------------------------------|---------------------------------------|
#if ITSDK_SIGFOX_LIB == __SIGFOX_S2LP
#define ITSDK_S2LP_SPI				hspi1								   // SPI To BE USED
																		   // SPI Configured by CubeMX
																		   //  Master, 8b, Polarity Low,
																		   //  first bit msb, CRC disable...

#define ITSDK_S2LP_CS_BANK			 __BANK_A							   // S2LP Chip Select PIN LAYOUT (Activ Low)
#define ITSDK_S2LP_CS_PIN			 __LP_GPIO_1
#define ITSDK_S2LP_SDN_BANK			 __BANK_A							   // S2LP Chip Shutdown PIN LAYOUT (Activ High)
#define ITSDK_S2LP_SDN_PIN			 __LP_GPIO_8
#define ITSDK_S2LP_GPIO0_BANK		 __BANK_A							   // S2LP Interrupt GPIO0 LAYOUT
#define ITSDK_S2LP_GPIO0_PIN		 __LP_GPIO_0						   //   Default PA0 <=> GPIO0 on S2LP
#define ITSDK_S2LP_GPIO1_BANK		 __BANK_A							   // S2LP Interrupt GPIO1 LAYOUT
#define ITSDK_S2LP_GPIO1_PIN		 __LP_GPIO_4						   //   Default PA4 <=> GPIO1 on S2LP
																		   //   Configured as Falling
#define ITSDK_S2LP_GPIO2_BANK		 __BANK_B							   // S2LP Interrupt GPIO2 LAYOUT
#define ITSDK_S2LP_GPIO2_PIN		 __LP_GPIO_0						   //   Default PB0 <=> GPIO2 on S2LP
																		   //   Configured as Falling
#define ITSDK_S2LP_GPIO3_BANK		 __BANK_C							   // S2LP Interrupt GPIO3 LAYOUT
#define ITSDK_S2LP_GPIO3_PIN		 __LP_GPIO_0						   //   Default PC0 <=> GPIO3 on S2LP
																		   //   Configured as Falling

#define ITSDK_S2LP_CNF_TCX0			__S2LP_W_O_TCXO					   	   // Absence of a TCXO
#define ITSDK_S2LP_CNF_RANGE		0
#define ITSDK_S2LP_CNF_BAND			3
#define ITSDK_S2LP_CNF_FREQ			50000000
#define ITSDK_S2LP_CNF_OFFSET		0


#endif //__SIGFOX_S2LP
// +------------SIGFOX-------------|--------------------------------------|---------------------------------------|
#if ITSDK_WITH_SIGFOX_LIB == 1
#define ITSDK_SIGFOX_MEM_SIZE		500										// Static memory allocated to sigfox
#define ITSDK_SIGFOX_NVM_SOURCE		__SFX_NVM_M95640						// where the non volatile information are stored
#define ITSDK_SIGFOX_NVM_BASEADDR	0x600									// Base address in the NVM
#define ITSDK_SIGFOX_ENCRYPTED		0										// Is the sigfox payload encrypted ?
#define ITSDK_SIGFOX_LOWPOWER		0										// When 1 the device can be switch to low power by the sigfox lib

#endif
// +-------------OTHERS------------|--------------------------------------|---------------------------------------|

#endif /* IT_SDK_CONFIG_SIGFOX_H_ */

