#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"
#include "stack.h"
#include "CSTree.h"
//#include "FileTest.h"
#include "Haffman.h"

void TestBinaryTree();
void TestCSTree();
void TestHaffman();

int main()
{
    //TestBinaryTree();
    //TestCSTree();
    //PrintDir("D:\\C-C++\\Test", 0);       //�ļ�����
    TestHaffman();
    //printf("\n\n�ļ����ݣ�\n");
    //printfText(PATH);
    return 0;
}

/**
 * ѹ���ͽ�ѹ��������ЩСbug���ļ������ļ����ַ��޷���ѹ������
 */
void TestHaffman()
{
    Haffman haff;
    HaffInit(&haff);
    Compress(&haff, PATH, PATH_MID_OUT);
    printf("\n\n");
    DeCompress(&haff, PATH_MID_OUT, PATH_OUT);
}

void TestCSTree()
{
    CSTree cst;
    int depth;
    InitCSTree(&cst);
    printf("��������ڵ㣺");
    CreatCSTree(&cst);

    printf("������ǰ����������\n");
    PreOrderTraverseCS(cst);

    printf("\n�����Ĳ�����������\n");
    depth = LevelTraverseCS(cst);

    printf("\n��������ȣ�%d\n", depth);

}

void TestBinaryTree()
{
     char str[20];
    BiTree * btree = (BiTree*)malloc(sizeof(BiTree));

    scanf("%s", str);
    PreOrderInputTree(str, &btree);

    //CreatBinTree(btree);

    printf("\nǰ����������\n");
    //PreOrderTraverse(btree);
    PreOrderTraverse_Re(btree);

    printf("\n������������\n");
    InOrderTraverse_Re(btree);

    //InThreading(btree);

    printf("\n\n����������\n");
    //PostOrderTraverse(btree);
    PostOrderTraverse_Re(btree);

    printf("\n\n����������\n");
    ZOrderTraverse(btree);

    free(btree);
}
