#include<stdio.h>
#include<malloc.h>
typedef struct Atree
{
    int x;
    struct Atree *lchild;
    struct Atree *rchild;
    int bf;    //平衡因子
    int ht;   //高度
} Tree;
int GetBf(Tree *p)          //计算平衡因子
{
    int l,r;
    if(p->lchild==NULL)
        l=0;
    else l=p->lchild->ht;
    if(p->rchild==NULL)
        r=0;
    else r=p->rchild->ht;
    return l-r;
}
int GetHt(Tree *p)
{
    if(p!=NULL)
    {
        GetHt(p->lchild);
        GetHt(p->rchild);
        if(p->lchild!=NULL)
        {
            if(p->rchild!=NULL)
            {
                if(p->lchild->ht>=p->rchild->ht)
                    p->ht=p->lchild->ht+1;
                else p->ht=p->rchild->ht+1;
            }
            else p->ht=p->lchild->ht+1;
        }
        else
        {
            if(p->rchild!=NULL)
                p->ht=p->rchild->ht+1;
            else p->ht=1;
        }
    }
}
void Insert(Tree *p,int xx)
{
    Tree *q;
    if(p->x==0)
    {
        p->x=xx;
        p->lchild=NULL;
        p->rchild=NULL;
        return;
    }
    while(p!=NULL)
    {
        q=p;
        if(p->x>xx)
        {
            p=p->lchild;
        }
        else if(p->x<xx)
        {
            p=p->rchild;
        }
        else
        {
            printf("已经存在该数，插入失败\n");
            return;
        }
    }
    if(q->x>xx)
    {
        q->lchild=malloc(sizeof(Tree));
        q=q->lchild;
        q->lchild=NULL;
        q->rchild=NULL;
        q->x=xx;
    }
    else
    {
        q->rchild=malloc(sizeof(Tree));
        q=q->rchild;
        q->lchild=NULL;
        q->rchild=NULL;
        q->x=xx;
    }
}
void ReNewBF(Tree *p)      //使用前必须先更新节点高度
{
    if(p!=NULL)
    {
        ReNewBF(p->lchild);
        ReNewBF(p->rchild);
        p->bf=GetBf(p);
    }
}
void LLC(Tree *p)
{
    Tree *q,*k;
    k=(Tree *)malloc(sizeof(Tree));
    k->x=p->x;
    k->rchild=p->rchild;
    q=p->lchild;
    p->x=q->x;
    p->lchild=q->lchild;
    p->rchild=k;
    k->lchild=q->rchild;
}
void RRC(Tree *p)
{
    Tree *q,*k;
    k=(Tree *)malloc(sizeof(Tree));
    k->x=p->x;
    k->lchild=p->lchild;
    q=p->rchild;
    p->x=q->x;
    p->lchild=k;
    p->rchild=q->rchild;
    k->rchild=q->lchild;
}
void change(Tree *p,int l)
{
    while(p->bf!=-2&&p->bf!=2&&p->x!=l)
    {
        if(p->x>l)
            p=p->lchild;
        else p=p->rchild;
    }
    if(p->bf==2)
    {
        if(p->lchild->bf==1)
        {
            LLC(p);
        }
        else
        {
            LLC(p->lchild);
            RRC(p);
        }
    }
    else if(p->bf==-2)
    {
        if(p->lchild->bf==-1)
        {
            RRC(p);
        }
        else
        {
            RRC(p->lchild);
            LLC(p);
        }
    }
    else
        return;

}
void AvlTree(Tree *p)
{
    int l,i;
    for(i=0;; i++)
    {
        printf("请输入下一个数\n");
        scanf("%d",&l);
        Insert(p,l);
        GetHt(p);
        ReNewBF(p);
        change(p,l);
        printf("是否继续输入(1继续,0结束)\n");
        scanf("%d",&l);
        if(l==0)
            break;
    }
}
void MidShow(Tree *p)
{
    if(p!=NULL)
    {
        MidShow(p->lchild);
        printf("%d ",p->x);
        MidShow(p->rchild);
    }
}
int main()
{
    Tree *p=(Tree *)malloc(sizeof(Tree));
    p->x=0;
    AvlTree(p);
    MidShow(p);
    return 0;
}
