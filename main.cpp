#include <iostream>
#include "Person.h"
#include <mysql.h>

using namespace std;
int main() {

    MYSQL mysql;    //一个数据库结构体
    MYSQL_RES* res; //一个结果集结构体
    MYSQL_ROW row;  //char** 二维数组，存放一条条记录
    //初始化数据库
    mysql_init(&mysql);
    //设置编码方式
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "UTF8");
    //连接数据库
    //判断如果连接失败就输出连接失败。
    //注意你连接的账户名密码    8.136.214.13
    if (mysql_real_connect(&mysql, "8.136.214.13", "root", "654321", "airsystem", 3306, NULL, 0) == NULL)
        printf("连接失败！\\n");








    //Person person;
    //User user1("1234", "习近平", "男", "18710062238", "password", "xjp@outlook.com");
    //User user2("1222", "张三", "男", "18710061111", "password", "zs@outlook.com");
    //User user3("3456", "张王八", "男", "18710061111", "password", "zs@outlook.com");
    //person.add_user(user1);
    //person.add_user(user2);
    //person.add_user(user3);
    //person.print_all_user();


    //int a = person.export_user("list.txt");
    //cout << a << endl;
    //int b = person.import_user("users.txt");
    //cout << b << endl;
    //person.print_user("1222");
    //person.print_all_user();




    return 0;
}
