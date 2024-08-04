// // | 12 | char *strncpy(char *dest, const char *src, size_t n) | Копирует до
// n
// // символов из строки, на которую указывает src, в dest. |

#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t count;
  for (count = 0; src[count] != '\0' && count < n; count++)
    dest[count] = src[count];
  while (count < n) {
    dest[count] = '\0';
    count++;
  }
  return dest;
}
