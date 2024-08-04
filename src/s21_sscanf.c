#include "s21_string.h"

static int check_nan_inf_ss(char *str, char *buffer);
static int cmp_pat(const char *buff, const char *pat);
static int chek_if_float(parser_struct2 *parser, char *buffer);

static int check_exp(const char *buffer);
static long double check_atof(const char *buffer);
static long double process_exp(long double res, const char *buffer);
static int check_nan_inf(const char *buffer);
static long double return_nan_inf(const char *buffer);
static int cmp_with_case(const char *buff, const char *pat);

int s21_sscanf(const char *str, const char *format, ...) {
  va_list ap;
  va_start(ap, format);

  parser_struct2 parser;
  parser.str = str;
  parser.str_count = 0;
  int frm_count = 0;
  parser.parsing_success = 0;
  parser.length_flag = 0;

  int success_check = 0;

  parser.error_flag = 0;
  parser.width = 0;
  parser.percent_flag = 0;
  parser.asterix_flag = 0;
  parser.space_flag = 0;
  char *first_ch = (char *)parser.str;

  if (checkline((char *)parser.str) == 1) {
    parser.error_flag = 1;
    parser.parsing_success = -1;
  }
  if (checkline((char *)format) == 1) {
    parser.error_flag = 1;
    parser.parsing_success = 0;
  }
  while (format[frm_count] && parser.error_flag != 1) {
    space_check(&parser, format, &frm_count);
    if (format[frm_count] == '%') {
      frm_count++;

      width_process(&parser, format + frm_count, &frm_count);

      h_l_L_parcer(&parser, format + frm_count, &frm_count);

      parser.current_flag = prepare_spec(format + frm_count);

      if (parser.current_flag.type == 'n') {
        parser.str_count = parser.str - first_ch;
      }

      success_check = parser.parsing_success;

      str_parser(&parser, ap);

      parser.error_flag = reading_success_check(&parser, success_check);
    }

    frm_count++;

    parser.length_flag = 0;
    parser.asterix_flag = 0;
    parser.space_flag = 0;
  }

  va_end(ap);

  return parser.parsing_success;  // parsing_success return
}

int s21_pow(int dec, int base) {
  if (base == 0)
    dec = 1;
  else {
    for (int i = 1; i < base; i++) {
      dec *= dec;
    }
  }
  return dec;
}

type_flag_struct prepare_spec(const char *format) {
  type_flag_struct flag;

  flag.type = *format;
  return flag;
}
_Bool checkline(char *line) {
  _Bool result = 1;
  if (line != NULL) {
    int counter = 0;
    while (line[counter] != '\0' && result == 1) {
      if (check_space(line[counter]) == 0) {
        result = 0;
      } else {
        counter++;
      }
    }
  }

  return result;
}
void space_check(parser_struct2 *parser, const char *format, int *counter) {
  while (format[*counter] != '\0' && *parser->str != '\0') {
    while (check_space(format[*counter]) == 1) {
      (*counter)++;
      while (check_space(*parser->str) == 1) {
        parser->str++;
      }
    }

    if (format[*counter] == '%' && format[*counter + 1] != '%') {
      break;
    }
    if (format[*counter] == '%' && format[*counter + 1] == '%') {
      (*counter)++;
    }

    if (format[*counter] == *parser->str) {
      (*counter)++;
      parser->str++;

    } else {
      parser->error_flag = 1;
      break;
    }
  }
}
_Bool check_space(char i) {
  _Bool result = 0;
  if (i == ' ' || i == '\n' || i == '\t') {
    result = 1;
  }

  return result;
}
_Bool reading_success_check(
    parser_struct2 *parser,
    int success_check) {  // func dlia proverki na udachnoe schitivanie
  _Bool flag = 0;
  if (success_check == parser->parsing_success &&
      parser->current_flag.type != 'n' && parser->asterix_flag != 1) {
    flag = 1;
    parser->str_count = 0;  // Nado podumat kak obnulat schetchick pri oshibke
  }
  return flag;
}

