//
// Created by Jinyuan on 8/30/21.
//

#include "Person.h"


Person::Person() {
}

Person::~Person() {
}

bool Person::add_buyer(Buyer& buyer) {
	//INSERT INTO admin(ID,`name`,gender,tel,`password`,email,company) VALUES ('dj123','戴骥','男','12345678987','daiji12345','daiji@163.com','Air China');
	string head1 = "INSERT INTO user(ID,`name`,gender,tel,`password`,email) VALUES (";
	string tail1 = ");";
	string sql1 = head1 + "\'" + buyer.ID + "\'," + "\'" + buyer.Name + "\'," + "\'" + buyer.Gender + "\'," + "\'" + buyer.Tel + "\'," + "\'" + buyer.Password + "\'," + "\'" + buyer.Email + "\'" + tail1;
	
	//SELECT ID from `user` WHERE ID='';
	string head2 = "SELECT ID from `user` WHERE ID='";
	string tail2 = "';";
	string sql2 = head2 + buyer.ID + tail2;
	//cout << sql2 << endl;

	//cout << db.query((char*)sql2.c_str()) << endl;
	if (db.query((char*)sql2.c_str()) != 0) {  //如果存在就不添加
		cout << "ng" << endl;
		return false;
	}
	else {
		//cout << sql << endl;
		db.query((char*)sql1.c_str());
		cout << "good" << endl;
		return true;
	}
	return true;
}


bool Person::add_admin(Admin& admin) {
	//INSERT INTO admin(ID,`name`,gender,tel,`password`,email,company) VALUES ('dj123','戴骥','男','12345678987','daiji12345','daiji@163.com','Air China');
	string head1 = "INSERT INTO admin(ID,`name`,gender,tel,`password`,email,company) VALUES (";
	string tail1 = ");";
	string sql1 = head1 + "\'" + admin.ID + "\'," + "\'" + admin.Name + "\'," + "\'" + admin.Gender + "\'," + "\'" + admin.Tel + "\'," + "\'" + admin.Password + "\'," + "\'" + admin.Email + "\'," + "\'" + admin.Company + "\'" + tail1;
	
	//SELECT ID from `admin` WHERE ID='';
	string head2 = "SELECT ID from `admin` WHERE ID='";
	string tail2 = "';";
	string sql2 = head2 + admin.ID + tail2;

	//cout << !db.query((char*)sql2.c_str()) << endl;
	if (db.query((char*)sql2.c_str()) != 0) {
		cout << "ng" << endl;
		return false;
	}
	else {
		//cout << sql << endl;
		db.query((char*)sql1.c_str());
		cout << "good" << endl;
		return true;
	}
	return true;
}


bool Person::del_buyer(string id) {
	//DELETE from user WHERE ID='dj123';
	string head = "DELETE from user WHERE ID='";
	string tail = "';";
	string sql = head + id + tail;
	db.query((char*)sql.c_str());
	return true;
}

bool Person::del_admin(string id) {
	//DELETE from admin WHERE ID='dj123';
	string head = "DELETE from user WHERE ID='";
	string tail = "';";
	string sql = head + id + tail;
	db.query((char*)sql.c_str());
	return true;
}

int Person::buyer_login(string& id, string& pw, Buyer& buyer) {
	//SELECT ID,`name`,gender,tel,`password`,email FROM user WHERE ID="dj123";
	string head1 = "SELECT ID,`name`,gender,tel,`password`,email FROM user WHERE ID=\"";
	string tail1 = "\";";
	string sql1 = head1 + id + tail1;

	if (db.query((char*)sql1.c_str()) == 0) {
		return 1;
	}
	else {
		vector<vector<string>> vec;

		db.fetch_data((char*)sql1.c_str(), vec);

		if (vec[0][3] != pw)
			return 2;
		else {
			buyer.ID = vec[0][0];
			buyer.Name = vec[0][1];
			buyer.Tel = vec[0][2];
			buyer.Password = vec[0][3];
			buyer.Email = vec[0][4];

			return 0;
		}

	}

}

int Person::admin_login(string& id, string& pw, Admin& admin) {
	//SELECT ID,`name`,gender,tel,`password`,email,company FROM user WHERE ID="dj123";
	string head1 = "SELECT ID,`name`,gender,tel,`password`,email,company FROM admin WHERE ID=\"";
	string tail1 = "\";";
	string sql1 = head1 + id + tail1;

	if (db.query((char*)sql1.c_str()) == 0) {
		return 1;
	}
	else {
		vector<vector<string>> vec;

		db.fetch_data((char*)sql1.c_str(), vec);

		if (vec[0][3] != pw)
			return 2;
		else {
			admin.ID = vec[0][0];
			admin.Name = vec[0][1];
			admin.Tel = vec[0][2];
			admin.Password = vec[0][3];
			admin.Email = vec[0][4];
			admin.Company = vec[0][5];

			return 0;
		}

	}

}