#pragma once
#include <string>

using std::string;

class Flight
{
public:

	string Airline;
	string Origin;
	string Destination;
	string Company;
	string Time_on;
	string Time_off;
	string Tomorrow;
	string Model;
	string A_remain;
	string B_remain;
	string C_remain;
	string A_sold;
	string B_sold;
	string C_sold;
	string Total_buyer;
	string Attendance;
	string Total_fare;
	string Date;
	string Rate;
	string Price;
	string Pilot;

public:
	Flight();
	~Flight() = default;
};

