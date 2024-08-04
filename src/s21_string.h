#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFF_SIZE 512
#define N 1000

#define s21_size_t unsigned long
#define S21_NULL ((void *)0)  // константа нуля
#define s21_NULL ((void *)0)  // в некоторых функциях константа нуля такая
#define UNKNOWN "Unknown error: "
#define is_flag(ch)                                                   \
  ((ch) == '-') || ((ch) == '+') || ((ch) == ' ') || ((ch) == '#') || \
      ((ch) == '0')
//%[флаги][ширина][.точность][длина]спецификатор.
#define is_digit(ch) ((ch) >= '0' && (ch) <= '9')

#define is_length(ch) ((ch) == 'h' || (ch) == 'l' || (ch) == 'L')

#define is_specifier(ch)                                                      \
  ((ch) == 'c' || (ch) == 'd' || (ch) == 'i' || (ch) == 'e' || (ch) == 'E' || \
   (ch) == 'f' || (ch) == 'g' || (ch) == 'G' || (ch) == 'o' || (ch) == 's' || \
   (ch) == 'u' || (ch) == 'x' || (ch) == 'X' || (ch) == 'p' || (ch) == 'n' || \
   (ch) == '%')

int s21_sprintf(char *str, const char *format, ...);

int s21_sscanf(const char *str, const char *format, ...);

void *s21_memchr(
    const void *str, int c,
    s21_size_t n);  // Выполняет поиск первого вхождения символа c (беззнаковый
//     тип)
//                 // в первых n байтах строки, на которую указывает аргумент
//                 str
int s21_memcmp(const void *str1, const void *str2,
               s21_size_t n);  // Сравнивает первые n байтов str1 и str2
void *s21_memcpy(void *dest, const void *src,
                 s21_size_t n);  // Копирует n символов из src в dest
void *s21_memmove(
    void *dest, const void *src,
    s21_size_t n);  // Еще одна функция для копирования n символов из src в dest
void *s21_memset(
    void *str, int c,
    s21_size_t n);  // Копирует символ c (беззнаковый тип) в первые n
//                          //символов строки, на которую указывает аргумент str
char *s21_strcat(char *dest,
                 const char *src);  // Добавляет строку, на которую указывает
//              src, в
//                                 // конец строки, на которую указывает dest
char *s21_strncat(
    char *dest, const char *src,
    s21_size_t n);  // Добавляет строку, на которую указывает src, в конец
//                 // строки, на которую указывает dest, длиной до n символов
char *s21_strchr(
    const char *str,
    int c);  // Выполняет поиск первого вхождения символа c (беззнаковый
//              // тип) в строке, на которую указывает аргумент str
int s21_strcmp(
    const char *str1,
    const char *str2);  //  Сравнивает строку, на которую указывает str1,
//                                //  со строкой, на которую указывает str2
int s21_strncmp(
    const char *str1, const char *str2,
    s21_size_t n);  //  Сравнивает не более первых n байтов str1 и str2
char *s21_strcpy(
    char *dest,
    const char *src);  //  Копирует строку, на которую указывает src, в dest
char *s21_strncpy(
    char *dest, const char *src,
    s21_size_t n);  // Копирует до n символов из строки, на которую
//                           // указывает src, в dest
s21_size_t s21_strcspn(
    const char *str1,
    const char *str2);  // Вычисляет длину начального сегмента str1, который
//                         // полностью состоит из символов, не входящих в str2
char *s21_strerror(int errnum);
// Выполняет поиск во внутреннем массиве номера ошибки
//                   // errnum и возвращает указатель на строку с сообщением об
//                   // ошибке. Нужно объявить макросы, содержащие массивы
//                   // сообщений об ошибке для операционных систем mac и linux.
//                   // Описания ошибок есть в оригинальной библиотеке. Проверка
//                   // текущей ОС осуществляется с помощью директив

s21_size_t s21_strlen(const char *str);  // Вычисляет длину строки str, не
                                         // включая завершающий нулевой символ

char *s21_strpbrk(
    const char *str1,
    const char *str2);  // Находит первый символ в строке str1, который
