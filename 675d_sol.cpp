#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef long long ll;
#define MD 1000000007
const int INF = 0x3f3f3f3f;
const double eps = 1e-8;
const int maxn = 100005;
int pre[maxn], key[maxn], ch[maxn][2], root, tot;
//���`�I�A��ȡA���k�Ĥl0��1�k�A�ڸ`�I�A�`�I�ƶq
int n;
void NewNode(int &r, int fa, int k)
{
    r = ++tot;
    pre[r] = fa;
    key[r] = k;
    ch[r][0] = ch[r][1] = 0;
}
void Rotate(int x, int kind)    //kind��1�ɥk�ۡA��0����
{
    int y = pre[x];
    ch[y][!kind] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if (pre[y])
        ch[pre[y]][ch[pre[y]][1]==y] = x;
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
}
void Splay(int r, int goal)
{
    while (pre[r] != goal)
    {
        if (pre[pre[r]] == goal) Rotate(r, ch[pre[r]][0]==r); //����l�k�ۥk��l����
        else
        {
            int y = pre[r];
            int kind = (ch[pre[y]][0] == y); //y�O����l��kind�O1�Ay�O�k��l��kind�O1
            if (ch[y][kind] == r)
            {
                Rotate(r, !kind);   //r�My���k���P�ɡA���r��
                Rotate(r, kind);
            }
            else
            {
                Rotate(y, kind);   //r�My�O�@���u�ɡA�@�r��
                Rotate(r, kind);
            }
        }
    }
    if (goal == 0) root = r;
}
int Insert(int k)
{
    int r = root;
    while (ch[r][key[r]<k])
    {
        //���e��?���A���`���J
        if (key[r] == k)
        {
            Splay(r, 0);
            return 0;
        }
        r = ch[r][key[r]<k];
    }
    NewNode(ch[r][key[r]<k], r, k);
    Splay(ch[r][key[r]<k], 0);
    return 1;
}
int get_small(int x)
{
    int temp = ch[x][0];
    if (temp == 0) return INF;
    while (ch[temp][1])
        temp = ch[temp][1];
    return key[temp];
}
int get_big(int x)
{
    int temp = ch[x][1];
    if (temp == 0) return INF;
    while (ch[temp][0])
        temp = ch[temp][0];
    return key[temp];
}
map<int, int> mp;

int main()
{
    //freopen("H:\\in.txt","r",stdin);
    //freopen("H:\\out.txt","w",stdout);
    while (scanf("%d", &n) != EOF)
    {
        root = tot = 0;
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            int num;
            scanf("%d", &num);
            mp[num] = i;
            if (i == 1)
            {
                NewNode(root, 0, num);
                continue;
            }
            if (Insert(num) == 0) continue;
            int a = get_small(root);
            int b = get_big(root);
            if (mp[a] > mp[b]) printf("%d ", a);
            else printf("%d ", b);
        }
    }
    return 0;
}
