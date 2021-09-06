//
// Created by Jinyuan on 8/30/21.
//
#pragma once


#include <iostream>
#include <string>
#include <ctype.h>
#include "Admin.h"
#include "Buyer.h"
#include "Database.h"


//using namespace std;

/***********************************************/
class Person {
    //总类
public:
    Person();
    ~Person();


    //新建user,成功返回true，已存在返回false
    bool add_buyer(Buyer& buyer);
    //新建admin,成功返回true，已存在返回false
    bool add_admin(Admin& admin);
    //删除user对象，成功返回true
    bool del_buyer(string id);
    //删除admin对象，成功返回true
    bool del_admin(string id);
    //用户登录,1:用户名不存在   2:密码错误
    int buyer_login(string& id, string& pw, Buyer& buyer);
    //admin登录
    int admin_login(string& id, string& pw, Admin& admin);

    //更新buyer数据
    void renew(Buyer& buyer);
    //更新admin数据
    void renew(Admin& admin);

public: 
    Database db;

};



