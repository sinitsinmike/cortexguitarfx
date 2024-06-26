#include "stdint.h"
#include "audio/compressor.h"
#include "romfunc.h"
#include "fastExpLog.h"
#include "audio/firstOrderIirFilter.h"

int16_t applyGain(int16_t sample,int16_t avgVolume,CompressorDataType*comp)
{
    int32_t gainFactor;
    int16_t sampleOut;
    int32_t sampleInterm=0;
    int16_t logAvg;

    logAvg = fastlog(avgVolume);
    if (logAvg < comp->gainFunction.threshhold) // below threshhold, amplification 1
    {
        sampleInterm=sample;
    }
    else if (comp->gainFunction.gainReduction > 4)
    {
        gainFactor = fastexp(comp->gainFunction.threshhold)*32767;
        if (avgVolume != 0)
        {
            gainFactor /=avgVolume;
            sampleInterm = (sample*gainFactor) >> 15;  // sampleInterm/avgVolume;
        }
    }
    else
    {
        gainFactor =  fastexp(comp->gainFunction.threshhold + ((logAvg-comp->gainFunction.threshhold) >> (comp->gainFunction.gainReduction)))*32767;
        if (avgVolume != 0)
        {
            gainFactor /=avgVolume;
            sampleInterm = (sample*gainFactor) >> 15;
        }
    }
    sampleOut=(int16_t)sampleInterm;
    return sampleOut;
}

int16_t getMaxGain(CompressorDataType*comp)
{
    if (comp->gainFunction.gainReduction > 4)
    {
        return fastexp(comp->gainFunction.threshhold);
    }
    else
    {
        return fastexp(comp->gainFunction.threshhold + ((0x7FFF-comp->gainFunction.threshhold) >> (comp->gainFunction.gainReduction)));
    }
}

int16_t compressorProcessSample(int16_t sampleIn,CompressorDataType*data)
{
    int16_t absSample;
    int16_t sampleOut;
    int32_t intermAvg;

    sampleOut = applyGain(sampleIn,data->currentAvg,data);
    
    if(sampleOut < 0)
    {
        absSample = -sampleOut;
    }
    else
    {
        absSample = sampleOut;
    }
    /*if(sampleIn < 0)
    {
        absSample = -sampleIn;
    }
    else
    {
        absSample = sampleIn;
    }*/
    intermAvg = firstOrderIirDualCoeffLPProcessSample(absSample,&data->avgLowpass);
    data->currentAvg = (int16_t)intermAvg; 
    return sampleOut;
}

void compressorReset(CompressorDataType*data)
{
    firstOrderIirDualCoeffLPReset(&data->avgLowpass);
    data->currentAvg = 0;
}