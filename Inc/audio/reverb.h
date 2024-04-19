#ifndef _REVERB_H_
#define _REVERB_H_
#include "stdint.h"
#include "audio/reverbUtils.h"

typedef struct 
{
    AllpassType allpasses[4];
    uint16_t delayPointer;
    float feedbackValues[4];
    float * delayPointers[4];
    float mix;
    uint8_t paramNr;

} ReverbType;


float reverbProcessSample(float sampleIn,ReverbType*reverbData);
void initReverb(ReverbType*reverbData,float,float*);
void setReverbTime(float reverbTime,ReverbType*reverbData);
const char * getReverbParameterSetName(ReverbType*reverbData);
#endif


