/*
 * config.c
 *
 *  Created on: Jan 6, 2021
 *      Author: lfarritor3
 */
#include "config.h"
#include "stm32f0xx_hal.h"
#include <stdbool.h>


__attribute__((__section__(".user_data"))) config_t flash_config;
config_t ram_config; // Ram config is stored in ram (as opposed to flash)

// Loads config from flash and into ram
void init_config() {
	// When code is uploaded, if you want to preserve past settings then make overwrite_config false.
	// If you want to set new settings, set them here and make overwrite_config true.
	bool overwrite_config = false;
	ram_config.note = 45;


	if(!memcmp(ram_config, flash_config, sizeof(config_t)) && overwrite_config) {
		Write_Flash();
	}
	ram_config = flash_config;
}

// Writes ram config struct to flash.
// If you want to change the config in flash, change ram config and call this function.
void Write_Flash()
{
	// Only write to flash if our config files differ
	if(memcmp(ram_config, flash_config, sizeof(config_t))) {
		return;
	}

    HAL_FLASH_Unlock();

    int startAddress = 0x08003c00;
    FLASH_EraseInitTypeDef flashPageEraseConfig;
    flashPageEraseConfig.NbPages = 1;
    flashPageEraseConfig.PageAddress = startAddress;
    flashPageEraseConfig.TypeErase = FLASH_TYPEERASE_PAGES;
    uint32_t pageErrors;
    HAL_FLASHEx_Erase(&flashPageEraseConfig, &pageErrors);
    uint32_t* data = (uint32_t*)&ram_config;
    for(int i = 0; i<sizeof(config_t); i++) {
    	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, startAddress+(4*i), data[i]);
    }
    HAL_FLASH_Lock();
}
