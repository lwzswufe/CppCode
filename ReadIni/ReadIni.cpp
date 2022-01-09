#include "ReadIni.h"

// 识别区域开始字符的位置
static int BEGIN {0};
// 下一个字符 识别区域末尾部分字符的位置
static int FORWARD {0};
// 行号 表示第几行
static int LINE_ID {0};
// 当前行起始位置
static int LINE_START_ID;
// 缓冲区
static const int BUFFER_SIZE{1024};
// 字符
static const char* CONTEXT{nullptr};
// 最大字符长度
static const int MAX_WORD_LENGTH{256};
// 文件指针
static FILE* PFILE {nullptr};

void ini_file_line_parse(char* line, std::string &key, std::string &value)
{   // 拆分一行字符串  
    char * pch_1;
    char * pch_2;
    const char delimit[6]{"=[]\r\n"};
    pch_1 = strtok(line, delimit);
    if (pch_1 != NULL)
        key = pch_1;
    else
        key = "";

    pch_2 = strtok(NULL, delimit);
    if (pch_2 != NULL)
        value = pch_2;
    else
        value = "";
}


// 从文件读取指定长度的字符串
static void ReadFile()
{   
    // 缓冲区
    static char buffer[BUFFER_SIZE];
    if (BEGIN == 0)
    {   // 第一次读取
        int result = fread(buffer, 1, BUFFER_SIZE - 1, PFILE);
        if (result == 0)
        {
            char s[512];
            sprintf(s, "we read 0 char from ini file");
            throw runtime_error(s);
        }
        // 标记缓冲区末尾
        buffer[result] = EOF;
        // 设置CONTEXT 指向buffer
        CONTEXT = buffer;
        printf("read %d char from file\n", result);
    }
    else
    {   
        printf("Begin: %d %c Forward:%d %c %d \n", BEGIN, CONTEXT[BEGIN], FORWARD, CONTEXT[FORWARD], CONTEXT[FORWARD]);
        // 临时变量
        char temp[BUFFER_SIZE];
        // 缓冲区剩余字符数量
        int residual = BUFFER_SIZE - 1 - BEGIN;
        // 拷贝尚未读取的文字
        strncpy(temp, buffer + BEGIN, residual);
        // 重置缓冲区
        memset(buffer, 0, BUFFER_SIZE);
        // 恢复未读取的部分
        strncpy(buffer, temp, residual);
        // 从文件里读取新内容
        int result = fread(buffer + residual, 1, BUFFER_SIZE - 1 - residual, PFILE);
        // 更新FORMARD 位置
        FORWARD -= BEGIN;
        // 更新BEGIN 位置
        BEGIN = 0;
        // 标记缓冲区末尾
        buffer[result + residual] = EOF;
        printf("Begin: %d %c Forward:%d %c %d\n", BEGIN, CONTEXT[BEGIN], FORWARD, CONTEXT[FORWARD], CONTEXT[FORWARD]);
        printf("read %d char from file\n", result);
    }
}


// 获取下一个字符
static char NextChar()
{   
    if (FORWARD > BUFFER_SIZE - 2)
    {
        ReadFile();
    }
    char c = CONTEXT[FORWARD++];
    if (c == '\n')
    {   
        // printf("find new line %d\n", FORWARD);
        ++LINE_ID;
        LINE_START_ID = FORWARD;
    }
    return c; 
}


std::string IndentifyComments(char c)
{
    // 从;开始  到 \n 结束 忽略末尾的\r
    // 返回识别的注释
    char last{0};
    while (c != EOF && c != '\n')
    {   
        c = NextChar();
    }
    // 检查终止符号错误
    if (c != '\n' && c != EOF)
    {
        char s[512];
        sprintf(s, "we can not find char \\\n for comments at Line:%s", LINE_ID);
        throw runtime_error(s);
    }
    // 识别完毕 提取字符
    char s[MAX_WORD_LENGTH];
    strncpy(s, CONTEXT+BEGIN, FORWARD - BEGIN);
    s[FORWARD - BEGIN] = 0;
    // 忽略末尾的\r
    if (FORWARD - BEGIN > 0 && s[FORWARD - BEGIN - 1] =='\r')
    {
        s[FORWARD - BEGIN - 1] = 0;
    }
    std::string comments{s};
    return comments;
}

