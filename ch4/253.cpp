// UVa253 Cube Painting
// wangqc

#include <stdio.h>
#include <string.h>

char s[15], s1[7], s2[7];
int dice[6][6] = 
{
    {0,1,2,3,4,5},{1,5,2,3,0,4},{2,1,5,0,4,3},
    {3,1,0,5,4,2},{4,0,2,3,5,1},{5,4,2,3,1,0}
};

int check()
{
    char s3[7] = {0};
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
            s3[j] = s1[dice[i][j]];
        for (int j = 0; j < 4; j++)
        {
            char c = s3[1];
            s3[1] = s3[2];
            s3[2] = s3[4];
            s3[4] = s3[3];
            s3[3] = c;
            if (strncmp(s2, s3, 6) == 0) return 1;
        }
    }
    return 0;
}

int main()
{
    while (scanf("%s", s) == 1)
    {
        for (int i = 0; i < 12; i++) 
            i < 6 ? s1[i] = s[i] : s2[i-6] = s[i];
        check() ? printf("TRUE\n") : printf("FALSE\n");
    }
    return 0;
}
