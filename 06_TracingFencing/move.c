#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "Not enoght arguments.\n");
		return -1;
	}
	const char *infile_name = argv[1];
	const char *outfile_name = argv[2];
	FILE *infile = fopen(infile_name, "r");
	if (!infile) {
		perror("Failed to open source file");
		return errno;
	}
	FILE *outfile = fopen(outfile_name, "w");
	if (!outfile) {
		perror("Failed to open destination file");
		return errno;
	}
	int c = EOF;
	errno = 0;
	while ((c = fgetc(infile)) != EOF) {
		int result = fputc(c, outfile);
		if (result == EOF) {
			perror("Failed to write to output file");
			return errno;
		}
	}
	if (errno != 0) {
		perror("Failed to read a source file");
		return errno;
	}
	if (fclose(outfile) != 0) {
		perror("Failed to close output file");
		if (fclose(infile) != 0) {
			perror("Failed to close input file");
			return errno;
		}
		return errno;
	}
	if (fclose(infile) != 0) {
		perror("Failed to close input file");
		return errno;
	}
	if (unlink(infile_name) != 0) {
		perror("Failed to delete input file");
		if (unlink(outfile_name) != 0) {
			perror("Failed to delete output file");
			return errno;
		}
		return errno;
	}
	return 0;
}
