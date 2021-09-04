//
// Created by Jinyuan on 8/31/21.
//
#pragma once


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/******************************************************************/

int CountLines(string filename);//���ļ�һ���ж�����

class Write {
    //д�ļ�
public:
    Write(string filename); //���캯����Ҫ�����ļ���
    ~Write();
    void append(string thing);  //���ļ�β׷��һ�У��Զ����У�
private:
    ofstream ofs;
};

class Read {
    //���ļ�
public:
    Read(string filename);  //���캯����Ҫ�����ļ���
    ~Read();
    string read_line(); //�����ϴε�λ�ö���һ�У���������string������������"EOF"
private:
    ifstream ifs;
};

/******************************************************************/

