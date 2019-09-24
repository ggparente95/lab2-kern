#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

//
// Definir aquÃ­ backtrace().
//

void backtrace(){
    int *ebp_0 = (int *) __builtin_frame_address(0);
    int *ebp_1 = (int *) __builtin_frame_address(1);
    int *ebp_2 = (int *) __builtin_frame_address(2);
    int *ebp_3 = (int *) __builtin_frame_address(3);
    int *ebp_4 = (int *) __builtin_frame_address(4);
    int *ebp_5 = (int *) __builtin_frame_address(5);
    int *ebp_6 = (int *) __builtin_frame_address(6);
    printf("[0x%08x] 0x%08x (%d) \n", ebp_0, *ebp_0 - sizeof(int), *((int *)__builtin_frame_address(0) - sizeof(int)));
    printf("[0x%08x] 0x%08x (%d) \n", ebp_1, *ebp_1 - sizeof(int), *((int *)__builtin_frame_address(1) - 2*sizeof(int)));
    printf("[0x%08x] 0x%08x (%d) \n", ebp_2, *ebp_2 - sizeof(int), *((int *)__builtin_frame_address(2) - 2*sizeof(int)));
    printf("[0x%08x] 0x%08x (%d) \n", ebp_3, *ebp_3 - sizeof(int), *((int *)__builtin_frame_address(3) - 2*sizeof(int)));
    printf("[0x%08x] 0x%08x (%d) \n", ebp_4, *ebp_4 - sizeof(int), *((int *)__builtin_frame_address(4) - 2*sizeof(int)));
    printf("[0x%08x] 0x%08x (%d) \n", ebp_5, *ebp_5 - sizeof(int), *((int *)__builtin_frame_address(5) - 2*sizeof(int)));
    printf("[0x%08x] 0x%08x (%d) \n", ebp_6, *ebp_6 - sizeof(int), *((int *)__builtin_frame_address(6) - 2*sizeof(int)));
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