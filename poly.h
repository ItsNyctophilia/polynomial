#ifndef POLY_H
#define POLY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct term polynomial;

struct term {
  int coeff;
  unsigned int exp;
  struct term *next;
  struct term *prev;
};

void poly_destroy(polynomial *eqn);

void poly_print(const polynomial *eqn);

char *poly_to_string(const polynomial *p);

polynomial *poly_add(const polynomial *a, const polynomial *b);

polynomial *poly_sub(const polynomial *a, const polynomial *b);

bool poly_equal(const polynomial *a, const polynomial *b);

double poly_eval(const polynomial *p, double x);

struct term *poly_create_term(int coeff, unsigned int exp);

#endif
