#pragma once
#include "Buyer.h"
class Admin :
    public Buyer
{
public:
    string Company;

public:
    Admin();
    Admin(string& id, string& name, string& gender, string& tel, string& password, string& email, string& company);
};

