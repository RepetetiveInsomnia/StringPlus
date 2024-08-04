#include "s21_string.h"

char* s21_strpbrk(const char* str1, const char* str2) {
  char* f_str1 = (char*)str1;
  char* f_str2 = (char*)str2;
  int length = s21_strlen(str2), check = 1;
  char* result = s21_NULL;
  while (check && *f_str1) {
    for (int count = 0; length > count && check == 1; count++) {
      if (f_str2[count] == *f_str1) {
        check = 0;
        result = f_str1;
      }
    }
    f_str1++;
  }
  return result;
}
