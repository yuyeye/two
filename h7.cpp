#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
struct polynode
{
    double coef;
    int exp;
    polynode *link;
};
typedef polynode *polypointer;

void makenull(polypointer &f)
{
    f=new polynode;
    f->coef=0;
    f->exp=0;
    f->link=NULL;
}
polypointer Attach(int c,int e,polypointer d)
{
    polypointer x;
    x=d->link;
    d->link=new polynode;
    d->link->coef=c;
    d->link->exp=e;
    d->link->link=x;

}
char Compare(int a,int b)
{
    if(a==b) return '=';
    if(a>b)  return '>';
    if(a<b)  return '<';
}
void addpoint(int c,int e,polypointer f)
{
    polypointer point;
    point=f;
    while((point->link!=NULL)&&(point->link->exp>e))
        point=point->link;
    if(point->link==NULL)
    {
        Attach(c,e,point);
    }
    else
    {
        if (point->link->exp == e)
            point->link->coef += c;
        else
            Attach(c,e,point);
    }
}
void showpoly(polypointer f)
{
    polypointer point;
    if (f->link!=NULL)
    {
        if (f->link->exp!=0)
            if (f->link->coef==1)
                //cout<<"x^"<<f->link->exp;
                printf("x^%d",f->link->exp);
            else
                cout<<f->link->coef<<"x^"<<f->link->exp;
                //printf("%dx^%d",f->link->coef,f->link->exp);
        else
            cout<<f->link->coef;
           // printf("%d",f->link->coef);
        point = f->link;
        while (point->link != NULL)
        {
            if (point->link->exp != 0)
                    cout<<" + "<<point->link->coef<<"x^"<<point->link->exp;
                   //printf("+%dx^%d",point->link->coef,point->link->exp);
            else
                printf("+%d",point->link->coef);
            point = point->link;
        }
        cout<<endl;
    }
    else
        cout<<0<<endl;
}
void readpoly(polypointer &f)
{
    polypointer point;
    int c;
    int e;
    makenull(f);
    point=f;
    do
    {
        printf("请输入多项式的系数和指数:");
        scanf("%d %d",&c,&e);
        if(c!=0)
        {
           addpoint(c,e,f);
        }
    }while(c!=0);
    printf("所输入的多项式为:");
    showpoly(f);
}

polypointer PolyAdd(polypointer a,polypointer b)
/*{
    polypointer p,q,d,c;
    int x;
    p=a;
    q=b;
    makenull(c);
    d=c;
    while((p->link!=NULL)&&(q->link!=NULL))
    switch(Compare(p->link->exp,q->link->exp))
    {
        case'=':
        x=p->link->coef+q->link->coef;
        if(x!=0)
        {
            Attach(x,p->link->exp,d);
            d=d->link;
        }
        p=p->link;
        q=q->link;
        break;
        case'>':
        Attach(p->link->coef,p->link->exp,d);
        d=d->link;
        p=p->link;
        break;
        case'<':
        Attach(q->coef,q->exp,d);
        d=d->link;
        q=q->link;
        break;
    }
    while(p!=NULL)
    {
        Attach(p->link->coef,p->link->exp,d);
        d=d->link;
        p=p->link;
    }

    while(q!=NULL)
    {
        Attach(q->link->coef,q->link->exp,d);
        d=d->link;
        q=q->link;
    }
    //d->link=NULL;
    //p=c;
    //c=c->link;
    delete p;
    return (c);
}*/
{
    polypointer p,q,c,d;
    int x;
    p=a;
    q=b;
    makenull(c);
    d=c;
    while((p->link!=NULL)&&(q->link!=NULL))
    {
        if(p->link->exp==q->link->exp)
        {
            x=p->link->coef+q->link->coef;
            if(x != 0)
            {
                Attach(x,p->link->exp,d);
                d=d->link;
            }
            p=p->link;
            q=q->link;
        }
        else if(p->link->exp>q->link->exp)
        {
            Attach(p->link->coef,p->link->exp,d);
            d=d->link;
            p=p->link;
        }
        else
        {
            Attach(q->link->coef,q->link->exp,d);
            d=d->link;
            q=q->link;
        }
    }
    while(p->link!=NULL)
    {
        Attach(p->link->coef,p->link->exp,d);
        d=d->link;
        p=p->link;
    }
    while(q->link!=NULL)
    {
        Attach(q->link->coef,q->link->exp,d);
        d=d->link;
        q=q->link;
    }
    return(c);
}
polypointer PolySub(polypointer a,polypointer b)
{
    polypointer point,answer;
    point=b;
    while(point->link!=NULL)
    {
        point->link->coef=-point->link->coef;
        point=point->link;
    }
    answer=PolyAdd(a,b);
    point=b;
    return answer;
}
polypointer PolyMul(polypointer a,polypointer b)
{
    polypointer c,temp1,temp2,point1,point2;
    makenull(c);
    point1=a;
    while(point1->link!=NULL)
    {
        makenull(temp1);
        temp2=temp1;
        point2=b;
        while(point2->link!=NULL)
        {
            Attach(point1->link->coef *point2->link->coef,point1->link->exp+point2->link->exp,temp1);
            temp1=temp1->link;
            point2=point2->link;
        }
        c=PolyAdd(c,temp2);
        point1=point1->link;
    }
    return c;
}
//polypointer PolyDiv(polypointer a,polypointer b)
int main()
{
    polypointer f1,f2;
    polypointer addanswer,subanswer,mulanswer;//divanswer;
    printf("请输入一个多项式:\n");
    readpoly(f1);
    printf("请再输入一个多项式:\n");
    readpoly(f2);
    addanswer=PolyAdd(f1,f2);
    printf("加法的结果为:");
    showpoly(addanswer);
    mulanswer=PolyMul(f1,f2);
    printf("乘法的结果为:");
    showpoly(mulanswer);
    subanswer=PolySub(f1,f2);
    printf("减法的结果为:");
    showpoly(subanswer);
    //subanswer=PolyDiv(f1,f2);
    //printf("除法的结果为:");
    //showpoly(divanswer);
    return 0;
}
