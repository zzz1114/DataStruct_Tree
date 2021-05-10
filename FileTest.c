#include "FileTest.h"

/**
 * ��ӡĿ¼�ṹ
 * @param dir ������Ŀ¼�ַ���
 * @param depth Ҫ��ӡ��Ŀ¼���
 */
void PrintDir(char * dir, int depth)
{
    DIR * dirPtr;
    char fullName[1024];
    if((dirPtr = opendir(dir)) == NULL)
    {
        sprintf(stderr, "�޷���Ŀ¼��<%s>\n", dir);
    }
    struct dirent * dirContent;     //Ŀ¼����
    while((dirContent = readdir(dirPtr)) != NULL)
    {
        if(strcmp(dirContent->d_name, ".") == 0 || strcmp(dirContent->d_name, "..") == 0)
            continue;
        sprintf(fullName, "%s\\%s", dir, dirContent->d_name);
        printf("%s", fullName);
        struct stat statInfo;
        if(stat(fullName, &statInfo) == -1)
            sprintf(stderr, "�޷���ȡ�ļ�<%s>����ϸ��Ϣ��\n", fullName);
        if((statInfo.st_mode & S_IFMT) == S_IFDIR)
        {
            printf("\t\t��һ��Ŀ¼\n");
            PrintDir(fullName, ++depth);
        }
        else if((statInfo.st_mode & S_IFMT) == S_IFREG)
        {
            printf("\t\t��һ���ļ�����СΪ��%ld\n", statInfo.st_size);
        }
    }
}











































