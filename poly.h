#ifndef POLY_H
#define POLY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct term polynomial;

struct term {
  int coeff;
  unsigned int exp;
  struct term *next;
};

void poly_destroy(polynomial *eqn);

void poly_print(const polynomial *eqn);

struct term *poly_create_term(int coeff, unsigned int exp);

#endif