void h_l_L_parcer(parser_struct2 *parser, const char *format, int *frm_count) {
  switch (*format) {
    case 'h':
      parser->length_flag = LGTH_F_h;
      *frm_count = *frm_count + 1;
      if (*(format + 1) == 'h') {
        *frm_count = *frm_count + 1;
      }
      break;
    case 'l':
      parser->length_flag = LGTH_F_l;
      *frm_count = *frm_count + 1;
      if (*(format + 1) == 'l') {
        *frm_count = *frm_count + 1;
      }
      break;
    case 'L':
      parser->length_flag = LGTH_F_L;
      *frm_count = *frm_count + 1;
      break;
  }
}

void cleaner(parser_struct2 *parser) {
  while (*parser->str == ' ' || *parser->str == '\t') {
    parser->str++;
  }
}

void str_parser(parser_struct2 *parser, va_list ap) {
  switch (parser->current_flag.type) {
    case 'c':
      spec_c(parser, ap);
      parser->percent_flag = 0;
      break;

    case 'd':
      cleaner(parser);
      spec_d(parser, ap);
      parser->percent_flag = 0;
      break;

    case 'i':
      cleaner(parser);
      spec_i(parser, ap);
      parser->percent_flag = 0;
      break;

    case 'E':
    case 'e':
    case 'G':
    case 'g':
    case 'f':
      cleaner(parser);
      spec_eEgGf(parser, ap);
      parser->percent_flag = 0;
      break;

    case 'o':
      cleaner(parser);
      spec_o(parser, ap);
      parser->percent_flag = 0;
      break;

    case 's':
      spec_s(parser, ap);
      break;

    case 'u':
      cleaner(parser);
      spec_u(parser, ap);
      parser->percent_flag = 0;
      break;

    case 'x':
    case 'X':
      cleaner(parser);
      spec_xX(parser, ap);
      parser->percent_flag = 0;
      break;

    case 'p':
      cleaner(parser);
      spec_p(parser, ap);
      parser->percent_flag = 0;

      break;

    case 'n':
      spec_n(parser, ap);
      break;

    case '%':
      parser->percent_flag = 1;
      break;

    default:
      break;
  }
}

void spec_eEgGf(parser_struct2 *parser, va_list ap) {
  init_types_eEgGf types = {0};

  char buffer[1000] = {0};

  init_eEgGf(parser, &types, ap);

  buffer_maker_eEgGf(parser, buffer);

  if (parser->error_flag == 0) {
    result_eEgGf(parser, &types, buffer);
  }
}

void spec_c(parser_struct2 *parser, va_list ap) {
  if (parser->asterix_flag != 1) {
    char *arg;
    arg = va_arg(ap, char *);

    if (percent_helper(parser) == 0) {
      *arg = *parser->str;

      parser->parsing_success++;
    }
  }
  parser->str++;
}
void spec_s(parser_struct2 *parser, va_list ap) {
  char *arg;
  if (parser->asterix_flag != 1) {
    arg = va_arg(ap, char *);
  }
  // добавить проверку на length_flag из parser_struct2 !!!
  char buffer[1024] = {'\0'};

  int i = 0;
  if (percent_helper(parser) == 0) {
    while (*parser->str != '\n' && *parser->str != '\t' &&
           *parser->str != ' ' && *parser->str != '\0') {
      buffer[i] = *parser->str;
      width_implementation(parser, buffer, i);
      parser->str++;
      i++;
    }

    buffer[i] = '\0';
    if (checkline(buffer) == 1) {
      parser->error_flag = 1;
    } else {
      if (parser->asterix_flag != 1) {
        s21_strcpy(arg, buffer);
        parser->parsing_success++;
      }
    }
  }
}

void spec_n(parser_struct2 *parser, va_list ap) {
  if (parser->asterix_flag != 1) {
    int *arg = 0;
    arg = va_arg(ap, int *);

    if (arg == NULL) {
      parser->error_flag = 1;
    }
    if (parser->error_flag != 1) {
      *arg = parser->str_count;
    }
  }
}

