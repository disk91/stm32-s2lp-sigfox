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


void loadConfig() {
	log_debug("In loadConfig \r\n");


	struct conf {
		uint8_t	v1;
		uint16_t v2;
		uint32_t v3;
	} s_conf;

	uint8_t v;
	if ( ! eeprom_read(&s_conf, sizeof(s_conf), 1,&v) ) {
		log_debug("Flashing\r\n");
		s_conf.v1 = 10;
		s_conf.v2 = 0xA5A5;
		s_conf.v3 = 0xFF5AA5FF;
		eeprom_write(&s_conf, sizeof(s_conf), 1);
	} else {
		log_debug("Load version %d\r\n",v);
		log_debug("v2 : %0X\r\n",s_conf.v2);
	}
}

uint8_t led = GPIO_PIN_SET;
void task() {
	log_debug("In task\r\n");
	led = (led==GPIO_PIN_SET)?GPIO_PIN_RESET:GPIO_PIN_SET;
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,led);

	log_info("time is %d\r\n",(uint32_t)itsdk_time_get_ms());
}


void project_setup() {
	log_init(ITSDK_LOGGER_CONF);
	log_info("Booting \r\n");
	// reboot cause
	log_info("Reset : %d\r\n",itsdk_getResetCause());
	itsdk_cleanResetCause();

	HAL_Delay(2000);

	loadConfig();

	log_info("temp : %d\r\n",(int)adc_getTemperature());


	itsdk_sigfox_setup();

	//s2lp_printConfig();

	uint8_t f[12] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	uint8_t r[8] = {0};

	int16_t rssi = 1000;
	uint16_t seqId = 0;
	itsdk_sigfox_getLastRssi(&rssi);
	log_info("Rssi %d\r\n",(int)rssi);
	itsdk_sigfox_getLastSeqId(&seqId);
	log_info("SeqId %d\r\n",(int)seqId);
	/*
	itsdk_sigfox_sendOob(
			SIGFOX_OOB_SERVICE,
			SIGFOX_SPEED_DEFAULT,
			SIGFOX_POWER_DEFAULT
	);

	itsdk_delayMs(5000);

	itsdk_sigfox_sendOob(
			SIGFOX_OOB_RC_SYNC,
			SIGFOX_SPEED_DEFAULT,
			SIGFOX_POWER_DEFAULT
	);
*/

	itdsk_sigfox_txrx_t ret = itsdk_sigfox_sendBit(true,2,SIGFOX_SPEED_DEFAULT,SIGFOX_POWER_DEFAULT,true,r);
	log_info("ret : [");
	for (int i=0 ; i < 8 ; i++) {
		log_info("%02X ",r[i]);
	}
	log_info(" ]\r\n");
	log_info("Returned code : %04X\r\n",ret);

	itsdk_sigfox_getLastRssi(&rssi);
	log_info("Rssi %d\r\n",(int)rssi);
	itsdk_sigfox_getLastSeqId(&seqId);
	log_info("SeqId %d\r\n",(int)seqId);

	uint8_t pac[8];
	uint32_t deviceId;
	itsdk_sigfox_getInitialPac(pac);
	itsdk_sigfox_getDeviceId(&deviceId);
	s2lp_sigfox_search4key(deviceId, pac);

/*
	itsdk_delayMs(5000);

	ret = itsdk_sigfox_sendFrame(f,4,2,SIGFOX_SPEED_DEFAULT,SIGFOX_POWER_DEFAULT,SIGFOX_ENCRYPT_NONE,true,r);

	log_info("ret : [");
	for (int i=0 ; i < 8 ; i++) {
		log_info("%02X ",r[i]);
	}
	log_info(" ]\r\n");
	log_info("Returned code : %04X\r\n",ret);
*/
	while(1){
		log_info(".");
		itsdk_delayMs(1000);
		wdg_refresh();
	}


	itdt_sched_registerSched(2000,ITSDK_SCHED_CONF_IMMEDIATE, &task);
}

void project_loop() {


}