std::string IdentifyValue(char c)
{   // = 开始 到 ;或 换行符 结束
    // 读取配置信息名称
    while (c > 0 && (c != ';' && c != '\n' && c != EOF) && c < 128)
    {   
        c = NextChar();
    }
    // 检查终止符号错误
    if (c == ';')
    {   // 最后一个字符是;回退一个字符
        --FORWARD;
    }
    else if (c != '\n' && c != EOF)
    {
        char s[512];
        sprintf(s, "we can not find char ; or \\\n for value at Line:%s", LINE_ID);
        throw runtime_error(s);
        
    }
    // 忽略起始的=
    ++BEGIN;
    // 识别完毕 提取字符
    char s[MAX_WORD_LENGTH];
    strncpy(s, CONTEXT+BEGIN, FORWARD - BEGIN);
    s[FORWARD - BEGIN] = 0;
    // 忽略末尾的\r
    if (FORWARD - BEGIN > 0 && s[FORWARD - BEGIN - 1] =='\r')
    {
        s[FORWARD - BEGIN - 1] = 0;
    }
    std::string name{s};
    return name;
}

std::string IdentifyKey(char c)
{   // 从字母下划线 开始 到 = 结束 忽略自第一个空格/制表符开始的字符
    // 读取配置信息名称
    while (c > 0 && c != '=' && c < 128)
    {   
        c = NextChar();
    }
    // 检查终止符号错误
    if (c != '=')
    {
        char s[512];
        sprintf(s, "we can not find char =");
        throw runtime_error(s);
        
    }
    else
    {
        --FORWARD;
    }
    // 识别完毕 提取字符
    char s[MAX_WORD_LENGTH];
    strncpy(s, CONTEXT+BEGIN, FORWARD - BEGIN);
    s[FORWARD - BEGIN] = 0;
    // 上一个被发现的空白符号的坐标
    int blank_idx = FORWARD - BEGIN;
    for (int i = 0; i < FORWARD - BEGIN; ++i)
    {
        if (s[i] == ' ' || s[i] == '\t')
        {
            s[i] = 0;
            blank_idx = i;
        }
        else if (i > blank_idx)
        {
            char str[512];
            sprintf(str, "we can find a blank char in word:%s at Line:%d", s,  LINE_ID);
            throw runtime_error(s);
        }
    }
    std::string name{s};
    return name;
}

std::string IdentifySection(char c)
{   // 从[ 开始  到 ] 结束
    // 返回识别的章节名称
    char last{0};
    while (c > 0 && c != ']' && c < 128)
    {   
        c = NextChar();
    }
    // 检查终止符号错误
    if (c != ']')
    {
        char s[512];
        sprintf(s, "we can not find char ] final char is:%c at line:%d", c, LINE_ID);
        throw runtime_error(s);
    }
    // 识别完毕 提取字符 去除首尾的[]
    char s[MAX_WORD_LENGTH];
    strncpy(s, CONTEXT+BEGIN+1, FORWARD - BEGIN-2);
    s[FORWARD - BEGIN-2] = 0;
    std::string name{s};
    return name;
}

void AddSection(IniType& config, std::string &name, IniSectionType &cur_section)
{   // 添加章节信息
    if (!name.empty())
        config[name] = cur_section;
    printf("add section:%s\n", name.c_str());
    cur_section.clear();
}


