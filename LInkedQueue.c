#include "LinkedQueue.h"
#include <stdio.h>
#include <stdlib.h>


/** �Ƿ�Ϊ�� */
Status isQueueEmpty(pQueue q)
{
    if(q->length == 0)
        return TRUE;
    else
        return FALSE;
}

/** ��ʼ�� */
Status QueueInit(pQueue q)
{
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    q->frontQ = node;
    q->rearQ = node;
    node->next = NULL;
    q->length = 0;
    return OK;
}

/** ���ӣ��Ӷ�β���� */
Status QueueInsert(pQueue q, BiTree* elem)
{
    QueueNode * node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = elem;
    node->next = NULL;
    q->rearQ->next = node;
    q->rearQ = node;
    q->length++;
    return OK;
}

/** ���� */
Status QueueDelet(pQueue q, BiTree** elem)
{
    if(isQueueEmpty(q))
    {
        printf("�����ǿյģ�����\n");
        return ERROR;
    }
    QueueNode * node = q->frontQ->next;
    *elem = node->data;
    q->frontQ->next = node->next;
    //!!!!
    if(node == q->rearQ)    //node�����һ��Ԫ��
        q->rearQ = q->frontQ;
    q->length--;
    free(node);
    return OK;
}