void spec_d(parser_struct2 *parser, va_list ap) {
  init_types_d_i types = {0};

  char buffer[1000] = {0};

  init_d_i(parser, &types, ap);

  buffer_maker_d_u_o(parser, buffer);

  if (parser->error_flag == 0) {
    result_d_i(parser, &types, buffer);
  }
}

void spec_u(parser_struct2 *parser, va_list ap) {
  init_types_u_o_xX types = {0};
  char buffer[1000] = {0};
  init_u_o_xX(parser, &types, ap);
  buffer_maker_d_u_o(parser, buffer);
  if (parser->error_flag == 0) {
    result_u_o_xX(parser, &types, buffer);
  }
}

void spec_i(parser_struct2 *parser, va_list ap) {
  init_types_d_i types = {0};
  char buffer[1000] = {0};
  init_d_i(parser, &types, ap);

  buffer_maker_i(parser, buffer);
  if (parser->error_flag == 0) {
    result_d_i(parser, &types, buffer);
  }
}

void spec_o(parser_struct2 *parser, va_list ap) {
  init_types_u_o_xX types = {0};
  char buffer[1000] = {0};
  init_u_o_xX(parser, &types, ap);
  buffer_maker_d_u_o(parser, buffer);
  if (parser->error_flag == 0) {
    result_u_o_xX(parser, &types, buffer);
  }
}

void spec_xX(parser_struct2 *parser, va_list ap) {
  init_types_u_o_xX types = {0};
  char buffer[1000] = {0};
  init_u_o_xX(parser, &types, ap);
  buffer_maker_i_xX(parser, buffer);
  if (parser->error_flag == 0) {
    result_u_o_xX(parser, &types, buffer);
  }
}

int check_i(parser_struct2 *parser) {
  int result = 10;
  int counter = 0;
  if (parser->error_flag != 1) {
    if (parser->str[counter] == '+' || parser->str[counter] == '-') {
      counter++;
    }
    if (parser->str[counter] == '0' &&
        (parser->str[counter + 1] == 'x' || parser->str[counter + 1] == 'X')) {
      result = 16;
    }
    if (parser->str[counter] == '0' &&
        (parser->str[counter + 1] != 'x' && parser->str[counter + 1] != 'X')) {
      result = 8;
    }
  }
  return result;
}
void init_u_o_xX(parser_struct2 *parser, init_types_u_o_xX *types, va_list ap) {
  if (parser->asterix_flag != 1) {
    if (parser->length_flag == LGTH_F_h) {
      types->arg1 = va_arg(ap, unsigned short int *);
      if (types->arg1 == NULL) {
        parser->error_flag = 1;
        types->arg1 = 0;
      }

    } else if (parser->length_flag == LGTH_F_l) {
      types->arg2 = va_arg(ap, unsigned long int *);
      if (types->arg2 == NULL) {
        parser->error_flag = 1;
        types->arg2 = 0;
      }

    } else if (parser->length_flag == 0 || parser->length_flag == LGTH_F_L) {
      types->arg = va_arg(ap, unsigned int *);
      if (types->arg == NULL) {
        parser->error_flag = 1;
        types->arg = 0;
      }
    }
  }
}

void init_d_i(parser_struct2 *parser, init_types_d_i *types, va_list ap) {
  if (parser->asterix_flag != 1) {
    if (parser->length_flag == LGTH_F_h) {
      types->arg1 = va_arg(ap, short int *);
      if (types->arg1 == NULL) {
        parser->error_flag = 1;
        types->arg1 = 0;
      }

    } else if (parser->length_flag == LGTH_F_l) {
      types->arg2 = va_arg(ap, long int *);
      if (types->arg2 == NULL) {
        parser->error_flag = 1;
        types->arg2 = 0;
      }

    } else if (parser->length_flag == 0 || parser->length_flag == LGTH_F_L) {
      types->arg = va_arg(ap, int *);
      if (types->arg == NULL) {
        parser->error_flag = 1;
        types->arg = 0;
      }
    }
  }
}

