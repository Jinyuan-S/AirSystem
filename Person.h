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
    //����
public:
    Person();
    ~Person();


    //�½�user,�ɹ�����true���Ѵ��ڷ���false
    bool add_buyer(Buyer& buyer);
    //�½�admin,�ɹ�����true���Ѵ��ڷ���false
    bool add_admin(Admin& admin);
    //ɾ��user���󣬳ɹ�����true
    bool del_buyer(string id);
    //ɾ��admin���󣬳ɹ�����true
    bool del_admin(string id);
    //�û���¼,1:�û���������   2:�������
    int buyer_login(string& id, string& pw, Buyer& buyer);
    //admin��¼
    int admin_login(string& id, string& pw, Admin& admin);

    //����buyer����
    void renew(Buyer& buyer);
    //����admin����
    void renew(Admin& admin);

public: 
    Database db;

};



