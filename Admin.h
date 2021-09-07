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
    //按上座率排序,返回begin到end时间段内的flight数据
    void order_by_attendance(string& begin, string& end, vector<Flight>& res);
    //按总钱数排序,返回begin到end时间段内的flight数据
    void order_by_total_fare(string& begin, string& end, vector<Flight>& res);
    //按已购买人数排序,返回begin到end时间段内的flight数据（老师要求排序未起飞的航班，后端不做判定）
    void order_by_total_buyer(string& begin, string& end, vector<Flight>& res);

private:
    Database db;
    inline void atd_sql(string& begin, string& end, string& sql);//attendance
    inline void ttf_sql(string& begin, string& end, string& sql);//total_fare
    inline void ttb_sql(string& begin, string& end, string& sql);//total_buyer

    inline void tail(string& sql, vector<Flight> res); //请求sql语句，取得vector<Flight>
};

