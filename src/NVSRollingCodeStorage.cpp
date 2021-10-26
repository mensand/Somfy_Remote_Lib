#include "NVSRollingCodeStorage.h"

#ifdef ESP32

#include <esp_system.h>
#include <nvs.h>
#include <nvs_flash.h>

NVSRollingCodeStorage::NVSRollingCodeStorage(const char *name, const char *key) : name(name), key(key) {}


uint16_t NVSRollingCodeStorage::RollingCode(uint16_t initialcode, bool getnextcode) {
	uint16_t code;
	esp_err_t err;
	nvs_handle rcs_handle;

    if (initialcode <= 0) {
		initialcode = 1;
	}

    code = initialcode;

	// Initialize NVS
	err = nvs_flash_init();
	if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		// NVS partition was truncated and needs to be erased
		// Retry nvs_flash_init
		ESP_ERROR_CHECK(nvs_flash_erase());
		err = nvs_flash_init();
	}
	ESP_ERROR_CHECK(err);
	err = nvs_open(name, NVS_READWRITE, &rcs_handle);
	ESP_ERROR_CHECK(err);

	err = nvs_get_u16(rcs_handle, key, &code);
	switch (err) {
		case ESP_OK:
			break;
		case ESP_ERR_NVS_NOT_FOUND:
		    getnextcode = true;
			code = initialcode;
			break;
		default:
			Serial.print("Error reading!");
			Serial.println(esp_err_to_name(err));
	}
	if (getnextcode == true) {
		code += 1;
	    err = nvs_set_u16(rcs_handle, key, code);
	    #ifdef DEBUG
	    Serial.println((err != ESP_OK) ? "nvs_set failed!" : "nvs_set done");
        #endif
        err = nvs_commit(rcs_handle);
	    #ifdef DEBUG
		Serial.println((err != ESP_OK) ? "nvs_commit failed!" : "nvs_commit done");
	    #endif
	} 
	nvs_close(rcs_handle);
	
	return code;
}

uint16_t NVSRollingCodeStorage::nextCode() {
   return RollingCode(1, true);
}

uint16_t NVSRollingCodeStorage::currentCode() {
   return RollingCode(1, false);
}

uint16_t NVSRollingCodeStorage::initCode(uint16_t initialvalue) {
    return RollingCode(initialvalue - 1, true);
}

#endif
