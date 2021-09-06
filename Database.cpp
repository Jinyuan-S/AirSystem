#include "Database.h"

Database::Database() {

    //初始化数据库
    mysql_init(&mysql);
    //设置编码方式
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
    //连接数据库
    //判断如果连接失败就输出连接失败。
    //注意你连接的账户名密码    8.136.214.13
    if (mysql_real_connect(&mysql, "8.136.214.13", "root", "654321", "airsystem", 3306, NULL, 0) == NULL)
        std::cout << "连接失败！" << std::endl;
    
    return;
}

Database::~Database() {

    //释放结果集
    mysql_free_result(res);
    //关闭数据库
    mysql_close(&mysql);
    return;
}

const char* Database::U2G(const char* utf8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return str;
}

char* Database::Gb2312ToUtf8(char* p) {
    DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
    char* psText;
    wchar_t* pwText = (wchar_t*)malloc(dwNum * sizeof(wchar_t));
    dwNum = MultiByteToWideChar(CP_ACP, 0, p, -1, pwText, dwNum);
    dwNum = WideCharToMultiByte(CP_UTF8, 0, pwText, -1, NULL, 0, NULL, NULL);
    psText = (char*)malloc(dwNum * sizeof(char));
    dwNum = WideCharToMultiByte(CP_UTF8, 0, pwText, -1, psText, dwNum, NULL, NULL);
    free(pwText);
    return psText;
}

int Database::query(char* sql) {
    //查询数据
    //char a[200] = "select airline,company,origin,destination,time from air where company=\"Air China\";";
    char* b = new char[1000];
    b = Gb2312ToUtf8(sql);
    int rowcount = 0;
    mysql_query(&mysql, b);
    this->res = mysql_store_result(&mysql);//获取结果集
    if(res)
        //一共查询到多少行（返回记录集总数）
        rowcount = mysql_num_rows(res);
    //free
    delete[] b;
    return rowcount;
}

unsigned int Database::field_num() {
    //取得表的字段数组 数量
    unsigned int fieldcount = mysql_num_fields(res);
    return fieldcount;
}


void Database::fetch_data(char *sql, vector<vector<std::string>> &vec) {
    int rownum = query(sql);
    unsigned int columnnum = field_num();
    
    int j = 0;
    
    //行指针 遍历行
    while (NULL != (row = mysql_fetch_row(res))) //while (j=0 ,j<行数 ，j++）
    {
        vec.push_back(vector<std::string>());
        for (int i = 0; i < columnnum; i++)
        {
            vec[j].push_back(U2G(row[i]));
        }
        ++j;
        std::cout << std::endl;
    }

}


//void Database::push_data(char* sql) {
//    char* b = new char[1000];
//    b = Gb2312ToUtf8(sql);
//    0 == mysql_query(&mysql, b);
//    return;
//}


//int Database::query(char* sql) {
//    //查询数据
//    //char a[200] = "select airline,company,origin,destination,time from air where company=\"Air China\";";
//    char* b = new char[1000];
//    b = Gb2312ToUtf8(sql);
//    int rowcount = 0;
//    if (0 == mysql_query(&mysql, b)) {
//        this->res = mysql_store_result(&mysql);//获取结果集
//        //一共查询到多少行（返回记录集总数）
//        rowcount = mysql_num_rows(res);
//    }
//    //free
//    delete[] b;
//    return rowcount;
//}
