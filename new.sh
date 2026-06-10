#!/bin/bash

filename="$1.c"

cat <<EOF > "$filename"
/**
 * Problem:
 *
 * Solution:
 *
 * Time Complexity:
 * Space Complexity:
 */
#include <stdlib.h>

int main(void)
{
    return EXIT_SUCCESS;
}
EOF

nvim $filename
