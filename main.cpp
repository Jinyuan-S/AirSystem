#include <iostream>
#include "Person.h"
#include <mysql.h>

using namespace std;
int main() {

    MYSQL mysql;    //һ�����ݿ�ṹ��
    MYSQL_RES* res; //һ��������ṹ��
    MYSQL_ROW row;  //char** ��ά���飬���һ������¼
    //��ʼ�����ݿ�
    mysql_init(&mysql);
    //���ñ��뷽ʽ
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "UTF8");
    //�������ݿ�
    //�ж��������ʧ�ܾ��������ʧ�ܡ�
    //ע�������ӵ��˻�������    8.136.214.13
    if (mysql_real_connect(&mysql, "8.136.214.13", "root", "654321", "airsystem", 3306, NULL, 0) == NULL)
        printf("����ʧ�ܣ�\\n");








    //Person person;
    //User user1("1234", "ϰ��ƽ", "��", "18710062238", "password", "xjp@outlook.com");
    //User user2("1222", "����", "��", "18710061111", "password", "zs@outlook.com");
    //User user3("3456", "������", "��", "18710061111", "password", "zs@outlook.com");
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
