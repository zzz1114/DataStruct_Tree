#ifndef HAFFMAN_H_INCLUDED
#define HAFFMAN_H_INCLUDED

#define MAX_HAFF_SIZE 255       //最大编码字符数量

typedef struct HaffNode{
    char data;          //字符
    int weight;         //字符对应的权值
    char code[50];      //哈弗曼编码
    struct HaffNode* left;
    struct HaffNode* right;
}HaffNode;

typedef struct Haff{
    HaffNode* HaffArray[MAX_HAFF_SIZE]; //保存所有哈夫曼节点的数组
    HaffNode* arr[MAX_HAFF_SIZE];       //保存已有字符节点数组，创建哈夫曼树就用这个数组
    int length;
}Haffman;


/** 根据节点数组中中的节点创建一棵哈夫曼树 */
void CreatHaffTree(HaffNode* arr[], int* length);

/** 根据节点的权值排序 */
void SortByWeight(HaffNode* arr[], int length);

/** 打印数组内容 */
void PrintHaffArr(HaffNode* arr[], int length);

/** 哈夫曼树的层序遍历 */
void LevelTraverseHaff(HaffNode* haff);

/** 根据一个哈夫曼树创建哈夫曼编码 */
void GetHaffCode(HaffNode* haff);

/** 压缩一个文件，输出另一个二进制文件 */
void Compress(Haffman* haff, char path[], char out[]);

/**
 * 解压缩
 * @param path 已经压缩了的二进制文件
 * @param out 输出文件
 */
void DeCompress(Haffman* haff, char path[], char out[]);

void HaffInit(struct Haff* haff);

/****************** 文件操作，创造出128个字符节点 *****************/

#define PATH            "D:\\C-C++\\C\\DataStruct_second\\Tree\\DataStruct_Tree\\testHaff.txt"
#define PATH_MID_OUT    "D:\\C-C++\\C\\DataStruct_second\\Tree\\DataStruct_Tree\\midout.txt"
#define PATH_OUT        "D:\\C-C++\\C\\DataStruct_second\\Tree\\DataStruct_Tree\\out.txt"

/** 测试，打印文件内容 */
void printfText(char path[]);

/** 创建节点 */
void CreatNode(struct Haff* haff, char path[]);

/****************** 队列结构 *****************/

typedef struct Qnode{
    HaffNode* data;
    struct Qnode* next;
}Qnode;

typedef struct Queue{
    Qnode* Qfront;
    Qnode* Qrear;
}Queue;

/** 初始化 */
void HaffQueInit(Queue* q);

/** 入队 */
void HaffEnQue(Queue* q, HaffNode* haff);

/** 出队 */
void HaffDeQue(Queue* q, HaffNode** haff);

int IsHaffQueEmpty(Queue* q);

#endif // HAFFMAN_H_INCLUDED
