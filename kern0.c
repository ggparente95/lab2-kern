#define VGABUF ((volatile char *) 0xb8000)

void comienzo(void) {
    volatile char *buf = VGABUF;

    *buf++ = 79;
    *buf++ = 47;
    *buf++ = 75;
    *buf++ = 47;

    while (1)
        asm("hlt");
}