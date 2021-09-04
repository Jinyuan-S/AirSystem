#pragma once
#include <iostream>
#include <mysql.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

class Database
{
private:
	MYSQL mysql;    //һ�����ݿ�ṹ��
	MYSQL_RES* res = NULL; //һ��������ṹ��
	MYSQL_ROW row = NULL;  //char** ��ά���飬���һ������¼



public:
	Database();
	~Database();
	
	void fetchdata(char* sql, vector<vector<string>>& vec);

private:
	const char* U2G(const char* utf8);
	char* Gb2312ToUtf8(char* p);
	int query(char *sql); //����sql��䣬���ز��ҵ��ĸ�����������
	unsigned int field_num();//ȡ�ñ����������������quary�ٵ��ã�����

};

