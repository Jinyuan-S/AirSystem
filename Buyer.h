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
    int change_id(string &new_id); //1:���Ȳ��Ϸ���λ��Ҫ��6-10λ֮�� 2:�Ƿ��ַ���������ĸ�������
    int change_name(string &new_name);//1:���Ȳ��Ϸ�
    int change_gender(string &new_gender);//1:�Ƿ��ַ�
    int change_tel(string &new_tel);//1:���Ȳ��Ϸ� 2:�Ƿ��ַ�
    int change_password(string &new_password);  //1:���Ȳ��Ϸ�����λ��Ҫ��6-20λ֮��
    int change_email(string &new_email);//1:��ʽ�Ƿ�

};

