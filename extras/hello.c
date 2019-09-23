#include <unistd.h>
#include <stdio.h>
#include <string.h>

char msg[] = "Hello, world!\n";

int main(void) {

    write(1, msg, sizeof(msg) - 1);
    return 0;
}