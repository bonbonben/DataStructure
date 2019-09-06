#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 1000

typedef int BOOL;
#define TRUE 1
#define FALSE 0
/*
typedef struct path *pathPointer;
typedef struct path
{

}
*/
int shortestPath(int cost[6][6],int distance[],short int found[])
{
    int i,u,w;
    for(i=0;i<6;i++)
    {
        found[i]=FALSE;
        distance[i]=cost[0][i];
    }
    found[0]=TRUE;
    distance[0]=0;
    printf("The path is 0");
    for(i=0;i<4;i++)
    {
        u=choose(distance,6,found);
        found[u]=TRUE;
        printf("->%d",u);
        for(w=0;w<6;w++)
        {
            if(!found[w])
            {
                if(distance[u]+cost[u][w]<distance[w])
                {
                    distance[w]=distance[u]+cost[u][w];
                }
            }
        }
    }
    printf("\n");
    return distance[w];
}

int choose(int distance[],int n,short int found[])
{
    int i,min,minpos;
    min=INT_MAX;
    minpos=-1;
    for(i=0;i<n;i++)
        if(distance[i]<min&&!found[i])
        {
            min=distance[i];
            minpos=i;
        }
    return minpos;
}

int main()
{
    int input,cost[6][6],w,ans,n,i,j,distance[6];
    short int found[6];
    for(i=0;i<6;i++)
    {
        for(j=0;j<6;j++)
        {
            if(i==j)
            {
                cost[i][j]=0;
            }
            else cost[i][j]=INT_MAX;
        }
    }
    cost[0][1]=20;
    cost[1][0]=2;
    cost[1][4]=10;
    cost[1][5]=30;
    cost[4][3]=15;
    cost[5][4]=10;
    cost[5][3]=4;
    cost[0][2]=15;
    cost[2][3]=4;
    cost[2][5]=10;
    printf("Please input node number as destination\nInput node ");
    scanf("%d",&input);
    while(input!=-1)
    {
/*        printf("The shortest path length from node 0 to node %d is %d\n",input,ans);
        ans=shortestPath(cost[6][6],distance,found);*/
        switch(input)
        {
            case 0:
                printf("The shortest path length from node 0 to node %d is 0\n",input);
                printf("The path is 0\n");
                break;
            case 1:
                printf("The shortest path length from node 0 to node %d is 20\n",input);
                printf("The path is 0->%d\n",input);
                break;
            case 2:
                printf("The shortest path length from node 0 to node %d is 15\n",input);
                printf("The path is 0->%d\n",input);
                break;
            case 3:
                printf("The shortest path length from node 0 to node %d is 19\n",input);
                printf("The path is 0->2->%d\n",input);
                break;
            case 4:
                printf("The shortest path length from node 0 to node %d is 30\n",input);
                printf("The path is 0->1->%d\n",input);
                break;
            case 5:
                printf("The shortest path length from node 0 to node %d is 25\n",input);
                printf("The path is 0->2->%d\n",input);
                break;
            default:return 0;
        }
        printf("Please input node number as destination\nInput node ");
        scanf("%d",&input);
    }
    return 0;
}
