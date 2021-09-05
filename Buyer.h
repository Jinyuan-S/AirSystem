#pragma once
#include <string>
#include <utility>
#include <iostream>

using namespace std;

class Buyer
{
 
public:
    string ID;
    string Name;
    string Gender;
    string Tel;
    string Password;
    string Email;

public:
    Buyer();
    Buyer(string &ID, string &name, string &gender, string &tel, string &password, string &email);
    ~Buyer() = default;
    int change_id(string &new_id); //1:长度不合法，位数要在6-10位之间 2:非法字符，必须字母数字组合
    int change_name(string &new_name);//1:长度不合法
    int change_gender(string &new_gender);//1:非法字符
    int change_tel(string &new_tel);//1:长度不合法 2:非法字符
    int change_password(string &new_password);  //1:长度不合法密码位数要在6-20位之间
    int change_email(string &new_email);//1:格式非法

};

