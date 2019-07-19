/*
 * This program calculates CRC8.
 *
 * Author: Victor Wu <goodwater.wu@gmail.com>
 * Date: 20190719
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

static void help(void)
{
	printf("Calculate CRC8\n"
		"Usage: crc8 [options]\n"
		"\t-f <file>\tfile name\n"
		"\t-n <size>\tmaximum size to be calculated\n"
		"\t-h\t\tshow this help\n");
	exit(EXIT_SUCCESS);
}

static unsigned char add_to_crc8(unsigned char c, unsigned char *crc)
{
	unsigned char ch = c;
	unsigned char odd = 0;
	int i;

	if (c < 0)
		ch = c + 256;

	for (i = 0; i != 8; i++) {
		odd = (((ch ^ *crc) & 1) == 1) ? 1 : 0;
		*crc >>= 1;
		ch >>= 1;
		if (odd)
			*crc ^= 0x8C;
	}

	return *crc;
}

unsigned char crc8(unsigned char *buf, unsigned int size)
{
	int i = 0;
	unsigned char crc = 0;

	for (i = 0; i != size; i++)
		add_to_crc8(*(buf + i), &crc);

	return crc;
}

int main(int argc, const char *argv[])
{
	FILE *file = stdin;
	unsigned char *buf = NULL;
	char *filename = NULL;
	unsigned int size = 0;
	unsigned int read_bytes = 0;
	int opt = 0;
	
	errno = 0;

	while ((opt = getopt(argc, (char **)argv, ":f:n:h")) != -1) {
		switch (opt) {
		case 'f':
			filename = optarg;
			break;
		case 'n':
			if (optarg[0] == '0' && tolower(optarg[1]) == 'x')
				size = strtoul(optarg, NULL, 16);
			else
				size = strtoul(optarg, NULL, 10);

			if (errno) {
				perror("size should be a dec or hex value");
				return -errno;
			}

			break;
		default:
			help();
		}
	}

	if (filename) {
		file = fopen(filename, "r");
		if (!file) {
			perror("cannot open the file");
			return -errno;
		}
	}

	buf = calloc(size, 1);
	if (!buf) {
		perror("cannot allocate memory");
		goto error_alloc;
	}

	read_bytes = fread(buf, 1, size, file);
	printf("%x\n", crc8(buf, read_bytes));	

	free(buf);
error_alloc:
	fclose(file);

	return 0;
}
