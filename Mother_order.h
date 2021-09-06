#pragma once
#include <string>

using std::string;

class Mother_order
{
public:
	string Mother;
	string Who;
	string Time;
	string Is_cancel;
	string Is_paid;
	string Money;
	string Contain;
	string Sub1;
	string Sub2;
	string Sub3;
	string Sub4;
	string Sub5;
public:
	Mother_order();
	//Mother_order(string& mother, string& who, string& time, string& is_cancel, string& is_paid,
		//string& money, string& contain, string& sub1, string& sub2, string& sub3, string &sub4, string& sub5);

	~Mother_order() = default;
};

