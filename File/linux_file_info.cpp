#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h> 
#include <string.h>
/*
头文件
#include <sys/types.h>    
#include <sys/stat.h>   
int stat(
　　const char *filename    //文件或者文件夹的路径
　　, struct stat *buf      //获取的信息保存在内存中
); 
struct stat  
{   
    dev_t       st_dev;     // ID of device containing file -文件所在设备的ID
    ino_t       st_ino;     // inode number -inode节点号 
    mode_t      st_mode;    // protection -保护模式?  
    nlink_t     st_nlink;   // number of hard links -链向此文件的连接数(硬连接)  
    uid_t       st_uid;     // user ID of owner -user id   
    gid_t       st_gid;     // group ID of owner - group id 
    dev_t       st_rdev;    // device ID (if special file) -设备号，针对设备文件  
    off_t       st_size;    // total size, in bytes -文件大小，字节为单位  
    blksize_t   st_blksize; // blocksize for filesystem I/O -系统块的大小  
    blkcnt_t    st_blocks;  // number of blocks allocated -文件所占块数  
    time_t      st_atime;   // time of last access -最近存取时间  
    time_t      st_mtime;   // time of last modification -最近修改时间  
    time_t      st_ctime;   // time of last status change - 最后一次改变属性的时间
};
*/

int get_hhmmss_from_timestamp(long timestamp)
{   
    timestamp += 8*3600;    // 北京时间+8h
    timestamp %= 86400;
    return (timestamp / 3600) * 10000 + (timestamp / 60 % 60) * 100 + timestamp % 60;
}

long get_file_last_modify_time(const char* filename)
{   
    FILE * fp;
    int fd;
    struct stat file_stat;
    fp = fopen(filename,"r"); 
    if (fp == NULL)
    {   
        perror(filename);
        return -1;
    }
    fd = fileno(fp);
    fstat(fd, &file_stat); 
    long modify_time=file_stat.st_mtime; 
    fclose(fp);

    int mtime = get_hhmmss_from_timestamp(modify_time);
    printf("%s modify time %ld, %06d\n", 
           filename, modify_time, mtime);

    return modify_time;
}

int main()
{
    long t;
    t = get_file_last_modify_time("data.txt");
    t = get_file_last_modify_time("data");
    return 0;
}