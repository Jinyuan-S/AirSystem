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
    bool change_password(string new_password);  //密码位数要在6-20位之间
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
    bool change_password(string new_password);  //密码位数要在6-20位之间
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
    //总类
public:
    Person();
    ~Person();


    //新建user
    bool add_user(User& user);
    //新建admin
    bool add_admin(Admin& admin);
    //删除user对象，成功返回true，没找到返回false
    bool del_user(string id);
    //删除admin对象，成功返回true，没找到返回false
    bool del_admin(string id);
    //查询指定user信息，成功返回user_node指针，没找到返回null
    user_node* search_user(string id);
    //查询指定Admin信息，成功返回admin_node指针，没找到返回null
    admin_node* search_admin(string id);
    //user登陆，返回该user对象的地址，登陆失败返回空指针。flag标志：成功返回1，没找到id返回2，密码错误返回3
    User* user_login(string id, string pw, int* flag);
    //user登陆，返回该admin对象的地址，登陆失败返回空指针。flag标志：成功返回1，没找到id返回2，密码错误返回3
    Admin* admin_login(string id, string pw, int* flag);



    //从文件里读，返回读到的user个数
    int import_user(string filename);
    //写入文件
    int export_user(string filename);



public: //调试代码
    //打印指定user
    void print_user(string id);
    void print_user(User user);
    //打印所有user
    void print_all_user();


public:
    Head heads;
    int user_number;   //现有的user数量
    int admin_number;   //现有的admin数量

private:

};



