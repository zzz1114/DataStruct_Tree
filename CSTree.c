#include "CSTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void QueInit(Que* q)
{
    q->Qfront = (QueNode*)malloc(sizeof(QueNode));
    q->Qfront->next = NULL;
    q->Qrear = q->Qfront;
}

/** 入队列 */
void enQueue(Que * q, CSNode * elem)
{
    QueNode * node = (QueNode*)malloc(sizeof(QueNode));
    node->data = elem;
    node->next = NULL;
    q->Qrear->next = node;
    q->Qrear = node;
}

/** 出队列 */
int deQueue(Que * q, CSNode ** elem)
{
    if(isQueEmpty(q))
        return 0;
    QueNode * node = q->Qfront->next;
    *elem = node->data;
    q->Qfront->next = node->next;
    if(q->Qrear == node)
        q->Qrear = q->Qfront;
    free(node);
    return 1;
}

int isQueEmpty(Que * q)
{
    if(q->Qrear == q->Qfront)
        return 1;
    return 0;
}

/***** 树的操作 ******/

static int id = 0;

/** 初始化一棵空树 */
void InitCSTree(CSNode ** cst)
{
    (*cst) = (CSTree)malloc(sizeof(CSNode));
    (*cst)->firstChild = NULL;
    (*cst)->nextSibling = NULL;
}

/** 递归法创建一棵树 */
void CreatCSTree(CSNode ** cst)
{
    char input[200];
    gets(input);
    if(strcmp(input, "\0") == 0)     //内容为空
    {
        return;
    }
    if((*cst) == NULL)
    {
        *cst = (CSNode*)malloc(sizeof(CSNode));
        (*cst)->firstChild = NULL;
        (*cst)->nextSibling = NULL;
    }
    //给结点赋值
    (*cst)->data.id = ++id;
    strcpy((*cst)->data.name, input);
    printf("请输入长子：");
    CreatCSTree(&((*cst)->firstChild));
    printf("请输入右兄弟：");
    CreatCSTree(&((*cst)->nextSibling));
}


/** 前序遍历 */
void PreOrderTraverseCS(CSNode * cst)
{
    //就当做一棵二叉树来遍历
    if(cst)
    {
        printf("[ %d, %s ]-", cst->data.id, cst->data.name);
        PreOrderTraverseCS(cst->firstChild);
        PreOrderTraverseCS(cst->nextSibling);
    }
}

/** 层序遍历，返回树的深度 */
int LevelTraverseCS(CSTree cst)
{
    int depth = 1;
    //要知道树的深度，需要两个指针，一个是这一层的最右边结点，一个是当前结点的最右边兄弟
    pQue q = (pQue)malloc(sizeof(Que));
    CSNode* node = (CSNode*)malloc(sizeof(CSNode));
    CSNode* lastNode = cst;    //记录当前出队结点的最右边孩子
    CSNode* rightSib = cst;    //这一层（与出队结点同一层）的最右边兄弟
    QueInit(q);
    enQueue(q, cst);
    printf("第1层：");
    while(!isQueEmpty(q))
    {
        deQueue(q, &node);
        printf("[ %d, %s ]-", node->data.id, node->data.name);
        CSNode * p = node->firstChild;
        while(p)//将所有的孩子进队
        {
            enQueue(q, p);
            lastNode = p;
            p = p->nextSibling;
        }
        if(node == rightSib && !isQueEmpty(q))    //！！！！！还要保证下一层有结点！！！！
        {
            printf("\n第%d层：", ++depth);
            rightSib = lastNode;    //当前出队的结点是最右边兄弟
        }
    }
    free(q);
    return depth;
}








