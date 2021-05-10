#include "FileTest.h"

/**
 * 打印目录结构
 * @param dir 给定的目录字符串
 * @param depth 要打印的目录深度
 */
void PrintDir(char * dir, int depth)
{
    DIR * dirPtr;
    char fullName[1024];
    if((dirPtr = opendir(dir)) == NULL)
    {
        sprintf(stderr, "无法打开目录：<%s>\n", dir);
    }
    struct dirent * dirContent;     //目录内容
    while((dirContent = readdir(dirPtr)) != NULL)
    {
        if(strcmp(dirContent->d_name, ".") == 0 || strcmp(dirContent->d_name, "..") == 0)
            continue;
        sprintf(fullName, "%s\\%s", dir, dirContent->d_name);
        printf("%s", fullName);
        struct stat statInfo;
        if(stat(fullName, &statInfo) == -1)
            sprintf(stderr, "无法获取文件<%s>的详细信息！\n", fullName);
        if((statInfo.st_mode & S_IFMT) == S_IFDIR)
        {
            printf("\t\t是一个目录\n");
            PrintDir(fullName, ++depth);
        }
        else if((statInfo.st_mode & S_IFMT) == S_IFREG)
        {
            printf("\t\t是一个文件，大小为：%ld\n", statInfo.st_size);
        }
    }
}











































