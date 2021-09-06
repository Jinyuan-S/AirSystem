#include "Buyer.h"


Buyer::Buyer() {
    this->ID = "empty";
    this->Name = "empty";
    this->Gender = "empty";
    this->Tel = "empty";
    this->Password = "empty";
    this->Email = "empty";
}

Buyer::Buyer(string& id, string& name, string& gender, string& tel, string& password, string& email) {
    ID = id;
    Name = name;
    Gender = gender;
    Tel = tel;
    Password = password;
    Email = email;
}

int Buyer::change_id(string &new_id) {
    if (new_id.length() < 6 || new_id.length() > 10) {
        return 1;
    }
    else {
        for (int i = 0; i < new_id.size(); i++) {
            if ((new_id.at(i) > '9') || (new_id.at(i) < '0'))
                return 2;
            else if ((new_id.at(i) > 'Z') || (new_id.at(i) < 'A'))
                return 2;
            else if ((new_id.at(i) > 'z') || (new_id.at(i) < 'a'))
                return 2;
        }
        ID = new_id;
        return 0;
    }
}

int Buyer::change_name(string &new_name) {
    //��೤��Ϊ10
    if (new_name.length() < 1 || new_name.length() > 10) {
        return 1;
    }
    Name = new_name;
    return 0;
}

int Buyer::change_gender(string &new_gender) {
    //�������л���Ů
    if (new_gender != "��" && new_gender != "Ů")
        return 1;
    else {
        Gender = new_gender;
        return 0;
    }
}

int Buyer::change_email(string &new_email)
{
	int cnt = 0;
	int at =0;
	int po=0; 
	int po1=-1; 
	int jud=0;
	for(int i=0; i <new_email.size();i++) {
		if(isalnum(new_email[i]) != 0) {
			cnt++;
		}
	}
	cnt = cnt+2; 
	for(int j=0; j <new_email.size();j++) {
		if(new_email.at(j) == '@') {
			at = j;
			break;
		}
	}
	for(int k=0; k <new_email.size();k++) {
			if(new_email.at(k) == '.') {
				po = k;
				break;
		}
	}
	for(int y=(po+1); y<new_email.size() ;y++) {
		if(new_email.at(y) == '.') {
			po1 = y;
			break;
		}
	}
	if( po1 == -1) {
		if(   ((at<po)&&(at<(po+1))&&(at!=1)&&((po+1)!=new_email.size())&&(cnt == new_email.size()) )   ) 
	{
		Email = new_email;
		jud = 1;
		return 1;
	}
	}
	
	if(po1 != -1) {
		if(    ((at<(po-1))&&(at!=1)&&(po<(po1-1))&&((po1+1)!=new_email.size())&&((cnt+1) == new_email.size()) )     ) {
			Email = new_email;
		    jud = 1;
		    return 0;
		}
	}
	
	if(jud != 1)   {
		printf("�����ʽ����!����������:");
		return 1; 
	}
	
} 



int Buyer::change_password(string &new_password)
{
    int num1 = 0;
    num1 = new_password.length();
    if (num1 < 6 || num1 > 20) {
        cout << "����λ��Ҫ��6-20λ֮��!����������" << endl;
        return 0;
    }
    else {
        Password = new_password;
        return 1;
    }
}

int Buyer::change_tel(string &new_tel) {
    int num = 0;
    num = new_tel.length();
    if (num != 11) /////////�жϵ绰����λ��
    {
        //printf("�绰����Ϊ11λ���֣�����������\n");
        return 1;
    }
    else {
        for (int i = 0; i < new_tel.size(); i++) {
            if ((new_tel.at(i) > '9') || (new_tel.at(i) < '0')) {
                //printf("�绰����ӦȫΪ����!����������\n");
                return 2;
            }
        }
        Tel = new_tel;
        return 0;
    }
}

