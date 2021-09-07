#pragma once
#include "Buyer.h"
#include "Database.h"
#include "Flight.h"

class Admin:public Buyer
{
public:
    string Company;

public:
    Admin();
    //������������,����begin��endʱ����ڵ�flight����
    void order_by_attendance(string& begin, string& end, vector<Flight>& res);
    //����Ǯ������,����begin��endʱ����ڵ�flight����
    void order_by_total_fare(string& begin, string& end, vector<Flight>& res);
    //���ѹ�����������,����begin��endʱ����ڵ�flight���ݣ���ʦҪ������δ��ɵĺ��࣬��˲����ж���
    void order_by_total_buyer(string& begin, string& end, vector<Flight>& res);

private:
    Database db;
    inline void atd_sql(string& begin, string& end, string& sql);//attendance
    inline void ttf_sql(string& begin, string& end, string& sql);//total_fare
    inline void ttb_sql(string& begin, string& end, string& sql);//total_buyer

    inline void tail(string& sql, vector<Flight> res); //����sql��䣬ȡ��vector<Flight>
};

