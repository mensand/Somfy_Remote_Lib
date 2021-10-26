#pragma once

#ifdef ESP32

#include "RollingCodeStorage.h"

/**
 * Stores the rolling codes in the NVS of an ESP32, the codes require two bytes.
 */
class NVSRollingCodeStorage : public RollingCodeStorage {
private:
	const char *name;
	const char *key;

public:
    
	NVSRollingCodeStorage(const char *name, const char *key);

	uint16_t nextCode() override;

	uint16_t currentCode() override;

	uint16_t initCode(uint16_t initialvalue) override;

};

#endif
