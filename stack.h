#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Tree.h"
/** 用于对树进行遍历操作 */

//栈节点
typedef struct node{
    BiTree* data;
    struct node* next;  //下一节点
}stackNode, *pNode;

typedef struct Stack{
    pNode top;      //栈顶指针
    int length;      //栈长度
}Stack, *pStack;

/** 栈的初始化 */
Status StackInit(pStack s);

/** 获取栈顶元素 */
Status StackGetTop(pStack s, BiTree** data);

/** 入栈 */
Status StackPush(pStack s, BiTree* data);

/** 出栈 */
Status StackPop(pStack s, BiTree** data);

Status IsStackEmpty(pStack s);

#endif // STACK_H_INCLUDED
