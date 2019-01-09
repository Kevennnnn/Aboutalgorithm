#include <iostream>
#include <queue>
#include "MYGraph.h"
using namespace std;

//邻接表的链表节点
struct Edgenode
{
    int vnodeindex;
    Edgenode * next;
    Edgenode(int index,Edgenode * n= nullptr):vnodeindex(index),next(n){}
};

//图的节点结构
struct Vnode
{
    int data;
    Edgenode * firstEdge;
    Vnode(int val=0,Edgenode * edge= nullptr):data(val),firstEdge(edge){}
};

const int MAX_VNODE_NUM=50;

//无向图
class UDG
{
public:
    Vnode UDGList[MAX_VNODE_NUM];//存储图节点的数组
    int nodenum;//图节点个数
    int edgenum;//边数
public:
    UDG(int NodeNum):nodenum(NodeNum){}
    ~UDG(){freeUDG();}
    void CreateUDG();
    void freeUDG();

};

void UDG::CreateUDG() {
    cout<<"输入每个节点的数据：\n";
    for(int i=0;i<nodenum;++i)
    {
        cin>>UDGList[i].data;
    }
    int maxedgenum=(nodenum-1)*nodenum/2;
    cout<<"输入要创建的边数，0<=边数<="<<maxedgenum<<"\n";
    cin>>edgenum;
    for(int i=0;i<edgenum;++i)
    {
        cout<<"请依次输入边(Vi,Vj)的顶点序号"<<endl;
        int l,r;
        cin>>l;
        cin>>r;
        auto e=new Edgenode(r);
        e->next=UDGList[l].firstEdge;
        UDGList[l].firstEdge=e;
        auto re=new Edgenode(l);
        re->next=UDGList[r].firstEdge;
        UDGList[r].firstEdge=re;

    }
}

void UDG::freeUDG()
{
 for(int i=0;i<nodenum;++i)
 {
     auto p=UDGList[i].firstEdge;
     while(p)
     {
         auto d=p;
         p=p->next;
         delete d;
     }
 }
}

bool isVisist[MAX_VNODE_NUM];
//深度优先遍历
void DFS(UDG & G,int index);
void DFS(Mgraph & G,int index);

void DFSTraverse(UDG & G);
void DFSTraverse(Mgraph & G);


//广度优先遍历
void BFSTraverse(UDG &G);
void BFSTraverse(Mgraph &G);




int main() {
//    UDG G(8);
//    G.CreateUDG();
//    DFSTraverse(G);
//    BFSTraverse(G);
    Mgraph G(8);
    G.CreateUDG();
    DFSTraverse(G);
    BFSTraverse(G);


}

void DFS(UDG & G,int index)
{
    isVisist[index]= true;
    cout<<G.UDGList[index].data<<endl;
    auto p=G.UDGList[index].firstEdge;
    while(p)
    {
        int  pnodeindex=p->vnodeindex;
        if(!isVisist[pnodeindex])
        {
            DFS(G,pnodeindex);
        }
        p=p->next;
    }
}
void DFS(Mgraph & G,int index)
{
    isVisist[index]= true;
    cout<<G.vnode[index]<<endl;
    for(int j=0;j<G.nodenum;++j)
    {
        if(G.arcs[index][j].adj)
        {
            if(!isVisist[j])
                DFS(G,j);
        }
    }
}

void DFSTraverse(UDG & G)
{
    cout<<"\n深度优先遍历：\n";
    for(int i=0;i<MAX_VNODE_NUM;++i)
        isVisist[i]= false;
    for(int j=0;j<G.nodenum;++j)
    {
        if(!isVisist[j])
            DFS(G,j);
    }

}

void DFSTraverse(Mgraph & G)
{
    cout<<"\n深度优先遍历：\n";
    for(int i=0;i<MAX_VNODE_NUM;++i)
        isVisist[i]= false;
    for(int j=0;j<G.nodenum;++j)
    {
        if(!isVisist[j])
            DFS(G,j);
    }
}

void BFSTraverse(UDG &G)
{
    queue<int> BFSqueue;
    cout<<"\n广度优先遍历：\n";
    for(int i=0;i<MAX_VNODE_NUM;++i)
        isVisist[i]= false;

    for(int i=0;i<G.nodenum;++i)
    {
        if(!isVisist[i])
        {
            BFSqueue.push(i);
            isVisist[i]= true;
            while(!BFSqueue.empty())
            {
                auto index=BFSqueue.front();
                BFSqueue.pop();
                cout<<G.UDGList[index].data<<endl;
                auto p=G.UDGList[index].firstEdge;
                while(p)
                {
                    if(!isVisist[p->vnodeindex])
                    {
                        BFSqueue.push(p->vnodeindex);
                        isVisist[p->vnodeindex]= true;
                    }
                    p=p->next;
                }
            }
        }
    }

}

void BFSTraverse(Mgraph &G)
{
    queue<int> BFSqueue;
    cout<<"\n广度优先遍历：\n";
    for(int i=0;i<MAX_VNODE_NUM;++i)
        isVisist[i]= false;
    for(int i=0;i<G.nodenum;++i)
    {
        if(!isVisist[i])
        {
            BFSqueue.push(i);
            isVisist[i]= true;
            while(!BFSqueue.empty())
            {
                int index=BFSqueue.front();
                BFSqueue.pop();
                cout<<G.vnode[index]<<endl;
                for(int j=0;j<G.nodenum;j++)
                {
                    if(G.arcs[index][j].adj)
                    {
                        if(!isVisist[j])
                        {
                            BFSqueue.push(j);
                            isVisist[j]= true;
                        }
                    }
                }
            }
        }
    }
}