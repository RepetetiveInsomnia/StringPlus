#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  int src_index = 0;
  for (; src[src_index]; src_index++) dest[src_index] = src[src_index];
  dest[src_index] = '\0';
  return dest;
}
