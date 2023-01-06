#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "poly.h"
// This data type must not be renamed
// Additional fields may be added, but these existing ones must not be removed, altered,
// or reordered

// The implementation may be modified, but the signature must not be
struct term *poly_create_term(int coeff, unsigned int exp)
{
  struct term *node = malloc(sizeof(*node));
  if (node) {
    node->coeff = coeff;
    node->exp = exp;
    node->next = NULL;
  }
  return node;
}
// The implementation may be modified, but the signature must not be
void poly_destroy(polynomial *eqn)
{
  while (eqn) {
    struct term *tmp = eqn->next;
    free(eqn);
    eqn = tmp;
  }
}
// The implementation may be modified, but the signature must not be
void poly_print(const polynomial *eqn)
{
  if (!eqn) {
    return;
  }
  if (eqn->coeff) {
    printf("%c%d", eqn->coeff > 0 ? '+' : '\0', eqn->coeff);
    if (eqn->exp > 1) {
      printf("x^%d", eqn->exp);
    } else if (eqn->exp == 1) {
      printf("x");
    }
    printf(" ");
  }
  poly_print(eqn->next);
}

static unsigned int sizeof_poly(const polynomial *p) {
  unsigned int total_size = 1; // Add first digit in coeff
  unsigned int coeff = abs(p->coeff);
  unsigned int exp = p->exp;

  while (coeff > 9) { // Add number of digits in coeff
    coeff /= 10;
    ++total_size;
  }
  if (p->coeff < 0) {
    ++total_size; // Add '-'
  }
  if (p->exp > 0) {
    ++total_size; // Add 'x'
  }
  if (p->exp > 1) {
    total_size += 2; // Add '^' + first digit of exp
    while (exp > 9) { // Add number of digits in exp
       exp /= 10;
      ++total_size;
    }
  }
  return(total_size);
}

char *poly_to_string(const polynomial *p)
{
  const polynomial *curr = p;

  char *end_poly_str = malloc(1);
  end_poly_str[0] = '\0';

  while(curr) {
    if (!curr->coeff) {
      curr = curr->next;
    }
    unsigned int poly_size = sizeof_poly(p);
    char *curr_poly_str = malloc(poly_size + 1); // Poly size plus '\0'
    snprintf(curr_poly_str, poly_size + 1, "%dx^%d", p->coeff, p->exp);
    end_poly_str = realloc(end_poly_str, strlen(end_poly_str) + poly_size + 1);
    strncat(end_poly_str, curr_poly_str, strlen(curr_poly_str));
    if (curr->next && curr->coeff >= 0) {
      strcat(end_poly_str, "+"); // Add + between terms
    }
    free(curr_poly_str);
    curr = curr->next;
  }
  return(end_poly_str);
}

