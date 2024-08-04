#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *t_dest = (char *)dest;
  const char *t_src = (const char *)src;
  if (dest < src) {
    while (n-- > 0) {
      *t_dest++ = *t_src++;
    }
  } else {
    t_dest = t_dest + n;
    t_src = t_src + n;
    while (n-- > 0) {
      *--t_dest = *--t_src;
    }
  }
  return dest;
}
