#ifndef __UTILS_STRINGUTILS
#define __UTILS_STRINGUTILS

void str_tolowercase(char *input);
void str_touppercase(char *input);
void str_trim(char *input);
void str_trim_quotes(char *input);
char *str_concatenate_words(int from, int to, char **words);

#endif // __UTILS_STRINGUTILS
