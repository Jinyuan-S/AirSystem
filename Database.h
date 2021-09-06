#pragma once
#include <iostream>
#include "mysql.h"
#include <stdlib.h>
#include <vector>
#include <string>

using std::vector;

class Database
{
private:
	MYSQL mysql;    //һ�����ݿ�ṹ��
	MYSQL_RES* res = NULL; //һ��������ṹ��
	MYSQL_ROW row = NULL;  //char** ��ά���飬���һ������¼



public:
	Database();
    ~Database();
    void fetch_data(char* sql, vector<vector<std::string>>& vec); //����sql���(char[1000])���Ͷ�άvector���ܷ���ֵ
    //void push_data(char* sql);
    int query(char* sql); //����sql��䣬���ز��ҵ��ĸ�����������

private:
    const char* U2G(const char* utf8);
    char* Gb2312ToUtf8(char* p);
    unsigned int field_num();//ȡ�ñ����������������quary�ٵ��ã�����
};