//                         // соответствует любому символу, указанному в str2
char *s21_strrchr(
    const char *str,
    int c);  // Выполняет поиск последнего вхождения символа c (беззнаковый
//              // тип) в строке, на которую указывает аргумент str
s21_size_t s21_strspn(const char *str1,
                      const char *str2);  // Вычисляет длину начального сегмента
                                          //   str1,
// который полностью состоит из символов
//   str2
char *s21_strstr(
    const char *haystack,
    const char *needle);  // Находит первое вхождение всей строки needle
//                           // (не включая завершающий нулевой символ),
//                           // которая появляется в строке haystack
char *s21_strtok(char *str, const char *delim);  // Разбивает строку str на
// ряд токенов, разделенных delim
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *str, const char *trim_chars);
int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);

/*----------------------------SPRINTF------------------------------*/
typedef struct s21_FORMAT {
  int flag_minus;  // Выравнивание по левому краю
  int flag_plus;  // Заставляет предварять результат знаком + или -
  int flag_space;  // Если знак не записан, перед значением
                   // вставляется пробел.
  int flag_sharp;  // При o, x или X значению предшествуют 0, 0x или
                   //  0X соответственно, если не нуль. При с e, E и
                   //  f заставляет записанный вывод содержать
                   // десятичную точку. По умолчанию, если цифры не
                   // следуют, десятичная точка не записывается.
  int flag_zero;  // Дополняет число слева нулями (0) вместо
                  // пробелов
  int width;  // Минимальное количество печатаемых символов.
  int precision;  // Для (d, i, o, u, x, X) − точность определяет минимальное
                  // количество записываемых цифр.
  char length;    // тип переменной
  char specifier;  // спецификатор

  int sign;     // Знак + или -
  int point;    // флаг для точки
  int stop;     // флаг для '\0'
  int nulls;    // флаг для подсчета '\0'
  int returnN;  // проверка на запись '\0'
} s21_FORMAT;

int s21_sprintf(char *str, const char *format, ...);
void s21_default_precision(s21_FORMAT *parameters);
void s21_check_flag(s21_FORMAT *parameters, const char *format);
void s21_sharp_flag(s21_FORMAT *parameters, char *str);

char *strchrncat(char *str, char ch, int n, int f);
char *s21_itoa(long long value, char *str, int radix);
char *s21_ftoa(long double value, char *str, s21_size_t accuracy, int f);
char *flt_to_str(va_list *args, char *str, s21_FORMAT *parameters);
char *s21_str_to_str(va_list *args, char *str, s21_FORMAT *parameters);

char *s21_str_to_int(int *number, const char *format, va_list *input);
void s21_int_to_str(s21_FORMAT *parameters, char *str, long double number);
void s21_ul_to_str(char *str, unsigned long long number,
                   s21_FORMAT *parameters);
void s21_ol_to_str(char *str, unsigned long long number, int prefix);
void s21_hl_to_str(char *str, unsigned long long number,
                   s21_FORMAT *parameters);
void s21_wch_to_str(char *str, wchar_t *wstr, s21_size_t length);

char *s21_check_specifier(char *str, s21_size_t *str_len, va_list *input,
                          s21_FORMAT *parameters);

void s21_move_string(char *str);
void s21_make_string_flags(s21_FORMAT *parameters, char *str);
void s21_make_string_width(s21_FORMAT *parameters, char *str);
void s21_make_string_precision(s21_FORMAT *parameters, char *str);
void s21_reverse_writing(char *str);

void s21_spec_c(char *str, va_list *input, s21_FORMAT *parameters);  // Символ
void s21_spec_di(char *str, va_list *input,
                 s21_FORMAT *parameters);  // Знаковое десятичное целое число
void s21_spec_o(char *str, va_list *input,
                s21_FORMAT *parameters);  // Беззнаковое восьмеричное число
void s21_spec_u(char *str, va_list *input,
                s21_FORMAT *parameters);  // Беззнаковое десятичное целое число
void s21_spec_xX(char *str, va_list *input,
                 s21_FORMAT *parameters);  // Беззнаковое шестнадцатеричное
                                           // целое число(X - заглавные буквы)
void s21_spec_p(char *str, va_list *input,
                s21_FORMAT *parameters);  // Адрес указателя
