#include <iostream>
#include "employee.h"

class KeyByID{
    private:
    int id;
    Employee* employee; 
    public:
    KeyByID(int id,Employee* employee):id(id),employee(employee){};
    ~KeyByID() = default;
    bool operator<(KeyByID key){
        if(id<key.id) return true;
        return false;
    }

    bool operator>(KeyByID key){
        if(id>key.id) return true;
        return false;
    }

    bool operator==(KeyByID key){
        if(id==key.id) return true;
        return false;
    }

     int getID(){
        return id;
    }

    Employee* getEmployee()
    {
        return employee;
    } 



};