#ifndef FILETEST_H_INCLUDED
#define FILETEST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dir.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct FileNode{
    char name[1024];            //�ļ���
    struct FileNode* firstChild;
    struct FileNode* nextSibling;
}FileNode;

/**
 * ��ӡĿ¼�ṹ
 * @param dir ������Ŀ¼�ַ���
 * @param depth Ҫ��ӡ��Ŀ¼���
 */
void PrintDir(char * dir, int depth);

#endif // FILETEST_H_INCLUDED
