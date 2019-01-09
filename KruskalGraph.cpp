//
// Created by hsuka on 2019-01-09.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxSize 20

typedef char VertexType;

typedef struct Graph {		//定义图的邻接矩阵表示法结构
    VertexType ver[MaxSize+1];
    int edg[MaxSize][MaxSize];
}Graph;

typedef struct gEdge {		//定义一个边集结构，用来存储图的所有边信息
    int begin;
    int end;
    int weight;
}gEdge;

void CreateGraph( Graph *g )		//邻接矩阵法图的生成函数
{
    int i = 0;
    int j = 0;
    int VertexNum;
    VertexType Ver;

    printf("请输入图的顶点:\n");
    while( '\n' != (Ver=getchar()) ) {
        g->ver[i++] = Ver;
    }
    g->ver[i] = '\0';

    VertexNum = strlen(g->ver);
    printf("请输入相应的的邻接矩阵:\n");
    for( i=0; i<VertexNum; i++ )
        for( j=0; j<VertexNum; j++ )
            scanf("%d", &g->edg[i][j]);
}

void PrintGraph( Graph g )		//打印图的结点标识符和邻接矩阵
{
    int i, j;
    int VertexNum = strlen(g.ver);
    printf("图的顶点为:\n");
    for( i=0; i<VertexNum; i++ )
        printf("%c ", g.ver[i]);
    printf("\n");

    printf("图的邻接矩阵为:\n");
    for( i=0; i<VertexNum; i++ ) {
        for( j=0; j<VertexNum; j++ )
            printf("%d ", g.edg[i][j]);
        printf("\n");
    }
}

int CalVerNum( Graph g )		//求图的顶点数
{
    return strlen(g.ver);
}

int CalEdgNum( Graph g )		//获取图的边数
{
    Graph p = g;
    int count = 0;
    int VertexNum = CalVerNum( p );
    for( int i=0; i<VertexNum; i++ )
        for( int j=i; j<VertexNum; j++ )		//邻接矩阵对称，计算上三角元素和即可
            if( 0 != p.edg[i][j] )
                count++;
    return count;
}

gEdge *CreateEdges( Graph g )					//生成图的排序过的边集数组
{
    int i, j;
    int k = 0;
    int EdgNum = CalEdgNum( g );
    int VertexNum = CalVerNum( g );
    gEdge temp;
    gEdge *p = (gEdge *)malloc(sizeof(gEdge)*EdgNum);

    for( i=0; i<VertexNum; i++ )				//边集数组初始化,同样只考虑上三角矩阵
        for( j=i; j<VertexNum; j++ )
            if( 0 != g.edg[i][j] ) {
                p[k].begin = i;
                p[k].end = j;
                p[k].weight = g.edg[i][j];
                k++;
            }

    for( i=0; i<EdgNum-1; i++ )		        	//对边集数组进行选择排序
        for( j=i+1; j<EdgNum; j++ )
            if( p[i].weight > p[j].weight ) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

    return p;
}

//Kruskal算法生成MST
void Kruskal( Graph g )
{
    int VertexNum = CalVerNum( g );
    int EdgNum = CalEdgNum( g );
    gEdge *p = CreateEdges( g );
    int *index = (int *)malloc(sizeof(int)*VertexNum);		    //index数组，其元素为连通分量的编号，index[i] = index[j] 表示编号为i 和 j的顶点在同一个连通分量中，反之则不在同一个连通分量
    int *MSTEdge = (int *)malloc(sizeof(int)*VertexNum-1);		//MSTEdge数组，用来存储已确定的MST的边的编号，共VertexNum-1条边
    int k= 0;
    int WeightSum = 0;
    int IndexBegin, IndexEnd;

    for(int i=0; i<VertexNum; i++ )		//初始化所有index = -1
        index[i] = -1;

    for( int i=0; i<VertexNum-1; i++ ) {
        for(int j=0; j<EdgNum; j++ ) {
            if( !(index[p[j].begin]>=0 && index[p[j].end]>=0 && index[p[j].begin]==index[p[j].end]) ) {  //找到当前还没加入到同一个连通分量且权值最下的边
                MSTEdge[i] = j;		//将其加入到MST中去

                if( (-1 == index[p[j].begin]) && (-1 == index[p[j].end]) )			//该边的两个顶点都没加入过任何一个连通分量
                    index[p[j].begin] = index[p[j].end] = i;

                else if( (-1 == index[p[j].begin]) && (index[p[j].end] >= 0) ) {	//该边的尾end已在一个连通分量，头begin未加入过任何连通分量
//                    index[p[j].begin] = i;
//                    IndexEnd = index[p[j].end];
//                    for(int n=0; n<VertexNum; n++ )
//                        if( index[n] == IndexEnd )
//                            index[n] = i;
                    index[p[j].begin] = index[p[j].end];
                }

                else if( (-1 == index[p[j].end]) && (index[p[j].begin] >= 0) ) {	//该边的头begin已在一个连通分量，尾end未加入过任何连通分量
//                    index[p[j].end] = i;
//                    IndexBegin = index[p[j].begin];
//                    for(int n=0; n<VertexNum; n++ )
//                        if( index[n] == IndexBegin )
//                            index[n] = i;
                    index[p[j].end] =index[p[j].begin];
                }

                else {
                    IndexEnd = index[p[j].end];
                    IndexBegin = index[p[j].begin];
                    for(int n=0; n<VertexNum; n++ )								//该边的两个顶点都已经存在于两个不同的连通分量中
                        if( index[n] == IndexBegin || index[n] == IndexEnd )
                            index[n] = i;										//将该连通分量编号全部修改为相同的值
                }
                break;
            }
        }
    }

    printf("MST的边为:\n");				//输出MST的边
    for( int i=0; i<VertexNum-1; i++ ) {
        printf("%c--%c\n", g.ver [p[MSTEdge[i]].begin] , g.ver [p[MSTEdge[i]].end] );
        WeightSum+=p[MSTEdge[i]].weight;
    }
    printf("MST的权值为:%d\n", WeightSum);		//输出MST的权值
}

int main()
{
    Graph g;
    CreateGraph( &g );

    PrintGraph( g );

    Kruskal( g );

    return 0;
}

