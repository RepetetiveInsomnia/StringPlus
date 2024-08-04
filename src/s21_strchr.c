#include "s21_string.h"

char* s21_strchr(const char* str, int c) {
  while (*str && (*str != (char)c)) str++;
  return (*str || ((*str == 0) && (c == 0))) ? (char*)str : 0;
}
