
.syntax unified
.cpu cortex-m0plus
.thumb

#include "hardware/regs/addressmap.h"
#include "hardware/regs/m0plus.h"


/* standard isr declarations as weak function */
.macro std_isr name
.weak \name
.type \name,%function
\name:
.endm

/* breakpoint isr, they are called upon a fault */
.macro bkpt_isr name
.weak \name
.type \name,%function
\name:
    bkpt #0
.endm

.section .vectors_core0, "ax"
.align 2

.global __vectors_core0 
__vectors_core0:
.word __StackTop
.word _start_c_runtime
.word isr_c0_nmi
.word isr_c0_hardfault
.word isr_c0_invalid // Reserved, should never fire
.word isr_c0_invalid // Reserved, should never fire
.word isr_c0_invalid // Reserved, should never fire
.word isr_c0_invalid // Reserved, should never fire
.word isr_c0_invalid // Reserved, should never fire
.word isr_c0_invalid // Reserved, should never fire
.word isr_c0_invalid // Reserved, should never fire
.word isr_c0_svcall
.word isr_c0_invalid // Reserved, should never fire
.word isr_c0_invalid // Reserved, should never fire
.word isr_c0_pendsv
.word isr_c0_systick
.word isr_c0_timer_irq0
.word isr_c0_timer_irq1
.word isr_c0_timer_irq2
.word isr_c0_timer_irq3
.word isr_c0_pwm_wrap_irq4
.word isr_c0_usbctrl_irq5
.word isr_c0_xip_irq6
.word isr_c0_pio0_irq0_irq7
.word isr_c0_pio0_irq1_irq8
.word isr_c0_pio1_irq0_irq9
.word isr_c0_pio1_irq1_irq10
.word isr_c0_dma_irq0_irq11
.word isr_c0_dma_irq1_irq12
.word isr_c0_io_irq_bank0_irq13
.word isr_c0_io_irq_qspi_irq14
.word isr_c0_sio_irq_proc0_irq15
.word isr_c0_sio_irq_proc1_irq16
.word isr_c0_clocks_irq17
.word isr_c0_spi0_irq18
.word isr_c0_spi1_irq19
.word isr_c0_uart0_irq20
.word isr_c0_uart1_irq21
.word isr_c0_adc_fifo_irq22
.word isr_c0_i2c0_irq23
.word isr_c0_i2c1_irq24
.word isr_c0_rtc_irq25
.word isr_c0_irq26
.word isr_c0_irq27
.word isr_c0_irq28
.word isr_c0_irq29
.word isr_c0_irq30
.word isr_c0_irq31



bkpt_isr isr_c0_nmi
bkpt_isr isr_c0_hardfault
bkpt_isr isr_c0_invalid
bkpt_isr isr_c0_svcall
bkpt_isr isr_c0_pendsv
bkpt_isr isr_c0_systick

std_isr isr_c0_timer_irq0
std_isr isr_c0_timer_irq1
std_isr isr_c0_timer_irq2
std_isr isr_c0_timer_irq3
std_isr isr_c0_pwm_wrap_irq4
std_isr isr_c0_usbctrl_irq5
std_isr isr_c0_xip_irq6
std_isr isr_c0_pio0_irq0_irq7
std_isr isr_c0_pio0_irq1_irq8
std_isr isr_c0_pio1_irq0_irq9
std_isr isr_c0_pio1_irq1_irq10
std_isr isr_c0_dma_irq0_irq11
std_isr isr_c0_dma_irq1_irq12
std_isr isr_c0_io_irq_bank0_irq13
std_isr isr_c0_io_irq_qspi_irq14
std_isr isr_c0_sio_irq_proc0_irq15
std_isr isr_c0_sio_irq_proc1_irq16
std_isr isr_c0_clocks_irq17
std_isr isr_c0_spi0_irq18
std_isr isr_c0_spi1_irq19
std_isr isr_c0_uart0_irq20
std_isr isr_c0_uart1_irq21
std_isr isr_c0_adc_fifo_irq22
std_isr isr_c0_i2c0_irq23
std_isr isr_c0_i2c1_irq24
std_isr isr_c0_rtc_irq25
std_isr isr_c0_irq26
std_isr isr_c0_irq27
std_isr isr_c0_irq28
std_isr isr_c0_irq29
std_isr isr_c0_irq30
std_isr isr_c0_irq31

.section .vectors_core1, "ax"
.align 2

