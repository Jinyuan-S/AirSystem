#include "Order.h"
int Order::get_all_order(string& id, vector<Mother_order>& vec) {
	//SELECT * FROM mother_order WHERE who='zhangsan1';
	string head = "SELECT * FROM mother_order WHERE who='";
	string tail = "';";
	string sql = head + id + tail;

	if (db.query((char*)sql.c_str())) {
		vector<vector<string>> svec;
		db.fetch_data((char*)sql.c_str(), svec);
		int j = 0;

		for (auto i = svec.begin(); i < svec.end(); i++) {
			Mother_order mo;
			mo.Mother = svec[j][0];
			mo.Who = svec[j][1];
			mo.Time = svec[j][2];
			mo.Is_cancel = svec[j][3];
			mo.Is_paid = svec[j][4];
			mo.Money = svec[j][5];
			mo.Contain = svec[j][6];
			mo.Sub1 = svec[j][7];
			mo.Sub2 = svec[j][8];
			mo.Sub3 = svec[j][9];
			mo.Sub4 = svec[j][10];
			mo.Sub5 = svec[j][11];

			vec.push_back(mo);
			j++;
		}
		return j;
	}
	else return 0;
}


int Order::get_sub_order(Mother_order& mo, vector<Children_order>& vec) {
	vector<string> s;
	int num = mo.Contain[0] - '0';
	s.push_back(mo.Sub1);
	s.push_back(mo.Sub2);
	s.push_back(mo.Sub3);
	s.push_back(mo.Sub4);
	s.push_back(mo.Sub5);

	int j = 0;
	for (auto i = s.begin(); i != s.end() && j < num; i++, j++) {
		Children_order co;
		vector<vector<string>> vs;
		//SELECT * FROM children_order WHERE children='0001';
		string head = "SELECT * FROM children_order WHERE children='";
		string tail = "';";
		string sql = head + s[j] + tail;
		db.fetch_data((char*)sql.c_str(), vs);
		co.Children = vs[0][0];
		co.Who = vs[0][1];
		co.Airline = vs[0][2];
		co.Date = vs[0][3];
		co.Seat = vs[0][4];
		co.Cabin = vs[0][5];
		co.Money = vs[0][6];
		vec.push_back(co);
	}

	return num;
}


bool Order::add_order(Mother_order& mo, vector<Children_order>& vec) {
	//添加的时候与没有做是否已存在的判定！！！
	int j = 0;
	vector<string> sv;
	for (auto i = vec.begin(); i != vec.end(); i++, j++) {
		//INSERT INTO children_order(who,airline,date,seat,cabin,money) VALUES('li1234','shit','2021-9-02','C1','A','100');
		string head = "INSERT INTO children_order(who,airline,date,seat,cabin,money) VALUES('";
		string tail = "');";
		string sql = head + vec[j].Who + "','" + vec[j].Airline + "','" + vec[j].Date + "','" + vec[j].Seat + "','" + vec[j].Cabin + "','" + vec[j].Money + tail;
		db.query((char*)sql.c_str());
		
		//SELECT A_remain,A_sold,total_buyer,total_fare FROM air WHERE airline='CA8214' AND date='9.2';
		//string s1 = "SELECT ";
		//string s2 = "_remain,";
		//string s3 = "_sold,total_buyer,total_fare FROM air WHERE airline='";
		//string s4 = "' AND date='";
		//string s5 = "';";
		//string sql2 = s1 + i->Cabin + s2 + i->Cabin + s3 + i->Airline + s4 + i->Date + s5;
		//vector<vector<string>> v;
		//db.fetch_data((char*)sql2.c_str(), v);

		//for (auto i = v.begin(); i != v.end(); i++) {
		//	//这块要拿到原来的数据进行更改，然后再提交，还没来及写
		//}

		sv.push_back(vec[j].Children);
	}
	while (j < 5) {
		sv.push_back("empty");
		j++;
	}
	mo.Contain = j;
	mo.Sub1 = sv[0];
	mo.Sub2 = sv[1];
	mo.Sub3 = sv[2];
	mo.Sub4 = sv[3];
	mo.Sub5 = sv[4];

	//INSERT INTO mother_order(mother,who,time,is_cancel,is_paid,money,contain,sub1,sub2,sub3,sub4,sub5) VALUES();
	string head = "INSERT INTO mother_order(who,is_cancel,is_paid,money,contain,sub1,sub2,sub3,sub4,sub5) VALUES(";
	string tail = ");";
	string sql = head + mo.Who + "','" + mo.Is_cancel + "','" + mo.Is_paid + "','" +mo.Money + "','" 
		+ mo.Contain + "','" + mo.Sub1 + "','" + mo.Sub2 + "','" + mo.Sub3 + "','" + mo.Sub4 + "','" + mo.Sub5 + tail;
	db.query((char*)sql.c_str());

	return true;
}

//int Order::change(string& table, string& factor, string& order_id, string& value) {
//	//UPDATE children_order SET money = '400' WHERE children = '0003';
//	string s1 = "UPDATE ";
//	string s2 = " SET ";
//	string s3 = "='";
//	string s4 = "' WHERE children='0003';"
//	string sql = s1 + table + s2 + factor + value +
//}

bool Order::renew(Mother_order& mo) {
	//UPDATE mother_order SET is_paid=0,is_cancel=1 WHERE mother=0000000001;
	string s1 = "UPDATE mother_order SET is_paid=";
	string s2 = ",is_cancel=";
	string s3 = " WHERE mother=";
	string s4 = ";";
	string sql = s1 + mo.Is_paid + s2 + mo.Is_cancel + mo.Mother + s4;
	db.query((char*)sql.c_str());
	return true;
}


bool Order::renew(Children_order& co) {
	//UPDATE children_order SET seat='1' WHERE children=0000000001;
	string s1 = "UPDATE children_order SET seat='";
	string s2 = "' WHERE children=";
	string s3 = ";";
	string sql = s1 + co.Seat + s2 + s3;
	db.query((char*)sql.c_str());
	return true;
}

