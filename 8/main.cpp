#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 500;
const int MAXM = 500*500;
const int INF = 0x3f3f3f3f;
struct Edge
{
    int v, f;
    int next;
}edge[MAXM];
int n, m;
int cnt;
int first[MAXN], level[MAXN];
int q[MAXN];
int a[MAXN],b[MAXN];
void init()
{
    cnt = 0;
    memset(first, -1, sizeof(first));
}
void addedge(int u, int v, int f)
{
    edge[cnt].v = v, edge[cnt].f = f;
    edge[cnt].next = first[u], first[u] = cnt++;
    edge[cnt].v = u, edge[cnt].f = 0;//����һ�����򻡣�����Ϊ0
    edge[cnt].next = first[v], first[v] = cnt++;
}
int bfs(int s, int t) //����Layered network
{
    memset(level, 0, sizeof(level));
    level[s] = 1;
    int ff = 0, r = 1;
    q[ff] = s;
    while(ff < r)
    {
        int x = q[ff++];
        if(x == t) return 1;
        for(int e = first[x]; e != -1; e = edge[e].next)
        {
            int v = edge[e].v, f = edge[e].f;
            if(!level[v] && f)
            {
                level[v] = level[x] + 1;
                q[r++] = v;
            }
        }
    }
    return 0;
}
int dfs(int u, int maxf, int t)//dfs��������·��
{
    if(u == t) return maxf;
    int ret = 0;
    for(int e = first[u]; e != -1; e = edge[e].next)
    {
        int v = edge[e].v, f = edge[e].f;
        if(level[u] + 1 == level[v] && f)
        {
            int Min = min(maxf-ret, f);
            f = dfs(v, Min, t);
            edge[e].f -= f;
            edge[e^1].f += f;
            ret += f;
            if(ret == maxf) return ret;
        }
    }
    return ret;
}
int Dinic(int s, int t)
{
    int ans = 0;
    while(bfs(s, t))
        ans += dfs(s, INF, t);
    return ans;
}
bool f(int mid)//����ͼ�ṹ Dinicʵ��ford-fulkerson���������
{
        init();
        for(int i = 1 ; i <= n ; i++)
            addedge(0,i,1);//����Դ���job��  ce=1
        for(int i = 0 ; i < n ; i++){
            addedge(i+1,a[i]+n,1);
            addedge(i+1,b[i]+n,1);//����job���computer��  ce=1
        }
        for(int i = n+1 ; i <= n+m ; i++)
            addedge(i,n+m+1,mid);//����computer����յ�  ce=mid
        int ans = Dinic(0,n+m+1);//�������
        if(ans >= n)//�ܷ��������job
            return true;
        return false;
}

int main()
{
    freopen("problem1.data","r",stdin);
    int ca = 0;
    while(scanf("%d %d",&n,&m)!= EOF)
    {
        for(int i = 0 ; i < n ; i++)
            scanf("%d %d",&a[i],&b[i]);
        int l = 0 ,r = n;
        while(l < r)//���ֲ���
        {
            int mid = (l+r)/2;
            if(f(mid))//���������job
                r = mid;//��С�Ͻ�
            else l = mid+1;//��job������ɣ�����½�
        }
        ca++;
        printf("��%d��ʵ��������ص���СֵΪ:%d\n",ca,l);
    }
    return 0;
}
