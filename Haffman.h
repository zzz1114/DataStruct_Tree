#ifndef HAFFMAN_H_INCLUDED
#define HAFFMAN_H_INCLUDED

#define MAX_HAFF_SIZE 255       //�������ַ�����

typedef struct HaffNode{
    char data;          //�ַ�
    int weight;         //�ַ���Ӧ��Ȩֵ
    char code[50];      //����������
    struct HaffNode* left;
    struct HaffNode* right;
}HaffNode;

typedef struct Haff{
    HaffNode* HaffArray[MAX_HAFF_SIZE]; //�������й������ڵ������
    HaffNode* arr[MAX_HAFF_SIZE];       //���������ַ��ڵ����飬�����������������������
    int length;
}Haffman;


/** ���ݽڵ��������еĽڵ㴴��һ�ù������� */
void CreatHaffTree(HaffNode* arr[], int* length);

/** ���ݽڵ��Ȩֵ���� */
void SortByWeight(HaffNode* arr[], int length);

/** ��ӡ�������� */
void PrintHaffArr(HaffNode* arr[], int length);

/** ���������Ĳ������ */
void LevelTraverseHaff(HaffNode* haff);

/** ����һ������������������������ */
void GetHaffCode(HaffNode* haff);

/** ѹ��һ���ļ��������һ���������ļ� */
void Compress(Haffman* haff, char path[], char out[]);

/**
 * ��ѹ��
 * @param path �Ѿ�ѹ���˵Ķ������ļ�
 * @param out ����ļ�
 */
void DeCompress(Haffman* haff, char path[], char out[]);

void HaffInit(struct Haff* haff);

/****************** �ļ������������128���ַ��ڵ� *****************/

#define PATH            "D:\\C-C++\\C\\DataStruct_second\\Tree\\DataStruct_Tree\\testHaff.txt"
#define PATH_MID_OUT    "D:\\C-C++\\C\\DataStruct_second\\Tree\\DataStruct_Tree\\midout.txt"
#define PATH_OUT        "D:\\C-C++\\C\\DataStruct_second\\Tree\\DataStruct_Tree\\out.txt"

/** ���ԣ���ӡ�ļ����� */
void printfText(char path[]);

/** �����ڵ� */
void CreatNode(struct Haff* haff, char path[]);

/****************** ���нṹ *****************/

typedef struct Qnode{
    HaffNode* data;
    struct Qnode* next;
}Qnode;

typedef struct Queue{
    Qnode* Qfront;
    Qnode* Qrear;
}Queue;

/** ��ʼ�� */
void HaffQueInit(Queue* q);

/** ��� */
void HaffEnQue(Queue* q, HaffNode* haff);

/** ���� */
void HaffDeQue(Queue* q, HaffNode** haff);

int IsHaffQueEmpty(Queue* q);

#endif // HAFFMAN_H_INCLUDED
