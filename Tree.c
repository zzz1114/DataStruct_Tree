#include "Tree.h"
#include "stack.h"
#include "LinkedQueue.h"
#include <stdio.h>
#include <stdlib.h>

/**
 *  Ϊ��tree�е�parent������һ�����ӽ��
 */
void InsertChild(Tree* tree, Node* parent, ElemType elem)
{
    if(tree->nodes == MAX_SIZE)
    {
        printf("������ˣ����ʧ��\n");
        return;
    }
    int index = 0;
    child* newChild = (child*)malloc(sizeof(child));    //����һ��parent�ĺ���

    child* leftSib = parent->child; //�ҵ�parent�����ұߵĺ���
    for(int i = 0; i < tree->nodes; i++)
    {
        if(tree->node[i].data.id == parent->data.id && tree->node[i].data.name == parent->data.name)
        {
            index = i;    //�ҵ�parent���±�
            break;
        }
    }
    tree->node[tree->nodes].child = NULL;
    tree->node[tree->nodes].data = elem;
    tree->node[tree->nodes].parent = index;

    newChild->index = tree->nodes;
    newChild->sibling = NULL;       //û�����ֵ�

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

/** �Ƿ��к��ӽ�� */
Status HaveChild(BiTree * T)
{
    if(T->lchild || T->rchild)  //������T->RTag  T->LTag���ж� ����û��������������
        return TRUE;
    else
        return FALSE;
}

/** �ݹ鷨 ǰ�������������� *****/
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

/** �ݹ鷨 ���������������� *****/
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

/** �ݹ鷨 ������������������������� */
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
        if(pre && !pre->rchild)            //ǰ��û���Һ���
        {
            pre->rTag = Thread;
            pre->rchild = T;
        }
        pre = T;
        InThreading(T->rchild);
    }
}

/** �ݹ鷨 ����һ�ö����� */
int CreatBinTree(BiTree* T)
{
    char ch = getchar();
    printf("adf\n");
    if(ch == '#')  //�ձ�־
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
        if(!CreatBinTree(T->lchild))    //�������������ӵĵ�ַ�����ӵ�ַָ��Ŀռ��ͷţ����ѵ�ַָ���
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
*   ʹ��ջ�������б����ķ�ʽ��ǰ����������������
*   1 ����ѹջ��ֱ���ڵ�������Ϊ��            �ҵ�����ߵ�Ҷ���
*   2 ��ջһ�Σ����ڵ����Ϊ��ջ�ڵ���Һ���
*   3 �ظ�1 2
*/

/** �ǵݹ鷽ʽ��ǰ����� */
void PreOrderTraverse_Re(BiTree * T)
{
    //ͨ��ջ�ķ�ʽǰ�����
    BiTree * root = T;
    BiTree * pop = (BiTree*)malloc(sizeof(BiTree));
    BiTree * temp = pop;

    pStack s = (pStack)malloc(sizeof(Stack));
    StackInit(s);

    while(root || !IsStackEmpty(s))
    {
        while(root) //�ڵ㲻Ϊ��
        {
            StackPush(s, root);
            //ǰ�������
            printf("%c - ", root->data);
            root = root->lchild;
        }
        StackPop(s, &pop);
        root = pop->rchild;
    }

    free(temp);
}

/** �ǵݹ鷽ʽ��������� */
void InOrderTraverse_Re(BiTree * T)
{
    BiTree * root = T;
    BiTree * pop = (BiTree*)malloc(sizeof(BiTree));
    BiTree * temp = pop;

    pStack s = (pStack)malloc(sizeof(Stack));
    StackInit(s);

    while(root || !IsStackEmpty(s))
    {
        while(root) //�ڵ㲻Ϊ��
        {
            StackPush(s, root);
            root = root->lchild;
        }
        StackPop(s, &pop);
        //���������
        printf("%c - ", pop->data);
        root = pop->rchild;
    }

    free(temp);
}

/** �ǵݹ鷽ʽ�ĺ������ */
//ǰ�����˳�� root-left-right
//�������˳�� left-rigth-root
//��ǰ������� left��right��������󷴹�������Ϳ���ʵ�ֺ������
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

/** ����������õ����� */
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

/**  ͨ����������ǰ���������һ��������
 *  !!!!!!ͨ���ݹ�ķ�������������������
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
        PreOrderInputTree(c, &(*T)->lchild);   //!!!!����Ҫ��lchild�ĵ�ַ��������
        PreOrderInputTree(c, &(*T)->rchild);    //�����溯��������input����ջ������ݵ�input++��Ľ��
    }
}
