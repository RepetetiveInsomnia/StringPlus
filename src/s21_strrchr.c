#include "s21_string.h"

char* s21_strrchr(const char* str, int c) {
  char* p = (char*)str;
  while (*str) str++;
  while (*p && *str != c) --str, ++p;
  return c == *str ? (char*)str : s21_NULL;
}
