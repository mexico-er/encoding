#include "encoding.h"

char from_hex(char ch) {
    return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

char *url_encode(const char *str) {
    char *pstr = (char *)str, *buf = (char*)malloc(strlen(str) * 3 + 1), *pbuf = buf;
    while (*pstr) {
        if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~')
            *pbuf++ = *pstr;
        else
            pbuf += sprintf(pbuf, "%%%02X", *pstr);
        pstr++;
    }
    *pbuf = '\0';
    return buf;
}

char *url_decode(const char *str) {
    char *pstr = (char *)str, *buf = (char*)malloc(strlen(str) + 1), *pbuf = buf;
    while (*pstr) {
        if (*pstr == '%') {
            if (pstr[1] && pstr[2]) {
                *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
                pstr += 2;
            }
        } else if (*pstr == '+') {
            *pbuf++ = ' ';
        } else {
            *pbuf++ = *pstr;
        }
        pstr++;
    }
    *pbuf = '\0';
    return buf;
}

char *hex_encode(const char *str) {
    char *output = (char*)malloc(strlen(str) * 2 + 1);
    for (int i = 0; i < strlen(str); i++) {
        sprintf(output + i * 2, "%02x", (unsigned char)str[i]);
    }
    return output;
}

char *hex_decode(const char *str) {
    int length = strlen(str) / 2;
    char *output = (char*)malloc(length + 1);
    for (int i = 0; i < length; i++) {
        output[i] = (from_hex(str[i * 2]) << 4) | from_hex(str[i * 2 + 1]);
    }
    output[length] = '\0';
    return output;
}

char *read_file(const char *filename) {
    FILE *file;
    char *buffer;
    long file_size;

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    fclose(file);
    
    return buffer;
}