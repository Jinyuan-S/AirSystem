#pragma once
#include "Database.h"
#include "Flight.h"
#include <algorithm>

using std::string;

class Inquiry
{
public:
	//根据，起飞地，目的地，日期查询，返回一个vector（默认按起飞时间排序）
    int search(string& origin, string& destination, string& date, vector<Flight>& vec);
    //根据，航班号，日期查询，返回一个vector（默认按起飞时间排序）
    int search(string& airline, string& date, vector<Flight>& vec);
	//按照起飞时间从早到晚排序（默认）
	void sort_by_time_inc(vector<Flight>& vec);
	//按照起飞时间从晚到早排序
	void sort_by_time_dec(vector<Flight>& vec);
	//按照价格升序排序
	void sort_by_price_inc(vector<Flight>& vec);
	//按照价格降序排序
	void sort_by_price_dec(vector<Flight>& vec);
	//按航空公司筛选，传入公司名，原始vector，空结果vector
	void filter_by_company(string& company,vector<Flight>& vec, vector<Flight>& res);
	//按照时间段筛选，传入时间只有小时，格式:（两位）
	void filter_by_time(string& begin, string& end, vector<Flight>& vec, vector<Flight>& res);
	//按照航班号进行筛选
	void filter_by_airline(string& airline, vector<Flight>& vec, vector<Flight>& res);
    //按照机型进行筛选
    void filter_by_model(string& model, vector<Flight>& vec, vector<Flight>& res);



	//首页推荐
	void recommand(string& date, vector<Flight>& res);
	


private:
	Database db;
    static bool cmp_timei(Flight f1, Flight f2);
    static bool cmp_timed(Flight f1, Flight f2);
    static bool cmp_priced(Flight f1, Flight f2);
    static bool cmp_pricei(Flight f1, Flight f2);
};

