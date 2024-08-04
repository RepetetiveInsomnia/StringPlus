// Сравнивает строку, на которую указывает str1 со строкой, на которую указывает
// str2 (функция возвращает 0,если str1=str2, >1 если str1>str2 и <1, если
// str1<str2)

#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  for (; *str1 && *str1 == *str2; str1++, str2++)
    ;
  return *str1 - *str2;
}
