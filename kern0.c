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
    volatile char *buf = VGABUF;

    vga_write("UNSTRING",-1,12);

    while (1)
        asm("hlt");
}
