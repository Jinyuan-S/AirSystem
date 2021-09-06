#pragma once
#include "Database.h"
#include "Flight.h"
#include <algorithm>

using std::string;

class Inquiry
{
public:
	//���ݣ���ɵأ�Ŀ�ĵأ����ڲ�ѯ������һ��vector��Ĭ�ϰ����ʱ������
	int search(string& origin, string& destination, string& date, vector<Flight>& vec);
	//�������ʱ����絽������Ĭ�ϣ�
	void sort_by_time_inc(vector<Flight>& vec);
	//�������ʱ�����������
	void sort_by_time_dec(vector<Flight>& vec);
	//���ռ۸���������
	void sort_by_price_inc(vector<Flight>& vec);
	//���ռ۸�������
	void sort_by_price_dec(vector<Flight>& vec);
	//�����չ�˾ɸѡ�����빫˾����ԭʼvector���ս��vector
	void filter_by_company(string& company,vector<Flight>& vec, vector<Flight>& res);
	//����ʱ���ɸѡ������ʱ��ֻ��Сʱ����ʽ��06����λ��
	void filter_by_time(string& begin, string& end, vector<Flight>& vec, vector<Flight>& res);

private:
	Database db;
	bool cmp_timei(Flight& f1, Flight& f2);
	bool cmp_timed(Flight& f1, Flight& f2);
	bool cmp_priced(Flight& f1, Flight& f2);
	bool cmp_pricei(Flight& f1, Flight& f2);
};