void s21_spec_n(
    s21_size_t const *str_len,
    va_list *input);  // Количество символов, напечатанных до появления %n
void s21_spec_percentage(char *str, s21_FORMAT *parameters);  // Символ %

/*----------------------------SSCANF------------------------------*/
#define LGTH_F_h 1
#define LGTH_F_l 2
#define LGTH_F_L 3
#define LGTH_F_hh 4
#define LGTH_F_ll 5

// структура описывающая настройки форматирования отдельного спецификатора
typedef struct type_flag_struct {
  char type;
} type_flag_struct;

// struktura parcera
typedef struct parser_struct {
  type_flag_struct current_flag;
  const char *str;
  int width;
  _Bool asterix_flag;
  int str_count;
  int parsing_success;
  int length_flag;
  _Bool percent_flag;
  _Bool error_flag;
  _Bool space_flag;
  _Bool arg_flag;
} parser_struct2;

// strukturi tipov zapisi
typedef struct init_types {
  long long int *arg4;
  signed char *arg3;
  long int *arg2;
  short int *arg1;
  int *arg;
} init_types_d_i;

typedef struct init_types2 {
  unsigned long long int *arg4;
  unsigned char *arg3;
  unsigned long int *arg2;
  unsigned short int *arg1;
  unsigned int *arg;
} init_types_u_o_xX;

typedef struct init_types3 {
  long double *arg2;
  double *arg1;
  float *arg;
} init_types_eEgGf;

//********* utility sscanf functions ***************
type_flag_struct prepare_spec(
    const char *format);  // ф-ия возвращающая настройки флага

void str_parser(parser_struct2 *parser, va_list ap);

void h_l_L_parcer(parser_struct2 *parser, const char *format, int *frm_count);

_Bool reading_success_check(parser_struct2 *parser, int success_check);

int check_i(parser_struct2 *parser);
int s21_pow(int dec, int base);
_Bool checkline(char *line);
void cleaner(parser_struct2 *parser);
// int check_octal(int number);
// int from8to10(int number);
// int from16to10(char *buffer);

//******** functions for initialising ap, buffer, and writing results *******
void init_d_i(parser_struct2 *parser, init_types_d_i *types, va_list ap);

void init_u_o_xX(parser_struct2 *parser, init_types_u_o_xX *types, va_list ap);

void init_eEgGf(parser_struct2 *parser, init_types_eEgGf *types, va_list ap);

void buffer_maker_i(parser_struct2 *parser, char *buffer);

void buffer_maker_i_xX(parser_struct2 *parser, char *buffer);

void buffer_maker_d_u_o(parser_struct2 *parser, char *buffer);

void buffer_maker_eEgGf(parser_struct2 *parser, char *buffer);

void result_d_i(parser_struct2 *parser, init_types_d_i *types, char *buffer);

void result_u_o_xX(parser_struct2 *parser, init_types_u_o_xX *types,
                   char *buffer);

void result_eEgGf(parser_struct2 *parser, init_types_eEgGf *types,
                  char *buffer);

_Bool percent_helper(parser_struct2 *parser);
_Bool check_space(char i);
_Bool width_process(parser_struct2 *parser, const char *format, int *frm_count);
void width_implementation(parser_struct2 *parser, char *buffer, int counter);
void space_check(parser_struct2 *parser, const char *format, int *counter);
long double s21_strtold(const char *buffer);
int s21_atoi(const char *str_carriage);
int s21_isdigit(char c);

//************ spec functions *******************
void spec_c(parser_struct2 *parser, va_list ap);
void spec_d(parser_struct2 *parser, va_list ap);
void spec_i(parser_struct2 *parser, va_list ap);
void spec_eEgGf(parser_struct2 *parser, va_list ap);
void spec_o(parser_struct2 *parser, va_list ap);
void spec_s(parser_struct2 *parser, va_list ap);
void spec_u(parser_struct2 *parser, va_list ap);
void spec_xX(parser_struct2 *parser, va_list ap);
void spec_n(parser_struct2 *parser, va_list ap);
void spec_p(parser_struct2 *parser, va_list ap);

#endif  // SRC_S21_STRING_H_
