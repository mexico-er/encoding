#ifndef ENCODING_H
#define ENCODING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *url_encode(const char *str);
char *hex_encode(const char *str);

char *url_decode(const char *str);
char *hex_decode(const char *str);

char from_hex(char ch);

char *read_file(const char *filename);

#endif
