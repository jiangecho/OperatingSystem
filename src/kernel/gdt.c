struct GDT {
	unsigned short seg_length_limit_0_15;
	unsigned short seg_base_addr_0_15;
	unsigned char seg_base_addr_16_23;
	unsigned char type :4;
	unsigned char s :1;
	unsigned char dpl :2;
	unsigned char p :1;
	unsigned char seg_length_limit_16_19 :4;
	unsigned char avl :1;
	unsigned char saved_0 :1;
	unsigned char d_or_b :1;
	unsigned char g :1;
	unsigned char seg_base_addr_24_31;
};

struct GDTDescriptor {
	unsigned short length;
	struct GDT *addr;
};

struct GDTDescriptor gdtDesc;
struct GDT gdt[256];

void setupGDT() {
	struct GDT p;
	p->avl = 0;
	p->d_or_b = 1;
	p->dpl = 0;
	p->g = 1;
	p->p = 1;
	p->s = 1;
	p->saved_0 = 0;
	p->seg_base_addr_0_15 = 0;
	p->seg_base_addr_16_23 = 0;
	p->seg_base_addr_24_31 = 0;
	p->seg_length_limit_0_15 = 0xffff;
	p->seg_length_limit_16_19 = 0xff;
	p->type = 0x9a;

	gdt[1] = p;
	gdt[2] = p;
	gdt[2].type = 0x92;

	gdtDesc.addr = gdt;
	gdtDesc.length = 0x7FF;

	__asm__("lgdt %0" : "=m"(gdtDescr));
}

void setGDTItem(int n, struct GDT *desc) {
	gdt[n] = desc;
}
