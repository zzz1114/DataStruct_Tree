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
    //PrintDir("D:\\C-C++\\Test", 0);       //文件测试
    TestHaffman();
    //printf("\n\n文件内容：\n");
    //printfText(PATH);
    return 0;
}

/**
 * 压缩和解压缩还是有些小bug，文件最后面的几个字符无法解压缩出来
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
    printf("请输入根节点：");
    CreatCSTree(&cst);

    printf("该树的前序遍历结果：\n");
    PreOrderTraverseCS(cst);

    printf("\n该树的层序遍历结果：\n");
    depth = LevelTraverseCS(cst);

    printf("\n该树的深度：%d\n", depth);

}

void TestBinaryTree()
{
     char str[20];
    BiTree * btree = (BiTree*)malloc(sizeof(BiTree));

    scanf("%s", str);
    PreOrderInputTree(str, &btree);

    //CreatBinTree(btree);

    printf("\n前序遍历结果：\n");
    //PreOrderTraverse(btree);
    PreOrderTraverse_Re(btree);

    printf("\n中序遍历结果：\n");
    InOrderTraverse_Re(btree);

    //InThreading(btree);

    printf("\n\n后序遍历结果\n");
    //PostOrderTraverse(btree);
    PostOrderTraverse_Re(btree);

    printf("\n\n层序遍历结果\n");
    ZOrderTraverse(btree);

    free(btree);
}
