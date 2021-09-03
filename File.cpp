//
// Created by Jinyuan on 8/31/21.
//

#include "File.h"

int CountLines(string filename)
{
    ifstream ReadFile;
    int n=0;
    string tmp;
    ReadFile.open(filename.c_str());//ios::in 表示以只读的方式读取文件
    if(ReadFile.fail())//文件打开失败:返回0
        {
        return 0;
        }
    else//文件存在
    {
        while(getline(ReadFile,tmp,'\n'))
        {
            n++;
        }
        ReadFile.close();
        return n;
    }
}

Read::Read(string filename) {
    this->ifs.open(filename, ios::binary);
    if (!ifs.is_open()){
        cout << filename << "文件打开失败" << endl;
    }
}

Read::~Read() {
    ifs.close();
}

string Read::read_line() {
    string line;
    if(getline(ifs, line)){
        return line;
    }else return "EOF";
}


Write::Write(string file_name) {
    this->ofs.open(file_name, ios::out);
}

Write::~Write() {
    this->ofs.close();
}

void Write::append(string things) {
    ofs << things << endl;
}
