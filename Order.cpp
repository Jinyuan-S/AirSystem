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
	int w = 0;  //��¼�±�
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
			
			conf_idx = w;  //��¼�±�
			return err;
		}
	}
	
	//��ʽ���
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
			//���Ҫ�õ�ԭ�������ݽ��и���
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
	//s1<s2����ture(��С����
	int p = stoi(f1[3].substr(0, 2));
	int q = stoi(f2[3].substr(0, 2));
	if (p > q) return false;
	else if (p < q) return true;
	else {
		int m = stoi(f1[3].substr(3, 2));
		int n = stoi(f2[3].substr(3, 2));
		if (m > n) return false;
		else return true;  //û�������ڵ��ж������ܳ�bug
	}
}


int Order::cannot(Children_order& co) {
    //SELECT * FROM children_order WHERE who='li1234' AND date='2021-09-05';
    string s1 = "SELECT * FROM children_order WHERE who='" + co.Who + "' AND date='" + co.Date + "';";
    if (!db.query((char*)s1.c_str()))
        return 0; //�������û���κζ����Ϳ�����
    else {
        vector<vector<string>> v1;
        db.fetch_data((char*)s1.c_str(), v1);  //�õ��ó˿͵������ж���
        string s3 = "SELECT origin,destination,time_on,time_off,tomorrow,date FROM air WHERE airline='" + co.Airline + "' AND date='" + co.Date + "';";
        vector<vector<string>> coinfotmp;
        vector<string> coinfo;  //�¼Ӷ�����Ϣ
        db.fetch_data((char*)s3.c_str(), coinfotmp);  //�õ��¼Ӷ����ĺ�����Ϣ
        coinfo = coinfotmp[0];

        //int co_on = to_minute(coinfo[2]);  //Ҫ��Ӻ�������ʱ��min
        //int co_off = to_minute(coinfo[3]);  //Ҫ��Ӻ���Ľ�����Ϣmin

        vector<vector<string>> airinfo;
        for (auto i = v1.begin(); i != v1.end(); i++) {
            //SELECT origin,destination,time_on,time_off,tomorrow,date FROM air WHERE airline='CA111' AND date='2021-8-26';
            string s2 = "SELECT origin,destination,time_on,time_off,tomorrow,date,airline FROM air WHERE airline='" + (*i)[2] + "' AND date='" + (*i)[3] + "';";
            vector<vector<string>> info; //�õ���������ĺ�����Ϣ
            db.fetch_data((char*)s2.c_str(), info);
            airinfo.push_back(info[0]);
        }
        for (auto j = airinfo.begin(); j != airinfo.end(); j++) {
            if ((*j)[4] == "1") { //tomorrow = 1 +24
            string h = (*j)[3].substr(0, 2);
            string m = (*j)[3].substr(2, 6);

            h = std::to_string(std::stoi(h) + 24);

            (*j)[3] = h + m;   //����hh:mm:ss����ʽ
            }
            //(*j)[2] = to_minute((*j)[2]);  //timeonת��min
            //(*j)[3] = to_minute((*j)[3]);  //timeoffת��min
        }
        sort(airinfo.begin(), airinfo.end(), cmp_timei); //���ս���ʱ���С��������,����string hh:mm:ss����ʽ

        auto k = airinfo.begin();
        while (to_minute((*k)[3]) < to_minute(coinfo[2])) k++; //*k3:timeoff(string)  coinfo2:timeon��string��
        if (k == airinfo.end()) { //�����ж��¶�����ɵغ���һ������Ŀ�ĵ�ʱ�乻������

            //string last_destination = airinfo.back()[1];
            int dur = between(airinfo.back()[1], coinfo[0]); //�õ��������м���루���ӣ�
            //���һ�ཱུ��ʱ�� airinfo.back()[3]
            int last_time = to_minute(airinfo.back()[3]) + dur; //��һ�κ�����ܷ��ӣ��Ӿ��룩
            //�º������ʱ��coinfo[2]
            int new_time = to_minute(coinfo[2]); //�¼Ӻ�����ܷ���

            if (last_time > new_time) {
                //airinfo.back()[6]:airline     airinfo.back()[5]:date
                //conflict = get_conflict(airinfo.back()[6], airinfo.back()[5]);
                return 2; //���ܼ�ʱ�ϵ�Ŀ�ĵ�

            }
            else {

                return 0; //���Է�
            }

        }
        else {

            //�¼Ӻ��ཱུ��ص㣺coinfo[1]
            //�¼Ӻ����һ���������ɵص㣺(*k)[0]

            int new_time = to_minute(coinfo[3]); //�¼Ӻ������ʱ�䣺coinfo[3]
            int next_time = to_minute((*k)[2]); //�¼Ӻ����һ����������ʱ�䣺(*k)[2]
            int new_ori = to_minute(coinfo[2]); //�¼Ӻ������ʱ�䣺coinfo[2]
            int last_ld = to_minute((*(k - 1))[3]); //�¼Ӻ���ǰһ����������ʱ�䣺(*(k-1))[3]

            if (next_time > new_time) {
                int dur1 = between(coinfo[1], (*k)[0]);
                int new_time_dur = to_minute(coinfo[3]) + dur1; //�Ӿ���
                if (new_time_dur > new_time) {

                    return 3; //���������¼Ӻ���Ŀ�ĵظ�����һ�ຽ�������
                }
                else {//�ж�ǰһ��������ص��¼Ӻ�������ܲ��ܷ�
                    if ((last_ld + dur1) > new_ori) {
                        return 2; //
                    }
                    else return 0;

                }

            }
            else {

                return 1; //�ڷɻ���
            }

        }

    }

}


inline int Order::to_minute(string& time) {
	string m = time.substr(0, 2);  //Сʱ
	return (std::stoi(m) * 60 + std::stoi(time.substr(3, 2))); //��һ�κ�����ܷ���
}

inline int Order::between(string& ori, string& des) {
	//SELECT `minute` FROM during WHERE origin='����' AND destination='�Ϻ�';
	string s4 = "SELECT `minute` FROM during WHERE origin='" + ori + "' AND destination='" + des + "';";
	vector<vector<string>> v;
	db.fetch_data((char*)s4.c_str(), v);
	//string during = v[0][0];  ��ʱ��������ʽ��
	return std::stoi(v[0][0]);
}

inline string Order::get_conflict(string& airline, string& date) {
	//SELECT children FROM children_order WHERE airline='' AND date='';
	string s5 = "SELECT children FROM children_order WHERE airline='" + airline + "' AND date='" + date + "';";
	vector<vector<string>> tmp;
	db.fetch_data((char*)s5.c_str(), tmp); //�õ���ͻ���Ӷ�����
	return tmp[0][0];
}


