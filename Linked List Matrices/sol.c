#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 50

typedef enum {head,entry} tagfield;
typedef struct matrixNode *matrixPointer;
typedef struct entryNode
{
    int row,col,term,value;
}entryNode;
typedef struct matrixNode
{
    matrixPointer down;
    matrixPointer right;
    tagfield tag;
    union
    {
        matrixPointer next;
        entryNode entry;
    }u;
}matrixNode;

matrixPointer hdnode[MAX_SIZE];

matrixPointer mread(int ch1,int ch2)
{
    FILE *fpr;
    switch(ch1)
    {
        case 1:
            switch(ch2)
            {
                case 1:fpr=fopen("add1_matrix.txt","r");break;
                case 2:fpr=fopen("add2_matrix.txt","r");break;
            }
            break;
        case 2:
            switch(ch2)
            {
                case 1:fpr=fopen("multi1_matrix.txt","r");break;
                case 2:fpr=fopen("multi2_matrix.txt","r");break;
            }
            break;
        case 3:
            fpr=fopen("transpos_matrix.txt","r");
            break;
    }
    int numRows,numCols,numTerms,numHeads,i;
    int row,col,term,value,currentRow;
    matrixPointer temp,last,node;
    fscanf(fpr,"%d%d%d",&numRows,&numCols,&numTerms);
    numHeads=(numCols>numRows)?numCols:numRows;
    node=malloc(sizeof(*node));
    node->tag=entry;
    node->u.entry.row=numRows;
    node->u.entry.col=numCols;
    node->u.entry.term=numTerms;
    if(!numHeads)node->right=node;
    else
    {
        for(i=0;i<numHeads;i++)
        {
            temp=malloc(sizeof(*temp));
            hdnode[i]=temp;hdnode[i]->tag=head;
            hdnode[i]->right=temp;hdnode[i]->u.next=temp;
        }
        currentRow=0;
        last=hdnode[0];
        for(i=0;i<numTerms;i++)
        {
            fscanf(fpr,"%d%d%d",&row,&col,&value);
            if(row>currentRow)
            {
                last->right=hdnode[currentRow];
                currentRow=row;last=hdnode[row];
            }
            temp=malloc(sizeof(*temp));
            temp->tag=entry;temp->u.entry.row=row;
            temp->u.entry.col=col;temp->u.entry.value=value;
            last->right=temp;
            last=temp;
            hdnode[col]->u.next->down=temp;
            hdnode[col]->u.next=temp;
        }
        last->right=hdnode[currentRow];
        for(i=0;i<numCols;i++)
        hdnode[i]->u.next->down=hdnode[i];
        for(i=0;i<numHeads-1;i++)
        hdnode[i]->u.next=hdnode[i+1];
        hdnode[numHeads-1]->u.next=node;
        node->right=hdnode[0];
    }
    return node;
}

void mwrite(matrixPointer node)
{
    int i;
    matrixPointer temp,head=node->right;
    printf("%d %d %d\n",node->u.entry.row,node->u.entry.col,node->u.entry.term);
    for(i=0;i<node->u.entry.row;i++)
    {
        for(temp=head->right;temp!=head;temp=temp->right)
        printf("%d %d %d\n",temp->u.entry.row,temp->u.entry.col,temp->u.entry.value);
        head=head->u.next;
    }
}

