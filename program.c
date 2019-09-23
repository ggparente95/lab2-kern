#include <stdio.h>

int main(void) {
    // unsigned int i = 0x726c6400;   in Big Endian
    unsigned int i = 0x00646c72;
    printf("H%x Wo%s\n", 57616, (char *) &i);
}