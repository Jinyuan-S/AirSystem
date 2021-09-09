#include "Admin.h"


Admin::Admin() {
	this->Company = "empty";
}

inline void Admin::atd_sql(string& begin, string& end, string& sql) {
	//SELECT * FROM air WHERE date>'2021-08-29' AND date<'2021-09-03' ORDER BY attendance DESC;";
	
	string s1 = "SELECT * FROM air WHERE date>'";
	string s2 = "' AND date<'";
	string s3 = "' ORDER BY attendance DESC;";
	sql = s1 + begin + s2 + end + s3;
}

inline void Admin::ttf_sql(string& begin, string& end, string& sql) {
	//SELECT * FROM air WHERE date>'2021-08-29' AND date<'2021-09-03' ORDER BY total_fare DESC;";

	string s1 = "SELECT * FROM air WHERE date>'";
	string s2 = "' AND date<'";
	string s3 = "' ORDER BY total_fare DESC;";
	sql = s1 + begin + s2 + end + s3;
}

inline void Admin::ttb_sql(string& begin, string& end, string& sql) {
	//SELECT * FROM air WHERE date>'2021-08-29' AND date<'2021-09-03' ORDER BY total_buyer DESC;";

	string s1 = "SELECT * FROM air WHERE date>'";
	string s2 = "' AND date<'";
	string s3 = "' ORDER BY total_buyer DESC;";
	sql = s1 + begin + s2 + end + s3;
}


inline void Admin::tail(string& sql, vector<Flight> res) {

	vector<vector<string>> v;
	db.fetch_data((char*)sql.c_str(), v);

	int j = 0;
	for (auto i = v.begin(); i != v.end(); i++, j++) {
		Flight f;
		f.Airline = v[j][1]; //�±�0��index��Ҫ����1��ʼȡ
		f.Origin = v[j][2];
		f.Destination = v[j][3];
		f.Company = v[j][4];
		f.Time_on = v[j][5];
		f.Time_off = v[j][6];
		f.Tomorrow = v[j][7];
		f.Model = v[j][8];
		f.A_remain = v[j][9];
		f.B_remain = v[j][10];
		f.C_remain = v[j][11];
		f.A_sold = v[j][12];
		f.B_sold = v[j][13];
		f.C_sold = v[j][14];
		f.Total_buyer = v[j][15];
		f.Attendance = v[j][16];
		f.Total_fare = v[j][17];
		f.Date = v[j][18];
		f.Rate = v[j][19];
		f.Price = v[j][20]; //price

		res.push_back(f);
	}
}

void Admin::order_by_attendance(string& begin, string& end, vector<Flight>& res) {
	string sql;
	atd_sql(begin, end, sql);
	tail(sql, res);
}

void Admin::order_by_total_fare(string& begin, string& end, vector<Flight>& res) {
	string sql;
	ttf_sql(begin, end, sql);
	tail(sql, res);
}

void Admin::order_by_total_buyer(string& begin, string& end, vector<Flight>& res) {
	string sql;
	ttb_sql(begin, end, sql);
	tail(sql, res);
}


inline int Admin::between(string& ori, string& des) {
	//SELECT `minute` FROM during WHERE origin='����' AND destination='�Ϻ�';
	string s4 = "SELECT `minute` FROM during WHERE origin='" + ori + "' AND destination='" + des + "';";
	vector<vector<string>> v;
	db.fetch_data((char*)s4.c_str(), v);
	//string during = v[0][0];  ��ʱ��������ʽ��
	return std::stoi(v[0][0]);
}

inline int Admin::to_minute(string& time) {
	string m = time.substr(0, 2);  //Сʱ
	return (std::stoi(m) * 60 + std::stoi(time.substr(3, 2))); //��һ�κ�����ܷ���
}

