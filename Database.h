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
	MYSQL mysql;    //一个数据库结构体
	MYSQL_RES* res = NULL; //一个结果集结构体
	MYSQL_ROW row = NULL;  //char** 二维数组，存放一条条记录



public:
	Database();
	~Database();
	
	void fetchdata(char* sql, vector<vector<string>>& vec);

private:
	const char* U2G(const char* utf8);
	char* Gb2312ToUtf8(char* p);
	int query(char *sql); //传入sql语句，返回查找到的个数（行数）
	unsigned int field_num();//取得表的列数，！！！先quary再调用！！！

};

