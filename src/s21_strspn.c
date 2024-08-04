#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  const char *copy1, *copy2;
  for (copy1 = str1; *copy1 != '\0'; copy1++) {
    for (copy2 = str2;; copy2++) {
      if (*copy2 == '\0') {
        return (copy1 - str1);
      } else if (*copy1 == *copy2) {
        break;
      }
    }
  }
  return (copy1 - str1);
}
