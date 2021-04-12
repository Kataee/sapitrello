#ifndef __PARSER_STQL
#define __PARSER_STQL

#include <stdbool.h>

bool stql_parse_single(char *statement);
bool stql_parse(char *input);

#endif // __PARSER_STQL
