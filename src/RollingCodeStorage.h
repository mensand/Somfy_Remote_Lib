#pragma once

#include <Arduino.h>

class RollingCodeStorage {
public:
	/**
	 * Get the next rolling code from the store. This should also increase the rolling code and store it persistently.
	 *
	 * @return next rolling code
	 */
	virtual uint16_t nextCode() = 0;


	/**
	 * Get the current rolling code from the store. 
	 *
	 * @return the current rolling code
	 */
	virtual uint16_t currentCode() = 0;



	/**
	 * Get the next rolling code from the store. This should also increase the rolling code and store it persistently.
	 * @initialvalue the value to use as initial value
	 * 
	 * @return next rolling code
	 */
	virtual uint16_t initCode(uint16_t initialvalue) = 0;




};
