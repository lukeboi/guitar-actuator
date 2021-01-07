#ifndef SRC_LUKES_CODE_CONFIG_H_
#define SRC_LUKES_CODE_CONFIG_H_

#include <stdint.h>

typedef struct config {
	uint32_t note;
	uint32_t strummed_on_position;
	uint32_t strummed_off_position;
} config_t;

extern config_t ram_config;

void init_config();
void Write_Flash();

#endif /* SRC_LUKES_CODE_CONFIG_H_ */
