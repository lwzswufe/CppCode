#include <string>
using std::string;
#include <sstream>
using std::ostringstream;
#include <string.h>
#include <iostream>
using std::cout; using std::endl;
#include <sys/time.h>

double get_time()
{
    struct timeval    tv; 
    struct timezone   tz; 
    struct tm         *p; 
    gettimeofday(&tv, &tz); 
    p = localtime(&tv.tv_sec);
    double now = p->tm_hour * 3600.0 +  p->tm_min * 60.0 + 
                 p->tm_sec * 1.0 + tv.tv_usec / 1000000.0;
    return now;
}

string vol_array2str(int arr_len, int * array)
{
    ostringstream string_out;
    for (int i = 0; i < arr_len; i++)
        string_out << array[i] << ", ";
    return string_out.str();
}

string vol_array2str_5(int arr_len, int * array)
{
    ostringstream string_out;
    for (int i = 0; i < arr_len; i+=5)
        string_out  << array[i+0] << ", " 
                    << array[i+1] << ", "
                    << array[i+2] << ", "
                    << array[i+3] << ", "
                    << array[i+4] << ", ";
    return string_out.str();
}

void vol_array2str(int arr_len, int * array, char * s)
{
    for (int i = 0; i < arr_len; i++)
    {
        sprintf(s + strlen(s), "%d, ", array[i]);
    }
}

void vol_array2str_5(int arr_len, int * array, char * s)
{
    for (int i = 0; i < arr_len; i+=5)
    {
        sprintf(s + strlen(s), "%d, %d, %d, %d, %d, ", 
        array[i+0], array[i+1], array[i+2], array[i+3], array[i+4]);
    }
}

void vol_array2str_10(int arr_len, int * array, char * s)
{
    for (int i = 0; i < arr_len; i+=10)
    {
        sprintf(s + strlen(s), "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, ", 
        array[i+0], array[i+1], array[i+2], array[i+3], array[i+4],
        array[i+5], array[i+6], array[i+7], array[i+8], array[i+9]);
    }
}

void vol_array2str_50(int arr_len, int * array, char * s)
{
    sprintf(s, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, \
                %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, \
                %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, \
                %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, \
                %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, ", 
                array[0], array[1], array[2], array[3], array[4],
                array[5], array[6], array[7], array[8], array[9],
                array[10], array[11], array[12], array[13], array[14],
                array[15], array[16], array[17], array[18], array[19],
                array[20], array[21], array[22], array[23], array[24],
                array[25], array[26], array[27], array[28], array[29],
                array[30], array[31], array[32], array[33], array[34],
                array[35], array[36], array[37], array[38], array[39],
                array[40], array[41], array[42], array[43], array[44],
                array[45], array[46], array[47], array[48], array[49]);
}

int main()
{   
    const int arr_len = 50, cycle = 10000;
    int arr[arr_len];
    double st_time, base, use_time;;
    for (int i=0; i<arr_len; i++)
    {
        arr[i] = i + 1;
    }
    char s[512];
    st_time = get_time();
    for (int i=0; i<cycle; i++)
    {   
        s[0] = 0;
        vol_array2str(arr_len, arr, s);
    }
    use_time = base = get_time() - st_time;
    printf("sprintf used:%.6lfs ratio:%.4lf\n", use_time, use_time/base);

    st_time = get_time();
    for (int i=0; i<cycle; i++)
        vol_array2str(arr_len, arr);
    use_time = get_time() - st_time;
    printf("isstream used:%.6lfs ratio:%.4lf\n", use_time, use_time/base);

    st_time = get_time();
    for (int i=0; i<cycle; i++)
        vol_array2str(arr_len, arr);
    use_time = get_time() - st_time;
    printf("isstream_multi_5 used:%.6lfs ratio:%.4lf\n", use_time, use_time/base);
    
    st_time = get_time();
    for (int i=0; i<cycle; i++)
    {   
        s[0] = 0;
        vol_array2str_5(arr_len, arr, s);
    }
    use_time = get_time() - st_time;
    printf("sprintf_multi_5 used:%.6lfs ratio:%.4lf\n", use_time, use_time/base);

    st_time = get_time();
    for (int i=0; i<cycle; i++)
    {   
        s[0] = 0;
        vol_array2str_10(arr_len, arr, s);
    }
    use_time = get_time() - st_time;
    printf("sprintf_multi_10 used:%.6lfs ratio:%.4lf\n", use_time, use_time/base);

    st_time = get_time();
    for (int i=0; i<cycle; i++)
    {   
        s[0] = 0;
        vol_array2str_50(arr_len, arr, s);
    }
    use_time = get_time() - st_time;
    printf("sprintf_all used:%.6lfs ratio:%.4lf\n", use_time, use_time/base);
    
    st_time = get_time();
    for (int i=0; i<cycle; i++)
    {   
        char* new_s = new char[512]; 
        vol_array2str(arr_len, arr, new_s);
        delete new_s;
    }
    use_time = get_time() - st_time;
    printf("sprintf with new used:%.6lfs ratio:%.4lf\n", use_time, use_time/base);
    return 0;
}