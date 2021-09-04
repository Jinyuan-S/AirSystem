//
// Created by Jinyuan on 8/31/21.
//
#pragma once


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/******************************************************************/

int CountLines(string filename);//数文件一共有多少行

class Write {
    //写文件
public:
    Write(string filename); //构造函数需要传入文件名
    ~Write();
    void append(string thing);  //在文件尾追加一行（自动换行）
private:
    ofstream ofs;
};

class Read {
    //读文件
public:
    Read(string filename);  //构造函数需要传入文件名
    ~Read();
    string read_line(); //接着上次的位置读下一行，读到返回string，读不到返回"EOF"
private:
    ifstream ifs;
};

/******************************************************************/

