#ifndef FILETEST_H_INCLUDED
#define FILETEST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dir.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct FileNode{
    char name[1024];            //文件名
    struct FileNode* firstChild;
    struct FileNode* nextSibling;
}FileNode;

/**
 * 打印目录结构
 * @param dir 给定的目录字符串
 * @param depth 要打印的目录深度
 */
void PrintDir(char * dir, int depth);

#endif // FILETEST_H_INCLUDED
