#include<stdio.h>
#include<stdlib.h>

struct treeNode
{
    struct treeNode *leftChild;
    struct treeNode *rightChild;
    int data;
    int count;
};

typedef struct treeNode tree;
typedef tree *treeptr;

void insert(treeptr *ptr ,int n)
{
    if(*ptr==NULL)
    {
        *ptr=malloc(sizeof(tree));
        (*ptr)->data=n;
        (*ptr)->count=1;
        (*ptr)->leftChild=NULL;
        (*ptr)->rightChild=NULL;
    }
    else
    {
        if(n<(*ptr)->data)
        {
            insert(&((*ptr)->leftChild),n);
        }
        if(n>(*ptr)->data)
        {
            insert(&((*ptr)->rightChild),n);
        }
        if(n==(*ptr)->data)
        {
            (*ptr)->count++;
        }
    }
}

void delete(treeptr *ptr,int n)
{
    if(n==(*ptr)->data)
    {
        (*ptr)->count--;
        if((*ptr)->count<=0&&(*ptr)->leftChild!=NULL)
        {
            ((*ptr)->leftChild)->rightChild=(*ptr)->rightChild;
            (*ptr)=(*ptr)->leftChild;
        }
        if((*ptr)->count<=0&&(*ptr)->leftChild==NULL)
        {
            (*ptr)=(*ptr)->rightChild;
        }
    }
    else
    {
        if(n<(*ptr)->data)
        {
            delete(&((*ptr)->leftChild),n);
        }
        if(n>(*ptr)->data)
        {
            delete(&((*ptr)->rightChild),n);
        }
    }
}

void print(treeptr ptr)
{
    if(ptr!=NULL)
    {
        printf("%2d%10d\n",ptr->data,ptr->count);
        if(ptr->leftChild!=NULL)print(ptr->leftChild);
        print(ptr->rightChild);
    }
}

int main()
{
    FILE *fpr;
    fpr=fopen("input.txt","r");
    int num,ch;
    treeptr rootptr=NULL;
    fscanf(fpr,"%d\n%d\n",&ch,&num);
    while(ch!=3)
    {
        switch(ch)
        {
            case 1:
                printf("Insert %d\n",num);
                printf("[Preorder] [Count]\n");
                insert(&rootptr,num);
                print(rootptr);
                break;
            case 2:
                printf("Delete %d\n",num);
                printf("[Preorder] [Count]\n");
                delete(&rootptr,num);
                print(rootptr);
                break;
        }
        fscanf(fpr,"%d\n%d\n",&ch,&num);
    }
    return 0;
}
