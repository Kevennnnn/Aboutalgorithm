//
// Created by hsuka on 2019-01-09.
//

#include <iostream>
#include <vector>
using namespace std;
const int MAX_NUM=1000;
struct EasyGraph
{
    char vnodedata[MAX_NUM];
    int edge[MAX_NUM][MAX_NUM];
    int vnodenum;
    EasyGraph(int num):vnodenum(num)
    {
        for(int i=0;i<MAX_NUM;++i)
        {
            for(int j=0;j<MAX_NUM;++j)
                edge[i][j]=0;
        }
    }
};


void createGraph(EasyGraph & G)
{
    cout<<"输入每个节点的值"<<endl;
    int num=G.vnodenum;
    for(int i=0;i<num;++i)
    {
        cin>>G.vnodedata[i];
    }
    cout<<"输入邻接矩阵:\n";

    for(int i=0;i<G.vnodenum;++i)
    {
        for(int j=0;j<G.vnodenum;++j)
            cin>>G.edge[i][j];
    }

    for(int i=0;i<G.vnodenum;++i)
    {
        for(int j=0;j<G.vnodenum;++j)
            if(G.edge[i][j]==0)
                G.edge[i][j]=MAX_NUM;
    }


}

void prim(EasyGraph &G,vector<vector<int>> &parent)
{
    int num=G.vnodenum;
    int lowcost[MAX_NUM];
    int closest[MAX_NUM]={0};
    int used[MAX_NUM]={0};

    used[0]=1;
    for(int i=0;i<num;++i)
    {
        lowcost[i]=G.edge[0][i];
    }

    int min;
    int key;
    for(int i=0;i<num-1;++i)
    {
        min=MAX_NUM;
        for(int j=0;j<num;++j)
        {
            if(used[j]==0&&lowcost[j]<min) {
                min = lowcost[j];
                key = j;
            }
        }

        parent.push_back({key,closest[key]});
        used[key]=1;

        for(int j=0;j<num;j++)
        {
            if(used[j]==0&&G.edge[key][j]<lowcost[j])
            {
                lowcost[j]=G.edge[key][j];
                closest[j]=key;
            }
        }

    }

}


void PrimMST(EasyGraph &G,vector<vector<int>> &parent)
{
    prim(G,parent);
    int ans=0;
    int num=G.vnodenum;
    for(int i=0;i<num-1;++i)
    {
        cout<<"边:"<<G.vnodedata[parent[i][1]]<<"--"<<G.vnodedata[parent[i][0]]<<endl;
        ans+=G.edge[parent[i][1]][parent[i][0]];
    }
    cout<<"最小权值和:"<<ans<<endl;
}

int main()
{
    EasyGraph G(7);
    createGraph(G);
    vector<vector<int>> preindex;
    PrimMST(G,preindex);
}

