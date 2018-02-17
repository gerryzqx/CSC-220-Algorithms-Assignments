// Name: Gerry Xu
// CSC 220 Algorithms Section C
// Homework 4

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define PATNUMBER 100
#define PATLENGTH 200
// total number of character in input alphebet
#define total_char_num 256
/*#define DEBUG*/


int multi_string_search(char *s, char **t, int k, int l)
{
    int primeNumber = 2017; // initialize the primeNumber to be 2017
    unsigned long int length_s = strlen(s); // String length of s
    int i; // iterator i
    int j; // iterator j
    int h = 1;
    int string_hash = 0; // initialize the hash value of string to 0;
    int *pattern_hash = (int*)malloc(sizeof(k)); // create an array of size k that will contain hash value for pattern
    
    for(int i = 0; i < k; i++)
    {
        pattern_hash[i] = 0; // set the hash value for pattern to 0
    }
    
    for(i = 0; i < l - 1; i++)
    {
        h = (h * total_char_num) % primeNumber; // calculate the value of h to be total_char_num^l % primeNumber
    }
    
    for(i = 0; i < l; i++)
    {
        // calculate the hash value of the string
        string_hash = (string_hash * total_char_num + s[i]) % primeNumber;
        for(j = 0; j < k; j++)
        {
            // calculate the hash value for pattern
            pattern_hash[j] = (pattern_hash[j] * total_char_num + t[j][i]) % primeNumber;
        }
    }
    
    i = 0;
    while(i < k)
    {
        j = 0;
        int m = string_hash;
        while(j < length_s - l + 1)
        {
            // if hash values matches
            if(m == pattern_hash[i])
            {
                int x = 0;
                bool condition = true;
                // check for characters one by one
                while(x < l && condition)
                {
                    if(s[j + x] != t[i][x])
                    {
                        condition = false;
                    }
                    x++;
                }
                // If hash equals the length of pattern string
                if(x == l)
                {
                    return j; // return the position of the start of the first pattern
                }
            }
            if(j < length_s - l)
            {
                // calculate the hash value for the next string
                m = (total_char_num *(m - s[j] * h) + s[j + l]) % primeNumber;
                if(m < 0)
                {
                    // convert to a positive value to account for negative value
                    m = m + primeNumber;
                }
            }
            j++;
        }
        i++;
    }
    // if no pattern occur returns -1
    return -1;
}

int main(void)
{  char sequence[100001];
    char *patterns[PATNUMBER];
    char t[PATNUMBER*PATLENGTH];
    int i, j;
    for(i=0; i<100000; i++)
        sequence[i] = 'a';
    sequence[100000]='\0';
    for(i=0; i<4000; i++)
    {  j = rand()%100000;
        sequence[j]='b';
    }
    for(i=0; i<PATNUMBER; i++)
    {  patterns[i] = t + PATLENGTH*i;
        for(j=0; j< PATLENGTH-1; j++)
            t[PATLENGTH*i+j] = sequence[PATLENGTH*i+j];
        t[PATLENGTH*i+PATLENGTH -1] = '\0';
        
    }
    for(i=0; i<PATNUMBER-1; i++)
    {  t[PATLENGTH*i+PATLENGTH -15] = 'b';
        t[PATLENGTH*i+PATLENGTH -14] = 'b';
        t[PATLENGTH*i+PATLENGTH -13] = 'b';
    }
#ifdef DEBUG
    { FILE *fp1, *fp2;
        fp1 = fopen("sequence", "w");
        fprintf(fp1, "%s\n", sequence);
        fclose(fp1);
        fp2 = fopen("patterns", "w");
        for(i=0; i<100; i++)
            fprintf(fp2, "%s\n", patterns[i]);
        fclose(fp2);
    }
#else
    if(multi_string_search(sequence, patterns, PATNUMBER, PATLENGTH-1) == (PATNUMBER-1)*PATLENGTH )
        printf("accepted\n");
    else
        printf("%s,%d needs check?\n","",multi_string_search(sequence, patterns, PATNUMBER, PATLENGTH-1));
#endif
}
