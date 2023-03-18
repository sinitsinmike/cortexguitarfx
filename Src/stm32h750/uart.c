#include "stdint.h"
#include "uart.h"
#include "stm32h750/stm32h750xx.h"
#include "bufferedInputHandler.h"
#include "system.h"
#include "qspi.h"

#define APB2_SPEED 120000000


#define QSPI_PROGRAMMER_IDLE 0
#define QSPI_PROGRAMMER_IDENTIFIER_RECEIVED 1
#define QSPI_PROGRAMMER_LENGTH_RECEIVED 2


extern uint32_t task;
extern uint8_t context; // used by printf to decide where a certain information should be output

//CommBufferType usbCommBuffer __attribute__((aligned (256)));
//CommBufferType btCommBuffer;


uint8_t uartInputBfr[256];
uint32_t uartInputBfrCntr=0;
uint32_t uartSendBfrCntr=0;
const uint8_t qspiProgrammerIdentifier[] = {0x23, 0xed, 0x12, 0xf3, 0x11, 0x6a, 0xc,0xa2};
const uint8_t ack[] = {'A', 'C', 'K'};
// 0: idle, 1: identifier received, 2: length received, 3: data package received
volatile uint32_t qspiFlashingState=0;
volatile uint32_t qspiPageCntr=0;
union datalength
{
    uint32_t binFileLength;
    uint8_t data[4];
};
union datalength dl;

void sendAck()
{
    while(uartSendBfrCntr < 3)
    {
        while((UART1->ISR & USART_ISR_TXE_TXFNF)==0);
        UART1->TDR = ack[uartSendBfrCntr++];
    }
    uartSendBfrCntr=0;

}

// irq for uart reception, "USB"-port
void USART1_IRQHandler()
{
    if ((USART1->ISR & (1 <<USART_ISR_RXNE_RXFNE_Pos))== (1 <<USART_ISR_RXNE_RXFNE_Pos))
    {
	    //usbCommBuffer.inputBuffer[usbCommBuffer.inputBufferCnt++]=USART1->RDR& 0xFF;
		//usbCommBuffer.inputBufferCnt &= (INPUT_BUFFER_SIZE-1);
		//task |= (1 << TASK_USB_CONSOLE_RX);
        switch(qspiFlashingState)
        {
            case QSPI_PROGRAMMER_IDLE:
                uartInputBfr[uartInputBfrCntr] = USART1->RDR& 0xFF;
                if (uartInputBfr[uartInputBfrCntr] != qspiProgrammerIdentifier[uartInputBfrCntr])
                {
                    uartInputBfrCntr = 0;
                }
                else
                {
                    uartInputBfrCntr++;
                }
                if (uartInputBfrCntr == 8)
                {
                    qspiFlashingState=QSPI_PROGRAMMER_IDENTIFIER_RECEIVED;
                    uartInputBfrCntr = 0;
                    sendAck();
                }
                break;
            case QSPI_PROGRAMMER_IDENTIFIER_RECEIVED:
                dl.data[uartInputBfrCntr++] = USART1->RDR& 0xFF;
                if (uartInputBfrCntr==4)
                {
                    qspiFlashingState = QSPI_PROGRAMMER_LENGTH_RECEIVED;

                    // call chip erase
                    QspiEraseChip();
                    sendAck();
                    uartInputBfrCntr=0;
                }
                break;
            case QSPI_PROGRAMMER_LENGTH_RECEIVED:
                uartInputBfr[uartInputBfrCntr++] = USART1->RDR& 0xFF;
                if (uartInputBfrCntr == 256 || (qspiPageCntr==(dl.binFileLength >> 8) 
                    && uartInputBfrCntr == (dl.binFileLength - (qspiPageCntr << 8))))
                {
                    // call program page
                    QspiProgramPage((qspiPageCntr << 8), uartInputBfr);
                    if (uartInputBfrCntr==256)
                    {
                        qspiPageCntr++;
                        if ((dl.binFileLength - (qspiPageCntr << 8))==0)
                        {
                            qspiFlashingState=QSPI_PROGRAMMER_IDLE;
                        }
                    }
                    else
                    {
                        qspiFlashingState=QSPI_PROGRAMMER_IDLE;
                    }
                    uartInputBfrCntr=0;
                    sendAck();
                }
                break;
        }
    }
}

// irq for uart reception, optional Bluetooth port

//setup
void initUart(uint16_t baudrate)
{
    uint32_t divider;
    uint32_t regbfr;
    uint32_t baudrateWord;
    baudrateWord=baudrate;
    // enable clock
    RCC->APB2ENR |= (1 << RCC_APB2ENR_USART1EN_Pos);

    // define baudrate
    divider = APB2_SPEED/baudrateWord; 
    USART1->BRR = divider & 0xFFFF;

    // enable usart, receiver and transmitter and receiver not empty interrupt
    USART1->CR1 = (1 << USART_CR1_UE_Pos) | (1 << USART_CR1_TE_Pos) | (1 << USART_CR1_RE_Pos) | (1 << USART_CR1_RXNEIE_RXFNEIE_Pos);

    // enable the usart1 interrupt
    __NVIC_EnableIRQ(USART1_IRQn);

    // wire up pb14(tx) and pb15 (rx)
    RCC->AHB4ENR |= (1 << RCC_AHB4ENR_GPIOBEN_Pos);
    regbfr = GPIOB->MODER;
    regbfr &= ~((3 << (14*2)) | (3 << (15*2)));
    regbfr |= (2 << (14*2)) | (2 << (15*2));
    GPIOB->MODER = regbfr;

    GPIOB->PUPDR &= ~((3 << (14*2)) | (3 << (15*2)));
    regbfr = GPIOB->AFR[1];
    regbfr &= ~((0xF << 24) | (0xF << 28));
    regbfr |= ((4 << 24) | (4 << 28));
    GPIOB->AFR[1] = regbfr; // define alternate funtion 7 for pin 14 and 15
}

void initBTUart(uint16_t baudrate)
{

}

/**
 * @brief send's one or multiple characters from out output buffer 
 * doesn't wait until the transmission has terminated
 * depending on the hardware one can fill a FIFO or use DMA to send the output buffer
 * the calling duration must be independent of the baud rate
 *  * 
 * @return uint8_t 1 if transmission has terminated (buffer emptied), 0 if buffer is not empty
 */
uint8_t sendCharAsyncUsb()
{
	//if (usbCommBuffer.outputBufferWriteCnt != usbCommBuffer.outputBufferReadCnt && ((USART1->ISR & (1 << USART_ISR_TXE_TXFNF_Pos))== (1 << USART_ISR_TXE_TXFNF_Pos)))
	//{
	//	USART1->TDR = *(usbCommBuffer.outputBuffer+usbCommBuffer.outputBufferWriteCnt);
	//	usbCommBuffer.outputBufferWriteCnt++;
    //    usbCommBuffer.outputBufferWriteCnt &= ((1 << OUTPUT_BUFFER_SIZE)-1);
    //    return 0;
	//}
	//if (usbCommBuffer.outputBufferWriteCnt == usbCommBuffer.outputBufferReadCnt)
	//{
	//	return 1;
	//}
    return 0;
}

uint8_t sendCharAsyncBt()
{
    return 1;
}
