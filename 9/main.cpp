#include<iostream>
#include<cstdio>
#include<limits>
#include<iomanip>
#define MAX 500
using namespace std;
struct Vertex{
    char ch;
    int e;
    int h;//高度
};
Vertex vertex[MAX];//图顶点
int graph[MAX][MAX]={0};//保存图的邻接矩阵
int a[MAX];//行和数组
int b[MAX];//列和数组
int r,c,n;//行数 列数 节点数
int pushRelabel(int s, int t)
{
    int  max_flow;
    vertex[s].h = n;//设定源点高度为n
    //预流设置 将源点的全部货物流出 update
    for (int u = 1; u <= t; u++) {
        if (graph[s][u] > 0) {
            vertex[u].e = graph[s][u];
            vertex[s].e -= graph[s][u];
            graph[u][s] = graph[s][u];
            graph[s][u] = 0;
        }
    }
    while(1) {
        int flag = 1;
        for (int u = s+1; u < t; u++) {//搜索除s t以外的节点
            if (vertex[u].e > 0) {//找到货物量大于0的节点 push
                flag = 0;
                int relabel = 1;//先假设u需要relabel,提高h
                for (int v = s; v <= t && vertex[u].e > 0; v++) {//搜索能push的顶点
                    if (graph[u][v] > 0 && vertex[u].h >vertex[v].h) {
                        relabel = 0;//顶点u不需要relabel
                        int bottleneck = min(graph[u][v], vertex[u].e);
                        vertex[u].e -= bottleneck;
                        vertex[v].e += bottleneck;
                        graph[u][v] -= bottleneck;
                        graph[v][u] += bottleneck;

                    }
                }
                if (relabel==1) {//没有可以push的顶点,relabel node u
                    vertex[u].h += 1;
                }
            }
        }
        if (flag==1) {//除s和t外,每个顶点的e[i]都为0
            max_flow = 0;
            for (int u = s; u <= t; u++) {
                if (graph[t][u] > 0) {
                    max_flow += graph[t][u];
                }
            }
            break;
        }
    }
    return max_flow;
}

//验证结果是否正确，将结果矩阵各行各列求和判断是否等于a[i] b[i]
int check()
{
    int i,j;
    int flag = 0;
    int sum;
    int temp;

    for(i = 1;i <= r;i++)//验证每行的和
    {
        sum = 0;
        for(j = 1;j <= c;j++)
        {
            temp = 1-graph[i][j+r];
            sum += temp;
        }
        if(sum != a[i-1])
        {
            flag = 1;
            break;
        }
    }

    for(j = 1;j <= c;j++)//验证每列的和
    {
        sum = 0;
        for(i = 1;i <= r;i++)
        {
            temp = 1-graph[i][j+r];
            sum += temp;
        }
        if(sum != b[j-1])
        {
            flag = 1;
            break;
        }
    }

    return flag;
}

int main(){
    freopen("problem2.data","r",stdin);
    freopen("out.txt","w",stdout);//结果文件
    int ca = 0;
    int res = 0;
    int i,j;
    while(scanf("%d %d",&r,&c)!= EOF)
    {
		//每次将图清零
        for(i = 0;i < MAX;i++)
            for(j = 0;j < MAX;j++)
               graph[i][j] = 0;
        ca++;
        cout<<"第"<<ca<<"个实例："<<endl;
        n = r + c + 2;
        for(i = 1; i <= r ; i++)
            scanf("%d",&graph[0][i]);//将源点与R个代表行和的点连接
        for(j = 1 ; j <= c ; j++)
            scanf("%d",&graph[j+r][n-1]);//将C个代表列和的点与终点连接
        for(i = 1;i <= r;i++)
            for(j = 1;j <= c;j++)
                graph[i][j+r] = 1;//将行点和列点一一连接，代表R*C个矩阵元素，边初值设1

		//行和列和存入a[i] b[i]数组，用于检验结果矩阵正确性
        for(i = 1; i <= r ; i++)
            a[i-1] = graph[0][i];
        for(j = 1 ; j <= c ; j++)
            b[j-1] = graph[j+r][n-1];

		//初始化节点结构
        vertex[0].ch='s';  vertex[0].e=0; vertex[0].h=0;
        vertex[n-1].ch='t';  vertex[n-1].e=0; vertex[n-1].h=0;
        for(i = 1;i <= r+c;i++)
        {
            vertex[i].ch=i;
            vertex[i].e=0;
            vertex[i].h=0;
        }

        cout<<"原图邻接矩阵："<<endl;
        for(i=0;i<=n-1;i++){
            for(j=0;j<=n-1;j++){
            cout<<graph[i][j]<<" ";
            }cout<<endl;
        }

        cout <<"第"<<ca<<"个实例的最大流="<<pushRelabel(0, n-1)<<endl;
        cout<<"结果矩阵："<<endl;

       //整理结果矩阵，即1-当前R*C个边的前向流值
       for(i = 1;i <= r;i++){
            for(j = 1;j <= c;j++){
                cout<<1-graph[i][j+r]<<" ";
            }cout<<endl;
       }

       res = check();//检验结果矩阵正确性
       if(res) cout << "第"<<ca<<"个实例的检验结果为：错误！"<<endl;
       else  cout << "第"<<ca<<"个实例的检验结果为：正确！"<<endl;
       cout << endl << endl;
    }
    return 0;
}