int Admin::fly(Flight& flt, int& which) {
	//SELECT time_on,time_off FROM air WHERE pilot1='����ȫ';
	string s1 = "SELECT origin,destination,time_on,time_off,tomorrow,date,airline FROM air WHERE pilot1='" + flt.Pilot1 + "';";
	int result = db.query((char*)s1.c_str());  //������һ����Ա��û�к���
	if (!result) {   //��һ������Աû�к���
		int wther2 = fly2(flt);
		if (!wther2) { //�ڶ���Ҳ�ܷ�
			return 0;
		}
		else {
			which = 2; //�ڶ�������Ա������
			return wther2;  //���صڶ�������Ա�ı���ֵ
		}
	}
	else {  //��һ������Ա�к���
		vector<vector<string>> v1;
		db.fetch_data((char*)s1.c_str(), v1);  //�õ��÷���Ա���յķ�����Ϣ
		//�¼Ӻ�����Ϣ flt
		flt.Time_on = std::to_string(to_minute(flt.Time_on));  //on  min
		flt.Time_off = std::to_string(to_minute(flt.Time_off));  //off min

		for (auto i = v1.begin(); i != v1.end(); i++) {
			//�Ϻ�����ɵأ�(*i)[0] ,Ŀ�ĵ� (*i)[1]
			//�º�����ɵأ�flt.origin,Ŀ�ĵ� flt.destination

			//�Ϻ���on=ԭʱ���ȥ���º���Ŀ�ĵص��Ϻ�����ɵص�ʱ��
			(*i)[2] = std::to_string(to_minute((*i)[2]) - between((*i)[0], flt.Destination));
			(*i)[3] = std::to_string(to_minute((*i)[3]) + between((*i)[1], flt.Origin));  //off  min

		}
		std::sort(v1.begin(), v1.end(), cmp_time_i); //���ս���ʱ���С��������

		for (auto j = v1.begin(); j != v1.end(); j++) {
			if (*j == v1.back() && j == v1.begin()) {  //Ψһһ��
				if (std::stoi((*j)[3]) < std::stoi(flt.Origin) || std::stoi((*j)[2]) > std::stoi(flt.Destination)) { //�󷽿ɲ�
					int wther2 = fly2(flt);
					if (!wther2) { //�ڶ���Ҳ�ܷ�
						return 0;
					}
					else {
						which = 2; //�ڶ�������Ա������
						return wther2;  //���صڶ�������Ա�ı���ֵ
					}
				}
				else return 1;
			}

			else if (*j == v1.back()) { //���һ��
				if (std::stoi((*j)[3]) < std::stoi(flt.Origin)) { //�󷽿ɲ�
					int wther2 = fly2(flt);
					if (!wther2) { //�ڶ���Ҳ�ܷ�
						return 0;
					}
					else {
						which = 2; //�ڶ�������Ա������
						return wther2;  //���صڶ�������Ա�ı���ֵ
					}
				}
				else return 1;
			}
			else {        //�¸��������ʱ��-��������º��ཱུ��ʱ��                     //���ʱ��+����С�������ʱ��
				if (std::stoi((*(j + 1))[2]) > std::stoi(flt.Destination) && std::stoi((*j)[3]) < std::stoi(flt.Origin)) {
					int wther2 = fly2(flt);
					if (!wther2) { //�ڶ���Ҳ�ܷ�
						return 0;
					}
					else {
						which = 2; //�ڶ�������Ա������
						return wther2;  //���صڶ�������Ա�ı���ֵ
					}
				}

				else {
					if (j == v1.begin() && std::stoi((*j)[2]) > std::stoi(flt.Destination)) {  //�׸�ǰ�����
						int wther2 = fly2(flt);
						if (!wther2) { //�ڶ���Ҳ�ܷ�
							return 0;
						}
						else {
							which = 2; //�ڶ�������Ա������
							return wther2;  //���صڶ�������Ա�ı���ֵ
						}
					}
					else return 1;
				}
			}
		}

	}
}

bool Admin::cmp_time_i(vector<string> f1, vector<string> f2) {
	//s1<s2����ture(��С����hh:mm:ss
	return(std::stoi(f1[3]) < std::stoi(f2[3])); //off min
}





