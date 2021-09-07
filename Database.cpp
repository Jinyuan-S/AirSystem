#include "Database.h"

Database::Database() {

    //�1�7�1�7�0�3�1�7�1�7�1�7�1�7�1�7�1�3�1�7
    mysql_init(&mysql);
    //�1�7�1�7�1�7�0�9�1�7�1�7�1�0�0�4
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
    //�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�3�1�7
    //�1�7�؄1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�2�1�7�1�8�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�2�1�7�1�9�1�7
    //�0�0�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�3�1�7�1�7�0�1�1�7�1�7�1�7�1�7�1�7�1�7�1�7    8.136.214.13
    if (mysql_real_connect(&mysql, "8.136.214.13", "root", "654321", "airsystem", 3306, NULL, 0) == NULL)
        std::cout << "�1�7�1�7�1�7�1�7�0�2�1�7�1�1�1�7" << std::endl;

    return;
}

Database::~Database() {

    //�1�7�0�5�0�5�1�7�1�7�1�7�1�7�1�7
    mysql_free_result(res);
    //�1�7�1�9�1�7�1�7�1�7�1�7�1�3�1�7
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
    //�1�7�1�7�0�9�1�7�1�7�1�7�1�7
    //char a[200] = "select airline,company,origin,destination,time from air where company=\"Air China\";";
    char* b = new char[1000];
    b = Gb2312ToUtf8(sql);
    int rowcount = 0;
    mysql_query(&mysql, b);
    this->res = mysql_store_result(&mysql);//�1�7�1�7�0�0�1�7�1�7�1�7�1�7�1�7�1�7
    if(res)
        //�0�5�1�7�1�7�1�7�1�7�0�9�1�7�1�7�1�7�1�7�1�7�1�7�1�7���1�7�1�7�1�7�1�7�1�0�1�7�0�4�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7
        rowcount = mysql_num_rows(res);
    //free
    delete[] b;
    return rowcount;
}

unsigned int Database::field_num() {
    //�0�0�1�7�0�9�1�7�1�7�1�7�1�7�0�6�1�7�1�7�1�7�1�7�1�7 �1�7�1�7�1�7�1�7
    unsigned int fieldcount = mysql_num_fields(res);
    return fieldcount;
}


void Database::fetch_data(char *sql, vector<vector<std::string>> &vec) {
    int rownum = query(sql);
    unsigned int columnnum = field_num();

    int j = 0;

    //�1�7�1�7�0�8�1�7�1�7 �1�7�1�7�1�7�1�7�1�7�1�7
    while (NULL != (row = mysql_fetch_row(res))) //while (j=0 ,j<�1�7�1�7�1�7�1�7 �1�7�1�7j++�1�7�1�7
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
//    //�1�7�1�7�0�9�1�7�1�7�1�7�1�7
//    //char a[200] = "select airline,company,origin,destination,time from air where company=\"Air China\";";
//    char* b = new char[1000];
//    b = Gb2312ToUtf8(sql);
//    int rowcount = 0;
//    if (0 == mysql_query(&mysql, b)) {
//        this->res = mysql_store_result(&mysql);//�1�7�1�7�0�0�1�7�1�7�1�7�1�7�1�7�1�7
//        //�0�5�1�7�1�7�1�7�1�7�0�9�1�7�1�7�1�7�1�7�1�7�1�7�1�7���1�7�1�7�1�7�1�7�1�0�1�7�0�4�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7
//        rowcount = mysql_num_rows(res);
//    }
//    //free
//    delete[] b;
//    return rowcount;
//}
