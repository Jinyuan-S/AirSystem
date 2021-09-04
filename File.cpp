//
// Created by Jinyuan on 8/31/21.
//
#include "File.h"


int CountLines(string filename)
{
    ifstream ReadFile;
    int n = 0;
    string tmp;
    ReadFile.open(filename.c_str());//ios::in ��ʾ��ֻ���ķ�ʽ��ȡ�ļ�
    if (ReadFile.fail())//�ļ���ʧ��:����0
    {
        return 0;
    }
    else//�ļ�����
    {
        while (getline(ReadFile, tmp, '\n'))
        {
            n++;
        }
        ReadFile.close();
        return n;
    }
}

Read::Read(string filename) {
    this->ifs.open(filename, ios::binary);
    if (!ifs.is_open()) {
        cout << filename << "�ļ���ʧ��" << endl;
    }
}

Read::~Read() {
    ifs.close();
}

string Read::read_line() {
    string line;
    if (getline(ifs, line)) {
        return line;
    }
    else return "EOF";
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
