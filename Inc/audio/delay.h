#ifndef _DELAY_H_
#define _DELAY_H_
#include <stdint.h>
#define DELAY_LINE_SDRAM_LENGTH (1<<23)
#define DELAY_LINE_RAM_LENGTH (1<<16)
#define DELAY_LINE_TYPE_SDRAM 0 
#define DELAY_LINE_TYPE_RAM 1

typedef float(*feedbackProcessor)(float,void*);

typedef struct 
{
    float * delayLine; 
    uint32_t delayLinePtr;
    int32_t delayInSamples;
    float feedback; 
    uint32_t delayBufferLength;
    float mix;
    feedbackProcessor feedbackFunction;
    void * feebackData;
} DelayDataType;
 
void initDelay(DelayDataType*data,float * memoryPointer,uint32_t bufferLength);

float delayLineProcessSample(float sampleIn,DelayDataType*data);

// simply returnes the sample delayed 
float getDelayedSample(DelayDataType*data);

// adds a sample to the delay line
void addSampleToDelayline(float sampleIn,DelayDataType*data);

float * getDelayMemoryPointer(uint8_t);

void clearDelayLine();

#endif