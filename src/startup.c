#include <stdint.h>

// Linker script symbols
extern uint32_t _sdata;  // start of .data in RAM
extern uint32_t _edata;  // end of .data in RAM
extern uint32_t _sbss;   // start of .bss
extern uint32_t _ebss;   // end of .bss


extern uint32_t _sdata_load;

extern int main(void);

// Reset_Handler
void Reset_Handler(void)
{
    // Copy .data from Flash to RAM
    uint32_t *src = (uint32_t *)&_sdata; // flash location of .data
    uint32_t *dst = &_sdata;
    while (dst < &_edata)
        *dst++ = *src++;

    // Zero .bss
    dst = &_sbss;
    while (dst < &_ebss)
        *dst++ = 0;

    // Call main
    main();

    // If main returns, loop forever
    while(1);
}

// Minimal vector table
__attribute__ ((section(".isr_vector")))
uint32_t *vector_table[] = {
    (uint32_t *)0x20020000, // top of RAM (_estack)
    (uint32_t *)Reset_Handler
};
