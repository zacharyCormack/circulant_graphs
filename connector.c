#include"connector.h"

const uint8_t primes[] = {
	2,	3,	5,	7,	11,	13,
	17,	19,	23,	29,	31,	37,
	41,	43,	47,	53,	59,	61,
	67,	71,	73,	79,	83,	89,
	97,	101,	103,	107,	109,	113,
	127,	131,	137,	139,	149,	151,
	157,	163,	167,	173,	179,	181,
	191,	193,	197,	199,	211,	223,
	227,	229,	233,	239,	241,	251,
	0
};

// write to output space
void *wr(void *_in)
{
	printf("Writing to %p\n", _in);
	strncpy(*(void **)_in, _in+1, sizeof(void *));
	// planned to later return information input
	return NULL;
}

tckt_ *set(void *_k)
{
	tckt_ *r = malloc(sizeof(tckt_));
	r->in = _k;
	r->out = &wr;
	return r;
}

// prepare new ticket
tckt_ *pack(tckt_ *_t)
{
	tckt_ *r = malloc(sizeof(tckt_));
	void  *z = malloc(3+sizeof(connector *));

	// todo: move to main function
	printf("Connector width: ");
	scanf("%hhu", (uint8_t *)z);

	// following inputs same as to stack
	strncpy(z+1, _t->in, 2+sizeof(connector *));
	// create new output space
	*(connector **)(z+2+sizeof(connector *)) =
		malloc(sizeof(connector)+*(uint8_t *)(z));
	r->in = z;
	r->out = &wr;

	return r;
}

// check if number is prime
char cp(uint8_t _p)
{
	for (const uint8_t *ck = primes; _p>=*ck; ck++)
		if (_p == *ck) return 0;
	
	return 1;
}

// check that block is valid
char c_bk(block *_b)
{
	short s = 0;
	for (char *p = _b->parts; *p; p++)
		if (cp(*p > 0 ? *p : -*p)) return 1;
		else s += *p;
	
	return s != _b->step;
}

// check if connector is valid
char c_ct(connector *_c, block *_b)
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

tckt_ *stack(tckt_ *_t)
{
	uint8_t k = *(uint8_t *)(_t->in) - 1;
	block **o = malloc(sizeof(block *) + sizeof(block) + k + 1);
	
	*o = *(block **)(_t->in+2);
	((block *)(o+1))->step = *(uint8_t *)(_t->in+1);
	memset(((block *)(o+1))->parts, 1, k);
	((block *)(o+1))->parts[k] = 0;

	do for (char *h = ((block *)(o+1))->parts; *h; h++)
		*h = ((rand()&2)-1)*primes[rand()%30];
	while (c_bk((block *)(o+1)) && (++_t)->in);

	free(o);

	return pack(--_t);
}

void search(tckt_ *_t)
{
	uint8_t w = *(uint8_t *)(_t->in) - 1, k = *((uint8_t *)(_t->in)+1);
	block **b = malloc(sizeof(block *));
	connector **o = malloc(sizeof(connector *) + sizeof(connector) + w + 1);
	printf("%p, %p\n", _t->in, _t->in+2);
	*b = *(block **)(_t->in+2);
	*o = *(connector **)(_t->in+2+sizeof(block *));

	do {
		for (char *h = ((connector *)(o+1))->parts; *h; h++)
			*h = ((rand()&2)-1)*primes[rand()%30];

		if (c_ct((connector *)(o+1), *b)) continue;

		(*_t++->out)(o);
	} while (_t->in);

	free(o);
}
