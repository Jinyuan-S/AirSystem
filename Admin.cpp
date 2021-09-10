#include "Admin.h"
#include <QDebug>

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

int Admin::fly(Flight flt, int& which) {
	//SELECT time_on,time_off FROM air WHERE pilot1='����ȫ';
    int ii = 0;
    qDebug() << ii++;
	string s1 = "SELECT origin,destination,time_on,time_off,tomorrow,date,airline FROM air WHERE pilot1='" + flt.Pilot1 + "';";
    qDebug() << "Admin::fly s1";
	int result = db.query((char*)s1.c_str());  //������һ����Ա��û�к���
    qDebug() << "Admin::fly res";
	if (!result) {   //��һ������Աû�к���
        int wther2 = fly2(flt);
        qDebug() << "Admin::fly if";
        if (!wther2) { //�ڶ���Ҳ�ܷ�
            qDebug() << "Admin::fly if11";
			return 0;
		}
		else {
			which = 2; //�ڶ�������Ա������
            qDebug() << "Admin::fly if12";
			return wther2;  //���صڶ�������Ա�ı���ֵ
		}
	}
	else {  //��һ������Ա�к���
        qDebug() << "Admin::fly if2";
		vector<vector<string>> v1;
		db.fetch_data((char*)s1.c_str(), v1);  //�õ��÷���Ա���յķ�����Ϣ

        qDebug() << "Admin::fly if2 afterFetch";
		//�¼Ӻ�����Ϣ flt
        if(!isChanged)
        {
            flt.Time_on = std::to_string(to_minute(flt.Time_on));  //on  min
            flt.Time_off = std::to_string(to_minute(flt.Time_off));  //off min
            isChanged = 1;
        }

        qDebug() << "Admin::fly if2 Time_on_off";

		for (auto i = v1.begin(); i != v1.end(); i++) {
			//�Ϻ�����ɵأ�(*i)[0] ,Ŀ�ĵ� (*i)[1]
			//�º�����ɵأ�flt.origin,Ŀ�ĵ� flt.destination

			//�Ϻ���on=ԭʱ���ȥ���º���Ŀ�ĵص��Ϻ�����ɵص�ʱ��
            (*i)[2] = std::to_string(to_minute((*i)[2]) - between((*i)[0], flt.Destination));
            (*i)[3] = std::to_string(to_minute((*i)[3]) + between((*i)[1], flt.Origin));  //off  min

		}

        qDebug() << "Admin::fly if2 sort";
        std::sort(v1.begin(), v1.end(), cmp_time_i); //���ս���ʱ���С��������
        qDebug() << "Admin::fly if2 sort END";

		for (auto j = v1.begin(); j != v1.end(); j++) {
            qDebug() << "Admin::fly if2 for";
			if (*j == v1.back() && j == v1.begin()) {  //Ψһһ��
                qDebug() << "Admin::fly if2 for if1";
                if (std::stoi((*j)[3]) < std::stoi(flt.Time_on) || std::stoi((*j)[2]) > std::stoi(flt.Time_off)) { //�󷽿ɲ�

                    qDebug() << "Admin::fly if2 for if11";
					int wther2 = fly2(flt);
					if (!wther2) { //�ڶ���Ҳ�ܷ�
                        qDebug() << "Admin::fly if2 for if111";
						return 0;
					}
					else {
                        qDebug() << "Admin::fly if2 for if112";
						which = 2; //�ڶ�������Ա������
						return wther2;  //���صڶ�������Ա�ı���ֵ
					}
				}
                else {
                    qDebug() << "Admin::fly if2 for if12";
                    return 1;
                }
			}

			else if (*j == v1.back()) { //���һ��
                qDebug() << "Admin::fly if2 for if2";
                if (std::stoi((*j)[3]) < std::stoi(flt.Time_on)) { //�󷽿ɲ�

                    qDebug() << "Admin::fly if2 for if21";
					int wther2 = fly2(flt);
                    if (!wther2) { //�ڶ���Ҳ�ܷ�
                        qDebug() << "Admin::fly if2 for if211";
						return 0;
					}
					else {
                        qDebug() << "Admin::fly if2 for if212";
						which = 2; //�ڶ�������Ա������
						return wther2;  //���صڶ�������Ա�ı���ֵ
					}
				}
                else
                {
                    qDebug() << "Admin::fly if2 for if22";
                    return 1;
                }
			}
			else {        //�¸��������ʱ��-��������º��ཱུ��ʱ��                     //���ʱ��+����С�������ʱ��
                qDebug() << "Admin::fly if2 for if3";
                if (std::stoi((*(j + 1))[2]) > std::stoi(flt.Time_off) && std::stoi((*j)[3]) < std::stoi(flt.Time_on)) {
                    qDebug() << "Admin::fly if2 for if31";
					int wther2 = fly2(flt);
					if (!wther2) { //�ڶ���Ҳ�ܷ�

                        qDebug() << "Admin::fly if2 for if311";
						return 0;
					}
					else {

                        qDebug() << "Admin::fly if2 for if312";
						which = 2; //�ڶ�������Ա������
						return wther2;  //���صڶ�������Ա�ı���ֵ
					}
				}

				else {

                    qDebug() << "Admin::fly if2 for if32";
                    if (j == v1.begin() && std::stoi((*j)[2]) > std::stoi(flt.Time_off)) {  //�׸�ǰ�����

                        qDebug() << "Admin::fly if2 for if321";
						int wther2 = fly2(flt);
						if (!wther2) { //�ڶ���Ҳ�ܷ�

                            qDebug() << "Admin::fly if2 for if3211";
							return 0;
						}
						else {

                            qDebug() << "Admin::fly if2 for if3212";
							which = 2; //�ڶ�������Ա������
							return wther2;  //���صڶ�������Ա�ı���ֵ
						}
					}
                    else
                    {
                        qDebug() << "Admin::fly if2 for if322r";
                        return 1;
                    }
				}
			}
		}


	}
}

