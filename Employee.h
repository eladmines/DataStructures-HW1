#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>

class  Employee{
    private:
    int employeeID;
    int salary;
    int companyId;
    int grade;
    Company* emcompany; //pointer to the the company node in the "big" avl tree of the companies.


    public:
    Employee(int employeeID,int companyId,int salary,int grade,Company* company){
       this->employeeID=employeeID;
       this->companyId=companyId;
       this->salary=salary;
       this->grade = grade;
       //emcompany = new Company();
       emcompany=company;
    }
    ~Employee() = default;
    Employee()
    {
        employeeID=0;
        salary=0;
        companyId=0;
        grade=0;

    }
    void setCompanyID(int companyID, Company* company){
        companyId=companyID;
        emcompany=company;
    }

    int getCompanyID()
    {
        return companyId;
    }

    Company* getCompany()
    {
        return emcompany;
    }

    int getSalary()
        {
            return salary;
        }

    void setSalary(int newSalary)
        {
            salary=newSalary;
        }
    
    void setGrade(int newGrade)
        {
            grade=newGrade;
        }

        int getGrade()
        {
            return grade;
        }

    int getEmployeeID()
        {
            return employeeID;
        }

    bool operator==(Employee emp){
        if(employeeID == emp.employeeID) return true;
        return false;
    }

    bool operator>(Employee emp){
        if(employeeID > emp.employeeID) return true;
        return false;
    }

    bool operator<(Employee emp){
        if(employeeID < emp.employeeID) return true;
        return false;
    }
    
};
#endif