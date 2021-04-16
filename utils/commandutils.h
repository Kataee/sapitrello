#ifndef __UTILS_COMMANDUTILS
#define __UTILS_COMMANDUTILS

void get_command_parameters(char *command, char *statement, char **target);
int extract_parameter(char **source, char **destination);

#endif // __UTILS_COMMANDUTILS
