#include "audio/delay.h"

__attribute__ ((section (".sdram_bss")))
float delayLineSdram[DELAY_LINE_LENGTH];

DelayDataType singletonDelay;

__attribute__((section (".qspi_code")))
DelayDataType * getDelayData()
{
    return &singletonDelay;
}

#ifndef FLOAT_AUDIO

#else

void initDelay(DelayDataType*data)
{
    data->delayLine = (float*)delayLineSdram;
    emptyDelayLine(data->delayLine);
    data->delayInSamples=1;
    data->delayLinePtr=0;
    data->feedback=0.0f;
    data->mix=0.0f;
    data->feedbackFunction=0;
    data->feebackData=0;
}

__attribute__((section (".qspi_code")))
float delayLineProcessSample(float sampleIn,DelayDataType*data)
{
    uint32_t delayIdx;
    float sampleOut;
    float sampleFedBack;
    delayIdx = (data->delayLinePtr - data->delayInSamples) & (DELAY_LINE_LENGTH -1);

    sampleOut = *(data->delayLine +delayIdx)*data->mix + sampleIn*(1.0f - data->mix);
    sampleFedBack = sampleOut;
    if (data->feedbackFunction != 0)
    {
        sampleFedBack = data->feedbackFunction(sampleFedBack,data->feebackData);
    }
    if (sampleFedBack > 1.0f)
    {
        sampleFedBack = 1.0f;
    }
    else if (sampleFedBack < -1.0f)
    {
        sampleFedBack = -1.0f;
    }
    *(data->delayLine + data->delayLinePtr) = sampleFedBack;
    data->delayLinePtr++;
    data->delayLinePtr &= (DELAY_LINE_LENGTH -1UL);
    return sampleOut;
}

__attribute__((section (".qspi_code")))
float * getDelayLine()
{
    return (float*)singletonDelay.delayLine;
}
__attribute__((section (".qspi_code")))
void emptyDelayLine(float*delayLine)
{
    for (uint32_t c=0;c<DELAY_LINE_LENGTH;c++)
    {
        delayLine[c]=0.0f;
    }
}

#endif