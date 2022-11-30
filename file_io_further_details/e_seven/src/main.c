// main file

#include <fcntl.h>
#include <tlpi/tlpi_hdr.h>

typedef struct _iov_demo {
	void* _base;
	size_t _len;
} IOV_DEMO;

#define BUF_SZ1 50
#define BUF_SZ2 100

ssize_t readv_demo(int fd, IOV_DEMO* idm, size_t count);
ssize_t writev_demo(int fd, IOV_DEMO* idm, size_t count);

int main(int argc, char **argv) {
	char buf1[BUF_SZ1];
	char buf2[BUF_SZ2];
	int buf3;

	int rfd = -1, wfd = -1;

	if(3 > argc || strncmp(argv[1], "--help", 6) == 0)
		usageErr("%s read-file write-file\n", argv[0]);

	rfd = open(argv[1], O_RDONLY);
	if(-1 == rfd)
		errExit("open read");

	wfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR, S_IWUSR);
	if(-1 == wfd)
		errExit("open write");

	IOV_DEMO idm[3] = {
		{
			._base = buf1,
			._len = BUF_SZ1
		},
		{
			._base = &buf3,
			._len = sizeof(buf3)
		},
		{
			._base = buf2,
			._len = BUF_SZ2
		}
	};

	size_t total_required = 0;
	for(int i = 0; i < 3; i++) total_required += idm[i]._len;

	ssize_t num_read = -1, num_write = -1;
	num_read = readv_demo(rfd, idm, 3);
	if(-1 == num_read)
		errExit("readv_demo");
	if(num_read < total_required)
		printf("partial reading happened\n");

	printf("total read: %zu, read_done: %zu\n", total_required, num_read);

	num_write = writev_demo(wfd, idm, 3);
	if(-1 == num_write)
		errExit("writev_demo");
	if(num_write < total_required)
		printf("partial writing happend\n");

	printf("total write: %zu, read_done: %zu\n", total_required, num_read);

	if(-1 == close(rfd))
		errExit("close rfd");
	if(-1 == close(wfd))
		errExit("close wfd");
	exit(EXIT_SUCCESS);
}

ssize_t readv_demo(int fd, IOV_DEMO* idm, size_t count) {
	ssize_t read_count = -1;
	for(size_t i = 0; i < count; i++) {
		ssize_t rcount = -1;
		rcount = read(fd, (idm + i)->_base, (idm + i)->_len);
		if(-1 == rcount)
			errExit("read, count: %d", i + 1);
		else if(rcount < (idm + i)->_len)
			errExit("partial read happened, count: %d", i + 1);
		read_count = (read_count == -1 ? rcount : (read_count + rcount));
	}

	return read_count;
}

ssize_t writev_demo(int fd, IOV_DEMO* idm, size_t count) {
	ssize_t write_count = -1;
	for(size_t i = 0; i < count; i++) {
		ssize_t wcount = -1;
		wcount = write(fd, (idm + i)->_base, (idm + i)->_len);
		if(-1 == wcount)
			errExit("write, count: %d", i + 1);
		else if(wcount < (idm + 1)->_len)
			errExit("partial write happend, count: %d", i + 1);
		write_count = (write_count == -1 ? wcount : (write_count + wcount));
	}

	return write_count;
}