matrixPointer madd(matrixPointer a,matrixPointer b)
{
    int numRows,numCols,numTerms,numHeads,i;
    int row,col,term,value,currentRow=0;
    matrixPointer temp,last,node;
    node=malloc(sizeof(*node));
    node->tag=entry;
    node->u.entry.row=a->u.entry.row;
    node->u.entry.col=a->u.entry.col;
    node->u.entry.term=0;
    numHeads=a->u.entry.row;
    a=a->right->right;b=b->right->right;
    for(i=0;i<numHeads;i++)
    {
        temp=malloc(sizeof(*temp));
        hdnode[i]=temp;hdnode[i]->tag=head;
        hdnode[i]->right=temp;hdnode[i]->u.next=temp;
    }
    last=hdnode[0]->right;
    for(currentRow=0;currentRow<numHeads;)
    {
        if(a->tag==head&&b->tag==head)
        {
            a=a->u.next->right;b=b->u.next->right;
            last->right=hdnode[currentRow];last=last->right;
            currentRow++;
        }
        else
        {
            last=hdnode[currentRow];
            while(1)
            {
                temp=malloc(sizeof(*temp));
                if(a->tag!=head&&b->tag!=head)
                {
                    if(a->u.entry.col<b->u.entry.col)
                    {
                        temp->u.entry.row=currentRow;
                        temp->u.entry.col=a->u.entry.col;
                        temp->u.entry.value=a->u.entry.value;
                        a=a->right;
                    }
                    else if(a->u.entry.col>b->u.entry.col)
                    {
                        temp->u.entry.row=currentRow;
                        temp->u.entry.col=b->u.entry.col;
                        temp->u.entry.value=b->u.entry.value;
                        b=b->right;
                    }
                    else if(a->u.entry.col==b->u.entry.col)
                    {
                        temp->u.entry.row=currentRow;
                        temp->u.entry.col=b->u.entry.col;
                        temp->u.entry.value=a->u.entry.value+b->u.entry.value;
                        b=b->right;a=a->right;
                    }
                }
                else if(a->tag==head&&b->tag==head){free(temp);break;}
                else if(a->tag==entry)
                {
                        temp->u.entry.row=currentRow;
                        temp->u.entry.col=a->u.entry.col;
                        temp->u.entry.value=a->u.entry.value;
                        a=a->right;
                }
                else if(b->tag==entry)
                {
                        temp->u.entry.row=currentRow;
                        temp->u.entry.col=b->u.entry.col;
                        temp->u.entry.value=b->u.entry.value;
                        b=b->right;
                }
                last->right=temp;
                last=temp;
                hdnode[temp->u.entry.col]->u.next->down=temp;
                hdnode[temp->u.entry.col]->u.next=temp;
                node->u.entry.term++;
            }
        }
    }
    for(i=0;i<numCols;i++)
    hdnode[i]->u.next->down=hdnode[i];
    for(i=0;i<numHeads-1;i++)
    hdnode[i]->u.next=hdnode[i+1];
    hdnode[numHeads-1]->u.next=node;
    node->right=hdnode[0];
    return node;
}

matrixPointer mmult(matrixPointer a,matrixPointer b)
{
    int numRows,numCols,numTerms,numHeads,i;
    int row,col,term,value,currentRow=0,currentCol;
    matrixPointer temp,last,node,tmpa,tmpb,Nowa,Nowb;
    node=malloc(sizeof(*node));
    node->tag=entry;
    numRows=node->u.entry.row=a->u.entry.row;
    numCols=node->u.entry.col=b->u.entry.col;
    node->u.entry.term=0;
    numHeads=numRows>numCols?numRows:numCols;
    a=a->right;b=b->right;
    for(i=0;i<numHeads;i++)
    {
        temp=malloc(sizeof(*temp));
        hdnode[i]=temp;hdnode[i]->tag=head;
        hdnode[i]->right=temp;hdnode[i]->u.next=temp;
    }
    last=hdnode[0]->right;
    for(currentRow=0;currentRow<numHeads;)
    {
        last=hdnode[currentRow];
        Nowa=a;Nowb=b;
        for(currentCol=0;currentCol<numCols;)
        {
            temp=malloc(sizeof(*temp));
            temp->tag=entry;
            temp->u.entry.row=currentRow;
            temp->u.entry.col=currentCol;
            temp->u.entry.value=0;
            tmpa=Nowa->right;tmpb=Nowb->down;
            while(tmpa->tag==entry&&tmpb->tag==entry)
            {
                if(tmpa->u.entry.col==tmpb->u.entry.row)
                {
                    temp->u.entry.value+=tmpa->u.entry.value*tmpb->u.entry.value;
                    tmpa=tmpa->right;tmpb=tmpb->down;
                }
                else if(tmpa->u.entry.col<tmpb->u.entry.row)
                tmpa=tmpa->right;
                else if(tmpa->u.entry.col>tmpb->u.entry.row)
                tmpb=tmpb->down;
            }
            if(temp->u.entry.value==0)free(temp);
            else
            {
                last->right=temp;
                last=temp;
                hdnode[temp->u.entry.col]->u.next->down=temp;
                hdnode[temp->u.entry.col]->u.next=temp;
                node->u.entry.term++;
            }
            Nowb=Nowb->u.next;
            currentCol++;
        }
        a=a->u.next;
        last->right=hdnode[currentRow];last=last->right;
        currentRow++;
    }
    for(i=0;i<numCols;i++)
    hdnode[i]->u.next->down=hdnode[i];
    for(i=0;i<numHeads-1;i++)
    hdnode[i]->u.next=hdnode[i+1];
    hdnode[numHeads-1]->u.next=node;
    node->right=hdnode[0];
    return node;
}

