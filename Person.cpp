//
// Created by Jinyuan on 8/30/21.
//

#include "Person.h"
#include <utility>


User::User() {
    this->ID = "empty";
    this->Name = "empty";
    this->Gender = "empty";
    this->Tel = "empty";
    this->Password = "empty";
    this->Email = "empty";
}

User::User(string id, string name, string gender, string tel, string password, string email)
    :ID(id), Name(name), Gender(gender), Tel(tel), Password(password), Email(email){}


bool User::change_name(string new_name) {
    Name = new_name;
    return true;
}

bool User::change_gender(string new_gender) {
    if (new_gender == "男" || new_gender == "女"){
        Gender = new_gender;
        return true;
    }else return false;
}

bool User::change_email(string new_email)
{
    int cnt = 0;
    int at =0;
    int po=0;
    for(int i=0; i <new_email.size();i++) {
        if(isalnum(new_email[i]) != 0) {
            cnt++;
            //	printf("cnt = %d\n",cnt);
        }
    }
    cnt = cnt+2;
    for(int j=0; j <new_email.size();j++) {
        if(new_email.at(j) == '@') {
            at = j;
            //	printf("at = %d\n",at);
            break;
        }
    }
    for(int k=0; k <new_email.size();k++) {
        if(new_email.at(k) == '.') {
            po = k;
            //	printf("po = %d\n",po);
            break;
        }
    }
    if(   ((at<po)&&(at<(po+1))&&(at!=1)&&(po!=new_email.size())&&(cnt == new_email.size()) )   )
    {
        Email = new_email;
        return 1;
    }
    else{
        printf("输入邮箱格式错误！请重新输入：");
        return 0;
    }

}


bool User::change_password(string new_password)
{
    int num1 = 0;
    num1 = new_password.length();
    if(num1 < 6 || num1 > 20) {
        cout << "密码位数要在6-20位之间!请重新输入" << endl;
        return 0;
    }
    else {
        Password = new_password;
        return 1;
    }
}

bool User::change_tel(string new_tel) {
    int num = 0;
    num = new_tel.length();
    if (num!=11) /////////判断电话号码位数
        {
        printf("电话号码为11位数字！请重新输入\n");
        return 0;
        }
    else {
        for (int i=0;i<new_tel.size() ;i++ ) {
            if((new_tel.at(i)>'9' ) || (new_tel.at(i)<'0')) {
                printf("电话号码应全为数字!请重新输入\n");
                return 0;
            }
        }
        Tel = new_tel;
        return 1;
    }
}





Admin::Admin() {
    this->ID = "empty";
    this->Name = "empty";
    this->Gender = "empty";
    this->Tel = "empty";
    this->Password = "empty";
    this->Email = "empty";
    this->Company = "empty";
}

Admin::Admin(string id, string name, string gender, string tel, string password, string email, string company)
:ID(id), Name(name), Gender(gender), Tel(tel), Password(password), Email(email), Company(company){}

bool Admin::change_name(string new_name) {
    Name = new_name;
}

bool Admin::change_gender(string new_gender) {
    if (new_gender == "男" || new_gender == "女"){
        Gender = new_gender;
        return true;
    }else return false;
}

bool Admin::change_email(string new_email) {
    Email = new_email;
}

bool Admin::change_password(string new_password) {
    int num1 = 0;
    num1 = new_password.length();
    if(num1 < 6 || num1 > 20) {
        cout << "密码位数要在6-20位之间!请重新输入" << endl;
        return 0;
    }
    else {
        Password = new_password;
        return 1;
    }
}

bool Admin::change_tel(string new_tel) {
    int num = 0;
    num = new_tel.length();
    if (num!=11) /////////判断电话号码位数
        {
        printf("电话号码为11位数字！请重新输入\n");
        return 0;
        }
    else {
        for (int i=0;i<new_tel.size() ;i++ ) {
            if((new_tel.at(i)>'9' ) || (new_tel.at(i)<'0')) {
                printf("电话号码应全为数字!请重新输入\n");
                return 0;
            }
        }
        Tel = new_tel;
        return 1;
    }
}



Person::Person() {
    //从文件中读数据？？

    this->heads.admin_head = nullptr;
    this->heads.user_head = nullptr;
    user_number = 0;
    admin_number = 0;
}

Person::~Person() {
    if (heads.user_head){
        user_node *p, *q = nullptr;
        for (q = heads.user_head, p = heads.user_head->next; p; q = p, p = p->next){
            delete q;
        }
        delete q;
    }
    if (heads.admin_head){
        admin_node *p, *q = nullptr;
        for (q = heads.admin_head, p = heads.admin_head->next; p; q = p, p = p->next){
            delete q;
        }
        delete q;
    }
}

