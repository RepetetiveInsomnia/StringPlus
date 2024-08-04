// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент s
#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  void *search_char = s21_NULL;
  for (s21_size_t i = 0; i < n && ptr; i++) {
    if (*ptr == (unsigned char)c) {
      search_char = ptr;
      break;
    }
    ptr++;
  }
  return search_char;
}
