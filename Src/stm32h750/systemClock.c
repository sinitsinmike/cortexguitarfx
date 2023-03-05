#include "stm32h750/stm32h750xx.h"
#include "systemClock.h"

void setupClock()
{
    uint32_t cfgr;
    // switch on external oscillator
    RCC->CR |= (1 << RCC_CR_HSEBYP_Pos);
    RCC->CR |= (1 << RCC_CR_HSEON_Pos);
    while ((RCC->CR & RCC_CR_HSERDY)==0);


    // switch to external oscillator
    cfgr = RCC->CFGR;
    cfgr &= ~(3 << RCC_CFGR_SW_Pos);
    cfgr |= (1 << RCC_CFGR_SW_Pos);
    RCC->CFGR = cfgr;
    while ((RCC->CFGR & (RCC_CFGR_SWS_HSE)) == 0);

    // set voltage scale to one and enable over-drive mode to achieve 180MHz
    RCC->APB1ENR |= (1 << RCC_APB1ENR_PWREN_Pos);
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");    
    __asm__("nop");
    cfgr = PWR->CR;
    cfgr |= (3 << PWR_CR_VOS_Pos);
    while ((PWR->CR & PWR_CSR_VOSRDY)==0);

    // configure and enable pll for 180 MHz systemclock
    RCC->PLLCFGR = (4 << RCC_PLLCFGR_PLLM_Pos) | (180 << RCC_PLLCFGR_PLLN_Pos) | (0 << RCC_PLLCFGR_PLLP_Pos) | (1 << RCC_PLLCFGR_PLLSRC_Pos);
    RCC->CR |= (1 << RCC_CR_PLLON_Pos);
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");    
    __asm__("nop");
    cfgr = PWR->CR;
    cfgr |= (1 << PWR_CR_ODEN_Pos);
    PWR->CR =cfgr;
    while((PWR->CSR & (1 << PWR_CSR_ODRDY_Pos))==0);
    PWR->CR |= (1 << PWR_CR_ODSWEN_Pos);
    while((PWR->CSR & (1 << PWR_CSR_ODSWRDY_Pos))==0);

    // wait for pll to be ready
    while ((RCC->CR & RCC_CR_PLLRDY) == 0);

    // setup peripheral clock by defining the respective dividers
    // divide apb1 by 4 (resulting in 45MHz) and apb2 by 2 (resulting in 90 MHz)
    // divide HSE by 8 to get 1MHz RTC Input
    RCC->CFGR |= (5 << RCC_CFGR_PPRE1_Pos) | (4 << RCC_CFGR_PPRE2_Pos) | (8 << RCC_CFGR_RTCPRE_Pos);

    // adapt flash latency
    FLASH->ACR |= 5;

    // switch to pll
    cfgr = RCC->CFGR;
    cfgr &= ~(3 << RCC_CFGR_SW_Pos);
    cfgr |= (2 << RCC_CFGR_SW_Pos);
    RCC->CFGR = cfgr;
    while ((RCC->CFGR & (RCC_CFGR_SWS_PLL)) == 0);


}