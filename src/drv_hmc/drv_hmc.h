
#ifndef SRC_DRV_HMC_DRV_HMC_H_
#define SRC_DRV_HMC_DRV_HMC_H_

#include "hal.h"
#include "ch.h"


class HMC
{
public:

	void init(void);

	void update(void);

	float magx, magy, magz;

	int16_t _mag_x, _mag_y, _mag_z;

private:

	bool _health;

	bool _write_reg(uint8_t address, uint8_t value);

	void _read_raw(void);

};

void start_hmc(void);

#endif /* SRC_DRV_HMC_DRV_HMC_H_ */
