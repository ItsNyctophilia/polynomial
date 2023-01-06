#include <stdio.h>
#include <stdlib.h>

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
