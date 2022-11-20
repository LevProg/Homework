#pragma once

int buffer_size;
struct buffer
{
	FILE* file;
	int data_size;
	char* data;
};
SystemInit(buffer_size);
SystemClose(buffer);
struct buffer open(char* name, char* mode);
close(file);
read(struct buffer buffer, int size_to_read);
write(struct buffer buffer, int size_to_write);