void init_eEgGf(parser_struct2 *parser, init_types_eEgGf *types, va_list ap) {
  if (parser->asterix_flag != 1) {
    if (parser->length_flag == LGTH_F_l) {
      types->arg1 = va_arg(ap, double *);
      if (types->arg1 == NULL) {
        parser->error_flag = 1;
        types->arg1 = 0;
      }

    } else if (parser->length_flag == LGTH_F_L) {
      types->arg2 = va_arg(ap, long double *);
      if (types->arg2 == NULL) {
        parser->error_flag = 1;
        types->arg2 = 0;
      }

    } else if (parser->length_flag == 0 || parser->length_flag == LGTH_F_h) {
      types->arg = va_arg(ap, float *);
      if (types->arg == NULL) {
        parser->error_flag = 1;
        types->arg = 0;
      }
    }
  }
}

void result_u_o_xX(parser_struct2 *parser, init_types_u_o_xX *types,
                   char *buffer) {
  int rad = 0;
  if (parser->current_flag.type == 'o') {
    rad = 8;
  } else if (parser->current_flag.type == 'x' ||
             parser->current_flag.type == 'X') {
    rad = 16;
  }
  if (parser->asterix_flag != 1) {
    if (parser->length_flag == LGTH_F_h) {
      *types->arg1 = (unsigned short int)strtol(buffer, NULL, rad);
    } else if (parser->length_flag == LGTH_F_l) {
      *types->arg2 = (unsigned long int)strtol(buffer, NULL, rad);
    }
    /* else if (parser->length_flag == LGTH_F_hh) {
       *types->arg3 = (unsigned char)strtol(buffer, NULL, rad);
     } else if (parser->length_flag == LGTH_F_ll) {
       *types->arg4 = (unsigned long long int)strtol(buffer, NULL, rad);
     } */
    else {
      *types->arg = (unsigned int)strtol(buffer, NULL, rad);
    }
    parser->parsing_success++;
  }
}

void result_d_i(parser_struct2 *parser, init_types_d_i *types, char *buffer) {
  if (parser->asterix_flag != 1) {
    if (parser->length_flag == LGTH_F_h) {
      *types->arg1 = (short int)strtol(buffer, NULL, 0);

    } else if (parser->length_flag == LGTH_F_l) {
      *types->arg2 = (long int)strtol(buffer, NULL, 0);

    }
    /*else if (parser->length_flag == LGTH_F_hh) {
      *types->arg3 = (signed char)strtol(buffer, NULL, 0);
    } else if (parser->length_flag == LGTH_F_ll) {
      *types->arg3 = (long long int)strtol(buffer, NULL, 0);
    }*/
    else {
      *types->arg = (int)strtol(buffer, NULL, 0);
    }
    parser->parsing_success++;
  }
}

void result_eEgGf(parser_struct2 *parser, init_types_eEgGf *types,
                  char *buffer) {
  if (parser->asterix_flag != 1) {
    if (parser->length_flag == LGTH_F_l) {
      *types->arg1 = (double)s21_strtold(buffer);

    } else if (parser->length_flag == LGTH_F_L) {
      *types->arg2 = s21_strtold(buffer);

    } else {
      *types->arg = (float)s21_strtold(buffer);
    }
    parser->parsing_success++;
  }
}

