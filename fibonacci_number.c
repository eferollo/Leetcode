int fib(int n){
    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    return fib(n-1) + fib(n-2);
}

int fib(int n){
    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    int a = 0, b = 1, tmp, i;
    
    for(i = 2; i <= n; i++) {
        tmp = a + b;
        a = b;
        b = tmp;
    }

    return b;
}
