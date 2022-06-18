#include"connector.h"

const unsigned char primes[] = {
	2,	3,	5,	7,	11,	13,
	17,	19,	23,	29,	31,	37,
	41,	43,	47,	53,	59,	61,
	67,	71,	73,	79,	83,	89,
	97,	101,	103,	107,	109,	113,
	127,	131,	137,	139,	149,	151,
	157,	163,	167,	173,	179,	181,
	191,	193,	197,	199,	211,	223,
	227,	229,	233,	239,	241,	251,
	0xFF
};

unsigned *wr_bk(struct {block *l; block b;} *_in)
{
	*_in->l = _in->b;
	free(_in);
	return _in->b.step ? (unsigned *)++_in : NULL;
}

tckt_ set(void *_k)
{
	tckt_ r;
	r.in = _k;
	r.out = (void *(*)(void *))&wr_bk;
	return r;
}

char chk(unsigned _b)
{
	return 0;
}

void stack(void *_p, tckt_ *_t)
{
	unsigned char k = *(unsigned *)(_p+1) - 1;
	block *b = malloc(sizeof(block) + k);
	
	b->step = *(unsigned char *)_p;

	unsigned char *j = malloc(k+1);
	*(j+k) = 0;

	while (_t) {
		unsigned char *h = j+k;
		while (k-->j)
			*h = (unsigned char)rand();

		if (chk(k)) continue;

		void *o = malloc(sizeof(b) + sizeof(*b));
		*(block *)(o) = *(block *)(_p+2);
		*(block *)(o + sizeof(b)) = *b;
		_t = (tckt_ *)((*(_t->out))(o));
	}

	free(j);
}
