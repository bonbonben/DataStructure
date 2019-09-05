#include<stdio.h>
#include<stdlib.h>
int f(int n,int m)
{
    int i,r=1;
    for(i=1;i<=m;i++)
    {
        r=r*(n-i+1)/i;
    }
    return r;
}
int g(int n,int m)
{
    if(n==m||m==0)return 1;
    else return g(n-1,m)+g(n-1,m-1);
}
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        if(n<m)break;
        printf("Answer(iterative version):%d\n",f(n,m));
        printf("Answer(recursive version):%d\n",g(n,m));
    }
    return 0;
}