.global __vectors_core1 
__vectors_core1:
.word __StackTop
.word _start_c_runtime
.word isr_c1_nmi
.word isr_c1_hardfault
.word isr_c1_invalid // Reserved, should never fire
.word isr_c1_invalid // Reserved, should never fire
.word isr_c1_invalid // Reserved, should never fire
.word isr_c1_invalid // Reserved, should never fire
.word isr_c1_invalid // Reserved, should never fire
.word isr_c1_invalid // Reserved, should never fire
.word isr_c1_invalid // Reserved, should never fire
.word isr_c1_svcall
.word isr_c1_invalid // Reserved, should never fire
.word isr_c1_invalid // Reserved, should never fire
.word isr_c1_pendsv
.word isr_c1_systick
.word isr_c1_timer_irq0
.word isr_c1_timer_irq1
.word isr_c1_timer_irq2
.word isr_c1_timer_irq3
.word isr_c1_pwm_wrap_irq4
.word isr_c1_usbctrl_irq5
.word isr_c1_xip_irq6
.word isr_c1_pio0_irq0_irq7
.word isr_c1_pio0_irq1_irq8
.word isr_c1_pio1_irq0_irq9
.word isr_c1_pio1_irq1_irq10
.word isr_c1_dma_irq0_irq11
.word isr_c1_dma_irq1_irq12
.word isr_c1_io_irq_bank0_irq13
.word isr_c1_io_irq_qspi_irq14
.word isr_c1_sio_irq_proc0_irq15
.word isr_c1_sio_irq_proc1_irq16
.word isr_c1_clocks_irq17
.word isr_c1_spi0_irq18
.word isr_c1_spi1_irq19
.word isr_c1_uart0_irq20
.word isr_c1_uart1_irq21
.word isr_c1_adc_fifo_irq22
.word isr_c1_i2c0_irq23
.word isr_c1_i2c1_irq24
.word isr_c1_rtc_irq25
.word isr_c1_irq26
.word isr_c1_irq27
.word isr_c1_irq28
.word isr_c1_irq29
.word isr_c1_irq30
.word isr_c1_irq31

bkpt_isr isr_c1_nmi
bkpt_isr isr_c1_hardfault
bkpt_isr isr_c1_invalid
bkpt_isr isr_c1_svcall
bkpt_isr isr_c1_pendsv
bkpt_isr isr_c1_systick

std_isr isr_c1_timer_irq0
std_isr isr_c1_timer_irq1
std_isr isr_c1_timer_irq2
std_isr isr_c1_timer_irq3
std_isr isr_c1_pwm_wrap_irq4
std_isr isr_c1_usbctrl_irq5
std_isr isr_c1_xip_irq6
std_isr isr_c1_pio0_irq0_irq7
std_isr isr_c1_pio0_irq1_irq8
std_isr isr_c1_pio1_irq0_irq9
std_isr isr_c1_pio1_irq1_irq10
std_isr isr_c1_dma_irq0_irq11
std_isr isr_c1_dma_irq1_irq12
std_isr isr_c1_io_irq_bank0_irq13
std_isr isr_c1_io_irq_qspi_irq14
std_isr isr_c1_sio_irq_proc0_irq15
std_isr isr_c1_sio_irq_proc1_irq16
std_isr isr_c1_clocks_irq17
std_isr isr_c1_spi0_irq18
std_isr isr_c1_spi1_irq19
std_isr isr_c1_uart0_irq20
std_isr isr_c1_uart1_irq21
std_isr isr_c1_adc_fifo_irq22
std_isr isr_c1_i2c0_irq23
std_isr isr_c1_i2c1_irq24
std_isr isr_c1_rtc_irq25
std_isr isr_c1_irq26
std_isr isr_c1_irq27
std_isr isr_c1_irq28
std_isr isr_c1_irq29
std_isr isr_c1_irq30
std_isr isr_c1_irq31


.section .reset,"ax"

.global _reset
.type _reset,%function
_reset:
// initialize the stack pointer
ldr r1, =(XIP_BASE + 0x100)
ldr r2,[r1]
msr msp, r2

// branch to _start_c_runtime
ldr r1, =(XIP_BASE + 0x104) 
ldr r2,[r1]
bx r2

.global _start_c_runtime,_entry_point
.type _start_c_runtime,%function
_start_c_runtime:
_entry_point:
// set the vector offset table register
ldr r0, =__vectors_core0
ldr r1,=PPB_BASE+M0PLUS_VTOR_OFFSET
str r0,[r1]



// Zero out the BSS
ldr r1, =__bss_start__
ldr r2, =__bss_end__
movs r0, #0
b bss_fill_test
bss_fill_loop:
stm r1!, {r0}
bss_fill_test:
cmp r1, r2
bne bss_fill_loop

// copy initialized data from  the end of the text section to the data section
ldr r4, =data_section_addresses
ldr r1,[r4]
ldr r2,[r4,#4]
ldr r3,[r4,#8]
//ldm r4!,{r1-r3}
b data_cpy

data_cpy_loop:
ldm r1!, {r0}
stm r2!, {r0}
data_cpy:
cmp r2, r3 
blo data_cpy_loop

// test jump to _boot_stage_2
//ldr r1, =_boot_stage_2
//blx r1


// jump off to main
ldr r1,=main
blx r1


// utility delay function

.global _sr35_delay
.type _sr35_delay,%function
_sr35_delay:
    movs r1,#0
    b _delay_test
    _delay_loop:
    adds r1,#1
    _delay_test:
    cmp r1,r0
    bne _delay_loop
    bx lr
        
// data table addresses used to copy data from flash to ram     

.align 4
data_section_addresses:
.word __etext
.word __data_start__
.word __data_end__
