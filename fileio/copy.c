#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define BUF_SIZE 4096

void copy_file(const char* src, const char* dst) {
	int rfd = open(src, O_RDONLY);
	if (rfd == -1) {
		return;
	}
	int wfd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (wfd == -1) {
		return;
	}
	char buf[BUF_SIZE];
	int n;
	while((n = read(rfd, buf, BUF_SIZE)) > 0) {
		write(wfd, buf, n);
	}
	close(rfd);
	close(wfd);
}
