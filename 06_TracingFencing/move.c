#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

enum ERROR_CODE {
	ERR_OK = 0,
	ERR_NOT_ENOUGH_ARGS,
	ERR_BAD_CLOSE_INPUT,
	ERR_BAD_CLOSE_OUTPUT,
	ERR_BAD_OPEN_INPUT,
	ERR_BAD_OPEN_OUTPUT,
	ERR_BAD_DELETE_INPUT,
	ERR_BAD_DELETE_OUTPUT,
	ERR_BAD_WRITE_OUTPUT,
	ERR_BAD_READ_INPUT
};

int try_to_close(FILE *file, int is_input) {
	if (fclose(file) != 0) {
		if (is_input) {
			perror("Failed to close input file");
			return ERR_BAD_CLOSE_INPUT;
		}
		perror("Failed to close output file");
		return ERR_BAD_CLOSE_OUTPUT;
	}
	return 0;
}

int try_to_unlink(const char *filename, int is_input) {	
	if (unlink(filename) != 0) {
		if (is_input) {
			perror("Failed to delete input file");
			return ERR_BAD_DELETE_INPUT;
		}
		perror("Failed to delete output file");	
		return ERR_BAD_DELETE_OUTPUT;
	}
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "Not enoght arguments.\n");
		return ERR_NOT_ENOUGH_ARGS;
	}
	const char *infile_name = argv[1];
	const char *outfile_name = argv[2];
	FILE *infile = fopen(infile_name, "r");
	if (!infile) {
		perror("Failed to open input file");
		return ERR_BAD_OPEN_INPUT;
	}
	FILE *outfile = fopen(outfile_name, "w");
	if (!outfile) {
		perror("Failed to open output file");
		int res = try_to_close(infile, 1);
		return res == 0 ? ERR_BAD_OPEN_OUTPUT : res;
	}
	int c = EOF;
	errno = 0;
	while ((c = fgetc(infile)) != EOF) {
		int result = fputc(c, outfile);
		if (result == EOF) {
			perror("Failed to write to output file");
			int res_in = try_to_close(infile, 1);
			if (!res_in)
				return res_in;
			int res_out = try_to_close(outfile, 0);
			if (!res_out)
				return res_out;
			return ERR_BAD_WRITE_OUTPUT;
		}
	}
	if (errno != 0) {
		perror("Failed to read a source file");
		int res = try_to_close(infile, 1);
		if (res != 0)
			return res;
		res = try_to_unlink(outfile_name, 0);
		if (res != 0)
			return res;
		return ERR_BAD_READ_INPUT;
	}
	int res = 0;
	if ((res = try_to_close(outfile, 0)) != 0) {
		int res2;
		if ((res2 = try_to_close(infile, 1)) != 0)
			return res2;
		return res;
	}
	if ((res = try_to_close(infile, 1)) != 0) {
		int res2;
		if ((res2 = try_to_unlink(outfile_name, 0)) != 0)
			return res2;
		return res;
	}
	if ((res = try_to_unlink(infile_name, 1)) != 0) {
		int res2;
		if ((res2 = try_to_unlink(outfile_name, 0)) != 0)
			return res2;
		return res;
	}
	return 0;
}
