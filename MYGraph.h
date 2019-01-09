//
// Created by hsuka on 2019-01-08.
//

#ifndef UNTITLED_MYGRAPH_H
#define UNTITLED_MYGRAPH_H

#include <iostream>
using namespace std;
//邻接矩阵的节点信息
struct arcinfo
{
    int adj;//边的权值
    arcinfo():adj(0){}

};

class Mgraph
{
public:

    int edgenum;
    arcinfo** arcs;

public:
    Mgraph(int nm):nodenum(nm),edgenum(0)
    {
        vnode=new int[nodenum];
        arcs=new arcinfo* [nodenum];
        for(int i=0;i<nodenum;++i)
        {
            arcs[i]=new arcinfo[nodenum];
        }
    }
    void init()
    {
        cout<<"输入每个节点的值：\n";
        for(int i=0;i<nodenum;++i)
        {
            cin>>vnode[i];
        }

    }

    void CreateUDG()
    {
        init();
        int maxedgenum=(nodenum-1)*nodenum/2;
        cout<<"输入要创建的边数，0<=边数<="<<maxedgenum<<"\n";
        cin>>edgenum;
        for(int a=0;a<edgenum;++a)
        {
            cout<<"请依次输入边(Vi,Vj)的顶点序号"<<endl;
            int i,j;
            cin>>i>>j;
            arcs[i][j].adj=1;
            arcs[j][i].adj=1;
        }
    }

    int *vnode;
    int nodenum;
};
#endif //UNTITLED_MYGRAPH_H
