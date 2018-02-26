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
    edge[cnt].v = u, edge[cnt].f = 0;//增加一条反向弧，容量为0
    edge[cnt].next = first[v], first[v] = cnt++;
}
int bfs(int s, int t) //构建Layered network
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
int dfs(int u, int maxf, int t)//dfs搜索增广路径
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
bool f(int mid)//构建图结构 Dinic实现ford-fulkerson计算最大流
{
        init();
        for(int i = 1 ; i <= n ; i++)
            addedge(0,i,1);//连接源点和job点  ce=1
        for(int i = 0 ; i < n ; i++){
            addedge(i+1,a[i]+n,1);
            addedge(i+1,b[i]+n,1);//连接job点和computer点  ce=1
        }
        for(int i = n+1 ; i <= n+m ; i++)
            addedge(i,n+m+1,mid);//连接computer点和终点  ce=mid
        int ans = Dinic(0,n+m+1);//求最大流
        if(ans >= n)//能否完成所有job
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
        while(l < r)//二分查找
        {
            int mid = (l+r)/2;
            if(f(mid))//能完成所有job
                r = mid;//减小上界
            else l = mid+1;//有job不能完成，提高下界
        }
        ca++;
        printf("第%d个实例，最大负载的最小值为:%d\n",ca,l);
    }
    return 0;
}
