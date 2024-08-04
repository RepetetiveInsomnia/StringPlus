#include "s21_string.h"

char *s21_strtok(char str[], const char *delims) {
  static char *s_pointer;
  char *f_tok;
  if (str == s21_NULL)
    f_tok = s_pointer;
  else
    f_tok = str;
  if (f_tok != s21_NULL && *f_tok) {
    while (*f_tok && f_tok && s21_strchr(delims, *f_tok)) f_tok++;
  }
  s_pointer = f_tok;

  while (s_pointer && !s21_strchr(delims, *s_pointer)) {
    s_pointer++;
  }
  if (f_tok) {
    if (*s_pointer != '\0') {
      *s_pointer = '\0';
      s_pointer++;
    }

    if (*f_tok == '\0') f_tok = s21_NULL;
  }
  return f_tok;
}
