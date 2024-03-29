
#include "pcm3060.h"
#include "gpio.h"
#include "stm32h750/stm32h750_cfg_pins.h"

void setupPCM3060()
{
    setAsOutput(PCM3060_DEEMPHASIS);
    setPin(PCM3060_DEEMPHASIS,0);
}
