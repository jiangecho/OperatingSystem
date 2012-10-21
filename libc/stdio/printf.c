
int printf(const char *restrict format, ...) {
	int count;
	count = fprintf(stdout, format);
	return count;
}
