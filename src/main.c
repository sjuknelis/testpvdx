void main(void);

__attribute__((section(".vectors"))) const long vectors[] = {0x2002FFFF, (long)main};

volatile int test = 8;

void main(void) {
    while (test != 8);

    volatile int a = 1;
    a++;
    for (;;);
}