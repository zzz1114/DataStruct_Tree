#ifndef CSTREE_H_INCLUDED
#define CSTREE_H_INCLUDED

/**
*   ���ĺ����ֵܱ�ʾ��  child-sibling-tree
*/

typedef struct{
    int id;
    char name[10];
}ElementType;

typedef struct CSNode{
    ElementType data;
    struct CSNode* firstChild;  //���ӣ�����
    struct CSNode* nextSibling; //���ֵ�
}CSNode, *CSTree;

/** ��ʼ��һ�ÿ��� */
void InitCSTree(CSNode ** cst);

/** ����һ���� */
void CreatCSTree(CSNode ** cst);

/** ǰ����� */
void PreOrderTraverseCS(CSNode * cst);

/** ���������������������� */
int LevelTraverseCS(CSTree cst);



/************ ���нṹ ***********/

typedef struct QueNode{
    CSNode * data;
    struct QueNode * next;
}QueNode;

typedef struct Que{
    QueNode* Qfront;    //��ͷָ��
    QueNode* Qrear;     //��βָ��
}Que, *pQue;

void QueInit(Que * q);

/** ����� */
void enQueue(Que * q, CSNode * elem);

/** ������ */
int deQueue(Que * q, CSNode ** elem);

int isQueEmpty(Que * q);

#endif // CSTREE_H_INCLUDED



