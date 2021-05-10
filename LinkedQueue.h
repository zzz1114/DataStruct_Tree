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

/** �Ƿ�Ϊ�� */
Status isQueueEmpty(pQueue q);

/** ��ʼ�� */
Status QueueInit(pQueue q);

/** ���� */
Status QueueInsert(pQueue q, BiTree* elem);

/** ���� */
Status QueueDelet(pQueue q, BiTree** elem);

#endif // LINKEDQUEUE_H_INCLUDED
