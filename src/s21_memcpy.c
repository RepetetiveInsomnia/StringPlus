// //| 3 | void *memcpy(void *dest, const void *src, size_t n) | Копирует n
// //символов из src в dest. |
#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *dp = dest;
  const char *sp = src;
  while (n--) *dp++ = *sp++;
  return dest;
}

// #include <strings.h>
//  int main() {
//    char string1[50] = "hello 1111";
//    char string2[50] = "world!";
//    char string3[50] = "hello 1111";
//    char string4[50] = "world!";
//    memcpy(string1, string2, 2);
//    printf("string1 = %s\n", string1);
//    string2[0] = 'q';
//    printf("string1 = %s\n", string1);
//    printf("---------\n");
//    s21_memcpy(string3, string4, 2);
//    printf("s21_string3 = %s\n", string3);
//    string4[0] = 'q';
//    printf("s21_string3 = %s\n", string3);
//  }
