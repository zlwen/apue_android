#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void copy_file(const char*, const char*);

static char* get_copy_file_name(const char* origin) {
	int len = strlen(origin);
	char* suffix = ".bak";
	int size = len + strlen(suffix) + 1;
	char* buffer = (char *)malloc(size);
	strncpy(buffer, origin, size);
	strcat(buffer, suffix);
	return buffer;
}

int main(int argc, char* argv[]) {
	char *name = argv[1];
	char *copy_name = get_copy_file_name(name);
	printf("copy file:%s to %s\n", name, copy_name);
	copy_file(name, copy_name);
	free(copy_name);
	return 0;
}
