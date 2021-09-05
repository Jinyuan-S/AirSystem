#include "Admin.h"


Admin::Admin() {
	this->Company = "empty";
}

Admin::Admin(string& id, string& name, string& gender, string& tel, string& password, string& email, string& company) {
	this->ID = id;
	this->Name = name;
	this->Gender = gender;
	this->Tel = tel;
	this->Password = password;
	this->Email = email;
	this->Company = company;
}