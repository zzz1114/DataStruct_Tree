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

/** ����� */
void enQueue(Que * q, CSNode * elem)
{
    QueNode * node = (QueNode*)malloc(sizeof(QueNode));
    node->data = elem;
    node->next = NULL;
    q->Qrear->next = node;
    q->Qrear = node;
}

/** ������ */
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

/***** ���Ĳ��� ******/

static int id = 0;

/** ��ʼ��һ�ÿ��� */
void InitCSTree(CSNode ** cst)
{
    (*cst) = (CSTree)malloc(sizeof(CSNode));
    (*cst)->firstChild = NULL;
    (*cst)->nextSibling = NULL;
}

/** �ݹ鷨����һ���� */
void CreatCSTree(CSNode ** cst)
{
    char input[200];
    gets(input);
    if(strcmp(input, "\0") == 0)     //����Ϊ��
    {
        return;
    }
    if((*cst) == NULL)
    {
        *cst = (CSNode*)malloc(sizeof(CSNode));
        (*cst)->firstChild = NULL;
        (*cst)->nextSibling = NULL;
    }
    //����㸳ֵ
    (*cst)->data.id = ++id;
    strcpy((*cst)->data.name, input);
    printf("�����볤�ӣ�");
    CreatCSTree(&((*cst)->firstChild));
    printf("���������ֵܣ�");
    CreatCSTree(&((*cst)->nextSibling));
}


/** ǰ����� */
void PreOrderTraverseCS(CSNode * cst)
{
    //�͵���һ�ö�����������
    if(cst)
    {
        printf("[ %d, %s ]-", cst->data.id, cst->data.name);
        PreOrderTraverseCS(cst->firstChild);
        PreOrderTraverseCS(cst->nextSibling);
    }
}

/** �������������������� */
int LevelTraverseCS(CSTree cst)
{
    int depth = 1;
    //Ҫ֪��������ȣ���Ҫ����ָ�룬һ������һ������ұ߽�㣬һ���ǵ�ǰ�������ұ��ֵ�
    pQue q = (pQue)malloc(sizeof(Que));
    CSNode* node = (CSNode*)malloc(sizeof(CSNode));
    CSNode* lastNode = cst;    //��¼��ǰ���ӽ������ұߺ���
    CSNode* rightSib = cst;    //��һ�㣨����ӽ��ͬһ�㣩�����ұ��ֵ�
    QueInit(q);
    enQueue(q, cst);
    printf("��1�㣺");
    while(!isQueEmpty(q))
    {
        deQueue(q, &node);
        printf("[ %d, %s ]-", node->data.id, node->data.name);
        CSNode * p = node->firstChild;
        while(p)//�����еĺ��ӽ���
        {
            enQueue(q, p);
            lastNode = p;
            p = p->nextSibling;
        }
        if(node == rightSib && !isQueEmpty(q))    //������������Ҫ��֤��һ���н�㣡������
        {
            printf("\n��%d�㣺", ++depth);
            rightSib = lastNode;    //��ǰ���ӵĽ�������ұ��ֵ�
        }
    }
    free(q);
    return depth;
}








