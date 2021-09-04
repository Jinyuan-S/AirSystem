//
// Created by Jinyuan on 8/30/21.
//
#pragma once


#include <iostream>
#include <string>
#include <ctype.h>
#include "File.h"

using namespace std;

class User {
public:
    string ID;
    string Name;
    string Gender;
    string Tel;
    string Password;
    string Email;

public:
    User();
    User(string id, string name, string gender, string tel, string password, string email);
    bool change_name(string new_name);
    bool change_gender(string new_gender);
    bool change_tel(string new_tel);
    bool change_password(string new_password);  //����λ��Ҫ��6-20λ֮��
    bool change_email(string new_email);
};

class Admin {
public:
    string ID;
    string Name;
    string Gender;
    string Tel;
    string Password;
    string Email;

    string Company;
public:
    Admin();
    Admin(string id, string name, string gender, string tel, string password, string email, string company);
    bool change_name(string new_name);
    bool change_gender(string new_gender);
    bool change_tel(string new_tel);
    bool change_password(string new_password);  //����λ��Ҫ��6-20λ֮��
    bool change_email(string new_email);
};

typedef struct _user_node {
    User man;
    _user_node* next = nullptr;
} user_node;

typedef struct _admin_node {
    Admin man;
    _admin_node* next = nullptr;
} admin_node;

typedef struct {
    user_node* user_head;
    admin_node* admin_head;
}Head;

/***********************************************/
class Person {
    //����
public:
    Person();
    ~Person();


    //�½�user
    bool add_user(User& user);
    //�½�admin
    bool add_admin(Admin& admin);
    //ɾ��user���󣬳ɹ�����true��û�ҵ�����false
    bool del_user(string id);
    //ɾ��admin���󣬳ɹ�����true��û�ҵ�����false
    bool del_admin(string id);
    //��ѯָ��user��Ϣ���ɹ�����user_nodeָ�룬û�ҵ�����null
    user_node* search_user(string id);
    //��ѯָ��Admin��Ϣ���ɹ�����admin_nodeָ�룬û�ҵ�����null
    admin_node* search_admin(string id);
    //user��½�����ظ�user����ĵ�ַ����½ʧ�ܷ��ؿ�ָ�롣flag��־���ɹ�����1��û�ҵ�id����2��������󷵻�3
    User* user_login(string id, string pw, int* flag);
    //user��½�����ظ�admin����ĵ�ַ����½ʧ�ܷ��ؿ�ָ�롣flag��־���ɹ�����1��û�ҵ�id����2��������󷵻�3
    Admin* admin_login(string id, string pw, int* flag);



    //���ļ���������ض�����user����
    int import_user(string filename);
    //д���ļ�
    int export_user(string filename);



public: //���Դ���
    //��ӡָ��user
    void print_user(string id);
    void print_user(User user);
    //��ӡ����user
    void print_all_user();


public:
    Head heads;
    int user_number;   //���е�user����
    int admin_number;   //���е�admin����

private:

};



