#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"


SystemInit(size) {
    buffer_size = size;
}
SystemClose(struct buffer* buf) {
    free(buf->data);
    free(buf);
}
struct buffer* open(char* name, char* mode) {
    FILE* fptr;
    fptr = fopen(name, mode);
    struct buffer *Buf = (struct buffer* )malloc(sizeof(struct buffer));
    Buf->data  = malloc(buffer_size);
    Buf->file = fptr;
    Buf->filename = name;
    Buf->data_size = 0;
    return Buf;
}
close(struct buffer* buf) {
    fclose(buf->file);
}
read(struct buffer *buffer, int size_to_read) {
    int i = 0;
    char ch;
    printf("read from %s:  ", buffer->filename);
    while (i <= size_to_read) {
        if ((ch = fgetc(buffer->file)) != EOF) {
            if (i < buffer_size) {
                buffer->data[i] = ch;
            }
            else {
                buffer->data_size = buffer_size;
                printf("%.*s", buffer->data_size, buffer->data);
                size_to_read -= i;
                i = 0;
            }
            i++;
        }
        else
        {
            buffer->data_size = i;
            printf("%.*s\n", buffer->data_size, buffer->data);
            break;
        }
    }
}
write_in_file(struct buffer* buf) {
    for (int i = 0; i < buf->data_size; i++) {
        fputc(buf->data[i], buf->file);
    }
}
char* slice(char* s, int from){
    return s + from;
}
write(struct buffer * buffer, int size_to_write) {
    char text[100];
    gets_s(text, 1);
    printf("write in %s: ", buffer->filename);
    if (fgets(text, size_to_write, stdin)) {
        if (strlen(text) < buffer_size) {
            strcpy(buffer->data, text);
            buffer->data_size = strlen(text);
            write_in_file(buffer);
        }
        else {
            for (int i = 0; i * buffer_size < strlen(text); i++) {
                strncpy(buffer->data,text, buffer_size);
                buffer->data_size = buffer_size;
                write_in_file(buffer);
                slice(text, (i + 1) * buffer_size);
            }
        }
    }
}