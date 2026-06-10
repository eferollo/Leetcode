/**
 * Problem:
 *
 * Solution:
 *
 * Time Complexity:
 * Space Complexity:
 */
#include <stdlib.h>
#include <string.h>

char* minWindow(char* s, char* t) 
{
    int t_len = strlen(t), s_len = strlen(s);
    char *l = NULL, *r = NULL;
    int right;

    for (right = 0; s[right] != '\0'; right++) {
        
    }
    
  
}

int main(void)
{
    char s[] = "ADOBECODEBANC";
    char t[] = "ABC";
    char *res = minWindow(s, t);
    return EXIT_SUCCESS;
}
