#include "Haffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** ���ݽڵ��������еĽڵ㴴��һ�ù������� */
void CreatHaffTree(HaffNode* arr[], int* length)
{
    if(*length <= 1)
        return;
    //�������̣����ҵ�������Ȩֵ��С�������ڵ㣬Ϊ�䴴��һ��˫�׽��
    HaffNode* parent = (HaffNode*)malloc(sizeof(HaffNode));
    HaffNode* left, *right;
    SortByWeight(arr, *length);
    left = arr[*length - 1];     //Ȩֵ��С����Ϊ����
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

/** ���ݽڵ��Ȩֵ���� */
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

/** ���������Ĳ������ */
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
    printf("��1��");
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
            printf("\n��%d�㣺", ++depth);
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

/** ����һ������������������������ */
int length = 0;
char data[50] = {0};
void GetHaffCode(HaffNode* haff)
{

    //�������������нڵ�Ķȶ���0��2��û����(��)���ӣ�����Ҷ���
    if(haff != NULL)
    {
        if(haff->left == NULL)  //��Ҷ���
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


/** ��ӡ�������� */
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

/** ѹ��һ���ļ��������һ���������ļ� */
void Compress(Haffman* haff, char path[], char out[])
{
    long fpSize;
    long outSize;
    char buff[50];  //������
    int buffLen = 0;//����������
    unsigned char byte = 0;     //Ҫ����Ķ���������
    char str[150];
    char* c;
    FILE* fp = fopen(path, "r");
    if(fp == NULL)
        printf("failed to open:<%s>", path);
    FILE* outp = fopen(out, "wb");      //д��������ļ�
    if(outp == NULL)
        printf("failed to creat:<%s>", out);
    CreatNode(haff, path);                 //��ȡ�ļ��������ַ����
    CreatHaffTree(haff->arr, &haff->length);  //������������
    GetHaffCode(haff->arr[0]);
    fgets(str, 100, fp);
    c = str;
    //�����ļ����ݰ������ַ��滻�ɹ���������
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
    printf("  ѹ����ɣ� \n");
    printf("  ѹ��ǰ��%ldKb \n", fpSize = ftell(fp));
    printf("  ѹ����%ldKb  \n", outSize = ftell(outp));
    printf("  ѹ���ȣ�%d%%  \n", (int)(outSize * 100 / fpSize));
    printf("***********************************\n");
    fclose(fp);
    fclose(outp);

    printf("\n\n\n�ڵ����������\n");
    //���Ӧ�ð�ʣ����ַ�Ҳд��ȥ
    LevelTraverseHaff(haff->arr[0]);
}

/**
 * ��ѹ��
 * @param path �Ѿ�ѹ���˵Ķ������ļ�
 * @param out ����ļ�
 */
void DeCompress(Haffman* haff, char path[], char out[])
{
    unsigned char byte = 0;
    char temp[8];       //������ת���ɵ��ַ���
    char buff[50];
    int buffLen = 0;
    int index;          //����ʱ���±�
    HaffNode* node = NULL;

    FILE* filep = fopen(path, "rb");
    if(filep == NULL)
        printf("failed to open:<%s>", path);

    FILE* outp = fopen(out, "w");
    if(outp == NULL)
        printf("failed to creat:<%s>", out);

    while(1)
    {
        //�Ƚ�byteת���ַ���
        if(buffLen < 20)
        {
            if(fread(&byte, sizeof(unsigned char), 1, filep) == 0)      //һ��Ҫת�ַ���ʱ����ȥ��ȡ����Ҫ��while�����ȡ
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
        if(buffLen > 15)        //ִ�н��� Ӧ���Ǵ��� �������-1
        {
            index = 0;
            node = haff->arr[0];
            while(node->left != NULL || node->right != NULL)        //����Ҷ���
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


/**************** �ļ����� **************/

void printfText(char path[])
{
    char str[150];
    FILE* file = fopen(path, "r");
    if(file == NULL)
    {
        printf("���ļ�ʧ�ܣ���\n");
        return;
    }
    while(fgets(str, 100, file) != NULL)
    {
        printf("%s\n", str);
    }
}

/** �����ڵ� */
void CreatNode(Haffman* haff, char path[])
{
    char str[150];
    char* c;
    FILE* file = fopen(path, "r");
    if(file == NULL)
    {
        printf("���ļ�ʧ�ܣ���\n");
        return;
    }
    while(fgets(str, 100, file) != NULL)
    {
        c = str;
        while(*c)
        {
            if(*c > 255)
            {
                printf("���󣡣���\n");
                return;
            }
            if(haff->HaffArray[(int)*c] == NULL)    //��û������ڵ�ʹ���һ���ڵ�
            {
                HaffNode* node = (HaffNode*)malloc(sizeof(HaffNode));
                node->data = *c;
                node->code[0] = 0;
                node->weight = 1;
                node->left = NULL;
                node->right = NULL;

                haff->arr[haff->length] = node;         //��¼һ������ڵ�
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




/**************** ���нṹ ***************/


/** ��ʼ�� */
void HaffQueInit(Queue* q)
{
    q->Qfront = (Qnode*)malloc(sizeof(Qnode));
    q->Qfront->next = NULL;
    q->Qrear = q->Qfront;
}

/** ��� */
void HaffEnQue(Queue* q, HaffNode* haff)
{
    Qnode* node = (Qnode*)malloc(sizeof(Qnode));
    node->data = haff;
    node->next = NULL;
    q->Qrear->next = node;
    q->Qrear = node;
}

/** ���� */
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


