// UVa1589 Xiangqi
// wangqc

#include <stdio.h>
#include <string.h>

int board[12][12];
int dr[4] = {-1, 1,  0, 0}; 
int dc[4] = { 0, 0, -1, 1};
int hr[8] =  {-2, -2, -1, -1,  1, 1,  2, 2}; 
int hc[8] =  {-1,  1, -2,  2, -2, 2, -1, 1};
// horse blocker
int hbr[8] = {-1, -1, -1, -1,  1, 1,  1, 1}; 
int hbc[8] = {-1,  1, -1,  1, -1, 1, -1, 1};

int valid(int x, int y)
{
    return x && x < 11 && y && y < 10;
}

int check(int r, int c)
{
    if (r < 1 || r > 3 || c < 4 || c > 6) return 1;
    for (int i = 0; i < 4; i++)
    {
        int cnt = 0;
        int x = r + dr[i], y = c + dc[i];
        for (; valid(x, y) && cnt < 2; x += dr[i], y += dc[i])
            if (char p = board[x][y])
            {
                if ((p == 'R' || p == 'G') && !cnt) return 1;   // ride and general
                else if (p == 'C' && cnt == 1) return 1;        // cannon need one piece
                cnt++;
            }
    }
    for (int i = 0; i < 8; i++)                                 // horse
    {
        int x = r + hr[i], y = c + hc[i], bx = r + hbr[i], by = c + hbc[i];
        if (valid(x, y) && board[x][y] == 'H' && !board[bx][by]) return 1;
    }
    return 0;
}

int main()
{
    int n, gr, gc, r, c, win;
    char s[2];
    while (scanf("%d%d%d", &n, &gr, &gc) == 3 && n)
    {
        int cnt = 0;
        memset(board, 0, sizeof(board));
        for (int i = 0; i < n; i++)
        {
            scanf("%s%d%d", s, &r, &c);
            board[r][c] = s[0];
        }
        int j = gr; // check flying general kill
        do {win = board[j][gc] == 'G';}  
        while (j < 11 && !board[j++][gc]);
        if (!win)
        {
            for (int i = 0; i < 4; i++)
            cnt += check(gr + dr[i], gc + dc[i]);
            cnt == 4 ? printf("YES\n") : printf("NO\n");
        }
        else printf("NO\n");
    }
    return 0;
}
