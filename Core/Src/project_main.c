/* ==========================================================
 * project_main.c - 
 * Project : Disk91 SDK
 * ----------------------------------------------------------
 * Created on: 6 sept. 2018
 *     Author: Paul Pinault aka Disk91
 * ----------------------------------------------------------
 * Copyright (C) 2018 Disk91
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
 * 
 * Add a such file in the main Src directory for executing
 * you own workload.
 *
 * ==========================================================
 */
#include <it_sdk/config.h>
#include <it_sdk/itsdk.h>
#include <it_sdk/time/time.h>
#include <it_sdk/logger/logger.h>
#include <it_sdk/sched/scheduler.h>
#include <it_sdk/statemachine/statemachine.h>
#include <it_sdk/sigfox/sigfox.h>
#include <it_sdk/eeprom/eeprom.h>

#define VERSION 0x03
struct conf {
		uint8_t			version;
		uint32_t		aesSharedkey;	// sigfox aes-ctr shared key (protected)
		uint64_t		speckSharedkey; // sigfox speck shared key (protected)
		uint8_t			nonce;			// sigfox aes-ctr current nonce
} s_conf;

void loadConfig() {

	uint8_t v;
	if ( ! eeprom_read(&s_conf, sizeof(s_conf), VERSION,&v) ) {
		log_info("Flash the initial configuration\r\n");
		s_conf.version 		  = VERSION;
		s_conf.aesSharedkey	  = ITSDK_SIGFOX_AES_SHAREDKEY;
		s_conf.speckSharedkey = ITSDK_SIGFOX_SPECKKEY;
		s_conf.nonce		  = ITSDK_SIGFOX_AES_INITALNONCE;
		eeprom_write(&s_conf, sizeof(s_conf), VERSION);
	} else {
		log_info("Loaded version %d\r\n",v);
	}
}


/**
 * Return current nonce - this function is used in sigfox library with AES encryption
 */
itsdk_sigfox_init_t itsdk_sigfox_eas_getNonce(uint8_t * nonce) {
	*nonce = s_conf.nonce;
	return SIGFOX_INIT_SUCESS;
}

/**
 * Return current sharedKey - this function is used in sigfox library with AES encryption
 */
itsdk_sigfox_init_t itsdk_sigfox_eas_getSharedKey(uint32_t * sharedKey) {
	*sharedKey = s_conf.aesSharedkey;
	return SIGFOX_INIT_SUCESS;
}

/**
 * Return current speck sharedKey - this function is used in sigfox library with Speck encryption
 */
itsdk_sigfox_init_t itsdk_sigfox_speck_getMasterKey(uint64_t * masterKey) {
	*masterKey = s_conf.speckSharedkey;
	return SIGFOX_INIT_SUCESS;
}

struct state {
	uint8_t 	led;
	uint32_t  	loops;
} s_state;

void initState() {
	s_state.led = GPIO_PIN_SET;
	s_state.loops = 0;
}

/**
 * Cycling task every 2 seconds
 */
void task() {
	s_state.led = (s_state.led==GPIO_PIN_SET)?GPIO_PIN_RESET:GPIO_PIN_SET;
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,s_state.led);
	//log_info("time is %d",(uint32_t)itsdk_time_get_ms());
}


void project_setup() {
	log_init(ITSDK_LOGGER_CONF);
	log_info("Booting \r\n");
	// reboot cause
	log_info("Reset : %d\r\n",itsdk_getResetCause());
	itsdk_cleanResetCause();

	// Init at boot time
	loadConfig();
	initState();

	// Misc init
	itsdk_sigfox_setup();

	uint8_t mk[16];
	itsdk_sigfox_eas_getMasterKey(mk);
	itsdk_encrypt_unCifferKey(mk,16);
	log_info("K : [ ");
	for ( int i = 0 ; i < 16 ; i++ ) {
		log_info("%02X ",mk[i]);
	}
	log_info("]\r\n");

	// Send a Sigfox Frame
	uint8_t f[12] = { 'a','b','c','d',4,5,6,7,8,9,10,11 };
	uint8_t r[8] = {0};
	itdsk_sigfox_txrx_t ret = itsdk_sigfox_sendFrame(f,4,2,SIGFOX_SPEED_DEFAULT,SIGFOX_POWER_DEFAULT,SIGFOX_ENCRYPT_AESCTR |SIGFOX_ENCRYPT_SPECK ,false,r);

	itdt_sched_registerSched(2000,ITSDK_SCHED_CONF_IMMEDIATE, &task);
}

void project_loop() {
	uint8_t t[4] = { '/','|','\\','-'};
	log_info("\r%c ",t[s_state.loops & 3]);
	s_state.loops++;
}

