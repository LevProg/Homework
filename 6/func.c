#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"


SystemInit(size) {
    buffer_size = size;
}
SystemClose(struct buffer buf) {
    free(buf.data);
}
struct buffer open(char* name, char* mode) {
    FILE* fptr;
    fptr = fopen(name, mode);
    struct buffer Buf = { fptr, 0, malloc(buffer_size)};
    return Buf;
}
close(struct buffer buf) {
    fclose(buf.file);
}
read(struct buffer buf, int size_to_read) {
    int i = 0;
    char ch;
    while (i <= size_to_read) {
        if ((ch = fgetc(buf.file)) != EOF) {
            if (i < buffer_size) {
                buf.data[i] = ch;
            }
            else {
                buf.data_size = buffer_size;
                printf("%.*s", buf.data_size, buf.data);
                size_to_read -= i;
                i = 0;
            }
            i++;
        }
        else
        {
            buf.data_size = i;
            printf("%.*s\n", buf.data_size, buf.data);
            break;
        }
    }
}
write_in_file(struct buffer buf) {
    for (int i = 0; i < buf.data_size; i++) {
        fputc(buf.data[i], buf.file);
    }
}
write(struct buffer buf, int size_to_write) {
    char text[100];    
    if (scanf("%s", &text)) {
        int i = 0;
        int j = 0;
        while (j <= strlen(text)) {
            if (i < buffer_size) {
                buf.data[i] = text[j];
            }
            else {
                buf.data = i;
                write_in_file(buf);
                i = 0;
                buf.data_size = i;
            }
            i++;
            j++;
        }
        buf.data_size = i-1;
        write_in_file(buf);
    }
}