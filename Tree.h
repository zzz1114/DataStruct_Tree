#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "ElementType.h"

#define MAX_SIZE 100

/****** 普通树 双亲孩子表示法 ******/
typedef struct child{
    int index;
    struct child* sibling;   //右兄弟
}child;               //孩子结点，记录结点的兄弟，双亲

typedef struct Node{
    ElemType data;
    int parent;     //双亲结点
    child* child;
}Node;

typedef struct Tree{
    Node node[MAX_SIZE];
    int root;   //根节点位置
    int nodes;  //结点数
}Tree;

void InsertChild(Tree* tree, Node* parent, ElemType elem);  //为树tree的结点parent增加一个孩子

/****** 二叉树 ********/
typedef enum{Link, Thread} PointerTag;

typedef struct BiTree{
    char data;       //数据，简化为存储一个字符
    struct BiTree * lchild;
    struct BiTree * rchild;
    PointerTag lTag;
    PointerTag rTag;
}BiTree;

/** 创建一棵二叉树 */
int CreatBinTree(BiTree* T);

/** 是否有孩子结点 */
Status HaveChild(BiTree * T);

/**  通过输入树的前序遍历创建一棵树 */
void PreOrderInputTree(char input[], BiTree ** T);

/**  前序遍历 */
void PreOrderTraverse(BiTree * T);   //前序遍历输出二叉树

/**  后序遍历 **/
void PostOrderTraverse(BiTree * T);     //递归法效率比较低

/** 中序遍历线索化二叉树二叉树 */
void InThreading(BiTree * T);

/** 非递归方式的中序遍历 */
void InOrderTraverse_Re(BiTree * T);

/** 非递归方式的前序遍历 */
void PreOrderTraverse_Re(BiTree * T);

/** 非递归方式的后取遍历 */
void PostOrderTraverse_Re(BiTree * T);

/** 层序遍历，用到队列 */
void ZOrderTraverse(BiTree * T);

#endif // TREE_H_INCLUDED
