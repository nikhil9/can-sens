

#ifndef SRC_UTIL_CUSTOM_UTIL_H_
#define SRC_UTIL_CUSTOM_UTIL_H_

#include "custom_maths.h"
#include "custom_shell.h"

#include "chprintf.h"

#define delay(x) chThdSleepMilliseconds(x)

#define debug(x, ...) chprintf((BaseSequentialStream *)&SDU1, x, ##__VA_ARGS__)

#endif /* SRC_UTIL_CUSTOM_UTIL_H_ */
