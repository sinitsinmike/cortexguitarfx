#include "stm32h750/stm32h750xx.h"
#include "stm32h750/stm32h750_cfg_pins.h"
#include "stm32h750/helpers.h"
#include "systick.h"
#include "i2c.h"
#include "cs4270_audio_codec.h"




static uint8_t cs4270Write(uint16_t data)
{
    uint8_t res=0;
    if (getTargetAddress()!=CS4270_I2C_ADDRESS)
    {
        setTargetAddress(CS4270_I2C_ADDRESS);
    }
    res += masterTransmit((uint8_t)((data >> 8)&0xFF),0);
    res += masterTransmit((uint8_t)(data&0xFF),1);
    return res;
}

static uint8_t cs4270Read(uint8_t reg)
{
    if (getTargetAddress()!=CS4270_I2C_ADDRESS)
    {
        setTargetAddress(CS4270_I2C_ADDRESS);
    }
    masterTransmit(reg,1);
    return masterReceive(1);
}

void init_cs4270_audio_codec()
{
    // reset
    uint32_t port;
    uint32_t regbfr;
    GPIO_TypeDef * gpio;
    uint16_t regdata;

    port = CS4270_RESET >> 4;
    RCC->AHB4ENR |= (1 << port);
    gpio=(GPIO_TypeDef*)(GPIOA_BASE + port*0x400);
    regbfr = gpio->MODER;
    regbfr &= ~(3 << ((CS4270_RESET & 0xF)<<1));
    regbfr |= (1 << ((CS4270_RESET & 0xF)<<1));
    gpio->MODER=regbfr;
    gpio->OTYPER &= ~(1 << (CS4270_RESET & 0xF));
    regbfr = gpio->OSPEEDR;
    //regbfr &=~(3 << ((CS4270_RESET & 0xF)<<1));
    regbfr |= (3 << ((CS4270_RESET & 0xF)<<1));
    gpio->OSPEEDR = regbfr;
    gpio->PUPDR &= ~(3 << ((CS4270_RESET & 0xF)<<1));


    // reset high
    gpio->BSRR = (1 << (CS4270_RESET & 0xF));
    waitSysticks(1);
    //reset low
    gpio->BSRR = (1 << ((CS4270_RESET & 0xF)+16));
    waitSysticks(1);
    // reset high
    gpio->BSRR = (1 << (CS4270_RESET & 0xF));
    for(uint8_t c=0;c<64;c++) // wait at least 500ns
    {
        __asm__("nop");
    }
    regdata = (CS4270_R2 << 8) | (1 << CS4270_R2_PDN_Pos); // power down
    cs4270Write(regdata);

    regdata = (CS4270_R3 << 8); // set single speed master, no pop protection
    cs4270Write(regdata);

    regdata = (CS4270_R4 << 8) | (1 << CS4270_R4_DAC_DIF0_Pos) | (1 << CS4270_R4_ADC_DIF0_Pos); // set i2s for dac and adc
    cs4270Write(regdata);

    regdata = (CS4270_R2 << 8); // power up again
    cs4270Write(regdata);

}

/*
    channel is either CS4270_CHANNEL_A or CS4270_CHANNEL_B,
    val: 1 means unmuted (on) and 0 means muted (off)
*/
void cs4270SetInputState(uint8_t channel,uint8_t val)
{
    uint16_t regdata;
    uint8_t regContent;
    if (getTargetAddress()!=CS4270_I2C_ADDRESS)
    {
        setTargetAddress(CS4270_I2C_ADDRESS);
    }
    regdata = (CS4270_R6 << 8);
    regContent = cs4270Read(CS4270_R6);
    if (val!=0)
    {
        if (channel == CS4270_CHANNEL_A || channel == CS4270_CHANNEL_BOTH)
        {
            regContent &= ~(1 << 3);
        }
        if (channel == CS4270_CHANNEL_B || channel == CS4270_CHANNEL_BOTH)
        {
            regContent &= ~(1 << 4);
        }
    }
    else
    {
        if (channel == CS4270_CHANNEL_A || channel == CS4270_CHANNEL_BOTH)
        {
            regContent |= (1 << 3);
        }
        if (channel == CS4270_CHANNEL_B || channel == CS4270_CHANNEL_BOTH)
        {
            regContent |= (1 << 4);
        }
    }
    regdata |= regContent;
    cs4270Write(regdata);
}

/*
    channel is either CS4270_CHANNEL_A or CS4270_CHANNEL_B,
    byte 0: Channel A, byte 1: Channel B
*/
uint8_t cs4270GetInputState()
{
    uint8_t regContent;
    if (getTargetAddress()!=CS4270_I2C_ADDRESS)
    {
        setTargetAddress(CS4270_I2C_ADDRESS);
    }
    regContent = cs4270Read(CS4270_R6);
    regContent >>= 3;
    regContent &= (0x3);
    regContent ^= (0x3);
    return regContent;
}

void cs4270SetOutputVolume(uint8_t channel,uint8_t volume)
{
    uint16_t regdata;
    if (getTargetAddress()!=CS4270_I2C_ADDRESS)
    {
        setTargetAddress(CS4270_I2C_ADDRESS);
    }
    if (channel == CS4270_CHANNEL_A) 
    {
        regdata = (CS4270_R7 << 8);
    }
    else if (channel == CS4270_CHANNEL_B)
    {
        regdata = (CS4270_R8 << 8);
    }
    else
    {
        regdata = ((0x80 | CS4270_R7) << 8);
    }
    regdata |= (0xFF - volume);
    if (channel != CS4270_CHANNEL_BOTH)
    {
        cs4270Write(regdata);
    }
    else
    {
        masterTransmit((0x80 | CS4270_R7),0);
        masterTransmit((0xFF - volume),0);
        masterTransmit((0xFF - volume),1);
    }
}

/*
returns the output volume for both channels
A is in the MSB, B in the LSB 
*/
uint16_t cs4270GetOutputVolume()
{
    uint16_t outval=0;
    uint8_t channelVal;
    if (getTargetAddress()!=CS4270_I2C_ADDRESS)
    {
        setTargetAddress(CS4270_I2C_ADDRESS);
    }
    masterTransmit((0x80 | CS4270_R7),1);
    channelVal = 0xFF - masterReceive(0);
    outval |= (channelVal << 8);
    channelVal = 0xFF - masterReceive(0);
    outval |= channelVal;
    return outval;
}