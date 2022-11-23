#pragma once

int buffer_size;
struct buffer
{
	FILE* file;
	int data_size;
	char* filename;
	char* data;
};
SystemInit(buffer_size);
SystemClose(buffer);
struct buffer* open(char* name, char* mode);
close(struct buffer* buffer);
read(struct buffer *buffer, int size_to_read);
write(struct buffer *buffer, int size_to_write);
