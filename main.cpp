#include <iostream>
#include "Person.h"


using namespace std;
int main() {

    Person person;
//    User user1("1234", "习近平", "男", "18710062238", "password", "xjp@outlook.com");
//    User user2("1222", "张三", "男", "18710061111", "password", "zs@outlook.com");
//    User user3("3456", "张王八", "男", "18710061111", "password", "zs@outlook.com");
//    person.add_user(user1);
//    person.add_user(user2);
//    person.add_user(user3);
//    person.print_all_user();


//
//    int a = person.export_user("list.txt");
//    cout << a << endl;
    int b = person.import_user("users.txt");
    cout << b << endl;
//    person.print_user("1222");
    person.print_all_user();


//    cout << person.user_number << endl;
//    person.print_user("1222");34");
//    find->man.change_name("宋yl"
////    user_node *find = person.search_user("12);
//    person.print_all_user();

//    Write file1("list.txt");
//    file1.append("12 34");
//    file1.append("123");
//    file1.append("1234");
//    file1.append("12345");
//    file1.append("123456");
//
//    cout << CountLines("list.txt") << endl;
//
//    Read read1("list.txt");
//    string a = read1.read_line();
//    string b = read1.read_line();
//    string c = read1.read_line();
//    string d = read1.read_line();
//    string e = read1.read_line();
//    string f = read1.read_line();
//    string g = read1.read_line();
//    string h = read1.read_line();
//
//    cout << a << endl;
//    cout << b << endl;
//    cout << c << endl;
//    cout << d << endl;
//    cout << e << endl;
//    cout << f << endl;
//    cout << g << endl;
//    cout << h << endl;







    return 0;
}
