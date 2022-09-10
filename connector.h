#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma once

// ticket determines where to put output
typedef struct tckt_ {
	void *in;
	void *(*out)(void *);
} tckt_;

// base which connector extends
typedef struct cnct_ {
	unsigned length: 5;
	unsigned start:  5;
	unsigned diff:   6;
} cnct_;

// numbers in descending order, terminating in 0
typedef struct block {
	uint8_t step;
	char parts[];
} block;

// connector attaches stacks
typedef struct connector {
	cnct_ base;
	block *b;
	char parts[];
} connector;

uint8_t const primes[55];

// make ticket
tckt_ *set(void *);
// find blocks
tckt_ *stack(tckt_ *);
// find connectors
void search(tckt_ *);
