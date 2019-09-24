#define VGABUF ((volatile char *) 0xb8000)

int LEN_LINE = 160;
int LINES = 24;

static void vga_write(const char *s, int linea, int color){
    volatile char *buf = VGABUF;
    int offset;

    if (linea<0)
        offset = (LINES + linea) * LEN_LINE;
    else
        offset = linea * LEN_LINE;

    buf = buf + offset;
	while(*s != 0){
		*buf++ = *s++;
		*buf++ = color;
	}
}

void comienzo(void) {
    //imprime OK  en el color 47
    //volatile char *buf = VGABUF;
    //*buf++ = 0x2F4B2F4B;
    // 79 = 4F
    // 75 = 4B
    // 47 = 2F

    //volatile uint64_t  *p2 = VGABUF + 160;
    //*p2 = 0xEF41EF4CEF4FEF48;
    // IMPRIME HOLA EN EL COLOR EF (en hexa)


    //vga_write("UNSTRING",-1,12);

    while (1)
        asm("hlt");
}
