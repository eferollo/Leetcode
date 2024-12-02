int myAtoi(char* s) {
    char *p;
    int neg = 0, num=0;

    /* Skip leading whitespaces */
    for (p = s; isspace(p[0]); p++);

    /* Check if negative or positibe and skip sign */
    if (*p == '-' || *p == '+') {
        neg = (*p == '-');
        p++;
    }

    while (isdigit(*p)) {
        int digit = *p - '0';

        /* Check for overflow before updating num */
        if (num > (INT_MAX - digit) / 10) {
            return neg ? INT_MIN : INT_MAX;
        }

        num = num * 10 + digit;
        p++;
    }

    return neg ? -num : num;
}
