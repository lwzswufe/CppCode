/*
struct _finddata_t: 这个结构体是用来存储文件各种信息的。
遍历给定目录下所有子目录，查找*.txt，放入stringArray中

unsigned atrrib：文件属性的存储位置。它存储一个unsigned单元，用于表示文件的属性。文件属性是用位表示的，主要有以下一些：
                _A_ARCH（存档）、_A_HIDDEN（隐藏）、_A_NORMAL（正常）、_A_RDONLY（只读）、_A_SUBDIR（文件夹）、_A_SYSTEM（系统）。
time_t time_create：这里的time_t是一个变量类型（长整型？相当于long int?），
                    用来存储时间的，我们暂时不用理它，只要知道，这个time_create变量是用来存储文件创建时间的就可以了。
time_t time_access：文件最后一次被访问的时间。
time_t time_write： 文件最后一次被修改的时间。
_fsize_t size：     文件的大小。这里的_fsize_t应该可以相当于unsigned整型，表示文件的字节数。
char name[_MAX_FNAME]：文件的文件名。这里的_MAX_FNAME是一个常量宏，它在<stdlib.h>头文件中被定义，表示的是文件名的最大长度。

long _findfirst( char *filespec, struct _finddata_t *fileinfo )；
        返回值：如果查找成功的话，将返回一个long型的唯一的查找用的句柄（就是一个唯一编号）。这个句柄将在_findnext函数中被使用。
        若失败，则返回-1。
int _findnext( long handle, struct _finddata_t *fileinfo );
        返回值：若成功返回0，否则返回-1。
int _findclose( long handle );
        返回值：成功返回0，失败返回-1。
*/
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>
using std::cout; using std::endl;
#include <io.h>  

void getFiles(string filepath, vector<string>& files, bool is_search_subdir=false)  
{  
    long   handle_File = 0;               //文件句柄   
    struct _finddata_t fileinfo;    // 文件信息类 文件信息  
    string sub_dir, filename;
    string p;                       // str2.assign(str1);即用str1给str2赋值
                                    // 查找第一个文件 并赋值给fileinfo
    handle_File = _findfirst(p.assign(filepath).append("\\*").c_str(), &fileinfo);
    if (handle_File !=  -1)  
    {  
        do                          //如果是目录,迭代之  
        {                           //如果不是,加入列表
            if(is_search_subdir and (fileinfo.attrib &  _A_SUBDIR))  
                                    // & 逻辑运算 比较 fileinfo.attrib 与 _A_SUBDIR
            {                       // 迭代 查询子文件夹
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
                    sub_dir = p.assign(filepath).append("\\").append(fileinfo.name);
                    getFiles(sub_dir, files, true);  
            }  
            else  
            {   
                filename = p.assign(filepath).append("\\").append(fileinfo.name);
                files.push_back(filename);  
            }  
        }
        while(_findnext(handle_File, &fileinfo)  == 0);  
        {
            _findclose(handle_File);  // 结束查找
        }
    }  
}

int main()
{   
    const char * filePath{"D:\\Share"}; 
    vector<string> files;
    ////获取该路径下的所有文件  
    getFiles(filePath, files);  
    getFiles(filePath, files, true);  
      
    int size = files.size();  
    for (int i = 0;i < size;i++)  
    {  
        cout << files[i].c_str() << endl;  
    }  
    return 0;
}

