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
		f.Airline = v[j][1]; //下标0是index不要，从1开始取
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





//void Admin::order_by_attendance(string& begin, string& end, vector<Flight>& res) {
//	//日期格式：2021-08-20
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
//		f.Airline = v[j][1]; //下标0是index不要，从1开始取
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