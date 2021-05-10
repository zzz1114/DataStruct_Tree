#include "stack.h"
#include "ElementType.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** 栈的初始化 */
Status StackInit(pStack s)
{
    s->length = 0;
    s->top = NULL;
    return OK;
}

/** 获取栈顶元素 */
Status StackGetTop(pStack s, BiTree** data)
{
    if(s->top)
    {
        *data = s->top->data;
        return OK;
    }
    else
        return ERROR;
}

/** 入栈 */
Status StackPush(pStack s, BiTree* data)
{
    pNode temp = (pNode)malloc(sizeof(stackNode));
    if(!temp)
        return ERROR;
    temp->data = data;
    temp->next = s->top;
    s->top = temp;
    s->length++;
    return OK;
}

/** 出栈 */
Status StackPop(pStack s, BiTree** data)
{
    if(!s->top)
    {
        printf("栈是空的！！\n");
        return ERROR;
    }
    pNode temp = s->top;
    s->top = temp->next;
    *data = temp->data;
    free(temp);
    temp = NULL;    //释放完之后一定记得指向空
    s->length--;
    return OK;
}

Status IsStackEmpty(pStack s)
{
    if(!s->top && s->length == 0)
        return TRUE;
    else
        return FALSE;
}
