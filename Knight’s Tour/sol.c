#include<stdio.h>

int main()
{
    int i,j,k,l,m,n,board[8][8],nexti[8],nextj[8],exit[9],min,npos;
    while(n)
    {
        for(i=0;i<8;i++)
        {
            for(j=0;j<8;j++)
            {
                board[i][j]=-1;
            }
        }
        scanf("%d",&i);
        if(i==-1)break;
        scanf("%d",&j);
        board[i][j]=0;
        printf("Starting Position (%d,%d)\n",i,j);
        printf("0:%d,%d\n",i,j);
        for(m=1;m<64;m++)
        {
            l=1;
            npos=0;
            int ktmove1[8]={-2,-1,1,2,2,1,-1,-2},ktmove2[8]={1,2,2,1,-1,-2,-2,-1};
            for(k=0;k<8;k++)
            {
                nexti[l]=i+ktmove1[k];
                nextj[l]=j+ktmove2[k];
                if((nexti[l]<0)||(nexti[l]>7)||(nextj[l]<0)||(nextj[l]>7)||(board[nexti[l]][nextj[l]]==0));
                else
                {
                    l++;
                    npos++;
                }
            }
            if(npos==0)break;
            else if(npos==1)
            {
                min=1;
                i=nexti[min];
                j=nextj[min];
                board[i][j]=0;
                printf("%d:%d,%d\n",m,i,j);
            }
            else
            {
                for(l=1;l<9;l++)
                exit[l]=0;
                for(l=1;l<=npos;l++)
                {
                    for(k=0;k<8;k++)
                    {
                        int nexti2[8]={0},nextj2[8]={0};
                        nexti2[l]=nexti[l]+ktmove1[k];
                        nextj2[l]=nextj[l]+ktmove2[k];
                        if(nexti2[l]<0||nexti2[l]>=8||nextj2[l]<0||nextj2[l]>=8||board[nexti2[l]][nextj2[l]]==0);
                        else exit[l]++;
                    }
                }
                min=1;
                for(l=1;l<=npos;l++)
                {
                    if(exit[l]<exit[min])
                    min=l;
                }
                i=nexti[min];
                j=nextj[min];
                board[i][j]=0;
                printf("%d:%d,%d\n",m,i,j);
            }
        }
    }
    system("pause");
    return 0;
}