void buffer_maker_d_u_o(parser_struct2 *parser, char *buffer) {
  if (parser->error_flag != 1) {
    int i = 0;
    char for_o = '9';

    if (parser->current_flag.type == 'o') {
      for_o = '7';
    }

    if (percent_helper(parser) == 0) {
      while ((*parser->str >= '0' && *parser->str <= for_o) ||
             ((i == 0) && (*parser->str == '+' || *parser->str == '-'))) {
        buffer[i] = *parser->str;

        width_implementation(parser, buffer, i);

        parser->str++;
        i++;
      }

      if (s21_strlen(buffer) == 0) {
        parser->error_flag = 1;
      }
      if (s21_strlen(buffer) == 1 && (buffer[0] == '-' || buffer[0] == '+')) {
        parser->error_flag = 1;
      }
    }
    parser->str = parser->str - (i - s21_strlen(buffer));
  }
}
void buffer_maker_i(parser_struct2 *parser, char *buffer) {
  int check = 0;
  int i = 0;
  check = check_i(parser);
  if (percent_helper(parser) == 0) {
    if (check == 16) {
      while ((*parser->str >= '0' && *parser->str <= '9') ||
             (*parser->str >= 'a' && *parser->str <= 'f') ||
             (*parser->str >= 'A' && *parser->str <= 'F') ||
             (*parser->str == '+' || *parser->str == '-') ||
             (*parser->str == 'x' || *parser->str == 'X')) {
        buffer[i] = *parser->str;
        width_implementation(parser, buffer, i);
        parser->str++;
        i++;
      }
    }
    if (check == 8) {
      while ((*parser->str >= '0' && *parser->str <= '7') ||
             ((i == 0) && (*parser->str == '+' || *parser->str == '-'))) {
        buffer[i] = *parser->str;

        width_implementation(parser, buffer, i);

        parser->str++;
        i++;
      }
    }
    if (check == 10) {
      while ((*parser->str >= '0' && *parser->str <= '9') ||
             ((i == 0) && (*parser->str == '+' || *parser->str == '-'))) {
        buffer[i] = *parser->str;

        width_implementation(parser, buffer, i);

        parser->str++;
        i++;
      }
    }
    if (s21_strlen(buffer) == 0) {
      parser->error_flag = 1;
    }
    if (s21_strlen(buffer) == 1 && (buffer[0] == '-' || buffer[0] == '+')) {
      parser->error_flag = 1;
    }
  }
  parser->str = parser->str - (i - s21_strlen(buffer));
}

void buffer_maker_i_xX(parser_struct2 *parser, char *buffer) {
  if (parser->error_flag != 1) {
    int i = 0;
    if (percent_helper(parser) == 0) {
      while ((*parser->str >= '0' && *parser->str <= '9') ||
             (*parser->str >= 'a' && *parser->str <= 'f') ||
             (*parser->str >= 'A' && *parser->str <= 'F') ||
             (*parser->str == '+' || *parser->str == '-') ||
             (*parser->str == 'x' || *parser->str == 'X')) {
        buffer[i] = *parser->str;
        width_implementation(parser, buffer, i);
        parser->str++;
        i++;
      }

      if (s21_strlen(buffer) == 0) {
        parser->error_flag = 1;
      }
      if (s21_strlen(buffer) == 1 && (buffer[0] == '-' || buffer[0] == '+')) {
        parser->error_flag = 1;
      }
    }
    parser->str = parser->str - (i - s21_strlen(buffer));
  }
}

static int cmp_pat(const char *buff, const char *pat) {
  int found = 0;
  int counter = 0;
  int len = (int)s21_strlen(pat);
  for (int j = 0; j < len; j++) {
    if ((buff[j] == (pat[j] - 'A') + 'a') ||
        (buff[j] == (pat[j] - 'a') + 'A') || pat[j] == buff[j]) {
      counter++;
    }
    if (len == counter) {
      found = 1;
      break;
    }
  }
  return found;
}

static int check_nan_inf_ss(char *str, char *buffer) {
  int sign = 0;

  if (*str == '+') {
    sign = 1;
  } else if (*str == '-') {
    sign = 2;
  }

  char *ptr = (sign == 0) ? str : str + 1;

  int test1 = cmp_pat(ptr, "inf");
  int test2 = cmp_pat(ptr, "nan");

  if (test1 == 1) {
    if (sign == 0) {
      s21_strncpy(buffer, str, 3);
      buffer[3] = '\0';
      str += 3;
    } else {
      s21_strncpy(buffer, str, 4);
      buffer[4] = '\0';
      str += 4;
    }
  }

  if (test2 == 1) {
    if (sign == 0) {
      s21_strncpy(buffer, str, 3);
      buffer[3] = '\0';
      str += 3;
    } else {
      s21_strncpy(buffer, str, 4);
      buffer[4] = '\0';
      str += 4;
    }
  }
  return (test1 || test2);
}

