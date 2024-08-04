// Сравнивает не более первых n байтов str1 и str2
#include "s21_string.h"

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  int flg = 1;
  int result = 0;
  char* f_str1 = (char*)str1;
  char* f_str2 = (char*)str2;
  for (s21_size_t i = 0; i < n && flg;) {
    if (f_str1[i] == f_str2[i])
      i++;
    else
      result = f_str1[i] - f_str2[i], flg = 0;
  }
  return result;
}
