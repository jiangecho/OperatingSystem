struct GDTDescriptor {
	unsigned short length;
	long long *addr;
};

struct GDTDescriptor gdtDesc;

/* 'long long' type in GCC:
 * .size XXXX, 8
 * XXXX:
 *     .long YYYY
 *     .long ZZZZ
 */
long long gdt[256];

void setupGDT() {
	gdt[1] = 0x00cf9a000000ffff;
	gdt[2] = 0x00cf92000000ffff;

	gdtDesc.addr = gdt;
	gdtDesc.length = 0x7FF;

	__asm__("lgdt %0" : "=m"(gdtDesc));
}
