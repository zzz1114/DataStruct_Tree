#ifndef CSTREE_H_INCLUDED
#define CSTREE_H_INCLUDED

/**
*   树的孩子兄弟表示法  child-sibling-tree
*/

typedef struct{
    int id;
    char name[10];
}ElementType;

typedef struct CSNode{
    ElementType data;
    struct CSNode* firstChild;  //左孩子，长子
    struct CSNode* nextSibling; //右兄弟
}CSNode, *CSTree;

/** 初始化一棵空树 */
void InitCSTree(CSNode ** cst);

/** 创建一棵树 */
void CreatCSTree(CSNode ** cst);

/** 前序遍历 */
void PreOrderTraverseCS(CSNode * cst);

/** 层序遍历，并返回树的深度 */
int LevelTraverseCS(CSTree cst);



/************ 队列结构 ***********/

typedef struct QueNode{
    CSNode * data;
    struct QueNode * next;
}QueNode;

typedef struct Que{
    QueNode* Qfront;    //队头指针
    QueNode* Qrear;     //队尾指针
}Que, *pQue;

void QueInit(Que * q);

/** 入队列 */
void enQueue(Que * q, CSNode * elem);

/** 出队列 */
int deQueue(Que * q, CSNode ** elem);

int isQueEmpty(Que * q);

#endif // CSTREE_H_INCLUDED



