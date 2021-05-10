#include "Tree.h"
#include "stack.h"
#include "LinkedQueue.h"
#include <stdio.h>
#include <stdlib.h>

/**
 *  为树tree中的parent结点添加一个孩子结点
 */
void InsertChild(Tree* tree, Node* parent, ElemType elem)
{
    if(tree->nodes == MAX_SIZE)
    {
        printf("结点满了，添加失败\n");
        return;
    }
    int index = 0;
    child* newChild = (child*)malloc(sizeof(child));    //创建一个parent的孩子

    child* leftSib = parent->child; //找到parent的最右边的孩子
    for(int i = 0; i < tree->nodes; i++)
    {
        if(tree->node[i].data.id == parent->data.id && tree->node[i].data.name == parent->data.name)
        {
            index = i;    //找到parent的下标
            break;
        }
    }
    tree->node[tree->nodes].child = NULL;
    tree->node[tree->nodes].data = elem;
    tree->node[tree->nodes].parent = index;

    newChild->index = tree->nodes;
    newChild->sibling = NULL;       //没有右兄弟

    tree->nodes++;
    if(!parent->child)
    {
        parent->child = newChild;
        return;
    }
    while(leftSib->sibling != NULL)
    {
        leftSib = leftSib->sibling;
    }
    leftSib->sibling = newChild;
    return;
}

/** 是否有孩子结点 */
Status HaveChild(BiTree * T)
{
    if(T->lchild || T->rchild)  //可以用T->RTag  T->LTag来判断 现在没有线索化二叉树
        return TRUE;
    else
        return FALSE;
}

/** 递归法 前序遍历输出二叉树 *****/
void PreOrderTraverse(BiTree * T)
{
    if(T == NULL)
        return;
    else
    {
        printf("%c ", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

/** 递归法 后序遍历输出二叉树 *****/
void PostOrderTraverse(BiTree * T)
{
    if(T == NULL)
        return;
    else
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c ", T->data);
    }
}

/** 递归法 中序遍历线索化二叉树二叉树 */
BiTree* pre;
void InThreading(BiTree * T)
{
    if(T)
    {
        InThreading(T->lchild);

        if(!T->lchild)
        {
            T->lTag = Thread;
            T->lchild = pre;
        }
        if(pre && !pre->rchild)            //前驱没有右孩子
        {
            pre->rTag = Thread;
            pre->rchild = T;
        }
        pre = T;
        InThreading(T->rchild);
    }
}

/** 递归法 创建一棵二叉树 */
int CreatBinTree(BiTree* T)
{
    char ch = getchar();
    printf("adf\n");
    if(ch == '#')  //空标志
    {
        free(T);
        //T = NULL;
        return 0;
    }
    else
    {
        T->lchild = (BiTree*)malloc(sizeof(BiTree));
        T->rchild = (BiTree*)malloc(sizeof(BiTree));
        T->data = ch;
        if(!CreatBinTree(T->lchild))    //传进来的是左孩子的地址，左孩子地址指向的空间释放，并把地址指向空
            T->lchild = NULL;
        if(!CreatBinTree(T->rchild))
            T->rchild = NULL;
    }
    return 1;
}

//ABD##E##CM##F#G##
//ABCDE##FI##JK##L##G##H###
//AB#DE##F##C##
/**
*   使用栈对数进行遍历的方式（前序遍历和中序遍历）
*   1 不断压栈，直到节点左子树为空            找到最左边的叶结点
*   2 出栈一次，将节点更新为出栈节点的右孩子
*   3 重复1 2
*/

/** 非递归方式的前序遍历 */
void PreOrderTraverse_Re(BiTree * T)
{
    //通过栈的方式前序遍历
    BiTree * root = T;
    BiTree * pop = (BiTree*)malloc(sizeof(BiTree));
    BiTree * temp = pop;

    pStack s = (pStack)malloc(sizeof(Stack));
    StackInit(s);

    while(root || !IsStackEmpty(s))
    {
        while(root) //节点不为空
        {
            StackPush(s, root);
            //前序遍历：
            printf("%c - ", root->data);
            root = root->lchild;
        }
        StackPop(s, &pop);
        root = pop->rchild;
    }

    free(temp);
}

/** 非递归方式的中序遍历 */
void InOrderTraverse_Re(BiTree * T)
{
    BiTree * root = T;
    BiTree * pop = (BiTree*)malloc(sizeof(BiTree));
    BiTree * temp = pop;

    pStack s = (pStack)malloc(sizeof(Stack));
    StackInit(s);

    while(root || !IsStackEmpty(s))
    {
        while(root) //节点不为空
        {
            StackPush(s, root);
            root = root->lchild;
        }
        StackPop(s, &pop);
        //中序遍历：
        printf("%c - ", pop->data);
        root = pop->rchild;
    }

    free(temp);
}

/** 非递归方式的后序遍历 */
//前序遍历顺序 root-left-right
//后序遍历顺序 left-rigth-root
//将前序遍历中 left与right交换，最后反过来输出就可以实现后序遍历
void PostOrderTraverse_Re(BiTree * T)
{
    BiTree * root = T;
    BiTree * pop = (BiTree*)malloc(sizeof(BiTree));
    BiTree * temp = pop;

    pStack s = (pStack)malloc(sizeof(Stack));
    pStack res = (pStack)malloc(sizeof(Stack));
    StackInit(s);
    StackInit(res);

    while(root || !IsStackEmpty(s))
    {
        while(root)
        {
            StackPush(s, root);
            StackPush(res, root);
            root = root->rchild;
        }
        StackPop(s, &pop);
        root = pop->lchild;
    }
    while(!IsStackEmpty(res))
    {
        StackPop(res, &pop);
        printf("%c - ", pop->data);
    }

    free(temp);
}

/** 层序遍历，用到队列 */
void ZOrderTraverse(BiTree * T)
{
    Queue q;
    QueueInit(&q);
    BiTree * tree = (BiTree*)malloc(sizeof(BiTree));

    QueueInsert(&q, T);
    while(!isQueueEmpty(&q))
    {
        QueueDelet(&q, &tree);
        printf("%c - ", tree->data);
        if(tree->lchild)
            QueueInsert(&q, tree->lchild);
        if(tree->rchild)
            QueueInsert(&q, tree->rchild);
    }

    free(tree);
}

/**  通过输入树的前序遍历创建一个二叉树
 *  !!!!!!通过递归的方法创建！！！！！！
*/
char * c;
void PreOrderInputTree(char * input, BiTree ** T)
{
    c = input;
    if(*c == 0)
        return;
    if(*c == '#')
    {
        c++;
        *T = NULL;
    }
    else
    {
        (*T) = (BiTree*)malloc(sizeof(BiTree));
        (*T)->data = *c;
        c++;
        PreOrderInputTree(c, &(*T)->lchild);   //!!!!这里要用lchild的地址！！！！
        PreOrderInputTree(c, &(*T)->rchild);    //从上面函数出来后，input被弹栈，会回溯到input++后的结果
    }
}
