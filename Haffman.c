#include "Haffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** 根据节点数组中中的节点创建一棵哈夫曼树 */
void CreatHaffTree(HaffNode* arr[], int* length)
{
    if(*length <= 1)
        return;
    //创建过程：先找到数组中权值最小的两个节点，为其创建一个双亲结点
    HaffNode* parent = (HaffNode*)malloc(sizeof(HaffNode));
    HaffNode* left, *right;
    SortByWeight(arr, *length);
    left = arr[*length - 1];     //权值最小的作为左孩子
    right = arr[*length - 2];
    parent->data = '@';
    parent->code[0] = 0;
    parent->left = left;
    parent->right = right;
    parent->weight = left->weight + right->weight;
    arr[*length - 2] = parent;
    (*length)--;
    CreatHaffTree(arr, length);
}

/** 根据节点的权值排序 */
void SortByWeight(HaffNode* arr[], int length)
{
    HaffNode* temp;
    for(int i = 0; i < length - 1; i++)
    {
        for(int j = length - 2; j >= i; j--)
        {
            if(arr[j]->weight < arr[j + 1]->weight)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/** 哈夫曼树的层序遍历 */
void LevelTraverseHaff(HaffNode* haff)
{
    int depth = 2;
    Queue q;
    HaffNode *lastNode, *rightSib;
    HaffNode *temp = (HaffNode*)malloc(sizeof(HaffNode));
    lastNode = haff;
    rightSib = haff;
    HaffQueInit(&q);
    HaffEnQue(&q, haff);
    printf("第1层");
    while(!IsHaffQueEmpty(&q))
    {
        HaffDeQue(&q, &temp);
        if(temp->data == '\n')
            printf("[\\n, %d, %s]-", temp->weight, temp->code);
        else
            printf("[%c, %d, %s]-", temp->data, temp->weight, temp->code);
        if(temp->left != NULL)
        {
            HaffEnQue(&q, temp->left);
            lastNode = temp->left;
        }
        if(temp->right != NULL)
        {
            HaffEnQue(&q, temp->right);
            lastNode = temp->right;
        }
        if(rightSib == temp && !IsHaffQueEmpty(&q))
        {
            printf("\n第%d层：", ++depth);
            rightSib = lastNode;
        }
    }
}

void HaffInit(Haffman* haff)
{
    haff->length = 0;
    for(int i = 0; i < MAX_HAFF_SIZE; i++)
    {
        haff->arr[i] = NULL;
        haff->HaffArray[i] = NULL;
    }
}

/** 根据一个哈夫曼树创建哈夫曼编码 */
int length = 0;
char data[50] = {0};
void GetHaffCode(HaffNode* haff)
{

    //哈夫曼树的所有节点的度都是0或2，没有左(右)孩子，就是叶结点
    if(haff != NULL)
    {
        if(haff->left == NULL)  //是叶结点
        {
            strcpy(haff->code, data);
            return;
        }
        data[length++] = '0';
        data[length] = 0;
        GetHaffCode(haff->left);
        data[length - 1] = '1';
        GetHaffCode(haff->right);
        length--;
        data[length] = 0;
    }
}


/** 打印数组内容 */
void PrintHaffArr(HaffNode* arr[], int length)
{
    for(int i = 0; i < length; i++)
    {
        if(arr[i]->data == '\n')
            printf("[ \\n : %d ]\n", arr[i]->weight);
        else
            printf("[ %c : %d ]\n", arr[i]->data, arr[i]->weight);
    }
}

/** 压缩一个文件，输出另一个二进制文件 */
void Compress(Haffman* haff, char path[], char out[])
{
    long fpSize;
    long outSize;
    char buff[50];  //缓冲区
    int buffLen = 0;//缓冲区长度
    unsigned char byte = 0;     //要保存的二进制数据
    char str[150];
    char* c;
    FILE* fp = fopen(path, "r");
    if(fp == NULL)
        printf("failed to open:<%s>", path);
    FILE* outp = fopen(out, "wb");      //写入二进制文件
    if(outp == NULL)
        printf("failed to creat:<%s>", out);
    CreatNode(haff, path);                 //读取文件，创建字符结点
    CreatHaffTree(haff->arr, &haff->length);  //创建哈夫曼树
    GetHaffCode(haff->arr[0]);
    fgets(str, 100, fp);
    c = str;
    //根据文件内容把所有字符替换成哈夫曼编码
    while(1)
    {
        if(buffLen < 20)
        {
            strcpy(buff + buffLen, haff->HaffArray[(int)*c]->code);
            buffLen += strlen(haff->HaffArray[(int)*c]->code);
            c++;
            if(*c == 0)
            {
                if(fgets(str, 100, fp) == NULL)
                {
                    break;
                }
                c = str;
            }
        }
        if(buffLen >= 15)
        {
            byte = 0;
            for(int i = 0; i < 8; i++)
            {
                if(buff[i] == '1')
                    byte++;
                if(i < 7)
                    byte *= 2;
            }
            //printf("%u\n", byte);
            buffLen -= 8;
            for(int i = 0; i <= buffLen; i++)
            {
                buff[i] = buff[i + 8];
            }
            fwrite(&byte, sizeof(unsigned char), 1, outp);
        }
    }
    printf("\n***********************************\n");
    printf("  压缩完成！ \n");
    printf("  压缩前：%ldKb \n", fpSize = ftell(fp));
    printf("  压缩后：%ldKb  \n", outSize = ftell(outp));
    printf("  压缩比：%d%%  \n", (int)(outSize * 100 / fpSize));
    printf("***********************************\n");
    fclose(fp);
    fclose(outp);

    printf("\n\n\n节点哈夫曼树：\n");
    //最后应该把剩余的字符也写进去
    LevelTraverseHaff(haff->arr[0]);
}

/**
 * 解压缩
 * @param path 已经压缩了的二进制文件
 * @param out 输出文件
 */
void DeCompress(Haffman* haff, char path[], char out[])
{
    unsigned char byte = 0;
    char temp[8];       //二进制转化成的字符串
    char buff[50];
    int buffLen = 0;
    int index;          //解码时的下标
    HaffNode* node = NULL;

    FILE* filep = fopen(path, "rb");
    if(filep == NULL)
        printf("failed to open:<%s>", path);

    FILE* outp = fopen(out, "w");
    if(outp == NULL)
        printf("failed to creat:<%s>", out);

    while(1)
    {
        //先将byte转成字符串
        if(buffLen < 20)
        {
            if(fread(&byte, sizeof(unsigned char), 1, filep) == 0)      //一定要转字符的时候再去读取，不要在while里面读取
                break;
            for(int i = 0; i < 8; i++)
            {
                temp[i] = byte % 2 + '0';
                byte /= 2;
            }
            for(int i = 0; i < 8; i++)
            {
                buff[buffLen + i] = temp[7 - i];
            }
            buffLen += 8;
            buff[buffLen] = '\0';
        }
        if(buffLen > 15)        //执行解码 应该是大于 树的深度-1
        {
            index = 0;
            node = haff->arr[0];
            while(node->left != NULL || node->right != NULL)        //不是叶结点
            {
                if(buff[index] == '0')
                    node = node->left;
                else if(buff[index] == '1')
                    node = node->right;
                index++;
            }
            fwrite(&node->data, 1, 1, outp);
            //fprintf(outp, "%c", node->data);
            buffLen -= index;
            for(int i = 0; i <= buffLen; i++)
            {
                buff[i] = buff[i + index];
            }
        }
    }
    fclose(filep);
    fclose(outp);
}


/**************** 文件操作 **************/

void printfText(char path[])
{
    char str[150];
    FILE* file = fopen(path, "r");
    if(file == NULL)
    {
        printf("打开文件失败！！\n");
        return;
    }
    while(fgets(str, 100, file) != NULL)
    {
        printf("%s\n", str);
    }
}

/** 创建节点 */
void CreatNode(Haffman* haff, char path[])
{
    char str[150];
    char* c;
    FILE* file = fopen(path, "r");
    if(file == NULL)
    {
        printf("打开文件失败！！\n");
        return;
    }
    while(fgets(str, 100, file) != NULL)
    {
        c = str;
        while(*c)
        {
            if(*c > 255)
            {
                printf("错误！！！\n");
                return;
            }
            if(haff->HaffArray[(int)*c] == NULL)    //还没有这个节点就创建一个节点
            {
                HaffNode* node = (HaffNode*)malloc(sizeof(HaffNode));
                node->data = *c;
                node->code[0] = 0;
                node->weight = 1;
                node->left = NULL;
                node->right = NULL;

                haff->arr[haff->length] = node;         //记录一下这个节点
                haff->HaffArray[(int)*c] = node;
                haff->length++;
            }
            else
            {
                haff->HaffArray[(int)*c]->weight++;
            }
            c++;
        }
    }
    printf("\ndone!\n\n");
}




/**************** 队列结构 ***************/


/** 初始化 */
void HaffQueInit(Queue* q)
{
    q->Qfront = (Qnode*)malloc(sizeof(Qnode));
    q->Qfront->next = NULL;
    q->Qrear = q->Qfront;
}

/** 入队 */
void HaffEnQue(Queue* q, HaffNode* haff)
{
    Qnode* node = (Qnode*)malloc(sizeof(Qnode));
    node->data = haff;
    node->next = NULL;
    q->Qrear->next = node;
    q->Qrear = node;
}

/** 出队 */
void HaffDeQue(Queue* q, HaffNode** haff)
{
    Qnode* node = q->Qfront->next;
    *haff = node->data;
    q->Qfront->next = node->next;
    if(node == q->Qrear)
        q->Qrear = q->Qfront;
    free(node);
}

int IsHaffQueEmpty(Queue* q)
{
    if(q->Qrear == q->Qfront)
        return 1;
    return 0;
}


