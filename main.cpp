#include <iostream>
#include "Person.h"
#include <mysql.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Database.h"
#include "Admin.h"
#include "Buyer.h"
#include "Person.h"
#include "Inquiry.h"



#include <algorithm>
using std::vector;


int main() {

    /*Database db;
    vector<vector<string>> vec;
    vector<vector<string>>::iterator i;
    char a[100] = "select airline from air where company=\"Air China\";";
    db.fetchdata(a, vec);
    for (i = vec.begin(); i != vec.end(); i++) {
        vector<string>::iterator j;
        for (auto str : *i)
        {
            cout << str << endl;
        }
    }*/

    string date = "2021-10-01";
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
    std::cout << out << std::endl;
    
    return 0;
}