matrixPointer mtranspose(matrixPointer a)
{
    int numRows,numCols,numTerms,numHeads,i,temp1;
    int row,col,term,value,currentCol;
    matrixPointer temp,last,node;
    node=malloc(sizeof(*node));
    node->tag=entry;
    numCols=node->u.entry.col=a->u.entry.row;
    numRows=node->u.entry.row=a->u.entry.col;
    node->u.entry.term=a->u.entry.term;
    numHeads=(numCols>numRows)?numCols:numRows;
    a=a->right->right;
    for(i=0;i<numHeads;i++)
    {
        temp=malloc(sizeof(*temp));
        hdnode[i]=temp;hdnode[i]->tag=head;
        hdnode[i]->right=temp;hdnode[i]->u.next=temp;
    }
    last=hdnode[0];
    for(currentCol=0;currentCol<numHeads;)
    {
        if(a->tag==head)
        {
            a=a->u.next->right;
            last->down=hdnode[currentCol];last=last->down;
            currentCol++;
        }
        else
        {
            last=hdnode[currentCol];
            while(1)
            {
                temp=malloc(sizeof(*temp));
                temp->tag=entry;temp->u.entry.row=a->u.entry.col;
                temp->u.entry.col=a->u.entry.row;temp->u.entry.value=a->u.entry.value;
                last->down=temp;
                last=temp;
                hdnode[a->u.entry.row]->u.next->right=temp;
                hdnode[a->u.entry.row]->u.next=temp;
                a=a->right;
                if(a->tag==head)break;
            }
        }
    }
    for(i=0;i<numRows;i++)
    hdnode[i]->u.next->right=hdnode[i];
    for(i=0;i<numHeads-1;i++)
    hdnode[i]->u.next=hdnode[i+1];
    hdnode[numHeads-1]->u.next=node;
    node->right=hdnode[0];
    return node;
}

int main()
{
    FILE *fpr;
    int ch;
    matrixPointer node,node1,node2,node3;
    printf("Please choose the following options:\n1.add matrices\n2.multi matrices\n3.transpose matrices\n");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
            node1=mread(1,1);
            printf("input1:\n");
            mwrite(node1);
            node2=mread(1,2);
            printf("input2:\n");
            mwrite(node2);
            node3=madd(node1,node2);
            printf("output:\n");
            mwrite(node3);
            break;
        case 2:
            node1=mread(2,1);
            printf("input1:\n");
            mwrite(node1);
            node2=mread(2,2);
            printf("input2:\n");
            mwrite(node2);
            node3=mmult(node1,node2);
            printf("output:\n");
            mwrite(node3);
            break;
        case 3:
            node=mread(3,1);
            printf("input:\n");
            mwrite(node);
            node3=mtranspose(node);
            printf("output:\n");
            mwrite(node3);
            break;
    }
    system("pause");
    return 0;
}