int Admin::fly2(Flight& flt) {
	//SELECT time_on,time_off FROM air WHERE pilot1='����ȫ';
	string s1 = "SELECT origin,destination,time_on,time_off,tomorrow,date,airline FROM air WHERE pilot1='" + flt.Pilot1 + "';";
	int result = db.query((char*)s1.c_str());  //������һ����Ա��û�к���
	if (!result) {   //��һ������Աû�к���
		return 0;
	}
	else {  //��һ������Ա�к���
		vector<vector<string>> v1;
		db.fetch_data((char*)s1.c_str(), v1);  //�õ��÷���Ա���յķ�����Ϣ
		//�¼Ӻ�����Ϣ flt
		flt.Time_on = std::to_string(to_minute(flt.Time_on));  //on  min
		flt.Time_off = std::to_string(to_minute(flt.Time_off));  //off min

		for (auto i = v1.begin(); i != v1.end(); i++) {
			//�Ϻ�����ɵأ�(*i)[0] ,Ŀ�ĵ� (*i)[1]
			//�º�����ɵأ�flt.origin,Ŀ�ĵ� flt.destination

			//�Ϻ���on=ԭʱ���ȥ���º���Ŀ�ĵص��Ϻ�����ɵص�ʱ��
			(*i)[2] = std::to_string(to_minute((*i)[2]) - between((*i)[0], flt.Destination));
			(*i)[3] = std::to_string(to_minute((*i)[3]) + between((*i)[1], flt.Origin));  //off  min

		}
		std::sort(v1.begin(), v1.end(), cmp_time_i); //���ս���ʱ���С��������

		for (auto j = v1.begin(); j != v1.end(); j++) {
			if (*j == v1.back() && j == v1.begin()) {  //Ψһһ��
				if (std::stoi((*j)[3]) < std::stoi(flt.Origin) || std::stoi((*j)[2]) > std::stoi(flt.Destination)) //�󷽿ɲ�
					return 0;
				else return 1;
			}

			else if (*j == v1.back()) { //���һ��
				if (std::stoi((*j)[3]) < std::stoi(flt.Origin)) //�󷽿ɲ�
					return 0;
				else return 1;
			}
			else {        //�¸��������ʱ��-��������º��ཱུ��ʱ��                     //���ʱ��+����С�������ʱ��
				if (std::stoi((*(j + 1))[2]) > std::stoi(flt.Destination) && std::stoi((*j)[3]) < std::stoi(flt.Origin))
					return 0;
				else {
					if (j == v1.begin() && std::stoi((*j)[2]) > std::stoi(flt.Destination)) {  //�׸�ǰ�����
						return 0;
					}
					else return 1;
				}
			}
		}

	}
}





















