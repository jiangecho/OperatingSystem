/* Copyright(C) 2012 Xiaoqie
 * This file is part of <OS>.
 *
 * <OS> is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * <OS> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with <OS>.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "kernel/multiboot.h"
#include "asm/head.h"

#define VIDEO 0xB8000

multiboot_info_t *mbi;

extern void sched_init();

// Temp print functions, use it before initial terminal.
static void boot_itoa(char *buf, int base, int d) {
	char *p = buf;
	char *p1, *p2;
	unsigned long ud = d;
	int divisor = 10;
	/* If %d is specified and D is minus, put `-' in the head. */
	if (base == 'd' && d < 0) {
		*p++ = '-';
		buf++;
		ud = -d;
	} else if (base == 'x')
		divisor = 16;
	/* Divide UD by DIVISOR until UD == 0. */
	do {
		int remainder = ud % divisor;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
	} while (ud /= divisor);
	/* Terminate BUF. */
	*p = 0;
	/* Reverse BUF. */
	p1 = buf;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}
static void boot_putchar(int c) {
	static int xpos;
	static int ypos;
	if (c == '\n' || c == '\r') {
	newline:
		xpos = 0;
		ypos++;
		if (ypos >= 24)
			ypos = 0;
		return;
	}
	*((unsigned char *) VIDEO + (xpos + ypos * 80) * 2) = c & 0xFF;
	*((unsigned char *) VIDEO + (xpos + ypos * 80) * 2 + 1) = 7;
	xpos++;
	if (xpos >= 80)
		goto newline;
}
static void boot_print(const char *format, ...) {
	char **arg = (char **) &format;
	int c;
	char buf[20];
	arg++;
	while ((c = *format++) != 0) {
		if (c != '%')
			boot_putchar(c);
		else {
			char *p;
			c = *format++;
			switch (c) {
			case 'd':
			case 'u':
			case 'x':
				boot_itoa(buf, c, *((int *) arg++));
				p = buf;
				goto string;
				break;
			case 's':
				p = *arg++;
				if (!p)
					p = "(null)";
				string: while (*p)
					boot_putchar(*p++);
				break;
			default:
				boot_putchar(*((int *) arg++));
				break;
			}
		}
	}
}

void start_kernel() {
	boot_print("Magic number: 0x%x\n", multiboot_magic);
	if (multiboot_magic == MULTIBOOT_BOOTLOADER_MAGIC) {
		mbi = (multiboot_info_t *) multiboot_mbi;
		boot_print("Memory lower: %dKB, Memory upper: %dKB", mbi->mem_lower,
				mbi->mem_upper);
	}
	while (1);
}
