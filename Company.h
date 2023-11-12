#include <iostream>
using namespace std;
#include "employee.h"
#include "KeyBySalary.h"



class Company{
    private:
    int companyId;
    int value;
    AVLTree<KeyBySalary*>* employeesSalaryKey;
    AVLTree<KeyByID*>* employeesIDKey;
    int HighestSalaryEmployee;
    int highestSalary;
    int LowestIDHighestSalaryEmployee;
    int lowestSalary;
    int numEmployees;
    Employee* highestEarner;
    public:
    Company(int companyId,int value){
        this->companyId=companyId;
        this->value=value;
        employeesSalaryKey = new AVLTree<KeyBySalary*>();
        employeesIDKey = new AVLTree<KeyByID*>();
        HighestSalaryEmployee=0;
        highestSalary=0;
        LowestIDHighestSalaryEmployee=0;
        numEmployees=0;
        highestEarner=new Employee();
    }
    Company() {
        companyId=0;
         value=0;
        //employeesSalaryKey = new AVLTree<KeyBySalary*>();
        //employeesIDKey = new AVLTree<KeyByID*>();
          HighestSalaryEmployee=0;
         highestSalary=0;
         LowestIDHighestSalaryEmployee=0;
         lowestSalary=0;
         numEmployees=0;
         highestEarner=new Employee();
    };
    AVLTree<KeyBySalary*>* getEmployeesSalaryKey(){
        return employeesSalaryKey;
    }

    AVLTree<KeyByID*>* getemployeesIDKey(){
        return employeesIDKey;
    }

     void setNumEmployees(int num){
        numEmployees=num;
    }

    void setValue(int num){
        value=num;
    }


    int getvalue(){
        return value;
    }

    int getNumEmployees(){
        return numEmployees;
    }

    int getCompanyID(){
        return companyId;
    }

    int getHighestEarner(){
        return HighestSalaryEmployee;
    }

    int getHigestSalary()
    {
         return highestSalary;;

    }

    Employee* getHighestEarnerEmployee(){
        return highestEarner;
    }

    void SetHighestEarner( Employee em){
        if(highestSalary<em.getSalary() || (highestSalary == em.getSalary() && HighestSalaryEmployee > em.getEmployeeID()))
        {
        *highestEarner = em;
        highestSalary = em.getSalary();
        HighestSalaryEmployee = em.getEmployeeID();
        }
    }

    StatusType addEmployeeToCompany(Employee* newEmployee)
    {
        try{
        KeyBySalary* newKeyBySalary = new KeyBySalary(newEmployee->getSalary(),newEmployee); //adding to the AVL tree by salary the employee
        employeesSalaryKey->root = employeesSalaryKey->insert(employeesSalaryKey->root,newKeyBySalary);

        KeyByID* newKeyByID = new KeyByID(newEmployee->getEmployeeID(),newEmployee); //adding to the AVL tree by ID the employee
        employeesIDKey->root = employeesIDKey->insert(employeesIDKey->root,newKeyByID);

        numEmployees++;
        if(newEmployee->getSalary()>highestSalary||(newEmployee->getSalary()==highestSalary && newEmployee->getEmployeeID() < HighestSalaryEmployee))
            {
                    highestSalary = newEmployee->getSalary();
                    HighestSalaryEmployee = newEmployee->getEmployeeID();
                    highestEarner=newEmployee;
            }
        
             return SUCCESS;
    
        }
        catch (std::bad_alloc&) {
            return ALLOCATION_ERROR;
        }
    }

    StatusType removeEmployeeFromCompany(Employee* retiredEmployee, Company* tempComp)
    {
        try{
        KeyBySalary* tempKeyBysalary = new KeyBySalary(retiredEmployee->getSalary(),retiredEmployee); //removing from the AVL tree by salary the employee
        tempComp->getEmployeesSalaryKey()->remove(tempComp->getEmployeesSalaryKey()->root,tempKeyBysalary);

         KeyByID* tempKeyByID = new KeyByID(retiredEmployee->getEmployeeID(),retiredEmployee); //removing from the AVL tree by ID the employee
         tempComp->getemployeesIDKey()->remove(tempComp->getemployeesIDKey()->root,tempKeyByID);
         numEmployees--;

        if(retiredEmployee->getSalary() == highestSalary && employeesSalaryKey->root!=NULL)
            {
                highestSalary = employeesSalaryKey->getMax(employeesSalaryKey->root)->data->getSalary();
                HighestSalaryEmployee = employeesSalaryKey->getMax(employeesSalaryKey->root)->data->getEmployee()->getEmployeeID();
                highestEarner= employeesSalaryKey->getMax(employeesSalaryKey->root)->data->getEmployee();
            }

        free(tempKeyBysalary);
        free(tempKeyByID);
        return SUCCESS;
        }
        catch (std::bad_alloc&) {
            return ALLOCATION_ERROR;
        }
    }

    void increaseCompanyValue(int increaseValue)
    {
        value += increaseValue;
    }
    
    ~Company() = default;
    bool operator<(Company comp){
        if(companyId<comp.companyId) return true;
        return false;
    }

    bool operator>(Company comp){
        if(companyId>comp.companyId) return true;
        return false;
    }

    bool operator==(Company comp){
        if(companyId==comp.companyId) return true;
        return false;
    }
};

