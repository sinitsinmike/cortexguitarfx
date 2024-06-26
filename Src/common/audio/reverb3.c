#include "audio/reverb3.h"
#include "audio/reverbUtils.h"
#include "audio/audiotools.h"

#define DIFFUSOR_SIZE 2048
const int16_t diffuserTimes[4][4]={
    {53, 701, 1361, 1993},
    {97, 487, 1327, 1973},
    {29, 367, 1493, 1987},
    {73, 293, 1597, 2011}
};
void initReverb3(Reverb3Type*data)
{
    int16_t * delayMemoryPtr = getDelayMemoryPointer();
    uint32_t cnt=0;
    for(uint8_t c=0;c<4;c++)
    {
        for(uint8_t q=0;q < 4;q++)
        {
            data->diffusers[c].delayPointers[q] = delayMemoryPtr + (cnt++)*DIFFUSOR_SIZE;
            data->diffusers[c].delayTimes[q] = diffuserTimes[c][q];
        }
        data->diffusers[c].delayPointer=0;
        data->diffusers[c].diffusorSize=DIFFUSOR_SIZE;
    }
    data->delayLength = 3911;
    data->delay.delayBufferLength = 0x1000;
    data->delay.delayInSamples = data->delayLength;
    data->delay.delayLine = delayMemoryPtr + cnt*DIFFUSOR_SIZE;
    data->delay.feebackData = 0;
    data->delay.feedback = 1 << 14;
    data->delay.feedbackFunction = 0;
    data->delay.mix = ((1 << 15) - 1);
    data->delayModulationDepth = 128;
    data->delayModulationTime = 2048;
    data->modulation=0;
    data->modulatorState=0;
    data->sampleCounter =0;
    for (uint32_t c=0;c<((cnt + 0xFFF)>>1);c++)
    {
        *(((uint32_t*)delayMemoryPtr)+c)=0;
    }
}


int16_t reverb3processSample(int16_t sampleIn,Reverb3Type*data)
{
    int32_t sampleOut=0,diffusorTaps[3];
    int32_t diffuserChannels[4];
    volatile uint32_t * audioState =  getAudioStatePtr();
    diffuserChannels[0]=sampleIn;
    diffuserChannels[1]=sampleIn;
    diffuserChannels[2]=sampleIn;
    diffuserChannels[3]=sampleIn;
    hadamardDiffuserProcessArray(diffuserChannels,&data->diffusers[0],audioState);
    diffusorTaps[0] = diffuserChannels[0];
    hadamardDiffuserProcessArray(diffuserChannels,&data->diffusers[1],audioState);
    diffusorTaps[1] = diffuserChannels[3];
    hadamardDiffuserProcessArray(diffuserChannels,&data->diffusers[2],audioState);
    diffusorTaps[2] = diffuserChannels[1];
    hadamardDiffuserProcessArray(diffuserChannels,&data->diffusers[3],audioState);
    sampleOut = diffuserChannels[2];
    sampleOut = clip(
        delayLineProcessSample(clip(sampleOut,audioState),&data->delay) + 
        diffusorTaps[0] + 
        diffusorTaps[1] + 
        diffusorTaps[2]
    ,audioState);
    data->sampleCounter++;
    if((data->sampleCounter & (data->delayModulationTime -1)) == 0)
    {
        if(data->modulatorState == REV3_MODULATOR_STATE_RISING)
        {
            data->modulation++;
            if(data->modulation >= data->delayModulationDepth)
            {
                data->modulation--;
                data->modulatorState = REV3_MODULATOR_STATE_FALLING;
            }
        }
        else
        {
            data->modulation--;
            if(data->modulation >= data->delayModulationDepth)
            {
                data->modulation++;
                data->modulatorState = REV3_MODULATOR_STATE_RISING;
            }
        }
        data->delay.delayInSamples = data->delayLength + data->modulation;
        data->sampleCounter = 1;
    }

    return sampleOut;
}