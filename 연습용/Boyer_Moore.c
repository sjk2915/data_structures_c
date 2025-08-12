#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) a >= b ? a : b
#define MAX_LEN 1000000

int* CreateBadCharTable(char *pattern)
{
    int p_len = strlen(pattern);
    int *bc_table = (int*)malloc(sizeof(int) * 256);
    for (int i=0; i<256; i++)
        bc_table[i] = p_len;
    for (int i=0; i<p_len; i++)
        bc_table[(int)pattern[i]] = p_len - (i+1);
    return bc_table;
}

int* CreateBorderTable(char *pattern)
{
    int p_len = strlen(pattern);
    int f = 0, b = p_len - 1;
    int *b_table = (int*)malloc(sizeof(int) * p_len);
    b_table[b] = b;
    for (int i = p_len - 2; i >= 0; --i)
    {
        // front와 back이 교차될때는 계산된 값을 활용
        if (i > b && b_table[i + p_len - 1 - f] < i - b)
            b_table[i] = b_table[i + p_len - 1 - f];
        else
        {
            if (i < b) b = i;
            f = i;
            while (b >= 0 && pattern[b] == pattern[b + p_len - 1 - f])
                --b;
            b_table[i] = f - b;
        }
    }
    return b_table;
}

int* CreateGoodSuffixTable(char *pattern, int *b_table)
{
    int p_len = strlen(pattern);
    int *gs_table = (int*)malloc(sizeof(int) * p_len);
    for (int i = 0; i < p_len; ++i)
        gs_table[i] = p_len;
    
    // 경우 1: 패턴의 접두부와 일치하는 접미부가 있는 경우
    int j = 0;
    for (int i = p_len - 1; i >= 0; --i)
        if (b_table[i] == i + 1)
            for (; j < p_len - 1 - i; ++j)
                if (gs_table[j] == p_len)
                    gs_table[j] = p_len - 1 - i;

    // 경우 2: 패턴의 접미부와 일치하는 부분이 있는 경우
    for (int i = 0; i < p_len - 1; ++i)
        gs_table[p_len - 1 - b_table[i]] = p_len - 1 - i;

    return gs_table;
}

void Boyer_Moore(char *str, char *pattern)
{
    int s_len = strlen(str);
    int p_len = strlen(pattern);
    int *bc_table = CreateBadCharTable(pattern);
    int *b_table = CreateBorderTable(pattern);
    int *gs_table = CreateGoodSuffixTable(pattern, b_table);
    int matched_cnt = 0;
    int *matched_idxs = (int*)malloc(sizeof(int) * s_len);
    int matched_idxs_idx = 0;
    
    int i = 0;
    while (i <= s_len - p_len)
    {
        int j = p_len-1;
        while (str[i + j] == pattern[j])  
            j--;
        if (j < 0)
        {
            // 패턴이 매칭되면 접미부가 0일때의 gs 규칙을 따름
            matched_cnt++;
            matched_idxs[matched_idxs_idx++] = i;
            i += gs_table[0];
        }
        else
        {
            int bc_shift = bc_table[str[i + j]] - (p_len - (j + 1));
            int gs_shift = gs_table[j];
            // bc 규칙과 gs 규칙 중 더 많이 움직일 수 있는 규칙을 따름
            i += MAX(bc_shift, gs_shift);
        }
    }

    printf("%d\n", matched_cnt);
    for (int i=0; i<matched_cnt; i++)
        printf("%d ", matched_idxs[i]+1);
    printf("\n");

    free(bc_table);
    free(b_table);
    free(gs_table);
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
    Boyer_Moore(str, pattern);

    return 0;
}