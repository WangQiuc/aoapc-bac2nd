// UVa489 Hangman Judge
// wangqc

#include <stdio.h>
#include <string.h>

int k, t;
char s1[100], s2[100];
int win, lose, guessed[26];

void guess(char c)
{
    guessed[c-'a'] = 1;
    int bad = 1;
    for (int i = 0; i < strlen(s1); i++)
        if (s1[i] == c)
            k = k-1, s1[i] = ' ', bad = 0;
    if (bad) t--;
    if (!t) lose = 1;
    if (!k) win = 1;
}

int main()
{
    int rnd;
    while (scanf("%d%s%s", &rnd, s1, s2) == 3 && rnd != -1)
    {
        printf("Round %d\n", rnd);
        win = 0, lose = 0, k = strlen(s1), t = 7;
        memset(guessed, 0, sizeof(guessed));
        for (int i = 0; i < strlen(s2) && !win && !lose; i++)
            if (!guessed[s2[i]-'a']) guess(s2[i]);
        if (win) printf("You win.\n");
        else if (lose) printf("You lose.\n");
        else printf("You chickened out.\n");
    }
    return 0;
}
