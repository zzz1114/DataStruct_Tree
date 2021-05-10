#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "ElementType.h"

#define MAX_SIZE 100

/****** ��ͨ�� ˫�׺��ӱ�ʾ�� ******/
typedef struct child{
    int index;
    struct child* sibling;   //���ֵ�
}child;               //���ӽ�㣬��¼�����ֵܣ�˫��

typedef struct Node{
    ElemType data;
    int parent;     //˫�׽��
    child* child;
}Node;

typedef struct Tree{
    Node node[MAX_SIZE];
    int root;   //���ڵ�λ��
    int nodes;  //�����
}Tree;

void InsertChild(Tree* tree, Node* parent, ElemType elem);  //Ϊ��tree�Ľ��parent����һ������

/****** ������ ********/
typedef enum{Link, Thread} PointerTag;

typedef struct BiTree{
    char data;       //���ݣ���Ϊ�洢һ���ַ�
    struct BiTree * lchild;
    struct BiTree * rchild;
    PointerTag lTag;
    PointerTag rTag;
}BiTree;

/** ����һ�ö����� */
int CreatBinTree(BiTree* T);

/** �Ƿ��к��ӽ�� */
Status HaveChild(BiTree * T);

/**  ͨ����������ǰ���������һ���� */
void PreOrderInputTree(char input[], BiTree ** T);

/**  ǰ����� */
void PreOrderTraverse(BiTree * T);   //ǰ��������������

/**  ������� **/
void PostOrderTraverse(BiTree * T);     //�ݹ鷨Ч�ʱȽϵ�

/** ������������������������� */
void InThreading(BiTree * T);

/** �ǵݹ鷽ʽ��������� */
void InOrderTraverse_Re(BiTree * T);

/** �ǵݹ鷽ʽ��ǰ����� */
void PreOrderTraverse_Re(BiTree * T);

/** �ǵݹ鷽ʽ�ĺ�ȡ���� */
void PostOrderTraverse_Re(BiTree * T);

/** ����������õ����� */
void ZOrderTraverse(BiTree * T);

#endif // TREE_H_INCLUDED
