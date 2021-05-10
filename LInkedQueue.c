#include "LinkedQueue.h"
#include <stdio.h>
#include <stdlib.h>


/** 是否为空 */
Status isQueueEmpty(pQueue q)
{
    if(q->length == 0)
        return TRUE;
    else
        return FALSE;
}

/** 初始化 */
Status QueueInit(pQueue q)
{
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    q->frontQ = node;
    q->rearQ = node;
    node->next = NULL;
    q->length = 0;
    return OK;
}

/** 进队，从队尾进队 */
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

/** 出队 */
Status QueueDelet(pQueue q, BiTree** elem)
{
    if(isQueueEmpty(q))
    {
        printf("队列是空的！！！\n");
        return ERROR;
    }
    QueueNode * node = q->frontQ->next;
    *elem = node->data;
    q->frontQ->next = node->next;
    //!!!!
    if(node == q->rearQ)    //node是最后一个元素
        q->rearQ = q->frontQ;
    q->length--;
    free(node);
    return OK;
}