bool Admin::cmp_time_i(vector<string> f1, vector<string> f2) {
	//s1<s2����ture(��С����hh:mm:ss
	return(std::stoi(f1[3]) < std::stoi(f2[3])); //off min
}





int Admin::fly2(Flight flt) {
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
        if(!isChanged)
        {
            isChanged = 1;
            flt.Time_on = std::to_string(to_minute(flt.Time_on));  //on  min
            flt.Time_off = std::to_string(to_minute(flt.Time_off));  //off min
        }


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
                if (std::stoi((*j)[3]) < std::stoi(flt.Time_on) || std::stoi((*j)[2]) > std::stoi(flt.Time_off)) //�󷽿ɲ�
					return 0;
				else return 1;
			}

			else if (*j == v1.back()) { //���һ��
                if (std::stoi((*j)[3]) < std::stoi(flt.Time_on)) //�󷽿ɲ�
					return 0;
				else return 1;
			}
			else {        //�¸��������ʱ��-��������º��ཱུ��ʱ��                     //���ʱ��+����С�������ʱ��
                if (std::stoi((*(j + 1))[2]) > std::stoi(flt.Time_off) && std::stoi((*j)[3]) < std::stoi(flt.Time_on))
					return 0;
				else {
                    if (j == v1.begin() && std::stoi((*j)[2]) > std::stoi(flt.Time_off)) {  //�׸�ǰ�����
						return 0;
					}
					else return 1;
				}
			}
		}

	}
}



int Admin::add_flight(Flight f) {
	//SELECT airline FROM air WHERE airline='CA111';
	string s1 = "SELECT airline FROM air WHERE airline='"+ f.Airline +"' AND date='"+ f.Date +"';";
	if (db.query((char*)s1.c_str())) {
		return 1; //�ú����Ѿ�����
	}
	else {
//		int which = 0;
        qDebug() << "Admin::add_flight plt";
        int plt = fly(f/*, which*/);
        qDebug() << "Admin::add_flight plt END";
        if (plt) {
			return 2; //����Ա��ͻ
		}
		else {
            string sql = "INSERT INTO air(airline,origin,destination,company,time_on,time_off,tomorrow,model,A_remain,B_remain,C_remain,A_sold,B_sold,C_sold,total_buyer,total_fare,date,rate,price,pilot1,pilot2,attendance) VALUES('"
                + f.Airline +"','" + f.Origin + "','"+ f.Destination + "','"+f.Company + "','"+f.Time_on + "','"+f.Time_off + "','"+ f.Tomorrow + "','"+f.Model + "','10','20','300','0','0','0','0','0','"+f.Date + "','60.00','" + f.Price + "','"+f.Pilot1 + "','"+f.Pilot2+ "','0');";
            qDebug() << QString::fromLocal8Bit(sql);
            std::cout << sql << std::endl;
            db.query((char*)sql.c_str());
			return 0;
		}
	}
}

int Admin::fly(Flight& flt) {
    string s1 = "SELECT origin,destination,time_on,time_off,tomorrow,date,airline FROM air WHERE pilot1='" + flt.Pilot1 + "' AND `date`='" + flt.Date + "';";
    int result = db.query((char*)s1.c_str());  //������һ����Ա��û�к���
    if (!result) {   //��һ������Աû�к���
        string s2 = "SELECT origin,destination,time_on,time_off,tomorrow,date,airline FROM air WHERE pilot1='" + flt.Pilot2 + "' AND `date`='" + flt.Date + "';";
        int res = db.query((char*)s2.c_str());  //������һ����Ա��û�к���
        if(!res){
            ttt = flt.Time_off;
            return 0;
        }else return 1;

    }else {
        int dur = std::stoi(ttt.substr(0,2)) - std::stoi(flt.Time_on.substr(0,2));
        if(dur>5) return 0;
        else return 1;
    }
}








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
