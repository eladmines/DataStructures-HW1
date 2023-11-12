#include <iostream>
#include "employee.h"

class KeyBySalary{
    private:
    int salary;
    Employee* employee; 
    public:
    ~KeyBySalary() = default;
    KeyBySalary() = default;
    KeyBySalary(int salary,Employee* employee)
    {
       this->salary = salary;
       this->employee = new Employee();
       this->employee = employee; 
    };

     bool operator==(KeyBySalary key){
        if(salary==key.salary) return true;
        return false;
    }

    bool operator>(KeyBySalary key){
        if(salary>key.salary) return true;
        return false;
    }

    bool operator<(KeyBySalary key){
        if(salary<key.salary) return true;
        return false;
    }

    int getSalary(){
        return salary;
    }

    Employee* getEmployee()
    {
        return employee;
    } 



};