int chek_if_float(parser_struct2 *parser, char *buffer) {
  int i = 0;
  int isSinglePoint = 0;
  int isSingleE = 0;
  int inf_nan_flag = check_nan_inf_ss((char *)parser->str, buffer);

  if (!((*parser->str >= '0' && *parser->str <= '9') ||
        (*parser->str == '+' || *parser->str == '-') ||
        (*parser->str == '.' && isSinglePoint < 1) || inf_nan_flag)) {
    parser->error_flag = 1;
  } else if (!inf_nan_flag) {
    if (*parser->str == '.') isSinglePoint++;
    buffer[i] = *parser->str;
    width_implementation(parser, buffer, i);
    parser->str++;
    i++;
  }

  while ((*parser->str >= '0' && *parser->str <= '9') ||
         ((*(parser->str - 1) == 'e' || *(parser->str - 1) == 'E') &&
          (*parser->str == '+' || *parser->str == '-')) ||
         ((*parser->str == 'e' || *parser->str == 'E') &&
          (isSingleE < 1 && *(parser->str - 1) != '.')) ||
         (*parser->str == '.' && isSinglePoint < 1)) {
    if (*parser->str == 'E' || *parser->str == 'e') isSingleE++;
    if (*parser->str == '.') isSinglePoint++;

    buffer[i] = *parser->str;

    width_implementation(parser, buffer, i);

    parser->str++;
    i++;
  }
  return i;
}

void buffer_maker_eEgGf(parser_struct2 *parser, char *buffer) {
  int float_length = 0;

  if (parser->error_flag != 1) {
    if (percent_helper(parser) == 0) {
      float_length = chek_if_float(parser, buffer);

      if (s21_strlen(buffer) == 0) {
        parser->error_flag = 1;
      }
      if (s21_strlen(buffer) == 1 && (buffer[0] == '-' || buffer[0] == '+')) {
        parser->error_flag = 1;
      }
    }

    parser->str = parser->str - (float_length - s21_strlen(buffer));
  }
}

void spec_p(parser_struct2 *parser, va_list ap) {
  char buffer[1000] = {0};
  void *arg;
  unsigned long int *tmp = 0;
  if (parser->asterix_flag != 1) {
    arg = va_arg(ap, void *);
    tmp = (unsigned long int *)arg;
  }

  buffer_maker_i_xX(parser, buffer);

  if (parser->error_flag != 1 && parser->asterix_flag != 1) {
    *tmp = (unsigned long int)strtol(buffer, NULL, 16);
    parser->parsing_success++;
  }
}

_Bool percent_helper(parser_struct2 *parser) {
  _Bool result = 0;
  if (parser->percent_flag == 1 && parser->str[0] != '%') {
    parser->error_flag = 1;
    result = 1;
  } else {
    if (parser->percent_flag == 1 && parser->str[0] == '%') {
      parser->str_count++;
      parser->str++;
    }
  }
  return result;
}
_Bool width_process(parser_struct2 *parser, const char *format,
                    int *frm_count) {
  _Bool error = 0;
  char buffer[1000] = {0};
  int counter = 0;
  if (format[counter] == '*') {
    *frm_count = *frm_count + 1;
    parser->asterix_flag = 1;
  }
  while (format[counter] >= '0' && format[counter] <= '9') {
    buffer[counter] = format[counter];
    counter++;
    *frm_count = *frm_count + 1;
  }
  parser->width = atoi(buffer);

  return error;
}

void width_implementation(parser_struct2 *parser, char *buffer, int counter) {
  if (parser->width != 0 && counter >= parser->width) {
    buffer[counter] = '\0';
  }
}

// _______________ S T R T O L D _______________

long double s21_strtold(const char *buffer) {
  long double res = 0.0;
  int includes_inf_nan = check_nan_inf(buffer);

  if (!includes_inf_nan) {
    res = check_atof(buffer);

    if (check_exp(buffer)) {
      res = process_exp(res, buffer);
    }
  }
  return (includes_inf_nan) ? return_nan_inf(buffer) : res;
}

