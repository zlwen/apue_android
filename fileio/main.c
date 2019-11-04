#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

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

static void test_copy(char* argv[]) {
	char *name = argv[1];
	char *copy_name = get_copy_file_name(name);
	printf("copy file:%s to %s\n", name, copy_name);
	copy_file(name, copy_name);
	free(copy_name);
}

static void test_lseek(int fd) {
	int cur = lseek(fd, 0, SEEK_CUR);
	printf("current position:%d\n", cur);
	printf("go to position:15\n");
	cur = lseek(fd, 15, SEEK_SET);
	cur = lseek(fd, 0, SEEK_CUR);
	printf("current position:%d\n", cur);
	printf("go to file end\n");
	cur = lseek(fd, 0, SEEK_END);
	printf("current position:%d\n", cur);
}

static void test_dup(int fd) {
	int new_fd = dup(fd);
	printf("fd:%d go to position:15\n", fd);
	int cur = lseek(fd, 15, SEEK_SET);
	cur = lseek(new_fd, 0, SEEK_CUR);
	printf("new fd:%d position:%d\n", new_fd, cur);
	cur = lseek(new_fd, 0, SEEK_END);
	cur = lseek(fd, 0, SEEK_CUR);
	printf("fd:%d position:%d\n", fd, cur);
}

static void test_stat(int fd) {
	struct stat stat;
	char buf[1024] = {0};
	snprintf(buf, sizeof(buf), "/proc/self/fd/%d", fd);
	printf("buf content:%s\n", buf);
	lstat(buf, &stat);
	char *ptr = "unknown";
	if (S_ISREG(stat.st_mode)) {
		ptr = "regular";
	} else if (S_ISDIR(stat.st_mode)) {
		ptr = "directory";
	} else if (S_ISLNK(stat.st_mode)) {
		ptr = "link";
	}
	printf("file type is %s\n", ptr);
}

int main(int argc, char* argv[]) {
	char *name = argv[1];
	int fd = open(name, O_RDONLY);
	if (fd < 0) {
		return -1;
	}
	test_stat(fd);
	return 0;
}
