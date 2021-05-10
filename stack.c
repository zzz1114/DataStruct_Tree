#include "stack.h"
#include "ElementType.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** ջ�ĳ�ʼ�� */
Status StackInit(pStack s)
{
    s->length = 0;
    s->top = NULL;
    return OK;
}

/** ��ȡջ��Ԫ�� */
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

/** ��ջ */
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

/** ��ջ */
Status StackPop(pStack s, BiTree** data)
{
    if(!s->top)
    {
        printf("ջ�ǿյģ���\n");
        return ERROR;
    }
    pNode temp = s->top;
    s->top = temp->next;
    *data = temp->data;
    free(temp);
    temp = NULL;    //�ͷ���֮��һ���ǵ�ָ���
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