IniType ReadIni(const char* filename)   
{   
    // 尝试打开配置文件
    FILE* pFile = fopen (filename , "r");
    if (pFile == nullptr)
    {   
        char s[512];
        sprintf(s, "%s Line %d error in read %s\n", __func__, __LINE__, filename);
        printf(s);
        throw runtime_error(s);
    }
    // 初始化 缓冲区
    PFILE = pFile;
    ReadFile();
    // 开始处理配置信息
    char c{0}, next_c{0};
    std::string name, key, value, comment;
    IniSectionType cur_section{};
    IniType config{};
    c = NextChar();
    while (c > 0)
    {   
        switch (c)
        {
            case '[':
                // 开始读取章节名称
                c = NextChar();
                AddSection(config, name, cur_section);
                name = IdentifySection(c); 
            case ';':
                // 开始读取注释
                comment = IndentifyComments(c); break;
            case 'a' ... 'z':
            case 'A' ... 'Z':
            case '_':
                // 开始读取配置信息
                c = NextChar();
                key = IdentifyKey(c);
                value.clear();
                cur_section[key] = value;
                break;
            case '=':
                // 开始读取配置值
                c = NextChar();
                value = IdentifyValue(c);
                // printf("find %s_=_%s\n", key.c_str(), value.c_str());
                cur_section[key] = value; break;
            default:
                ;
                // pass
        }
        BEGIN = FORWARD;
        c = NextChar();
    }
    printf("final c is :%c %d FORWARD:%d  %d %d\n", c, c, FORWARD, CONTEXT[FORWARD-1], CONTEXT[FORWARD]);
    printf("%s", CONTEXT);
    // 添加最后一个章节
    AddSection(config, name, cur_section);
    printf("\n>>>>>>>>>>scan over<<<<<<<<<<\n");
    return config;
};


void ShowIni(IniType config)
{   //显示配置文件的内容
    char buffer[100];
    for (auto i= config.begin(); i!= config.end(); i++)
    {   
        std::string key = i->first;
        auto value      = i->second;
        sprintf(buffer, "[%s]:\n", key.data());
        fputs (buffer , stdout);  
        for (auto ii= value.begin(); ii != value.end(); ii++)
        {
            std::string key_   = ii->first;
            std::string value_ = ii->second;
            sprintf(buffer, "        <%s : %s>\n", key_.data(), value_.data());
            fputs (buffer , stdout);  
        }
    }
}

std::vector<double> read_vector_from_ini(std::string linestr)
{   
    std::vector<double> vec_d;
    char *word, *next_token = NULL, line_c[1024];
    const char delimit[7]{",=[]\r\n"};
    strncpy(line_c, linestr.c_str(), 1024);
    word = strtok(line_c, delimit);
    while (word != NULL)
    {   
        vec_d.push_back(atof(word));
        word = strtok(NULL, delimit);
    }
    return vec_d;
}

int GetIntFromKey(IniSectionType &strmap, std::string key)
{
    std::string value = strmap[key];
    char s[128];
    int i;
    if (value.empty())
    {
        sprintf(s, "No Key Named >>>%s<<<\n", key.c_str());
        printf(s);
        i = 0;
    }
    else
    {   
        i = stoi(value);
        sprintf(s, "Set %s:%d\n", key.c_str(), i);
        printf(s);
    }
    return i;
}

double GetDoubleFromKey(IniSectionType &strmap, std::string key)
{
    std::string value = strmap[key];
    char s[128];
    double d;
    if (value.empty())
    {
        sprintf(s, "No Key Named >>>%s<<<\n", key.c_str());
        printf(s);
        d = 0;
    }
    else
    {
        d = stof(value);
        printf("Set %s:%.4lf\n", key.c_str(), d);
    }
    return d;
}

std::vector<double> GetVectorDoubleFromKey(IniSectionType &strmap, std::string key)
{
    std::string value = strmap[key];
    char s[128];
    std::vector<double> vec_d;
    if (value.empty())
    {
        sprintf(s, "No Key Named >>>%s<<<\n", key.c_str());
        printf(s);
    }
    else
    {
        vec_d = read_vector_from_ini(value);
        printf("Set %s:", key.c_str());
        for (double d : vec_d)
        {
            printf("%.4lf, ", d);
        }
        printf("\n");
    }
    return vec_d;
}
