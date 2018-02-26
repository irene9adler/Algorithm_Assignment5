#include<iostream>
#include<cstdio>
#include<limits>
#include<iomanip>
#define MAX 500
using namespace std;
struct Vertex{
    char ch;
    int e;
    int h;//�߶�
};
Vertex vertex[MAX];//ͼ����
int graph[MAX][MAX]={0};//����ͼ���ڽӾ���
int a[MAX];//�к�����
int b[MAX];//�к�����
int r,c,n;//���� ���� �ڵ���
int pushRelabel(int s, int t)
{
    int  max_flow;
    vertex[s].h = n;//�趨Դ��߶�Ϊn
    //Ԥ������ ��Դ���ȫ���������� update
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
        for (int u = s+1; u < t; u++) {//������s t����Ľڵ�
            if (vertex[u].e > 0) {//�ҵ�����������0�Ľڵ� push
                flag = 0;
                int relabel = 1;//�ȼ���u��Ҫrelabel,���h
                for (int v = s; v <= t && vertex[u].e > 0; v++) {//������push�Ķ���
                    if (graph[u][v] > 0 && vertex[u].h >vertex[v].h) {
                        relabel = 0;//����u����Ҫrelabel
                        int bottleneck = min(graph[u][v], vertex[u].e);
                        vertex[u].e -= bottleneck;
                        vertex[v].e += bottleneck;
                        graph[u][v] -= bottleneck;
                        graph[v][u] += bottleneck;

                    }
                }
                if (relabel==1) {//û�п���push�Ķ���,relabel node u
                    vertex[u].h += 1;
                }
            }
        }
        if (flag==1) {//��s��t��,ÿ�������e[i]��Ϊ0
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

//��֤����Ƿ���ȷ�������������и�������ж��Ƿ����a[i] b[i]
int check()
{
    int i,j;
    int flag = 0;
    int sum;
    int temp;

    for(i = 1;i <= r;i++)//��֤ÿ�еĺ�
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

    for(j = 1;j <= c;j++)//��֤ÿ�еĺ�
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
    freopen("out.txt","w",stdout);//����ļ�
    int ca = 0;
    int res = 0;
    int i,j;
    while(scanf("%d %d",&r,&c)!= EOF)
    {
		//ÿ�ν�ͼ����
        for(i = 0;i < MAX;i++)
            for(j = 0;j < MAX;j++)
               graph[i][j] = 0;
        ca++;
        cout<<"��"<<ca<<"��ʵ����"<<endl;
        n = r + c + 2;
        for(i = 1; i <= r ; i++)
            scanf("%d",&graph[0][i]);//��Դ����R�������к͵ĵ�����
        for(j = 1 ; j <= c ; j++)
            scanf("%d",&graph[j+r][n-1]);//��C�������к͵ĵ����յ�����
        for(i = 1;i <= r;i++)
            for(j = 1;j <= c;j++)
                graph[i][j+r] = 1;//���е���е�һһ���ӣ�����R*C������Ԫ�أ��߳�ֵ��1

		//�к��кʹ���a[i] b[i]���飬���ڼ�����������ȷ��
        for(i = 1; i <= r ; i++)
            a[i-1] = graph[0][i];
        for(j = 1 ; j <= c ; j++)
            b[j-1] = graph[j+r][n-1];

		//��ʼ���ڵ�ṹ
        vertex[0].ch='s';  vertex[0].e=0; vertex[0].h=0;
        vertex[n-1].ch='t';  vertex[n-1].e=0; vertex[n-1].h=0;
        for(i = 1;i <= r+c;i++)
        {
            vertex[i].ch=i;
            vertex[i].e=0;
            vertex[i].h=0;
        }

        cout<<"ԭͼ�ڽӾ���"<<endl;
        for(i=0;i<=n-1;i++){
            for(j=0;j<=n-1;j++){
            cout<<graph[i][j]<<" ";
            }cout<<endl;
        }

        cout <<"��"<<ca<<"��ʵ���������="<<pushRelabel(0, n-1)<<endl;
        cout<<"�������"<<endl;

       //���������󣬼�1-��ǰR*C���ߵ�ǰ����ֵ
       for(i = 1;i <= r;i++){
            for(j = 1;j <= c;j++){
                cout<<1-graph[i][j+r]<<" ";
            }cout<<endl;
       }

       res = check();//������������ȷ��
       if(res) cout << "��"<<ca<<"��ʵ���ļ�����Ϊ������"<<endl;
       else  cout << "��"<<ca<<"��ʵ���ļ�����Ϊ����ȷ��"<<endl;
       cout << endl << endl;
    }
    return 0;
}
