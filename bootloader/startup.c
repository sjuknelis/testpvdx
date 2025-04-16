extern char _sdata;   // Start of .data in RAM
extern char _edata;   // End of .data in RAM
extern char _sidata;  // Start of .data in FLASH

extern char _sbss;    // Start of .bss in RAM
extern char _ebss;    // End of .bss in RAM

extern void bootloader(void);

void startup(void);

__attribute__((section(".vectors"))) const long startup_vectors[] = {0x2003FFFF, (long)startup};

void startup(void) {
    // Copy bootloader's data segment
    char *src = &_sidata;
    char *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    // Zero out bootloader's BSS segment
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    bootloader();
}