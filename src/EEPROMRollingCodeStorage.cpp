
#include "EEPROMRollingCodeStorage.h"

EEPROMRollingCodeStorage::EEPROMRollingCodeStorage(int address) : address(address) {}

uint16_t EEPROMRollingCodeStorage::nextCode() {
	uint16_t code;
	EEPROM.get(address, code);
#ifdef DEBUG
	Serial.print("Rolling code: ");
	Serial.println(code);
#endif
	EEPROM.put(address, (uint16_t)(code + 1));
#if defined(ESP32) || defined(ESP8266)
	EEPROM.commit();
#endif
	return code;
}


	uint16_t  EEPROMRollingCodeStorage::currentCode() {
		return 0;
	}

	uint16_t  EEPROMRollingCodeStorage::initCode(uint16_t initialvalue) {
		return 0;
	}