//int Admin::whether1(Flight& f) {    //��û��pilot2�����⣬�ȸ�flight������⡣
//	//SELECT time_on,time_off FROM air WHERE pilot='����ȫ';
//
//	string s3 = "SELECT time_on,time_off,tomorrow FROM air WHERE pilot1='" + f.Pilot1 + "';";
//	string s4 = "SELECT time_on,time_off,tomorrow FROM air WHERE airline='" + f.Airline + "';";
//	if (!db.query((char*)s3.c_str()))
//		return 1; //�Ҳ�������1
//	else if (!db.query((char*)s4.c_str()))
//		return 3; //�����ظ�����3
//	else {
//		string tmp = f.Time_off; 
//
//		if (f.Tomorrow == "1") { //+24
//			string h = tmp.substr(0, 2);
//			string m = tmp.substr(2, 3);
//
//			h = std::to_string(std::stoi(h) + 24);
//
//			tmp = h + m;
//		}
//		vector<vector<string>> t;
//		db.fetch_data((char*)s3.c_str(), t);
//
//		for (auto j = t.begin(); j != t.end(); j++) {
//
//			(*j)[0] = (*j)[0].substr(0, 5);//hh:mm
//			(*j)[1] = (*j)[0].substr(0, 5);
//
//			if ((*j)[2] == "1") {  //+24
//				string h = (*j)[1].substr(0, 2);
//				string m = (*j)[1].substr(2, 3);
//
//				h = std::to_string(std::stoi(h) + 24);
//
//				(*j)[1] = h + m;
//			}
//		}
//
//		auto i = t.begin();
//		while ((*i)[1] < f.Time_on && i != t.end())  i++;
//		if (i == t.end()) {
//
//			//INSERT INTO air(airline,origin,destination,company,time_on,time_off,tomorrow,model,A_remain,B_remain,C_remain,date,price,pilot) VALUES();
//			string s1 = "INSERT INTO air(airline,origin,destination,company,time_on,time_off,tomorrow,model,A_remain,B_remain,C_remain,date,price,pilot) VALUES('";
//			string s2 = "');";
//			string sql = s1 + f.Airline + "','" + f.Origin + "','" + f.Destination + "','" + f.Company + "','" + f.Time_on + "','" + f.Time_off + "','" + f.Tomorrow + "','"
//				+ f.Model + "','" + f.A_remain + "','" + f.B_remain + "','" + f.C_remain + "','" + f.Date + "','" + f.Price + "','" + f.Pilot + s2;
//
//			db.query((char*)sql.c_str());
//
//			return 0;
//		}
//		else {
//			if (tmp < (*i)[0]) {
//
//				//INSERT INTO air(airline,origin,destination,company,time_on,time_off,tomorrow,model,A_remain,B_remain,C_remain,date,price,pilot) VALUES();
//				string s1 = "INSERT INTO air(airline,origin,destination,company,time_on,time_off,tomorrow,model,A_remain,B_remain,C_remain,date,price,pilot) VALUES('";
//				string s2 = "');";
//				string sql = s1 + f.Airline + "','" + f.Origin + "','" + f.Destination + "','" + f.Company + "','" + f.Time_on + "','" + f.Time_off + "','" + f.Tomorrow + "','"
//					+ f.Model + "','" + f.A_remain + "','" + f.B_remain + "','" + f.C_remain + "','" + f.Date + "','" + f.Price + "','" + f.Pilot + s2;
//
//				db.query((char*)sql.c_str());
//
//				return 0;
//			}
//			else return 2;  //��ͻ
//		}
//
//
//	}
//	
//}


//void Admin::order_by_attendance(string& begin, string& end, vector<Flight>& res) {
//	//���ڸ�ʽ��2021-08-20
//	
//	string s1 = "SELECT * FROM air WHERE date>'";
//	string s2 = "' AND date<'";
//	string s3 = "' ORDER BY attendance DESC;";
//	string sql = s1 + begin + s2 + end + s3;
//
//	vector<vector<string>> v;
//	db.fetch_data((char*)sql.c_str(), v);
//
//	int j = 0;
//	for (auto i = v.begin(); i != v.end(); i++, j++) {
//		Flight f;
//		f.Airline = v[j][1]; //�±�0��index��Ҫ����1��ʼȡ
//		f.Origin = v[j][2];
//		f.Destination = v[j][3];
//		f.Company = v[j][4];
//		f.Time_on = v[j][5];
//		f.Time_off = v[j][6];
//		f.Tomorrow = v[j][7];
//		f.Model = v[j][8];
//		f.A_remain = v[j][9];
//		f.B_remain = v[j][10];
//		f.C_remain = v[j][11];
//		f.A_sold = v[j][12];
//		f.B_sold = v[j][13];
//		f.C_sold = v[j][14];
//		f.Total_buyer = v[j][15];
//		f.Attendance = v[j][16];
//		f.Total_fare = v[j][17];
//		f.Date = v[j][18];
//		f.Rate = v[j][19];
//		f.Price = v[j][20]; //price
//
//		res.push_back(f);
//	}
//
//	
//}