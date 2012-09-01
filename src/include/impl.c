/**
 * Kernel Method Implementation of kernel.h
 * Do not compile this file with -std=c99!!!
 */
#include "kernel.h"

unsigned short rgb565(unsigned char r, unsigned char g, unsigned char b) {
	union {
		unsigned int color;
		struct {
			unsigned char b :5;
			unsigned char g :6;
			unsigned char r :5;
		};
	} u;
	u.r = r % 32;
	u.g = g % 64;
	u.b = b % 32;
	return u.color;
}
