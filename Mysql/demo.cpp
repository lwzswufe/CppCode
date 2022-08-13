#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

/*
gcc -std=c++11 demo.cpp -o demo.out `mysql_config --cflags --libs` -L/usr/lib64/mysql
*/

int main(int argc, char **argv)
{
    // 获取版本信息
    printf("MySQL client version: %s\n", mysql_get_client_info());
    MYSQL mysql;

    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "connector");
    if (!mysql_real_connect(&mysql, "192.168.0.198", "user", "password", "test", 3306, NULL, 0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
            mysql_error(&mysql));
    }
    else
    {
        printf("connect mysql successful\n");
    }
    // 选择数据表
    int res = mysql_select_db(&mysql, "sgy_hoot");
    if (res == 0)
    {
        printf("successful select database sgy_hoot");
    }
    else
    {
        fprintf(stderr, "Failed to select database sgy_hoot: Error: %s\n",
            mysql_error(&mysql));
    }
    // 查看数据表
    MYSQL_RES * result = mysql_list_tables(&mysql, NULL);
    if (result != NULL)
    {
        int num_rows = mysql_num_rows(result);
        int num_fields = mysql_num_fields(result);
        printf("行数：%d,列数:%d\n",num_rows,num_fields);
        for(int i=0;i<num_rows;i++)
        {
            MYSQL_ROW row = mysql_fetch_row(result);//从结果集中获取下一行
            for(int j=0;j<num_fields;j++)
            {
                    printf("%s\t",row[j]);
            }
            printf("\n");
        }
    }
    // 查询数据
    char query_str[1024]{"SELECT fcode, fdatetime, b1pr, b1vol FROM `ticklevel` where fcode='000001';"};
    res = mysql_query(&mysql, query_str);
    if (res == 0)
    {
        // 返回作用在连接上的最近查询的列数
        result = mysql_store_result(&mysql);
        if (result != NULL)
        {
            int num_rows = mysql_num_rows(result);
            int num_fields = mysql_num_fields(result);
            printf("行数：%d,列数:%d\n",num_rows,num_fields);
            for(int i=0;i<num_rows;i++)
            {
                MYSQL_ROW row = mysql_fetch_row(result);//从结果集中获取下一行
                for(int j=0;j<num_fields;j++)
                {
                        printf("%s\t",row[j]);
                }
                printf("\n");
            }
        }
    }
    else
    {
        fprintf(stderr, "Failed to query:%s: Error: %s\n", query_str,
            mysql_error(&mysql));
    }
    // 查询数据 允许查询语句包含二进制 数据 '\0'
    char query_str2[1024]{"SELECT fcode, fdatetime, totalbidvol, b1pr, b1vol FROM `ticklevel` where fcode='000010';"};
    res = mysql_real_query(&mysql, query_str2, 1024);
    if (res == 0)
    {
        // 返回作用在连接上的最近查询的列数
        result = mysql_store_result(&mysql);
        if (result != NULL)
        {
            int num_rows = mysql_num_rows(result);
            int num_fields = mysql_num_fields(result);
            printf("行数：%d,列数:%d\n",num_rows,num_fields);
            // 输出每一列的列名 类型 参见enum_field_types
            MYSQL_FIELD *field;
            while((field = mysql_fetch_field(result)))
            {
                printf("field name %s type:%d\n", field->name, field->type);

            }
            // 输出每一行的数据
            for(int i=0;i<num_rows;i++)
            {   // 输出每一列的数据
                MYSQL_ROW row = mysql_fetch_row(result);//从结果集中获取下一行
                for(int j=0;j<num_fields;j++)
                {       
                    if (row[j] != nullptr)
                        printf("%s\t",row[j]);
                    else
                        printf("None\t");
                }
                printf("\n");
            }
        }
    }
    else
    {
        fprintf(stderr, "Failed to query:%s: Error: %s\n", query_str2,
            mysql_error(&mysql));
    }
    // 插入数据 fcode, fdatetime, b1pr, b1vol 
    char insert_str[1024]{"INSERT INTO `ticklevel` (`fcode`, `fdatetime`, `b1pr`, `b1vol`) VALUES ('100001', '2022-07-18 10:25:00', 13.31, 1478);"};
    res = mysql_query(&mysql, insert_str);
    if (res != 0)
    {
        fprintf(stderr, "Failed to query:%s: Error: %s\n", insert_str,
                mysql_error(&mysql));
    }
    else
    {   // 提交
        mysql_commit(&mysql);
    }
     // 批量插入数据 fcode, fdatetime, b1pr, b1vol 
    char insert_str2[1024]{"INSERT INTO `ticklevel` (`fcode`, `fdatetime`, `b1pr`, `b1vol`) VALUES ('100002', '2022-07-18 10:21:00', 13.31, 1478), "
                           "('100003', '2022-07-18 10:22:00', 13.31, 1478), ('100004', '2022-07-18 10:23:00', 13.31, 1478);"};
    res = mysql_query(&mysql, insert_str2);
    if (res != 0)
    {
        fprintf(stderr, "Failed to query:%s: Error: %s\n", insert_str2,
                mysql_error(&mysql));
    }
    else
    {   // 提交
        mysql_commit(&mysql);
    }
    // 关闭连接
    mysql_close(&mysql);
    // 关闭对mysql动态库的使用
    mysql_library_end();
    exit(0);

    return 0;
}