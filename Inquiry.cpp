#include "Inquiry.h"

int Inquiry::search(string& origin, string& destination, string& date, vector<Flight>& vec) {
	
	//SELECT * FROM air WHERE origin='北京' AND destination='广州' AND date='9.2';

	string s1 = "SELECT * FROM air WHERE origin='";
	string s2 = "' AND destination='";
	string s3 = "' AND date='";
	string s4 = "';";
	string sql = s1 + origin + s2 + destination + s3 + date + s4;

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

		vec.push_back(f);
	}
	sort_by_time_inc(vec);

	return j;
}

int Inquiry::search(string& airline, string& date, vector<Flight>& vec)
{
    string s1 = "SELECT * FROM air WHERE airline='";
    //no s2 because it's copied
    string s3 = "' AND date='";
    string s4 = "';";
    string sql = s1 + airline + s3 + date + s4;

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

        vec.push_back(f);
    }
    sort_by_time_inc(vec);

    return j;
}

bool Inquiry::cmp_timei(Flight f1, Flight f2) {
	//s1<s2返回ture(从小到大）
    int p = stoi(f1.Time_on.substr(0, 2));
    int q = stoi(f2.Time_on.substr(0, 2));
	if (p > q) return false;
	else if (p < q) return true;
	else {
        int m = stoi(f1.Time_on.substr(3, 2));
        int n = stoi(f2.Time_on.substr(3, 2));
		if (m > n) return false;
		else return true;  //没有做等于的判定，可能出bug
	}
}

void Inquiry::sort_by_time_inc(vector<Flight>& vec) {
    sort(vec.begin(), vec.end(), cmp_timei);
}

bool Inquiry::cmp_timed(Flight f1, Flight f2) {
	//s1<s2返回ture(从小到大）
    int p = stoi(f1.Time_on.substr(0, 2));
    int q = stoi(f2.Time_on.substr(0, 2));
	if (p > q) return true;
	else if (p < q) return false;
	else {
        int m = stoi(f1.Time_on.substr(3, 2));
        int n = stoi(f2.Time_on.substr(3, 2));
		if (m > n) return true;
		else return false;  //没有做等于的判定，可能出bug
	}
}

void Inquiry::sort_by_time_dec(vector<Flight>& vec) {
	sort(vec.begin(), vec.end(), cmp_timed);
}

bool Inquiry::cmp_pricei(Flight f1, Flight f2) {
    return (stoi(f1.Price) < stoi(f2.Price));
}

void Inquiry::sort_by_price_inc(vector<Flight>& vec) {
	sort(vec.begin(), vec.end(), cmp_pricei);
}

bool Inquiry::cmp_priced(Flight f1, Flight f2) {
    return (stoi(f1.Price) > stoi(f2.Price));
}

void Inquiry::sort_by_price_dec(vector<Flight>& vec) {
	sort(vec.begin(), vec.end(), cmp_priced);
}

void Inquiry::filter_by_company(string& company, vector<Flight>& vec, vector<Flight>& res) {
	for (auto i = vec.begin(); i != vec.end(); i++) {
		if (i->Company == company)
			res.push_back(*i);
	}
}

void Inquiry::filter_by_time(string& begin, string& end, vector<Flight>& vec, vector<Flight>& res) {
//	sort_by_time_inc(vec);
	for (auto i = vec.begin(); i != vec.end(); i++) {
		string p = i->Time_on.substr(0, 2);
        if (stoi(p) >= stoi(begin) && stoi(p) <= stoi(end))
			res.push_back(*i);
	}
}

void Inquiry::filter_by_airline(string& airline, vector<Flight>& vec, vector<Flight>& res) {
//	sort_by_time_inc(vec);
	for (auto i = vec.begin(); i != vec.end(); i++) {
		if (i->Airline == airline)
			res.push_back(*i);
	}
}

void Inquiry::filter_by_model(string& model, vector<Flight>& vec, vector<Flight>& res) {
//	sort_by_time_inc(vec);
    for (auto i = vec.begin(); i != vec.end(); i++) {
        if (i->Model == model)
            res.push_back(*i);
    }
}

void Inquiry::recommand(string& date, vector<Flight>& res) {
	//8 2021-08-20
	string d1 = date.substr(8, 2);
	string m = date.substr(5, 2);
	string y = date.substr(0, 4);

	int a = std::stoi(d1);
	//std::cout << a << std::endl;
	string d = "";
	if (d1 > "01") {
		a--;
		d = std::to_string(a);
		if (d.length() < 2)
			d = "0" + d;
	}
	else {
		d = "31";
		int b = std::stoi(m);
		b--;
		m = std::to_string(b);
		if (m.length() < 2)
			m = "0" + m;
	}
	string out = y + "-" + m + "-" + d;

	//SELECT * FROM air WHERE date='2021-08-26' ORDER BY attendance DESC LIMIT 0,5;
	string s1 = "SELECT * FROM air WHERE date='";
	string s2 = "' ORDER BY attendance DESC LIMIT 0,5;";
	string sql = s1 + out + s2;

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
		//f.Date = v[j][18];

		string dd = date.substr(8, 2);
		string mm = date.substr(5, 2);
		string yy = date.substr(0, 4);
		int a = std::stoi(dd);
		string ddd = "";
		if (dd < "31") {
			a++;
			ddd = std::to_string(a);
			if (ddd.length() < 2)
				ddd = "0" + ddd;
		}
		else {
			dd = "01";
			int b = std::stoi(mm);
			b++;
			mm = std::to_string(b);
			if (mm.length() < 2)
				mm = "0" + mm;
		}
		f.Date = yy + "-" + mm + "-" + ddd;

		f.Rate = v[j][19];
		f.Price = v[j][20]; //price

		res.push_back(f);
	}
}
