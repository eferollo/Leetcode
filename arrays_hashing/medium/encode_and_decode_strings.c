/**
 * Problem:
 * Given an array of strings s[], you are required to create an algorithm in
 * the encode() function that can convert the given strings into a single 
 * encoded string, which can be transmitted over the network and then decoded
 * back into the original array of strings. The decoding will happen in the 
 * decode() function. You need to implement two functions:
 *   1. encode(): This takes an array of strings s[] and encodes it into a 
 *      single string. 
 *   2. decode(): This takes the encoded string as input and returns an array 
 *      of strings containing the original array as given in the encode method.
 * 
 * Note: You are not allowed to use any inbuilt serialize method
 * <<<<
 * 1<=s.size()<=100
 * 1<=s[i].size()<=100
 * s[i] contains any possible characters out of the 256 ASCII characters.
 *
 * Solution:
 * Serialization and deserialization of an array of strings using a binary 
 * length-prefix encoding scheme.
 * This solution encodes each string by prefixing it with its length
 * stored in a single byte, followed by the raw characters of the string.
 * The encoded result is a contiguous buffer containing all strings.
 *
 * Encoding format for each string:
 *   [1 byte length][string bytes]
 *
 * The decode function reconstructs the original array by reading:
 *   1. The first byte (length of the string)
 *   2. The following 'length' bytes as the string content
 *   3. Repeating until the end of the buffer
 *
 * - String length is stored in one byte → maximum length per string is 255.
 *
 * Time Complexity: O(N)
 *   - Buffer resizing is amortized O(1) due to exponential growth.
 * Space Complexity: O(N)
 */

#include <stdlib.h>
#include <string.h>
/*
 * Encode an array of strings into a single string.
 */
char *encode(char **s, int size)
{
    size_t capacity = 64;
    size_t used = 0;
    size_t needed = 0;
    size_t smallest = 1;
    int i, len, pos = 0;
    char *tmp;

    char *buffer = calloc(capacity, sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }

    for (i = 0; i < size; i++) {
        len = strlen(s[i]);
        /* We need 1 byte for the prefix size and 1 byte for null termination */
        needed = used + len + 2;
        if (needed > capacity) {
            needed -= capacity;
            smallest = 1;
            /* Find the smallest power of two which is greater or equal to needed */
            while (smallest <= needed) {
                smallest <<= 1;
            }
            capacity += smallest;
            tmp = realloc(buffer, capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
        buffer[pos] = (char)len;
        pos++;
        memcpy(buffer + pos, s[i], len);
        pos += len;
        used = pos;
    }
    buffer[pos] = '\0';
    return buffer;
}

/*
 * Decode a single encoded string back into an array of strings.
 * returnSize will store the number of decoded strings.
 */
char **decode(char *str, int *returnSize) {
    int l, cnt = 0;
    char *s = NULL;
    size_t size = 2;
    char **decoded = calloc(size, sizeof(char *));

    char *p = str;
    while (*p != '\0') {
        if (cnt >= size) {
            size *= 2;
            char **tmp = realloc(decoded, size * sizeof(char *));
            if (tmp == NULL) {
                free(decoded);
                return NULL;
            }
            decoded = tmp;
        }
        l = (unsigned char)*p;
        s = calloc(l + 1, sizeof(char));
        memcpy(s, ++p, l);
        s[l] = '\0';
        p += l;
        decoded[cnt++] = s;
    }
    *returnSize = cnt;
    return decoded;
}

int main(void)
{
    char *input[] = {"hello", "world", "foo", "bar"};
    int size = 4;

    char *encoded = encode(input, size);

    int decodedSize = 0;
    char **decoded = decode(encoded, &decodedSize);

    return 0;
}
