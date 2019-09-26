#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

void backtrace(){
    int *ebp = (int *)__builtin_frame_address(0);
    ebp = (int*)*ebp;
    int flag = 1;
    int numfrm = 1;

    while(flag == 1){
        printf("#%d [0x%x] 0x%x ( 0x%x 0x%x 0x%x )\n", numfrm, ebp, *(ebp+1), *(ebp+2), *(ebp+3), *(ebp+4));  
        ebp = (int*)*ebp;
        numfrm++;
        if (ebp == NULL)
            flag = 0;
    }
}


void my_write(int fd, const void *msg, size_t count) {
    backtrace();
    fprintf(stderr, "=> write(%d, %p, %zu)\n", fd, msg, count);
    write(fd, msg, count);
}

void recurse(int level) {
    if (level > 0)
        recurse(level - 1);
    else
        my_write(2, "Hello, world!\n", 15);
}

void start_call_tree() {
    recurse(5);
}

int main(void) {
    start_call_tree();
}