static int cmp_with_case(const char *buff, const char *pat) {
  int found = 0;
  int len = (int)s21_strlen(pat);
  for (int i = 0; buff[i] && !found; i++) {
    int counter = 0;
    for (int j = 0; j < len; j++) {
      if ((buff[i] == (pat[j] - 'A') + 'a') ||
          (buff[i] == (pat[j] - 'a') + 'A') || pat[j] == buff[i]) {
        counter++;
        i++;
      }
      if (len == counter) {
        found = 1;
        break;
      }
    }
  }

  return found;
}

static int check_nan_inf(const char *buffer) {
  int res = 0;

  int test1 = cmp_with_case(buffer, "-inf");
  int test2 = cmp_with_case(buffer, "+inf");
  int test3 = cmp_with_case(buffer, "-nan");
  int test4 = cmp_with_case(buffer, "+nan");
  if (test1 || test2 || test3 || test4) {
    res = 1;
  }
  return res;
}

static long double return_nan_inf(const char *buffer) {
  long double res = 0;

  if (buffer[0] == '-' && (buffer[1] == 'I' || buffer[1] == 'i')) {
    res = INFINITY * (-1);
  }

  if (buffer[0] == '+' && (buffer[1] == 'I' || buffer[1] == 'i')) {
    res = INFINITY;
  }

  if (buffer[0] == 'I' || buffer[0] == 'i') {
    res = INFINITY;
  }

  if ((buffer[0] == '-' && (buffer[1] == 'N' || buffer[1] == 'n')) ||
      (buffer[0] == '+' && (buffer[1] == 'N' || buffer[1] == 'n'))) {
    res = NAN;
  }

  if (buffer[0] == 'N' || buffer[0] == 'n') {
    res = NAN;
  }

  return res;
}

static long double process_exp(long double res, const char *buffer) {
  char sign = '+';
  int expon = 0;

  for (char *p = (char *)buffer; *p; p++) {
    if (*p == 'e' || *p == 'E') {
      if (*(p + 1) == '-' || *(p + 1) == '+') {
        sign = *(p + 1);
        expon = s21_atoi(p + 2);
      } else {
        expon = s21_atoi(p + 1);
      }
    }
  }

  while (expon) {
    if (sign == '-') {
      res /= 10.0;
    } else {
      res *= 10.0;
    }
    expon--;
  }

  return res;
}

static int check_exp(const char *buffer) {
  int res = 0;

  for (char *p = (char *)buffer; *p; p++) {
    if (s21_strspn(p, "eE")) {
      res = 1;
      break;
    }
  }

  return res;
}

static long double check_atof(const char *buffer) {
  long double frac = 0.0;
  char *p = (char *)buffer;
  int minus_flag = (*p == '-');
  if (*p == '-' || *p == '+') p++;

  long double res = s21_atoi(p);

  while (s21_isdigit(*p)) p++;

  if (*p == '.') {
    p++;
    int trailing_zeros = s21_strspn(p, "0");
    frac = s21_atoi(p);
    int tmp = (int)frac;
    while (tmp) {
      frac /= 10.0;
      tmp /= 10;
    }
    while (trailing_zeros) {
      frac /= 10.0;
      trailing_zeros--;
    }
  }

  res += frac;

  return minus_flag ? -res : res;
}
// _______________ A T O I ______________
int s21_atoi(const char *str_carriage) {
  int result = 0;
  int sign = 1;
  int overflow = 0;

  while (*str_carriage == ' ') str_carriage++;

  if (*str_carriage == '-') {
    str_carriage++;
    sign = -1;
  }

  if (*str_carriage == '+') {
    str_carriage++;
  }

  while (*str_carriage && *str_carriage >= '0' && *str_carriage <= '9') {
    result = result * 10 + (*str_carriage - '0');
    if (result < 0) {
      overflow = 1;
      break;
    }
    str_carriage++;
  }
  if (overflow)
    result = sign > 0 ? INT32_MAX : INT32_MIN;
  else
    result *= sign;

  return result;
}

// _______________ I S D I G I T ______________
int s21_isdigit(char c) {
  if (c >= '0' && c <= '9') {
    return 1;
  }
  return 0;
}