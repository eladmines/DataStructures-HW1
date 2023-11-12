#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

#include <iostream>
#include "avl.h"
#include "library1.h"

class Company;
class KeyBySalary;


class  EmployeeManager{
    private:
    AVLTree<Company*> *companies;
    AVLTree<Employee*> *employees;
    AVLTree<KeyBySalary*> *EmployeesbySalary;
    int HighestSalaryEmployee;
    int highestSalary;
    int LowestIDHighestSalaryEmployee;
    int lowestSalary;
    int totalEmployees;
    int totalCompanies;
    public:
    EmployeeManager(){
        companies = new AVLTree<Company*>();
        employees = new AVLTree<Employee*>();
        EmployeesbySalary = new AVLTree<KeyBySalary*>();
        HighestSalaryEmployee=0;
        highestSalary=0;
        LowestIDHighestSalaryEmployee=0;
        lowestSalary=0;
        totalEmployees=0;
        totalCompanies=0;
    }
    
    ~EmployeeManager() = default;

    void setNumOfEmployees(int num)
    {
        totalEmployees=num;
    }

    void setNumOfCompanies(int num)
    {
        totalCompanies=num;
    }

    int getNumOfEmployee()
    {
        return totalEmployees;
    }

    int getNumOfCompanies(){
        return totalCompanies;
    }

    void *Init(){
                EmployeeManager* emanager = new EmployeeManager();
                return (emanager!=NULL) ? emanager:NULL;
    }

    StatusType AddCompany(void *DS, int CompanyID, int Value){
        if(DS==NULL||CompanyID<=0||Value<=0)
            return INVALID_INPUT;

           EmployeeManager* emanager = (EmployeeManager*) DS;
           try{
           Company* newCompany = new Company(CompanyID,Value);
           if(emanager->companies->findNode(emanager->companies->root,newCompany)!=NULL) //checks if the company allready exists in the system.
            { 
                free(newCompany);
                return  FAILURE;
            }
            emanager->companies->root = emanager->companies->insert(emanager->companies->root,newCompany);
            emanager->setNumOfCompanies(emanager->getNumOfCompanies()+1);
           return SUCCESS;
           }
           catch (std::bad_alloc&) {
            return ALLOCATION_ERROR;
           }
    }

        StatusType RemoveCompany(void *DS, int CompanyID){
            if(DS==NULL||CompanyID<=0)
            return INVALID_INPUT;

           EmployeeManager* emanager = new EmployeeManager();
           emanager = (EmployeeManager*) DS;
           
           try{
            Company* newCompany = new Company(CompanyID,0);
            Company* targetCompany = new Company(0,0);
           if(emanager->companies->findNode(emanager->companies->root,newCompany) != NULL )  //checks if the company not exists in the system.
            {    
                targetCompany = emanager->companies->findNode(emanager->companies->root,newCompany)->data;
                if( targetCompany->getNumEmployees() !=0)
                    return  FAILURE;
            emanager->companies->remove(emanager->companies->root,targetCompany);
            emanager->setNumOfCompanies(emanager->getNumOfCompanies()-1);
            return SUCCESS;
            }
            else return FAILURE;

           }

           catch (std::bad_alloc&) {
            return ALLOCATION_ERROR;
           } 

    }    

    StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade){
         if(DS==NULL||CompanyID<=0||EmployeeID<=0||Salary<=0||Grade<0){
            return INVALID_INPUT;
         }
            EmployeeManager* emanager = (EmployeeManager*) DS;

            try{
                 Company* tempCompany = new Company(CompanyID,1); //the value (1) doesn't matter, we only want to see if there is a company with the same ID.
                if(emanager->companies->findNode(emanager->companies->root,tempCompany) == NULL)// checks if the company (ONLY by ID) doesn't exist in the system.
                   {
                        free(tempCompany);
                        return  FAILURE;
                   }
                 
                 Employee* newEmployee = new Employee(EmployeeID,CompanyID,Salary,Grade,emanager->companies->findNode(emanager->companies->root,tempCompany)->data);
                 KeyBySalary* newKeyBySalary = new KeyBySalary(CompanyID,newEmployee);
                
                if(emanager->employees->findNode(emanager->employees->root,newEmployee) != NULL) //checks if the employee exists in the system.
                   {
                        free(tempCompany);
                        free(newEmployee);
                        free(newKeyBySalary);
                        return FAILURE;
                   }
                    if(Salary>=highestSalary && EmployeeID<HighestSalaryEmployee)
                        {
                            highestSalary = Salary;
                            HighestSalaryEmployee = EmployeeID;
                        }

                    emanager->employees->root = emanager->employees->insert(emanager->employees->root,newEmployee);
                    if(emanager->companies->findNode(emanager->companies->root,tempCompany) == NULL)
                        return FAILURE;
                    emanager->EmployeesbySalary->root = emanager->EmployeesbySalary->insert(emanager->EmployeesbySalary->root,newKeyBySalary);
                    if(emanager->companies->findNode(emanager->companies->root,tempCompany)->data->addEmployeeToCompany(newEmployee)==SUCCESS)
                       { 
                        emanager->setNumOfEmployees(emanager->getNumOfEmployee()+1);
                        return SUCCESS;
                       }

            }
            catch (std::bad_alloc&) {
            return ALLOCATION_ERROR;
           }
           return FAILURE;
    }

    StatusType RemoveEmployee(void *DS, int EmployeeID){
        if(DS==NULL||EmployeeID<=0)
                    return INVALID_INPUT;
        
        EmployeeManager* emanager = (EmployeeManager*) DS;
        try{
            Employee* tempEmployee = new Employee(EmployeeID,1,1,1,NULL); //the values (1) doesn't matter, we only want to see if there is an employee with the same ID.
            if(emanager->employees->findNode(emanager->employees->root,tempEmployee) == NULL)
                {
                free(tempEmployee);
                return FAILURE;
            }
            Employee* retiredEmployee = emanager->employees->findNode(emanager->employees->root,tempEmployee)->data;

            int salary = retiredEmployee->getSalary();
            if(retiredEmployee->getCompany()->removeEmployeeFromCompany(retiredEmployee,retiredEmployee->getCompany()) == SUCCESS)
            {
                    emanager->employees->remove( emanager->employees->root,retiredEmployee);
                    if(salary==highestSalary)
                    {
                        highestSalary=employees->getMax(employees->root)->data->getSalary();
                        HighestSalaryEmployee=employees->getMax(employees->root)->data->getEmployeeID();
                    }
                    emanager->setNumOfEmployees(emanager->getNumOfEmployee()-1);
                    return SUCCESS;
            }
        }

        catch (std::bad_alloc&) {
            return ALLOCATION_ERROR;
        }

    return FAILURE;
    }

    StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees){
        if(DS==NULL||CompanyID<=0||Value==NULL||NumEmployees==NULL)
                    return INVALID_INPUT;

         EmployeeManager* emanager = (EmployeeManager*) DS;
           try{
           Company* tempCompany = new Company(CompanyID,1);//the value (1) doesn't matter, we only want to see if there is a company with the same ID.
           if(emanager->companies->findNode(emanager->companies->root,tempCompany)==NULL) //checks if the company isn't exists in the system.
            { 
                free(tempCompany);
                return  FAILURE;
            }
            Company* targetCompany = emanager->companies->findNode(emanager->companies->root,tempCompany)->data;
            int companyValue = targetCompany->getvalue();
            int companyNumEmployees = targetCompany->getNumEmployees();
            *Value = companyValue;
            *NumEmployees = companyNumEmployees;
            free(tempCompany);
            return SUCCESS;

           }

            catch (std::bad_alloc&) {
                return ALLOCATION_ERROR;
            }


    }

    StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade){
        if(DS==NULL||EmployeeID<=0||EmployerID==NULL||Salary==NULL||Grade==NULL)
                    return INVALID_INPUT;

        EmployeeManager* emanager = (EmployeeManager*) DS;
           try{
               Employee* tempEmployee = new Employee(EmployeeID,1,1,1,NULL);
                if(emanager->employees->findNode(emanager->employees->root,tempEmployee) == NULL)
                    {
                    free(tempEmployee);
                    return FAILURE;
                    }
               Employee* targetEmployee = emanager->employees->findNode(emanager->employees->root,tempEmployee)->data;
                 
                *Salary=targetEmployee->getSalary();
                *EmployerID=targetEmployee->getCompanyID();
                *Grade=targetEmployee->getGrade();
                return SUCCESS;

           }

            catch (std::bad_alloc&) {
                return ALLOCATION_ERROR;
            }

    }

    StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease){
            if(DS==NULL||CompanyID<=0||ValueIncrease<=0){

                    return INVALID_INPUT;
            }

         EmployeeManager* emanager = (EmployeeManager*) DS;
         try{
         Company* tempCompany = new Company(CompanyID,1);//the value (1) doesn't matter, we only want to see if there is a company with the same ID.
           if(emanager->companies->findNode(emanager->companies->root,tempCompany)==NULL) //checks if the company isn't exists in the system.
            { 
                free(tempCompany);
                return  FAILURE;
            }
            emanager->companies->findNode( emanager->companies->root,tempCompany)->data->increaseCompanyValue(ValueIncrease);
            free(tempCompany);
            return SUCCESS;

         }
        catch (std::bad_alloc&) {
                return ALLOCATION_ERROR;
            }

    }

    StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade){
         if(DS==NULL||EmployeeID<=0||SalaryIncrease<=0||BumpGrade<=0)
                    return INVALID_INPUT;
        EmployeeManager* emanager = (EmployeeManager*) DS;
         try{

             Employee* tempEmployee = new Employee(EmployeeID,1,1,1,NULL);
             Employee* targetEmployee = new Employee(EmployeeID,2,2,2,NULL);
             if(emanager->employees->findNode(emanager->employees->root,tempEmployee)!=NULL){
                    targetEmployee = emanager->employees->findNode(emanager->employees->root,tempEmployee)->data;
             }
             else{
                 targetEmployee=NULL;
             }

                 if(targetEmployee==NULL)
            {
                free(tempEmployee);
                return FAILURE;
            }
            else{


            targetEmployee->setSalary(targetEmployee->getSalary()+SalaryIncrease);
            }
            if(targetEmployee->getCompany()->getHighestEarner() != targetEmployee->getEmployeeID() && targetEmployee->getCompany()->getHigestSalary() < targetEmployee->getSalary())
                {
                    targetEmployee->getCompany()->SetHighestEarner(*targetEmployee);
                    HighestSalaryEmployee = targetEmployee->getEmployeeID();
                }
            targetEmployee->setGrade( targetEmployee->getGrade()+1);
            return SUCCESS;

         }
          catch (std::bad_alloc&) {
                return ALLOCATION_ERROR;
            }
    }



    StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID){
            if(DS==NULL||EmployeeID<=0||NewCompanyID<=0)
                    return INVALID_INPUT;

            EmployeeManager* emanager = (EmployeeManager*) DS;
            try{
            
            Employee* tempEmployee = new Employee(EmployeeID,1,1,1,NULL); //the values (1) doesn't matter, we only want to see if there is an employee with the same ID.
            Employee* hiredEmployee = new Employee(EmployeeID,1,1,1,NULL);
            if (emanager->employees->root !=NULL)
                {
                if(emanager->employees->findNode(emanager->employees->root,tempEmployee)->data != NULL)
                    hiredEmployee = emanager->employees->findNode(emanager->employees->root,tempEmployee)->data;
                else
                {
                    free(tempEmployee);
                     free(hiredEmployee);
                     return FAILURE;
                }
                }
            else{
                free(tempEmployee);
                free(hiredEmployee);
                return FAILURE;
            }

            Company* beforeCompany = new Company(hiredEmployee->getCompanyID(),1); //the value (1) doesn't matter, we only want to see if there is a company with the same ID.
            Company* afterCompany = new Company(NewCompanyID,1); //as above
            if(emanager->companies->findNode(emanager->companies->root,afterCompany) == NULL || emanager->companies->findNode(emanager->companies->root,beforeCompany) == NULL)
            return FAILURE;
            afterCompany = emanager->companies->findNode(emanager->companies->root,afterCompany)->data; // 69//

            *tempEmployee = Employee(hiredEmployee->getEmployeeID(),hiredEmployee->getCompanyID(),hiredEmployee->getSalary(),hiredEmployee->getGrade(),hiredEmployee->getCompany());//copy of the employee with the old company
            hiredEmployee->setCompanyID(NewCompanyID,afterCompany);//changing the employee's companyID to the new one in the manager's employee tree
            if(tempEmployee->getCompany()->removeEmployeeFromCompany(tempEmployee,beforeCompany) == SUCCESS)//removing the employee from the old company
                if(hiredEmployee->getCompany()->addEmployeeToCompany(hiredEmployee) == SUCCESS)//adding the employee to the new company
                    {  
                    hiredEmployee->getCompany()->SetHighestEarner(*hiredEmployee);
                    free(beforeCompany);
                    return SUCCESS;
                    }

            
            //if 1 of the above "ifs" returned ALLOCATION_ERROR:
            free(tempEmployee);
            free(beforeCompany);
            free(afterCompany);
            free(hiredEmployee);
            return ALLOCATION_ERROR;

            }

            catch (std::bad_alloc&) {
                return ALLOCATION_ERROR;
            }


    }


    StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID){
             if(DS==NULL||EmployeeID<=0||CompanyID==0){
                    return INVALID_INPUT;
             }

                    EmployeeManager* emanager = (EmployeeManager*) DS;
                    int highestEarnerID;
            try{
                    if(CompanyID<0)
                        return FAILURE;//when company ID <0 there isn't a way that the company will not be empty because the way addEmployee works.
                    
                    Company* tempCompany = new Company(CompanyID,1);//the value (1) doesn't matter, we only want to see if there is a company with the same ID.
                    Company* targetCompany = new Company(CompanyID,1);
                    if (emanager->companies->findNode(emanager->companies->root,tempCompany) != NULL)
                    targetCompany = emanager->companies->findNode(emanager->companies->root,tempCompany)->data;
                    else //checks if the company isn't exists in the system.
                    { 
                        free(tempCompany);
                        free(targetCompany);
                        return  FAILURE;
                    }
                    
                     //Employee* highestEarner = emanager->employees->getHeight

                     if(targetCompany->getNumEmployees() == 0)//means there are not Employees in the company.
                    {
                        free(tempCompany);
                        free(targetCompany);
                        return FAILURE;
                    }
                    
                    if(CompanyID>0)
                    {
                     highestEarnerID = targetCompany->getHighestEarner();
                    *EmployeeID = highestEarnerID;
                    }
                    else
                    {
                     highestEarnerID = emanager->HighestSalaryEmployee;
                     *EmployeeID = highestEarnerID;
                    }
                    free(tempCompany);
                    return SUCCESS;

            }


            catch (std::bad_alloc&) {
                return ALLOCATION_ERROR;
            }


        return FAILURE;
    }

    StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor){
                 if(DS==NULL||AcquirerID<=0||TargetID<=0||Factor<1||AcquirerID==TargetID)
                    return INVALID_INPUT;
       
                EmployeeManager* emanager = (EmployeeManager*) DS;
            
                try{
                        Company* tempAquirerCompany = new Company(AcquirerID,1); //the value (1) doesn't matter, we only want to see if there is a company with the same ID.
                        Company* tempTargetCompany = new Company(TargetID,1); //as above
                        Company* aquirerCompany = new Company(1,1);
                        Company* targetCompany = new Company(1,1);;

                        if(emanager->companies->findNode(emanager->companies->root,tempAquirerCompany) != NULL){
                            aquirerCompany = emanager->companies->findNode(emanager->companies->root,tempAquirerCompany)->data;
                        }

                         if(emanager->companies->findNode(emanager->companies->root,tempTargetCompany) != NULL){
                          targetCompany = emanager->companies->findNode(emanager->companies->root,tempTargetCompany)->data;
                        }
                        

                        
                        if(aquirerCompany->getvalue()<10*targetCompany->getvalue())
                            {
                                free(tempAquirerCompany);
                                free(tempTargetCompany);
                                free(aquirerCompany);
                                free(targetCompany);
                                return FAILURE;
                            }
                            
                         

                        aquirerCompany->getemployeesIDKey()->root = aquirerCompany->getemployeesIDKey()->mergeAVL(aquirerCompany->getemployeesIDKey()->root,targetCompany->getemployeesIDKey()->root);
                        aquirerCompany->getEmployeesSalaryKey()->root = aquirerCompany->getEmployeesSalaryKey()->mergeAVL(aquirerCompany->getEmployeesSalaryKey()->getRoot(),targetCompany->getEmployeesSalaryKey()->getRoot());
                        aquirerCompany->setNumEmployees(aquirerCompany->getNumEmployees()+targetCompany->getNumEmployees());
                        aquirerCompany->setValue((aquirerCompany->getvalue()+targetCompany->getvalue())*Factor);
                        emanager->companies->findNode(emanager->companies->root,tempTargetCompany)->data->setNumEmployees(0);
                        
                          Node<KeyBySalary*>** employeesRoot= new Node<KeyBySalary*>*();
                           employeesRoot = aquirerCompany->getEmployeesSalaryKey()->ReverseInOrder(aquirerCompany->getEmployeesSalaryKey()->getRoot());
                           int i=0;
                           
                           if(employeesRoot == NULL)
                            return FAILURE;
                           //cout<< employeesRoot[i]->data->getSalary();
                           //cout<<employeesRoot[i]->data->getEmployee();
                            while(employeesRoot[i]!=NULL)
                            {
                                
                                employeesRoot[i]->data->getEmployee()->setCompanyID(aquirerCompany->getCompanyID(),aquirerCompany);
                                employeesRoot[i]->data->getEmployee()->getCompany()->SetHighestEarner(*employeesRoot[i]->data->getEmployee());

                                i++;
                            }
                        
                        RemoveCompany(DS,TargetID);

                        free(tempAquirerCompany);
                        free(tempTargetCompany);
                        //free(aquirerCompany);
                        //free(targetCompany);
                        return SUCCESS;



                }
                
    

                catch (std::bad_alloc&) {
                return ALLOCATION_ERROR;
            }    
            return SUCCESS; 
  
    
     }
    
    StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees){
        if(DS==NULL||CompanyID==0||Employees==NULL||NumOfEmployees==NULL)
                    return INVALID_INPUT;

                EmployeeManager* emanager = (EmployeeManager*) DS;

                try{
                    if(CompanyID>0)
                        {
                            Company* tempCompany = new Company(CompanyID,1);//the value (1) doesn't matter, we only want to see if there is a company with the same ID.
                             Company* targetCompany = new Company(CompanyID,1);
                            if(emanager->companies->findNode( emanager->companies->root,tempCompany)!= NULL)
                                targetCompany = emanager->companies->findNode( emanager->companies->root,tempCompany)->data;
                            else targetCompany=NULL;

                            if(targetCompany == NULL)
                                {   
                                    free(tempCompany);
                                    return FAILURE;
                                }

                            if(targetCompany->getNumEmployees()==0)
                                return FAILURE;
                            *NumOfEmployees=targetCompany->getNumEmployees();
                            Node<KeyBySalary*>** employeesRoot= (Node<KeyBySalary*>**)targetCompany->getEmployeesSalaryKey()->ReverseInOrder(targetCompany->getEmployeesSalaryKey()->getRoot());
                            int** employeesArr = (int**) malloc(sizeof(int*)*targetCompany->getNumEmployees());
                            for(int i=0; i<targetCompany->getNumEmployees()-1; i++)
                                *employeesArr[i]=employeesRoot[i]->data->getEmployee()->getEmployeeID();
                            
                            Employees=employeesArr;
                            free(tempCompany);
                            return SUCCESS;

                        }
                            if(emanager->getNumOfEmployee()==0)
                                return FAILURE;
                             Node<KeyBySalary*>** employeesRoot= (Node<KeyBySalary*>**)emanager->EmployeesbySalary->ReverseInOrder(emanager->EmployeesbySalary->getRoot());
                              int** employeesArr = (int**) malloc(sizeof(int*)*emanager->getNumOfEmployee());
                            for(int i=0; i<emanager->getNumOfEmployee()-1; i++)
                                *employeesArr[i]=employeesRoot[i]->data->getEmployee()->getEmployeeID();
                            
                            Employees=employeesArr;


                            return SUCCESS;
                
                }        

                 catch (std::bad_alloc&) {
                return ALLOCATION_ERROR;
            }                


    }

    StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees){
        if(DS==NULL||NumOfCompanies==0||Employees==NULL||NumOfCompanies==0)
                    return INVALID_INPUT;        

     EmployeeManager* emanager = (EmployeeManager*) DS;

    try{
        
        Node<Company*>** companiesReverseArr= new Node<Company*>*();
       if(emanager->companies->getRoot()==NULL)
            {
                free(companiesReverseArr);
                return FAILURE;
            }

        
        companiesReverseArr = (Node<Company*>**)emanager->companies->ReverseInOrder(emanager->companies->getRoot());
        
        int n = companies->getSize(companies->root); 
        int empty=0;
        int j=0;
        int* EmployeesArr = (int*)malloc(sizeof(int)*n);
        for(int i = 0; i<n; i++)
        {
            if(companiesReverseArr[i]->data->getNumEmployees()>0)
            {
                EmployeesArr[j] = companiesReverseArr[i]->data->getHighestEarner();
                j++;
            }   
            else empty++;
        }
        int temp;
        int* gEmployees = (int*)malloc(sizeof(int)*(j));
        for(int i =j-1; i>=0; i--)
        {
            temp = EmployeesArr[i]; 
            gEmployees[j-1-i] = temp;
        }
        *Employees = gEmployees;
        free(EmployeesArr);
        return SUCCESS;
        

        }        
                 catch (std::bad_alloc&) {
                return ALLOCATION_ERROR;
            }               

    }

    StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees){
    if(DS==NULL||CompanyID==0||MinEmployeeID<0||MaxEmployeeId<0||MaxEmployeeId<MinEmployeeID||MinSalary<0||MinGrade<0||TotalNumOfEmployees==NULL||NumOfEmployees==NULL)
                return INVALID_INPUT;   

    EmployeeManager* emanager = (EmployeeManager*) DS;

    try{
        int totalNumOfEm=0;
        int numOfEm=0;
         if(CompanyID>0)
            {
            Company* tempCompany = new Company(CompanyID,1);//the value (1) doesn't matter, we only want to see if there is a company with the same ID.
            Company* targetCompany = new Company(1,1);
            if(emanager->companies->findNode(emanager->companies->root,tempCompany) == NULL ||emanager->employees->getRoot())
                return FAILURE;
            targetCompany = emanager->companies->findNode(emanager->companies->root,tempCompany)->data;
            if(targetCompany->getNumEmployees()==0)
            return FAILURE;

             Node<KeyBySalary*>** employeesRoot= (Node<KeyBySalary*>**)targetCompany->getEmployeesSalaryKey()->ReverseInOrder(targetCompany->getEmployeesSalaryKey()->getRoot());
            int** employeesArr = (int**) malloc(sizeof(int*)*targetCompany->getNumEmployees());
            for(int i=0; i<targetCompany->getNumEmployees()-1; i++)
                {
                    if(employeesRoot[i]->data->getEmployee()->getEmployeeID()<=MaxEmployeeId && employeesRoot[i]->data->getEmployee()->getEmployeeID() >=MinEmployeeID)
                        {
                        *employeesArr[totalNumOfEm]=employeesRoot[i]->data->getEmployee()->getEmployeeID();
                        totalNumOfEm++;
                        }
                 }
            
            for(int i=0; i<totalNumOfEm; i++)
                {
                    if(*employeesArr[i] >= MinSalary &&  *employeesArr[i] <= MinGrade )
                        numOfEm++;
                }
            
            *TotalNumOfEmployees = totalNumOfEm;
            *NumOfEmployees = numOfEm;
            return SUCCESS;

            }

            if(emanager->getNumOfEmployee()==0)
                return FAILURE;
            
            Node<KeyBySalary*>** employeesRoot = (Node<KeyBySalary*>**)emanager->employees->ReverseInOrder(emanager->employees->getRoot());
            int** employeesArr = (int**) malloc(sizeof(int*)*emanager->getNumOfEmployee());
            for(int i=0; i<emanager->getNumOfEmployee()-1; i++)
                {
                    if(employeesRoot[i]->data->getEmployee()->getEmployeeID()<=MaxEmployeeId && employeesRoot[i]->data->getEmployee()->getEmployeeID() >=MinEmployeeID)
                        {
                        *employeesArr[totalNumOfEm]=employeesRoot[i]->data->getEmployee()->getEmployeeID();
                        totalNumOfEm++;
                        }
                 }
            
            for(int i=0; i<totalNumOfEm; i++)
                {
                    if(*employeesArr[i] >= MinSalary &&  *employeesArr[i] <= MinGrade )
                        numOfEm++;
                }
            
            *TotalNumOfEmployees = totalNumOfEm;
            *NumOfEmployees = numOfEm;
            return SUCCESS;

    }

    catch (std::bad_alloc&) {
                return ALLOCATION_ERROR;
            }                



    }

    void Quit(void **DS){
         
         if(DS==NULL)
            return;
        EmployeeManager* emanager = (EmployeeManager*) *DS;
          free(emanager);
    }


};

#endif

