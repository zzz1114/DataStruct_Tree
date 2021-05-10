#ifndef LINKEDQUEUE_H_INCLUDED
#define LINKEDQUEUE_H_INCLUDED

#include "ElementType.h"
#include "Tree.h"

typedef struct QueueNode{
    BiTree * data;
    struct QueueNode* next;
}QueueNode;

typedef struct Queue{
    QueueNode* frontQ;
    QueueNode* rearQ;
    int length;
}Queue, *pQueue;

/** 是否为空 */
Status isQueueEmpty(pQueue q);

/** 初始化 */
Status QueueInit(pQueue q);

/** 进队 */
Status QueueInsert(pQueue q, BiTree* elem);

/** 出队 */
Status QueueDelet(pQueue q, BiTree** elem);

#endif // LINKEDQUEUE_H_INCLUDED
