#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "poly.h"

static void sort_poly(polynomial *p);
static void sort_poly(polynomial *p);

struct term *poly_create_term(int coeff, unsigned int exp)
{
	struct term *node = malloc(sizeof(*node));
	if (node) {
		node->coeff = coeff;
		node->exp = exp;
		node->next = NULL;
		node->prev = NULL;
	}
	return node;
}

void poly_destroy(polynomial * eqn)
{
	while (eqn) {
		struct term *tmp = eqn->next;
		free(eqn);
		eqn = tmp;
	}
}

void poly_print(const polynomial * eqn)
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

static unsigned int sizeof_poly(const polynomial * p)
{
	unsigned int total_size = 1;	// Add first digit in coeff
	unsigned int coeff = abs(p->coeff);
	unsigned int exp = p->exp;

	while (coeff > 9) {	// Add number of digits in coeff
		coeff /= 10;
		++total_size;
	}
	if (p->coeff < 0) {
		++total_size;	// Add '-'
	}
	if (p->exp > 0) {
		++total_size;	// Add 'x'
	}
	if (p->exp > 1) {
		total_size += 2;	// Add '^' + first digit of exp
		while (exp > 9) {	// Add number of digits in exp
			exp /= 10;
			++total_size;
		}
	}
	return (total_size);
}

char *poly_to_string(const polynomial *p)
{
	// Syntax modified from Liam Echlin's whiteboard demo
	if (!p) {
		return (NULL);
	}

	char *end_poly_str = malloc(1);
	end_poly_str[0] = '\0';

	while (p) {
		while (!p->coeff) {
			p = p->next;
		}
		unsigned int poly_size = sizeof_poly(p);
		poly_size += 2;	// plus space for " +/-"
		char *curr_poly_str = malloc(poly_size + 1);	// Poly size plus '\0'
		snprintf(curr_poly_str, poly_size + 1, "%dx^%d", p->coeff,
			 p->exp);
		end_poly_str =
		    realloc(end_poly_str, strlen(end_poly_str) + poly_size + 1);
		if (!p->next) {
			snprintf(curr_poly_str, poly_size + 1, "%dx^%d",
				 p->coeff, p->exp);
			strncat(end_poly_str, curr_poly_str,
				strlen(curr_poly_str));
			free(curr_poly_str);
			break;
		}
		snprintf(curr_poly_str, poly_size + 1, "%dx^%d %s", p->coeff,
			 p->exp, p->next->coeff > 0 ? "+" : "");
		strncat(end_poly_str, curr_poly_str, strlen(curr_poly_str));
		free(curr_poly_str);
		p = p->next;
	}
	return (end_poly_str);
}

polynomial *poly_add(const polynomial * a, const polynomial * b)
{
	// Syntax taken from Liam Echlin

	polynomial *chain = NULL;
	polynomial **curr = &chain;
	polynomial *last = NULL;

	if (!a || !b) {
		return (NULL);
	}
	while (a && b) {
		if (a->exp > b->exp) {
			*curr = poly_create_term(a->coeff, a->exp);
			a = a->next;
		} else if (a->exp < b->exp) {
			*curr = poly_create_term(b->coeff, b->exp);
			b = b->next;
		} else {
			int coeff_total = a->coeff + b->coeff;
			*curr = poly_create_term(coeff_total, a->exp);
			a = a->next;
			b = b->next;
		}
		curr = &(*curr)->next;
	}
	while (a) {
		*curr = poly_create_term(a->coeff, a->exp);
		(*curr)->prev = last;
		last = *curr;
		a = a->next;
		curr = &(*curr)->next;
	}
	while (b) {
		*curr = poly_create_term(b->coeff, b->exp);
		b = b->next;
		(*curr)->prev = last;
		last = *curr;
		curr = &(*curr)->next;
	}
  sort_poly(chain);
	return chain;
}

polynomial *poly_sub(const polynomial * a, const polynomial * b)
{
	// Syntax taken from Liam Echlin

	polynomial *chain = NULL;
	polynomial **curr = &chain;
	polynomial *last = NULL;

	if (!a || !b) {
		return (NULL);
	}
	while (a && b) {
		if (a->exp > b->exp) {
			*curr = poly_create_term(a->coeff, a->exp);
			a = a->next;
		} else if (a->exp < b->exp) {
			*curr = poly_create_term((-1) * b->coeff, b->exp);
			b = b->next;
		} else {
			int coeff_total = a->coeff - b->coeff;
			*curr = poly_create_term(coeff_total, a->exp);
			a = a->next;
			b = b->next;
		}
		curr = &(*curr)->next;
	}
	while (a) {
		*curr = poly_create_term(a->coeff, a->exp);
		(*curr)->prev = last;
		last = *curr;
		a = a->next;
		curr = &(*curr)->next;
	}
	while (b) {
		*curr = poly_create_term((-1) * b->coeff, b->exp);
		b = b->next;
		(*curr)->prev = last;
		last = *curr;
		curr = &(*curr)->next;
	}
  sort_poly(chain);
	return chain;
}

bool poly_equal(const polynomial *a, const polynomial *b) 
{
  if (!a || !b) {
    return(false);
  }
  while(a && b) {
    if (a->coeff != b->coeff || a->exp != b->exp) {
      return(false);
    }
    a = a->next;
    b = b->next;
  }
  if(a || b) {
    return(false);
  }
  return(true);
}

double poly_eval(const polynomial *p, double x)
{
  if (!p) {
    return(0.0);
  }
  double total = 0.0;
  while(p) {
    total += (p->coeff * (pow(x, p->exp)));
    p = p->next;
  }
  return(total);
}
static void swap_poly(polynomial *p) {
// Swaps a given polynomial's data with the previous polynomial's data
// if the given polynomial p has a larger exponent than it.
    int tmp_coeff = p->prev->coeff;
    unsigned int tmp_exp = p->prev->exp;
    p->prev->coeff = p->coeff;
    p->prev->exp = p->exp;
    p->coeff = tmp_coeff;
    p->exp = tmp_exp;
    return;
}

static void sort_poly(polynomial *p) 
{
  if (!p) {
    return;
  }
  // Code based off of from Liam Echlin's insertion sort demo
  unsigned int sz = 0;

  polynomial *p_tmp = p;
  while(p_tmp) {
    ++sz;
    p_tmp = p_tmp->next;
  }

  for (unsigned int i = 1; i < sz; ++i) {
    unsigned int idx = i;
     while(idx > 0 && p->prev && p->exp > p->prev->exp) {
      swap_poly(p);
      --idx;
    }
    ++i;
  }
  return;
}
