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

void *wr_bk(struct {block *l; block b;} *_in)
{
	*_in->l = _in->b;
	return NULL;
}

tckt_ *set(void *_k)
{
	tckt_ *r = malloc(sizeof(tckt_));
	r->in = _k;
	r->out = (void *(*)(void *))&wr_bk;
	return r;
}

char chk(unsigned _b)
{
	return 0;
}

void stack(tckt_ *_t)
{
	unsigned char k = *(unsigned char *)(_t->in) - 1;
	block *b = malloc((k+1) * sizeof(block));
	
	b->step = *(unsigned char *)(_t->in+1);

	unsigned char *j = malloc(k);
	*(j+k) = 0;

	while (_t->in) {
		unsigned char *h = j+k;
		while (h-->j)
			*h = (unsigned char)rand();

		if (chk(k)) continue;

		void *o = malloc(sizeof(b) + sizeof(*b));
		*(block **)o = *(block **)(_t->in+2);
		*(block *)(o + sizeof(b)) = *b;
		((*(_t->out))(o));
		free(o);
		_t++;
	}

	free(j);
}
