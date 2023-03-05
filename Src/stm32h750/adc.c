#include "adc.h"
#include "stm32h750/stm32h750xx.h"
#include "stm32h750/stm32h750_cfg_pins.h"
#include "system.h"

extern uint32_t task;

volatile uint16_t adcChannelValues[3];


void DMA2_Stream0_IRQHandler() //raised when all 3 adc values have been read
{
    TIM2->CR1 &= ~(1 << TIM_CR1_CEN_Pos);
    DMA2->LIFCR = (1 << DMA_LIFCR_CTCIF0_Pos);
    task |= (1 << TASK_UPDATE_POTENTIOMETER_VALUES);
}

/**
 * @brief Set the encoded sample cycles for a given adc channel for adc1
 * 
 * @param cycles 000: 3 cycles
                    001: 15 cycles
                    010: 28 cycles
                    011: 56 cycles
                    100: 84 cycles
                    101: 112 cycles
                    110: 144 cycles
                    111: 480 cycles     
 * @param channel 
 */
inline void setSampleCycles(uint8_t cycles,uint8_t channel)
{
    if (channel < 10)
    {
        ADC1->SMPR2 |= (cycles << (channel*3));
    }
    else
    {
        ADC1->SMPR1 |= ( cycles << ((channel-10)*3));
    }
}

void initAdc()
{
    GPIO_TypeDef * gpio;
    uint32_t port;

    RCC->APB2ENR |= (1 << RCC_APB2ENR_ADC1EN_Pos);
    ADC->CCR |= (3 << ADC_CCR_ADCPRE_Pos); // divide by 8 --> 90Mzh/8= 13.33 MSPS
    ADC1->SQR1 |= (2 << ADC_SQR1_L_Pos);
    ADC1->SQR3 = (POT1_CHANNEL << 0) | (POT2_CHANNEL << 5) | (POT3_CHANNEL << 10);
    setSampleCycles(7,POT1_CHANNEL);
    setSampleCycles(7,POT2_CHANNEL);
    setSampleCycles(7,POT3_CHANNEL);
    ADC1->CR1 |= (1 << ADC_CR1_SCAN_Pos);

    // enable the port to which the pots are attached
    // and set mode to analog
    port = POT1 >> 4;
    RCC->AHB1ENR |= (1 << port);
    gpio=(GPIO_TypeDef*)(GPIOA_BASE + port*0x400);
    gpio->MODER |= (3 << ((POT1 & 0xF)<<1));
    gpio->PUPDR &= ~(3 << ((POT1 & 0xF)<< 1));

    port = POT2 >> 4;
    RCC->AHB1ENR |= (1 << port);
    gpio=(GPIO_TypeDef*)(GPIOA_BASE + port*0x400);
    gpio->MODER |= (3 << ((POT2 & 0xF)<<1));
    gpio->PUPDR &= ~(3 << ((POT2 & 0xF)<< 1));

    port = POT3 >> 4;
    RCC->AHB1ENR |= (1 << port);
    gpio=(GPIO_TypeDef*)(GPIOA_BASE + port*0x400);
    gpio->MODER |= (3 << ((POT3 & 0xF)<<1));
    gpio->PUPDR &= ~(3 << ((POT3 & 0xF)<< 1));

        //setup timer 2
    RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM2EN_Pos);
    TIM2->PSC = 65217; // divide 90MHz by 65217 (Prescaler) and 46 (ARR, CCR2) to achieve 30Hz ADC Sampling Frequency
                       // among all three channels thus update the potentiometers at 10Hz
    TIM2->ARR=46;
    TIM2->CCR2=46;
    //TIM2->PSC = 65535;
    //TIM2->ARR=137;
    //TIM2->CCR2=137;
}

void initRoundRobinReading()
{
    TIM2->CNT=0;
    TIM2->CCMR1 = (3 << TIM_CCMR1_OC2M_Pos);
    TIM2->CCER |= (1 << TIM_CCER_CC2E_Pos);
    TIM2->CR1 |= (1 << TIM_CR1_CEN_Pos);

    // setup dma 2 channel 0 stream 0
    DMA2_Stream0->PAR=(uint32_t)&(ADC1->DR);
    DMA2_Stream0->M0AR=(uint32_t)adcChannelValues;
    DMA2_Stream0->M1AR=(uint32_t)adcChannelValues;
    DMA2_Stream0->CR = (1 << DMA_SxCR_MSIZE_Pos) | (1 << DMA_SxCR_PSIZE_Pos) | (1 << DMA_SxCR_MINC_Pos) | (1 << DMA_SxCR_TCIE_Pos) | (1 << DMA_SxCR_CIRC_Pos);
    DMA2_Stream0->NDTR=3;
    DMA2_Stream0->CR |=(1 << DMA_SxCR_EN_Pos);
    NVIC_EnableIRQ(DMA2_Stream0_IRQn);

    // use Timer 2 CC2 as a Trigger source
    ADC1->CR2 |= (1 << ADC_CR2_ADON_Pos) | (1 << ADC_CR2_EXTEN_Pos) | (3 << ADC_CR2_EXTSEL_Pos) | (0 << ADC_CR2_CONT_Pos) | (0 << ADC_CR2_EOCS_Pos)
                 | (1 << ADC_CR2_DMA_Pos) | (1 << ADC_CR2_DDS_Pos);
}

void restartAdc()
{
    //DMA2_Stream0->M0AR=(uint32_t)adcChannelValues;
    //DMA2_Stream0->NDTR = 3;
    //DMA2_Stream0->CR |= (1 << DMA_SxCR_EN_Pos);
    //ADC1->CR2 &= ~(1 << ADC_CR2_DMA_Pos);
    //ADC1->CR2 |= (1 << ADC_CR2_DMA_Pos);
    TIM2->SR &= ~(1 << TIM_SR_CC2IF_Pos);
    //TIM2->CNT=0;
    TIM2->CR1 |= (1 << TIM_CR1_CEN_Pos);
}

uint16_t getChannel0Value()
{
    return adcChannelValues[0];
}

uint16_t getChannel1Value()
{
    return adcChannelValues[1];
}

uint16_t getChannel2Value()
{
    return adcChannelValues[2];
}