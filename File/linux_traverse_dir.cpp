// 使用递归来遍历文件夹下的文件

#include<stdio.h>
#include <errno.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATHNAME 512


/*
用于存储目录中的文件信息（文件名、扩展名等等）
struct dirent 
{
    ino_t d_ino;                // inode number 索引节点号 
    off_t d_off;                // offset to this dirent 在目录文件中的偏移 
    unsigned short d_reclen;    // length of this d_name 文件名长 
    unsigned char d_type;       // the type of d_name 文件类型 
    char d_name[256];           // file name (null-terminated) 文件名，最长255字符 
};

*/
extern void print_file_info(const char *pathname);
extern void dir_order(const char *pathname);

void dir_order(const char *pathname)
{
	DIR *dir_ptr;
	char name[MAX_PATHNAME];
	struct dirent *dir_io;
	if ((dir_ptr = opendir(pathname)) == NULL)
	{
		printf("dir_order: can't open %s\n %s", pathname, strerror(errno));
		return;
	}
	while ((dir_io = readdir(dir_ptr)) != NULL)
	{
		if (strncmp(dir_io->d_name, ".", 1) == 0)
			continue; /* 跳过当前文件夹和上一层文件夹以及隐藏文件*/
		if (strlen(pathname) + strlen(dir_io->d_name) + 2 > sizeof(name))
		{
			printf("dir_order: name %s %s too long\n", pathname, dir_io->d_name);
		} 
        else
		{
			memset(name, 0, sizeof(name));
			sprintf(name, "%s/%s", pathname, dir_io->d_name);
			print_file_info(name);
		}
	}
	closedir(dir_ptr);
}

void print_file_info(const char *pathname)
{
	struct stat filestat;
	if (stat(pathname, &filestat) == -1)
	{
		printf("cannot access the file %s", pathname);
		return;
	}
	if ((filestat.st_mode & S_IFMT) == S_IFDIR)
	{   // 文件夹
		dir_order(pathname);
	}
	printf("%s \t\tsize:%8ld\n", pathname, filestat.st_size);
}

int main()
{
	dir_order(".");
    dir_order("..");
	return 0;
}


