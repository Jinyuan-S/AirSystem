
#pragma once
#include "Mother_order.h"
#include "Database.h"
#include <vector>
#include "Children_order.h"
#include <algorithm>


class Order
{
public:
	//�õ�һ���û������ж���,�����ҵ�ĸ�����ĸ���
	int get_all_order(string& id, vector<Mother_order>& vec);
	//�õ�һ��ĸ�������е��Ӷ����������ҵ��Ӷ����ĸ���
	int get_sub_order(Mother_order& mo, vector<Children_order>& vec);
	/*
	���Ӷ���:����һ��ĸ�������Ӷ���vector���Զ�����ĸ������������ӵ����ݿ⣬����bool
	�����ĸ������Ҫ��дTime��Contain��sub1-5֮���������Ϣ
	�Ӷ����Ĳ�λ������A,B,C��ʽ���������
	�Ӷ������ڱ����� 9.03 �ĸ�ʽ���������

	conf_idx�ǳ�ͻ��vector<Children_order>�±꣬�������ͻ����-1��children�ǳ�ͻ�����ж�������

	����ֵ��
		0���ɹ�����
		1����ǰ���ڷɻ���
		2�����ܼ�ʱ����һ�˺�����صظϵ��¼Ӻ�����ɵ�
		3�����������¼Ӻ���Ŀ�ĵظ�����һ�ຽ�������
	*/
	//bool add_order(Mother_order& mo, vector<Children_order>& vec);
	int add_order(Mother_order& mo, vector<Children_order>& vec, int& conf_idx, Children_order& conf);
	
	//����mother_order��ֻ�������is_paid��is_cancel
	bool renew(Mother_order& mo);
	//����mother_order��ֻ�������seat
	bool renew(Children_order& co);
	
	//���ݻ��Ͳ�����ɵ�Ŀ�ĵأ�����vector��origin,destination,time_on,time_off,tomorrow
    void where2where(vector<string>airline, vector<vector<string>> &res);

	//��ѯ����Ա/�û��ܲ��ܵ���
	//bool wuhu(string land, string off);
	/*
		�û��ܲ�����,�����ʱ���ʽһ����hh:mm:ss�����س�ͻ������
		0:������
		1����ǰ���ڷɻ���
		2�����ܼ�ʱ����һ�˺��ཫ��ظϵ��¼Ӻ�����ɵ�
		3�����������¼Ӻ���Ŀ�ĵظ�����һ�ຽ�������
	
	*/
	int cannot(Children_order& co, string& conflit);

private:
	Database db;
	//�ȽϺ������������ʱ��Ƚϴ�С����С����)
	static bool cmp_timei(vector<string> f1, vector<string> f2);
	//��hh:mm:ss����ʽת���ɷ���
	inline int to_minute(string& time);
	//��ѯ�����ط�֮��ľ��루���ӣ�
	inline int between(string& ori, string& des);
	//ͨ������ź�������children_order��Ѱ�Ҷ�����children
	inline string get_conflict(string& airline, string& date);
};

