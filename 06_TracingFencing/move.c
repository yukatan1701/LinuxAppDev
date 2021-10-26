#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int try_to_close(FILE *file, int is_input) {
	if (fclose(file) != 0) {
		if (is_input)
			perror("Failed to close input file");
		else
			perror("Failed to close output file");
		return errno;
	}
	return 0;
}

int try_to_unlink(const char *filename, int is_input) {	
	if (unlink(filename) != 0) {
		if (is_input)
			perror("Failed to delete input file");
		else
			perror("Failed to delete output file");	
		return errno;
	}
	return 0;
}

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
		try_to_close(infile, 1);
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
	if (try_to_close(outfile, 0) != 0) {
		try_to_close(infile, 1);
		return errno;
	}
	try_to_close(infile, 1);
	if (try_to_unlink(infile_name, 1) != 0) {
		try_to_unlink(outfile_name, 0);
		return errno;
	}
	return 0;
}
