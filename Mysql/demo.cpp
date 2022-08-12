#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

/*
gcc demo.cpp -o demo.out `mysql_config --cflags --libs` -L/usr/lib64/mysql
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
    // 关闭连接
    mysql_close(&mysql);
    exit(0);

    return 0;
}