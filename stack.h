#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Tree.h"
/** ���ڶ������б������� */

//ջ�ڵ�
typedef struct node{
    BiTree* data;
    struct node* next;  //��һ�ڵ�
}stackNode, *pNode;

typedef struct Stack{
    pNode top;      //ջ��ָ��
    int length;      //ջ����
}Stack, *pStack;

/** ջ�ĳ�ʼ�� */
Status StackInit(pStack s);

/** ��ȡջ��Ԫ�� */
Status StackGetTop(pStack s, BiTree** data);

/** ��ջ */
Status StackPush(pStack s, BiTree* data);

/** ��ջ */
Status StackPop(pStack s, BiTree** data);

Status IsStackEmpty(pStack s);

#endif // STACK_H_INCLUDED
