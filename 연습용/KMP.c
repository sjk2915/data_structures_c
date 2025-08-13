#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000000

// Longest Prefix which is also a Suffix
// LPS배열이라고도 부름
int* CreatePiTable(char *pattern)
{
    int pattern_len = strlen(pattern);
    int *pi_array = (int*)malloc(sizeof(int) * pattern_len);
    for (int i = 0; i < pattern_len; i++)
        pi_array[i] = 0;

    int j = 0;
    for (int i=1; i<pattern_len; i++)
    {
        while (j > 0 && pattern[i] != pattern[j])
            j = pi_array[j-1];
        
        if (pattern[i] == pattern[j])
            j++;
            
        pi_array[i] = j;
    }
    return pi_array;
}

void KMP(char *str, char *pattern)
{
    int *pi = CreatePiTable(pattern);
    int str_len = strlen(str);
    int pattern_len = strlen(pattern);

    int matched_cnt = 0;
    int *matched_idxs = (int*)malloc(sizeof(int) * str_len);
    int matched_idxs_idx = 0;

    int p_idx = 0;
    for (int s_idx=0; s_idx<str_len; s_idx++)
    {
        while (p_idx>0 && str[s_idx] != pattern[p_idx])
            p_idx = pi[p_idx-1];
        
        if (str[s_idx] == pattern[p_idx])
        {
            if (p_idx == pattern_len - 1)
            {
                matched_cnt++;
                matched_idxs[matched_idxs_idx++] = s_idx - pattern_len + 1;
                p_idx = pi[p_idx];
            }
            else
            {
                p_idx++;
            }
        }
    }

    printf("%d\n", matched_cnt);
    for (int i=0; i<matched_cnt; i++)
        printf("%d ", matched_idxs[i]+1);
    printf("\n");

    free(pi);
    free(matched_idxs);
}

int main()
{
    char str[MAX_LEN+1]; 
    char pattern[MAX_LEN+1];

    scanf("%[^\n]s", str);
    // 개행문자 제거
    scanf("%*c");
    scanf("%[^\n]s", pattern);
    KMP(str, pattern);

    return 0;
}