#include "Order.h"
#include <QDebug>
int Order::get_all_order(string& id, vector<Mother_order>& vec) {
	//SELECT * FROM mother_order WHERE who='zhangsan1';
	string head = "SELECT * FROM mother_order WHERE who='";
	string tail = "';";
	string sql = head + id + tail;

	if (db.query((char*)sql.c_str())) {
		vector<vector<string>> svec;
		db.fetch_data((char*)sql.c_str(), svec);
		int j = 0;

        for (auto i = svec.begin(); i != svec.end(); i++) {
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
            std::cout << mo.Contain;
            std::cout << mo.Sub1;
            std::cout << mo.Is_cancel;
            std::cout << mo.Sub5;
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


int Order::add_order(Mother_order& mo, vector<Children_order>& vec, int& conf_idx, Children_order& conf) {
	string conflict = "empty";
	int w = 0;  //记录下标
	for (auto i = vec.begin(); i != vec.end(); i++, w++) {
		int err = cannot((*i), conflict);
		if (err) {
			//SELECT * FROM children_order WHERE children='';
			string sql = "SELECT * FROM children_order WHERE children='" + conflict + "';";
			vector<vector<string>> res;
			db.fetch_data((char*)sql.c_str(), res);
			conf.Children = res[0][0];
			conf.Who = res[0][1];
			conf.Airline = res[0][2];
			conf.Date = res[0][3];
			conf.Seat = res[0][4];
			conf.Cabin = res[0][5];
			conf.Money = res[0][6];
			
			conf_idx = w;  //记录下标
			return err;
		}
	}
	
	//正式添加
	conf_idx = -1;
	int j = 0;
	vector<string> sv;
	for (auto i = vec.begin(); i != vec.end(); i++, j++) {
		//INSERT INTO children_order(who,airline,date,seat,cabin,money) VALUES('li1234','shit','2021-9-02','C1','A','100');
		string head = "INSERT INTO children_order(who,airline,date,seat,cabin,money) VALUES('";
		string tail = "');";
		string sql = head + vec[j].Who + "','" + vec[j].Airline + "','" + vec[j].Date + "','" + vec[j].Seat + "','" + vec[j].Cabin + "','" + vec[j].Money + tail;
		db.query((char*)sql.c_str());
		
		//SELECT A_remain,A_sold,total_buyer,total_fare FROM air WHERE airline='CA8214' AND date='9.2';
		string s1 = "SELECT ";
		string s2 = "_remain,";
		string s3 = "_sold,total_buyer,total_fare FROM air WHERE airline='";
		string s4 = "' AND date='";
		string s5 = "';";
		string sql2 = s1 + i->Cabin + s2 + i->Cabin + s3 + i->Airline + s4 + i->Date + s5;
		vector<vector<string>> v;
		db.fetch_data((char*)sql2.c_str(), v);

		string remain = "empty";
		string sold = "empty";
		string ttbuyer = "empty";
		string ttfare = "empty";

		for (auto k = v.begin(); k != v.end(); k++) {
			//这块要拿到原来的数据进行更改
			int tmp = std::stoi((*k)[0]);
			tmp--;
			remain = std::to_string(tmp);
			tmp = std::stoi((*k)[1]);
			tmp++;
			sold = std::to_string(tmp);
			tmp = std::stoi((*k)[2]);
			tmp++;
			ttbuyer = std::to_string(tmp);
			tmp = std::stoi((*k)[3]);
			tmp += std::stoi((*i).Money);
			ttfare = std::to_string(tmp);

		}

		//UPDATE air SET A_remain='9' WHERE airline='CA111' AND date='2021-8-26';
		string tl = "' WHERE airline='" + i->Airline + "' AND date='" + i->Date + "';";
		//string a = "UPDATE air SET " + i->Cabin + "_remain='" + remain + "' WHERE airline='" + i->Airline + "' AND date='" + i->Date + "';";
		string a = "UPDATE air SET " + i->Cabin + "_remain='" + remain + tl;
		db.query((char*)a.c_str());
		a = "UPDATE air SET " + i->Cabin + "_sold='" + sold + tl;
		db.query((char*)a.c_str());
		a = "UPDATE air SET total_buyer='" + ttbuyer + tl;
		db.query((char*)a.c_str());
		a = "UPDATE air SET total_fare='" + ttfare + tl;
		db.query((char*)a.c_str());
		//SELECT children FROM children_order WHERE who='' AND airline='' AND date='';
		string fuck = "SELECT children FROM children_order WHERE who='" + vec[j].Who + "' AND airline='" + vec[j].Airline + "' AND date='" + vec[j].Date + "';";
		vector<vector<string>> cc;
		db.fetch_data((char*)fuck.c_str(), cc);
		sv.push_back(cc[0][0]);
    }
    int k = j;
	while (j < 5) {
		sv.push_back("empty");
		j++;
    }
    mo.Contain = std::to_string(k);
	mo.Sub1 = sv[0];
	mo.Sub2 = sv[1];
	mo.Sub3 = sv[2];
	mo.Sub4 = sv[3];
	mo.Sub5 = sv[4];
    qDebug() << "Sub1" << QString::fromLocal8Bit(mo.Sub1);
    qDebug() << "Sub2" << QString::fromLocal8Bit(mo.Sub2);

    qDebug() << "Sub5" << QString::fromLocal8Bit(mo.Sub5);
    //INSERT INTO mother_order(mother,who,time,is_cancel,is_paid,money,contain,sub1,sub2,sub3,sub4,sub5) VALUES();
	string head = "INSERT INTO mother_order(who,is_cancel,is_paid,money,contain,sub1,sub2,sub3,sub4,sub5) VALUES('";
    string tail = "');";
	string sql = head + mo.Who + "','" + mo.Is_cancel + "','" + mo.Is_paid + "','" +mo.Money + "','" 
		+ mo.Contain + "','" + mo.Sub1 + "','" + mo.Sub2 + "','" + mo.Sub3 + "','" + mo.Sub4 + "','" + mo.Sub5 + tail;
	db.query((char*)sql.c_str());

	return 0;
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
    string s1 = "UPDATE mother_order SET is_paid='";
    string s2 = "',is_cancel='";
    string s3 = "' WHERE mother='";
    string s4 = "';";
    string sql = s1 + mo.Is_paid + s2 + mo.Is_cancel + s3 + mo.Mother + s4;
    std::cout << sql;
	db.query((char*)sql.c_str());
	return true;
}


bool Order::renew(Children_order& co) {
	//UPDATE children_order SET seat='1' WHERE children=0000000001;
	string s1 = "UPDATE children_order SET seat='";
	string s2 = "' WHERE children=";
	string s3 = ";";
    string sql = s1 + co.Seat + s2 + co.Children +s3;
	db.query((char*)sql.c_str());
	return true;
}

void Order::where2where(vector<string>airline, vector<vector<string>> &res) {
	for (auto i = airline.begin(); i != airline.end(); i++) {
		//SELECT origin,destination,time_on,time_off,tomorrow FROM air WHERE airline='CA1222' AND date='2021-09-01';
		string s1 = "SELECT origin,destination,time_on,time_off,tomorrow FROM air WHERE airline='";
		string s2 = "' AND date='2021-09-01';";
		string sql = s1 + *i + s2;

		vector<vector<string>> v;
		db.fetch_data((char*)sql.c_str(), v);
		res.push_back(v[0]);
	}

}

bool Order::cmp_timei(vector<string> f1, vector<string> f2) {
	//s1<s2返回ture(从小到大）
	int p = stoi(f1[3].substr(0, 2));
	int q = stoi(f2[3].substr(0, 2));
	if (p > q) return false;
	else if (p < q) return true;
	else {
		int m = stoi(f1[3].substr(3, 2));
		int n = stoi(f2[3].substr(3, 2));
		if (m > n) return false;
		else return true;  //没有做等于的判定，可能出bug
	}
}


int Order::cannot(Children_order& co) {
    //SELECT * FROM children_order WHERE who='li1234' AND date='2021-09-05';
    string s1 = "SELECT * FROM children_order WHERE who='" + co.Who + "' AND date='" + co.Date + "';";
    if (!db.query((char*)s1.c_str()))
        return 0; //如果当日没有任何订单就可以买
    else {
        vector<vector<string>> v1;
        db.fetch_data((char*)s1.c_str(), v1);  //拿到该乘客当日所有订单
        string s3 = "SELECT origin,destination,time_on,time_off,tomorrow,date FROM air WHERE airline='" + co.Airline + "' AND date='" + co.Date + "';";
        vector<vector<string>> coinfotmp;
        vector<string> coinfo;  //新加订单信息
        db.fetch_data((char*)s3.c_str(), coinfotmp);  //拿到新加订单的航班信息
        coinfo = coinfotmp[0];

        //int co_on = to_minute(coinfo[2]);  //要添加航班的起飞时间min
        //int co_off = to_minute(coinfo[3]);  //要添加航班的降落信息min

        vector<vector<string>> airinfo;
        for (auto i = v1.begin(); i != v1.end(); i++) {
            //SELECT origin,destination,time_on,time_off,tomorrow,date FROM air WHERE airline='CA111' AND date='2021-8-26';
            string s2 = "SELECT origin,destination,time_on,time_off,tomorrow,date,airline FROM air WHERE airline='" + (*i)[2] + "' AND date='" + (*i)[3] + "';";
            vector<vector<string>> info; //拿到这个订单的航班信息
            db.fetch_data((char*)s2.c_str(), info);
            airinfo.push_back(info[0]);
        }
        for (auto j = airinfo.begin(); j != airinfo.end(); j++) {
            if ((*j)[4] == "1") { //tomorrow = 1 +24
            string h = (*j)[3].substr(0, 2);
            string m = (*j)[3].substr(2, 6);

            h = std::to_string(std::stoi(h) + 24);

            (*j)[3] = h + m;   //还是hh:mm:ss的形式
            }
            //(*j)[2] = to_minute((*j)[2]);  //timeon转成min
            //(*j)[3] = to_minute((*j)[3]);  //timeoff转成min
        }
        sort(airinfo.begin(), airinfo.end(), cmp_timei); //按照降落时间从小到大排序,还是string hh:mm:ss的形式

        auto k = airinfo.begin();
        while (to_minute((*k)[3]) < to_minute(coinfo[2])) k++; //*k3:timeoff(string)  coinfo2:timeon（string）
        if (k == airinfo.end()) { //继续判断新订单起飞地和上一个订单目的地时间够不够飞

            //string last_destination = airinfo.back()[1];
            int dur = between(airinfo.back()[1], coinfo[0]); //拿到两个城市间距离（分钟）
            //最后一班降落时间 airinfo.back()[3]
            int last_time = to_minute(airinfo.back()[3]) + dur; //上一次航班的总分钟（加距离）
            //新航班起飞时间coinfo[2]
            int new_time = to_minute(coinfo[2]); //新加航班的总分钟

            if (last_time > new_time) {
                //airinfo.back()[6]:airline     airinfo.back()[5]:date
                //conflict = get_conflict(airinfo.back()[6], airinfo.back()[5]);
                return 2; //不能及时赶到目的地

            }
            else {

                return 0; //可以飞
            }

        }
        else {

            //新加航班降落地点：coinfo[1]
            //新加航班后一个航班的起飞地点：(*k)[0]

            int new_time = to_minute(coinfo[3]); //新加航班落地时间：coinfo[3]
            int next_time = to_minute((*k)[2]); //新加航班后一个航班的起飞时间：(*k)[2]
            int new_ori = to_minute(coinfo[2]); //新加航班起飞时间：coinfo[2]
            int last_ld = to_minute((*(k - 1))[3]); //新加航班前一个航班的落地时间：(*(k-1))[3]

            if (next_time > new_time) {
                int dur1 = between(coinfo[1], (*k)[0]);
                int new_time_dur = to_minute(coinfo[3]) + dur1; //加距离
                if (new_time_dur > new_time) {

                    return 3; //来不及从新加航班目的地赶往下一班航班出发地
                }
                else {//判断前一个航班落地到新加航班起飞能不能飞
                    if ((last_ld + dur1) > new_ori) {
                        return 2; //
                    }
                    else return 0;

                }

            }
            else {

                return 1; //在飞机上
            }

        }

    }

}


inline int Order::to_minute(string& time) {
	string m = time.substr(0, 2);  //小时
	return (std::stoi(m) * 60 + std::stoi(time.substr(3, 2))); //上一次航班的总分钟
}

inline int Order::between(string& ori, string& des) {
	//SELECT `minute` FROM during WHERE origin='北京' AND destination='上海';
	string s4 = "SELECT `minute` FROM during WHERE origin='" + ori + "' AND destination='" + des + "';";
	vector<vector<string>> v;
	db.fetch_data((char*)s4.c_str(), v);
	//string during = v[0][0];  耗时（分钟形式）
	return std::stoi(v[0][0]);
}

inline string Order::get_conflict(string& airline, string& date) {
	//SELECT children FROM children_order WHERE airline='' AND date='';
	string s5 = "SELECT children FROM children_order WHERE airline='" + airline + "' AND date='" + date + "';";
	vector<vector<string>> tmp;
	db.fetch_data((char*)s5.c_str(), tmp); //拿到冲突的子订单号
	return tmp[0][0];
}


