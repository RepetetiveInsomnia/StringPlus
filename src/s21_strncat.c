//| 7 | char *strncat(char *dest, const char *src, size_t n) | Добавляет строку,
// на которую указывает src, в конец строки, на которую указывает dest, длиной
// до
// // n символов. |
#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int dest_index = s21_strlen(dest);
  unsigned int src_index = 0;
  for (; src[src_index] && src_index < n; src_index++)
    dest[dest_index + src_index] = src[src_index];
  return dest;
}
