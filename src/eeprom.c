/*
 * eeprom.c
 *
 *  Created on: Mar 6, 2019
 *      Author: 500022
 */
#include "eeprom.h"
#include "test.h"
#include "fdl.h"
#include "fdl_descriptor.h"

#include "eel.h"
#include "eel_descriptor.h"
#include "eel_user_types.h"

fdl_status_t dataFlashStatus;
eel_status_t eepromStatus;
eel_request_t eepromRequest;

void counterRead(void) {
	dataFlashStatus = FDL_Init(&fdl_descriptor_str);
	FDL_Open();

	eepromStatus = EEL_Init();
	EEL_Open();

	eepromRequest.address_pu08 = 0;
	eepromRequest.identifier_u08 = 0;
	eepromRequest.command_enu = EEL_CMD_STARTUP;

	/* command initiation - STARTUP */
	do {
		EEL_Execute(&eepromRequest);
		EEL_Handler(); /* proceed background process */
	} while (eepromRequest.status_enu == EEL_ERR_REJECTED);

	/* command execution */
	// a call to the Handler will return "idle" status
	do {
		EEL_Handler();
	} while (eepromRequest.status_enu == EEL_BUSY);

	///////////////////////////////////////////////////////

	// read to failed
	eepromRequest.address_pu08 = (eel_u08 *) &tested;
	eepromRequest.identifier_u08 = 1;
	eepromRequest.command_enu = EEL_CMD_READ;

	/* command initiation - WRITE */
	do {
		EEL_Execute(&eepromRequest);
		EEL_Handler(); /* proceed background process */
	} while (eepromRequest.status_enu == EEL_ERR_REJECTED);

	/* command execution */
	// a call to the Handler will return "idle" status
	do {
		EEL_Handler();
	} while (eepromRequest.status_enu == EEL_BUSY);

	eepromRequest.address_pu08 = (eel_u08 *) &passed;
	eepromRequest.identifier_u08 = 2;
	eepromRequest.command_enu = EEL_CMD_READ;

	/* command initiation - WRITE */
	do {
		EEL_Execute(&eepromRequest);
		EEL_Handler(); /* proceed background process */
	} while (eepromRequest.status_enu == EEL_ERR_REJECTED);

	/* command execution */
	// a call to the Handler will return "idle" status
	do {
		EEL_Handler();
	} while (eepromRequest.status_enu == EEL_BUSY);

	eepromRequest.address_pu08 = (eel_u08 *) &failed;
	eepromRequest.identifier_u08 = 3;
	eepromRequest.command_enu = EEL_CMD_READ;

	/* command initiation - WRITE */
	do {
		EEL_Execute(&eepromRequest);
		EEL_Handler(); /* proceed background process */
	} while (eepromRequest.status_enu == EEL_ERR_REJECTED);

	/* command execution */
	// a call to the Handler will return "idle" status
	do {
		EEL_Handler();
	} while (eepromRequest.status_enu == EEL_BUSY);

	///////////////////////////////////////////////////////
	eepromRequest.address_pu08 = 0;
	eepromRequest.identifier_u08 = 0;
	eepromRequest.command_enu = EEL_CMD_SHUTDOWN;

	/* command initiation - SHUTDOWN */
	do {
		EEL_Execute(&eepromRequest);
		EEL_Handler(); /* proceed background process */
	} while (eepromRequest.status_enu == EEL_ERR_REJECTED);

	/* command execution */
	// a call to the Handler will return "idle" status
	do {
		EEL_Handler();
	} while (eepromRequest.status_enu == EEL_BUSY);
	//////////////////////////////////////////////////////

	EEL_Close();
	FDL_Close();

}

void counterWrite(void) {
	dataFlashStatus = FDL_Init(&fdl_descriptor_str);
	FDL_Open();

	eepromStatus = EEL_Init();
	EEL_Open();

	///////////////////////////////////////////////////////
	eepromRequest.address_pu08 = 0;
	eepromRequest.identifier_u08 = 0;
	eepromRequest.command_enu = EEL_CMD_FORMAT;

	/* command initiation - FORMAT */
	do {
		EEL_Execute(&eepromRequest);
		EEL_Handler(); /* proceed background process */
	} while (eepromRequest.status_enu == EEL_ERR_REJECTED);

	/* command execution */
	// a call to the Handler will return "idle" status
	do {
		EEL_Handler();
	} while (eepromRequest.status_enu == EEL_BUSY);

	///////////////////////////////////////////////////////
	eepromRequest.address_pu08 = 0;
	eepromRequest.identifier_u08 = 0;
	eepromRequest.command_enu = EEL_CMD_STARTUP;

	/* command initiation - STARTUP */
	do {
		EEL_Execute(&eepromRequest);
		EEL_Handler(); /* proceed background process */
	} while (eepromRequest.status_enu == EEL_ERR_REJECTED);

	/* command execution */
	// a call to the Handler will return "idle" status
	do {
		EEL_Handler();
	} while (eepromRequest.status_enu == EEL_BUSY);

	///////////////////////////////////////////////////////

	eepromRequest.address_pu08 = (eel_u08 *) &tested;
	eepromRequest.identifier_u08 = 1;
	eepromRequest.command_enu = EEL_CMD_WRITE;

	/* command initiation - WRITE */
	do {
		EEL_Execute(&eepromRequest);
		EEL_Handler(); /* proceed background process */
	} while (eepromRequest.status_enu == EEL_ERR_REJECTED);

	/* command execution */
	// a call to the Handler will return "idle" status
	do {
		EEL_Handler();
	} while (eepromRequest.status_enu == EEL_BUSY);

	eepromRequest.address_pu08 = (eel_u08 *) &passed;
	eepromRequest.identifier_u08 = 2;
	eepromRequest.command_enu = EEL_CMD_WRITE;

	/* command initiation - WRITE */
	do {
		EEL_Execute(&eepromRequest);
		EEL_Handler(); /* proceed background process */
	} while (eepromRequest.status_enu == EEL_ERR_REJECTED);

	/* command execution */
	// a call to the Handler will return "idle" status
	do {
		EEL_Handler();
	} while (eepromRequest.status_enu == EEL_BUSY);

	eepromRequest.address_pu08 = (eel_u08 *) &failed;
	eepromRequest.identifier_u08 = 3;
	eepromRequest.command_enu = EEL_CMD_WRITE;

	/* command initiation - WRITE */
	do {
		EEL_Execute(&eepromRequest);
		EEL_Handler(); /* proceed background process */
	} while (eepromRequest.status_enu == EEL_ERR_REJECTED);

	/* command execution */
	// a call to the Handler will return "idle" status
	do {
		EEL_Handler();
	} while (eepromRequest.status_enu == EEL_BUSY);

	///////////////////////////////////////////////////////
	eepromRequest.address_pu08 = 0;
	eepromRequest.identifier_u08 = 0;
	eepromRequest.command_enu = EEL_CMD_SHUTDOWN;

	/* command initiation - SHUTDOWN */
	do {
		EEL_Execute(&eepromRequest);
		EEL_Handler(); /* proceed background process */
	} while (eepromRequest.status_enu == EEL_ERR_REJECTED);

	/* command execution */
	// a call to the Handler will return "idle" status
	do {
		EEL_Handler();
	} while (eepromRequest.status_enu == EEL_BUSY);
	//////////////////////////////////////////////////////

	EEL_Close();
	FDL_Close();
}

