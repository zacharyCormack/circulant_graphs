#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma once

// ticket determines where to put output
typedef struct {
	void *in;
	void *(*out)(void *);
} tckt_;

// base which connector extends
typedef struct {
	unsigned length: 4;
	unsigned start:  7;
	unsigned diff:   6;
} cnct_;

// numbers in descending order, terminating in 0
typedef struct {
	unsigned char step;
	unsigned char parts[];
} block;

// connector attaches stacks
typedef struct {
	cnct_ base;
	unsigned char parts[];
} connector;

unsigned char const primes[55];

// make ticket
tckt_ set(void *);
// find blocks
void stack(void *, tckt_ *);
// find connectors
void search(block, cnct_, tckt_);
