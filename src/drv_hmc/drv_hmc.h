
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

	int16_t magx_raw, magy_raw, magz_raw;

	bool health;

private:
	bool _write_reg(uint8_t address, uint8_t value);



};

void start_hmc(void);

#endif /* SRC_DRV_HMC_DRV_HMC_H_ */
