#include <iostream>
#include "Person.h"
#include <mysql.h>
#include <stdlib.h>
#include <vector>
#include "Database.h"
#include "Admin.h"
#include "Buyer.h"
#include "Person.h"


#include <algorithm>
using std::vector;



bool cmp(string & s1, string & s2) {
    //s1<s2返回ture
    string p = s1.substr(0, 2);
    string q = s2.substr(0, 2);
    if (p > q) return false;
    else if (p < q) return true;
    else {
        string m = s1.substr(3, 2);
        string n = s2.substr(3, 2);
        if (m > n) return false;
        else return true;  //没有做等于的判定，可能出bug
    }
}


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
 

    string s1 = "06:25:00";
    string s2 = "00:35:00";
    string s3 = "06:35:00";

    bool a = cmp(s1, s2);
    std::cout << a << std::endl;
    vector<string> v;
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);

    std::sort(v.begin(), v.end(), cmp);
    
    std::cout << v[0] << std::endl;
    std::cout << v[1] << std::endl;
    std::cout << v[2] << std::endl;

    return 0;
}
