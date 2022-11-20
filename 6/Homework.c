#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "func.h"


int main(void)
{
    struct buffer buffer1,buffer2;
    int text_size;
    int buffer_size;
    if (scanf("%d", &buffer_size)) {
        SystemInit(buffer_size);
        buffer1 = open("data.txt", "a+");
        buffer2 = open("data2.txt", "a+");
        read(buffer1,100);
        write(buffer2, 100);
        SystemClose(buffer1);
        SystemClose(buffer2);
    }
    return 0;
}