bool Person::add_user(User &user) {

    user_node *p1 = nullptr;
    for (p1 = heads.user_head; p1; p1 = p1->next){
        if (p1->man.ID == user.ID ){
            printf("此账户已经存在，请重新输入:");
            return false;
        }
    }

    user_node* p = new user_node;
    p->man = user;
    p->next = nullptr;
    if (heads.user_head){
        user_node *last = heads.user_head;
        while(last->next){
            last = last->next;
        }
        last->next = p;
    }else{
        heads.user_head = p;
    }
    this->user_number++;
    return true;
}


bool Person::add_admin(Admin &admin) {
    admin_node *p1 = nullptr;
    for (p1 = heads.admin_head; p1; p1 = p1->next){
        if (p1->man.ID == admin.ID ){
            printf("此账户已经存在，请重新输入:");
            return false;
        }
    }

    admin_node* p = new admin_node;
    p->man = admin;
    p->next = nullptr;
    if (heads.admin_head){
        admin_node *last = heads.admin_head;
        while(last->next){
            last = last->next;
        }
        last->next = p;
    }else{
        heads.admin_head = p;
    }
    this->admin_number++;
    return true;
}


user_node *Person::search_user(string id) {
    user_node *p = nullptr;
    for (p = heads.user_head; p; p = p->next){
        if (p->man.ID == id){
            return p;
        }
    }
    return nullptr;
}

admin_node *Person::search_admin(string id) {
    admin_node *p = nullptr;
    for (p = heads.admin_head; p; p = p->next){
        if (p->man.ID == id){
            return p;
        }
    }
    return nullptr;
}

bool Person::del_user(string id) {
    user_node *p, *q = nullptr;
    for (p = heads.user_head; p; q = p, p = p->next){
        if (p->man.ID == id){
            if (q){  //p不是头结点
                q->next = p->next;
            }else{   //p是头结点
                heads.user_head = p->next;
            }
            delete p;
            this->user_number--;
            return true;
        }
    }
    return false;
}

bool Person::del_admin(string id) {
    admin_node *p, *q = nullptr;
    for (p = heads.admin_head; p; q = p, p = p->next){
        if (p->man.ID == id){
            if (q){  //p不是头结点
                q->next = p->next;
            }else{   //p是头结点
                heads.admin_head = p->next;
            }
            delete p;
            this->admin_number--;
            return true;
        }
    }
    return false;
}

User* Person::user_login(string id, string pw, int *flag) {
    user_node *p = search_user(id);
    if (p){
        if (p->man.Password == pw){
            *flag = 1;
            return &(p->man);
        }
        else {
            *flag = 3;
            return nullptr;
        };
    }else{
        *flag = 2;
        return nullptr;
    }
}

Admin* Person::admin_login(string id, string pw, int *flag) {
    admin_node *p = search_admin(id);
    if (p){
        if (p->man.Password == pw){
            *flag = 1;
            return &(p->man);
        }
        else {
            *flag = 3;
            return nullptr;
        };
    }else{
        *flag = 2;
        return nullptr;
    }
}

void Person::print_user(string id) {
    print_user(search_user(id)->man);
}

void Person::print_user(User user) {
    cout << "ID: " << user.ID << endl;
    cout << "Name: " << user.Name << endl;
    cout << "Gender: " << user.Gender << endl;
    cout << "Tel: " << user.Tel << endl;
    cout << "Password: " << user.Password << endl;
    cout << "Email: " << user.Email << endl;
}

void Person::print_all_user() {
    int cnt = 0;
    for (user_node *p = heads.user_head; p; p = p->next){
        cout << ++cnt << endl;
        print_user(p->man);
        cout << endl;
    }
}

int Person::import_user(string filename) {
    Read read(filename);
    user_node *tmp = new user_node;
    int cnt = 0; //统计一下读了多少进去

    //要求文件中至少有一套数据
    cnt++;
    tmp->man.ID = read.read_line();
    tmp->man.Name = read.read_line();
    tmp->man.Gender = read.read_line();
    tmp->man.Tel = read.read_line();
    tmp->man.Password = read.read_line();
    tmp->man.Email = read.read_line();
    heads.user_head = tmp;
    user_node *p = heads.user_head;

    string test = read.read_line();
    while (test != "EOF"){
        user_node *tmp2 = new user_node;
        cnt++;
        tmp2->man.ID = test;
        tmp2->man.Name = read.read_line();
        tmp2->man.Gender = read.read_line();
        tmp2->man.Tel = read.read_line();
        tmp2->man.Password = read.read_line();
        tmp2->man.Email = read.read_line();
        p->next = tmp2;
        p = p->next;
        test = read.read_line();
    }
    return cnt;
}

int Person::export_user(string filename) {
    Write write(filename);
    user_node *p = heads.user_head;
    int cnt = 0;
    for (p = heads.user_head; p; p = p->next){
        cnt++;
        write.append(p->man.ID);
        write.append(p->man.Name);
        write.append(p->man.Gender);
        write.append(p->man.Tel);
        write.append(p->man.Password);
        write.append(p->man.Email);
    }
    return cnt;
}