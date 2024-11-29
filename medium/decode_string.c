int strToInt(const char *str, int len) {
    char temp[len + 1];
    strncpy(temp, str, len);
    temp[len] = '\0';
    return atoi(temp);
}

char* decodeString(char* s) {
    /* MAX is 10^5 */
    char *str = calloc(10000, sizeof(char)), *sub_str = NULL;
    int i, depth = 0, str_idx = 0, prev = 0, rep = 0;

    for (i = 0; s[i] != '\0'; i++) {
        if (depth == 0 && isalpha(s[i])) {
            str[str_idx++] = s[i];
            prev = i + 1;
        }
        if (s[i] == '[') {
            depth++;
            if (depth == 1) {
                rep = strToInt(&s[prev], i - prev);
                prev = i + 1;
            } 
        } else if (s[i] == ']') {
            depth--;
            if (depth == 0) {
                sub_str = decodeString(strndup(&s[prev], i - prev));
                while (rep > 0) {
                    strcat(str, sub_str);
                    str_idx += strlen(sub_str);
                    rep--;
                }
                free(sub_str);
                prev = i + 1;
            }
        }
    }
    return str;
}
