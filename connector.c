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
	255
};

void *wr_bk(struct {block *l; block b;} _in)
{
	printf("%p\n", &_in);
	printf("Writing to %p\n", _in.l);
	*_in.l = _in.b;
	// planned to later return information input 
	return NULL;
}

tckt_ *set(void *_k)
{
	tckt_ *r = malloc(sizeof(tckt_));
	printf("Set for %p\n", r);
	r->in = _k;
	r->out = (void *(*)(void *))&wr_bk;
	return r;
}

char cp(unsigned char _p)
{
	const unsigned char *ck = primes;
	do if (_p == *ck) return 0;
	while (~*++ck);

	return 1;
}

char chk_bk(block *_b)
{
	short s = 0;
	char *p = _b->parts;
	do s += *p;
	while (*++p);

	return cp(s > 0 ? s : -s);
}

char chk_ct(connector *_c, block *_b)
{
	short s = 0;
	char *q = _b->parts, *p = _c->parts;

	do if (s += *p <= 0) return 1;
	while (*++p);

	s = 0;
	while (p-->_c->parts) if (s -= *p <= 0) return 1;

	s = _b->step;
	do if (cp(s += *p++ - *q > 0 ? s : -s)) return 1;
	while (*++q);

	q = _c->parts;
	do if (cp(s += *p - *q++ > 0 ? s : -s)) return 1;
	while (*++p);
	
	s = _b->step;
	q = _b->parts;
	do if (cp(s -= *p-- - *q > 0 ? s : -s)) return 1;
	while (*++q);

	p = _c->parts;
	for (p = _c->parts; *p; p -= s = -1)
		for (q = p; *q; q++)
			if (~(s += *q))
				return 1;

	for (p = q = _c->parts; *p; p++);
	if (p-q != _c->base.length) return 1;
	if (!(*p+*q)) return 1;

	for (s = 0; *q; q++)
		s += *q;
	if (s != _c->base.diff) return 1;

	return 0;
}

void stack(tckt_ *_t)
{
	unsigned char k = *(unsigned char *)(_t->in) - 1;
	block *o = malloc(sizeof(block *) + sizeof(block) + k + 1);
	printf("Output is: %p\n", o);
	
	*(block **)o = *(block **)(_t->in+2);
	printf("Space provided: %p\n", *(block **)o);
	(o+1)->step = *(unsigned char *)(_t->in+1);
	(o+1)->parts[k] = 0;

	while (_t->in) {
		printf("Shuffling...\n");
		char *h = (o+1)->parts + k;
		while (h-->((o+1)->parts))
			*h = (char)rand();

		if (chk_bk(o+1)) continue;

		printf("Recording...\n");

		(*_t->out)(o);
		_t++;
	}

	free(o);
}

void search(block _b, cnct_ _c, tckt_ _t)
{
	unsigned char k = *(unsigned char *)(_t->in) - 1;
	connector *o = malloc(sizeof(connector *) + sizeof(connector) + k + 1);
	// printf("Output is: %p\n", o);
	
	// *(connector **)o = *(connector **)(_t->in+2);
	// printf("Space provided: %p\n", *(connector **)o);
	// (o+1)->step = *(unsigned char *)(_t->in+1);
	// (o+1)->parts[k] = 0;

	// while (_t->in) {
	// 	printf("Shuffling...\n");
	// 	char *h = (o+1)->parts + k;
	// 	while (h-->((o+1)->parts))
	// 		*h = (char)rand();

	// 	if (chk_ct(o+1)) continue;

	// 	printf("Recording...\n");

	// 	(*_t->out)(o);
	// 	_t++;
	// }

	free(o);
}
