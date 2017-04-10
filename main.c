#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#define STACKSIZE 50
int a[100];
typedef struct
{
    int top;
    int items[STACKSIZE];
} Stack;
void initialize(Stack *s)
{
    s->top=0;
}
void push(Stack *s,int value)
{
    s->items[s->top++]=value;
}
int pop(Stack *s)
{
    return s->items[--s->top];
}
int isfull(Stack *s)
{
    return s->top<STACKSIZE?0:1 ;
}
//if top<STACKSIZE return 0 else return 1;
int isempty(Stack *s)
{
    return s->top==0?1:0;
}




void makeEmpty(Stack *s)
{
    while (!isempty(s))
        pop(s);
}

void display(Stack *s)
{
    Stack cop;
    initialize(&cop);
    printf("[");
    while (!isempty(s))
    {
        int x=pop(s);
        printf("%d ",x);
        push(&cop,x);
    }
    printf("]\n");
    while (!isempty(&cop)) push (s,pop(&cop));
}
int max(Stack *s)
{
    Stack n;
    initialize(&n);
    int retval=pop(s);
    push (&n,retval);
    while(!isempty(s))
    {
        int x=pop(s);
        push (&n,x);
        if(x>retval) retval=x;
    }
    while(!isempty(&n)) push(s,pop(&n));
    return retval;
}
int count(Stack *s)
{
    Stack n;
    initialize(&n);
    int c=0;
    while(!isempty(s))
    {
        c++;
        push(&n,pop(s));
    }
    while(!isempty(&n)) push(s,pop(&n));
    return c;
}
int peep( Stack *s)
{
    int x=pop(s);
    push(s,x);
    return x;
}
/** Postfix*/
int priority(char c)
{
    if (c>='0' && c<= '9') return 0;
    switch (c)
    {
    case '+' :
    case '-' :
        return 1;
    case '*' :
    case '/' :
        return 2;
    case '(' :
        return 3;
    default :
        return -1;
    }
}
void print_postfix(char*str,char *out)
{
    char ch;
    int index=0;
    Stack stack, *s=&stack;
    initialize(s);
    while (ch=*str++)
    {
        int pr=priority(ch);
        if (!pr) out[index++]=ch;
        else if (ch==')') /** pop up to ( */
        {
            while(!isempty(s) && peep(s)!='(') out[index++]=pop(s);
            pop(s);
        }
        else
        {
            while(!isempty(s) && priority(peep(s))>=pr && peep(s)!='(')
            {
                char x=pop(s);
                if (x!='(') out[index++]=x;
            }
            push(s,ch);
        }
    }
    while(!isempty(s)) out[index++]=pop(s);// remaining
    out[index++]=0;
    for (index=0; index<strlen(out); index++) printf("%c ",out[index]);
    printf("\n");
}
int eval(char *str)
{
    char ch;
    Stack stack,*data=&stack;
    initialize(data);
    int res;
    while (ch=*str++)
    {
        if (priority(ch)==0) push(data,ch-'0') ;
        else
        {
            switch(ch)
            {
            case ' ':
                continue;
            case '+':
                res= pop(data);
                res+=pop(data);
                break;
            case '-':
                res= pop(data);
                res-=pop(data);
                break;
            case '*':
                res= pop(data);
                res*=pop(data);
                break;
            case '/':
                res= pop(data);
                res/=pop(data);
                break;
            }
            push(data,res);
        }
    }
    return pop(data);
}
void evaluate(char *str)
{

    char post[100];
    print_postfix(str,post);
    printf("Evaluate: %s [Post:%s]= %d",str,post, eval(post));
}
void main()
{
    Stack s;
    char exp[50];
    int i;
    initialize(&s);
    char out[100];
    printf("Enter the Expression:\n");
    scanf("%s",exp);
    print_postfix(exp,out);
    evaluate(exp);
}
