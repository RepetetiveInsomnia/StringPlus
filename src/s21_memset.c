#include "s21_string.h"

void *s21_memset(void *memptr, int val, s21_size_t num) {
  unsigned char *tmp = memptr;
  while (num > 0) {
    *tmp = val;
    num--;
    tmp++;
  }
  return (memptr);
}
