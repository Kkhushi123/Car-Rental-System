#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <bits/stdc++.h>

using namespace std;
// Craeted a date structure.
struct date
{
    int d, m, y;
    void printdate()
    {
        cout << d << "/" << m << "/" << y << endl;
    }
};

const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const int MAX_VALID_YR = 9999;
const int MIN_VALID_YR = 1800;

// Returns true if
// given year is valid.
bool isLeap(int year)
{
    // Return true if year
    // is a multiple of 4 and
    // not multiple of 100.
    // OR year is multiple of 400.
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}

// Returns true if given
// year is valid or not.
bool isValidDate(int d, int m, int y)
{
    // If year, month and day
    // are not in given range
    if (y > MAX_VALID_YR ||
        y < MIN_VALID_YR)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;

    // Handle February month
    // with leap year
    if (m == 2)
    {
        if (isLeap(y))
            return (d <= 29);
        else
            return (d <= 28);
    }

    // Months of April, June,
    // Sept and Nov must have
    // number of days less than
    // or equal to 30.
    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
        return (d <= 30);

    return true;
}

int countLeapYears(date d)
{
    int ye = d.y;

    if (d.m <= 2)
        ye--;

    return ye / 4 - ye / 100 + ye / 400;
}

// Function to find difference between two dates.
int getDifference(date dt1, date dt2)
{

    long int n1 = dt1.y * 365 + dt1.d;

    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];

    n1 += countLeapYears(dt1);
    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    return (n2 - n1);
}

int offsetDays(int d, int m, int y)
{
    int offset = d;

    switch (m - 1)
    {
    case 11:
        offset += 30;
    case 10:
        offset += 31;
    case 9:
        offset += 30;
    case 8:
        offset += 31;
    case 7:
        offset += 31;
    case 6:
        offset += 30;
    case 5:
        offset += 31;
    case 4:
        offset += 30;
    case 3:
        offset += 31;
    case 2:
        offset += 28;
    case 1:
        offset += 31;
    }

    if (isLeap(y) && m > 2)
        offset += 1;

    return offset;
}

// Given a year and days elapsed in it, finds
// date by storing results in d and m.
void revoffsetDays(int offset, int y, int *d, int *m)
{
    int month[13] = {0, 31, 28, 31, 30, 31, 30,
                     31, 31, 30, 31, 30, 31};

    if (isLeap(y))
        month[2] = 29;

    int i;
    for (i = 1; i <= 12; i++)
    {
        if (offset <= month[i])
            break;
        offset = offset - month[i];
    }

    *d = offset;
    *m = i;
}

// Function to Add x days to the given date.
date addDays(int d1, int m1, int y1, int x)
{
    int offset1 = offsetDays(d1, m1, y1);
    int remDays = isLeap(y1) ? (366 - offset1) : (365 - offset1);

    // y2 is going to store result year and
    // offset2 is going to store offset days
    // in result year.
    int y2, offset2;
    if (x <= remDays)
    {
        y2 = y1;
        offset2 = offset1 + x;
    }

    else
    {
        // x may store thousands of days.
        // We find correct year and offset
        // in the year.
        x -= remDays;
        y2 = y1 + 1;
        int y2days = isLeap(y2) ? 366 : 365;
        while (x >= y2days)
        {
            x -= y2days;
            y2++;
            y2days = isLeap(y2) ? 366 : 365;
        }
        offset2 = x;
    }

    // Find values of day and month from
    // offset of result year.
    int m2, d2;
    revoffsetDays(offset2, y2, &d2, &m2);

    // cout << "d2 = " << d2 << ", m2 = " << m2
    //      << ", y2 = " << y2;
    return {d2, m2, y2};
}

class Car;

// CReated a map which stores id as key and vector of car details like(condition,availibility,rental price) as its value
map<int, vector<int>> AllCarList;

//created a vector pair of pairs which stores details of customer and employees in the format ({{unique id,name},{password,record}}).
vector<pair<pair<int, string>, pair<string, int>>> Cus_list;
vector<pair<pair<int, string>, pair<string, int>>> Emp_list;

// created a map which stores car's id as key and customer/employee'id as value . I ahve created this to know that which car is rented to whicch customer/employee.
map<int, int> car_rented_to_cust;
map<int, int> car_rented_to_emp;

// stores the id of the cars which are available in the store
vector<int> AvailableCars;

// Created a Class Car
class Car
{
protected:
    int model;
    int condition;
    int availability;
    int rentalPrice;

public:
    // Decleration of customer Constructor
    Car() {}
    Car(int model, int condition, int available, int rentalPrice)
    {
        this->model = model;
        this->condition = condition;
        this->availability = available;
        this->rentalPrice = rentalPrice;
    }
    // Decleratin of Destructor
     ~Car(){};
};

class Person
{
protected:
    int id;
    string name;
    string password;
    vector<int> rented_Car;

public:

    // Created some Virtual functions which I have defined in  inherited Customer and Employee class from the Person class

    // Function to print all available cars in the store
    virtual void print_available_cars() = 0;

    // Function to print dues of Customer/Employee
    virtual int print_dues()=0;

    // Function to clear dues of Customer/Employee
    virtual void clear_dues(){return;};

    // Function which rents a car to Customer/Employee 
    virtual void rentcar(){return;};

    // Function to print rented cars of a customer/EMployee
    virtual void print_rented_cars()=0;

    // Function to check return dates of a car rented by a Customer/Employee.
    virtual bool check_return_dates(){return false;};

    // Function which checks if a car is rented to that Customer/Employee
    virtual bool check_rented_car(){return false;};

    // Function to return a car rented by a Customer/Employee
    virtual void car_return(){return;};

    // Function to print due dates of retunr of a car rented by a Customer/Employee
    virtual void print_due_dates()=0;
};

// Declared these class here but defined them later.
class Customer;
class Employee;
class Manager;

// Created a map which stores car id as key and the car object as the value.
map<int, Car> CarList;

// Created a map which stores Customer id as key and the Customer object as the value.
map<int, Customer> CustomerList;

// Created a map which stores employee id as key and the Employee object as the value.
map<int, Employee> EmployeeList;

// Created a map which stores Manager id as key and the Manager object as the value.
map<int, Manager> ManagerList;


class Customer : public Person
{
protected:
    int Customer_record;
    vector<pair<int, pair<date, date>>> customer_rented_cars; 
    // will store model id of rented cars by the customer
    // first date-> rented date, second date-> due date

    //stores the id as key and dues as value
    map<int, int> cust_dues;
    int fine = 1; //fine of Rs.1/day will be imposed after due date of car return

public:
    vector<int> Cust_ids;
    // Customer Constructor
    Customer() {}
    Customer(int Customer_id, string Customer_name, string Customer_password, int Customer_record)
    {
        this->id = Customer_id;
        this->name = Customer_name;
        this->password = Customer_password;
        this->Customer_record = Customer_record;
        Cust_ids.push_back(Customer_id);
    }
    // Customer Destructor
    ~Customer(){};

    // customer can see their record 
    void GetCust_record()
    {
        if (CustomerList.find(id) != CustomerList.end())
        {
            cout << "Customer record: " << CustomerList[id].Customer_record << endl;
        }
    }

    // customer can see their dues if any
    int print_dues()
    {
        if (cust_dues.size() == 0)
        {
            cout << "No Dues Pending!! Relax :)\n" << endl;
            return 0;
        }
        else
        {
            for (auto it : cust_dues)
            {
                cout << "Car model is: " << it.first << endl
                     << "dues Pending: " << it.second << endl;
                cout << endl;
            }
            return 1;
        }
    }

    // customer can clear their dues if any
    void clear_dues(int ModelName)
    {
        if (cust_dues.find(ModelName) != cust_dues.end())
        {
            cout << "dues Successfully cleared" << endl;
            cust_dues.erase(ModelName);
        }
        else
        {
            cout << "You have no dues of this model of the car" << endl;
        }
    }

    
    // customer can rent a car
    void rentcar(int id, int model, date rentdate)
    {
        int i, flag = 0;
        if (Customer_record > customer_rented_cars.size())
        {

            for (i = 0; i < AvailableCars.size(); i++)
            {

                if (AvailableCars[i] == model)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag && AllCarList[model][1] != 0)
            {
                AvailableCars.erase(AvailableCars.begin() + i);
                rented_Car.push_back(model);
                customer_rented_cars.push_back({model, {rentdate, addDays(rentdate.d, rentdate.m, rentdate.y, 15)}});
                AllCarList[model][1] = 0;
                car_rented_to_cust[model] = id;
                cout << "Successfully rented :)\n You have to return the car after 15 days\n";
                cout << "If not, you will have to pay a fine of Rs 1 per day after the due date. If the condition of the car deteriorates, then your record will get worse, once it becomes 0 then you'll not be able to rent a car further\n";

                cout << "Your current record is:\n";
                GetCust_record();
            }

            else
                cout << "Sorry! We don't have car of this model available at present.\n";
        }
        else
            cerr << "You have already reached max limit of cars to be rented by your ID.\n";
    }

    // prints rented car of a customer
    void print_rented_cars()
    {
        for (auto it : customer_rented_cars)
        {
            vector<int> temp_car = AllCarList[it.first];

            cout << "Model name: " << it.first << ", Condition: " << temp_car[0] << ", Rent price: " << temp_car[2] << endl;
        }

        if (customer_rented_cars.size() == 0)
            cout << "You do not have any rented cars\n";
    }

    // prints due dates of rented cars of a customer if any
    void print_due_dates()
    {
        for (auto it : customer_rented_cars)
        {
            cout << "Model name: " << it.first << endl
                 << "Booking date: " << it.second.first.d << "/" << it.second.first.m << "/" << it.second.first.y << endl;
            cout << "Due date: " << it.second.second.d << "/" << it.second.second.m << "/" << it.second.second.y << endl;
        }

        if (customer_rented_cars.size() == 0)
            cout << "You do not have any rented cars\n";
    }

    // checking if a car is rented to the customer
    bool check_rented_car(int ModelName)
    {
        for (int i = 0; i < rented_Car.size(); i++)
        {
            if (rented_Car[i] == ModelName)
            {
                return true;
            }
        }
        return false;
    }

    // checks return date
    bool check_return_date(int modelId, date return_date)
    {
        int i;

        for (i = 0; i < customer_rented_cars.size(); i++)
        {
            if (customer_rented_cars[i].first == modelId)
            {
                break;
            }
        }
        if (getDifference(customer_rented_cars[i].second.first, return_date) < 0)
        {
            return false;
        }
        return true;
    }


    // implements returning of a car by a customer
    void car_return(int ModelName, int cond, date return_date)
    {

        for (int i = 0; i < customer_rented_cars.size(); i++)
        {
            if (customer_rented_cars[i].first == ModelName)
            {
                AvailableCars.push_back(ModelName);

                AllCarList[ModelName][1] = 1;

                if (AllCarList[ModelName][0] > cond)
                {
                    Customer_record = Customer_record - 1;
                }

                AllCarList[ModelName][0] = cond;

                // No. of days after due time
                int days = getDifference(customer_rented_cars[i].second.second, return_date);

                // if the number of days are more than 0, it means he is returning the car after the due date, so a fine of Rs 1(here) per day is imposed for this no. of days
                if (days > 0)
                {
                    cust_dues[ModelName] = days * fine;
                    Customer_record = Customer_record - 1;
                }

                customer_rented_cars.erase(customer_rented_cars.begin() + i);
                for (int i = 0; i < rented_Car.size(); i++)
                {
                    if (rented_Car[i] == ModelName)
                    {
                        break;
                    }
                }
                rented_Car.erase(rented_Car.begin() + i);
              
            }
        }
    }

    // prints available cars in the store
    void print_available_cars()
    {
        for (auto it : AvailableCars)
        {
            vector<int> temp_car = AllCarList[it];
            if (AllCarList[it][1] != 0)
            {

                cout << "Model name: " << it << ", Condition: " << temp_car[0] << ", Rent price: " << temp_car[2] << endl;
            }
        }
    }
};

class Employee : public Person
{

protected:
    int Employee_record;
    double discount = 0.15;

    vector<pair<int, pair<date, date>>> employee_rented_cars; // will store model id of rented cars by the employee
    // first date-> rented date, second date-> due date

    map<int, int> emp_dues;
    int fine = 1;

public:
    vector<int> Emp_ids;

    Employee() {}
    Employee(int Employee_id, string Employee_name, string Employee_password, int Employee_record)
    {
        this->id = Employee_id;
        this->name = Employee_name;
        this->password = Employee_password;
        this->Employee_record = Employee_record;
        Emp_ids.push_back(Employee_id);
    }
    ~Employee(){};

    // Employee can see their record
    void GetEmp_record()
    {
        if (EmployeeList.find(id) != EmployeeList.end())
        {
            cout << "Employee record: " << EmployeeList[id].Employee_record << endl;
        }
    }


    // employee can see their dues if any
    int print_dues()
    {
        if (emp_dues.size() == 0)
        {
            cout << "No Dues Pending!! Relax :)" << endl;
            return 0;
        }
        else
        {
            for (auto it : emp_dues)
            {
                cout << "Car model is: " << it.first << endl
                     << "dues Pending: " << it.second << endl;
                cout << endl;
            }
            return 1;
        }
    }

 // employee can clear their dues if any
    void clear_dues(int ModelName)
    {
        if (emp_dues.find(ModelName) != emp_dues.end())
        {
            cout << "dues Successfully cleared" << endl;
            emp_dues.erase(ModelName);
        }
        else
        {
            cout << "You have no dues of this model of the car" << endl;
        }
    }

   // employee can rent a car
    void rentcar(int id, int model, date rentdate)
    {
        int i, flag = 0;
        if (Employee_record > employee_rented_cars.size())
        {

            for (i = 0; i < AvailableCars.size(); i++)
            {

                if (AvailableCars[i] == model)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag && AllCarList[model][1] != 0)
            {
                AvailableCars.erase(AvailableCars.begin() + i);
                rented_Car.push_back(model);
                employee_rented_cars.push_back({model, {rentdate, addDays(rentdate.d, rentdate.m, rentdate.y, 15)}});
                AllCarList[model][1] = 0;
                car_rented_to_emp[model] = id;
                cout << "Successfully rented :)\n You have to return the car after 15 days\n";
                cout << "If not, you will have to pay a fine of Rs 1 per day after the due date. If the condition of the car deteriorates, then your record will get worse, once it becomes 0 then you'll not be able to rent a car further\n";

                cout << "Your current record is:\n";
                GetEmp_record();
            }

            else
                cout << "Sorry! We don't have car of this model available at present.\n";
        }
        else
            cerr << "You have already reached max limit of cars to be rented by your ID.\n";
    }


     // prints rented car of a employee
    void print_rented_cars()
    {
        for (auto it : employee_rented_cars)
        {
            vector<int> temp_car = AllCarList[it.first];

            cout << "Model name: " << it.first << ", Condition: " << temp_car[0] << ", Rent price: " << temp_car[2] << endl;
        }

        if (employee_rented_cars.size() == 0)
            cout << "You do not have any rented cars\n";
    }

     // prints due dates of rented cars of a employee if any
    void print_due_dates()
    {
        for (auto it : employee_rented_cars)
        {
            cout << "Model name: " << it.first << endl
                 << "Booking date: " << it.second.first.d << "/" << it.second.first.m << "/" << it.second.first.y << endl;
            cout << "Due date: " << it.second.second.d << "/" << it.second.second.m << "/" << it.second.second.y << endl;
        }

        if (employee_rented_cars.size() == 0)
            cerr << "You do not have any rented cars\n";
    }


    // checking if a car is rented to the employee
    bool check_rented_car(int ModelName)
    {
        for (int i = 0; i < rented_Car.size(); i++)
        {
            if (rented_Car[i] == ModelName)
            {
                return true;
            }
        }
        return false;
    }

    // checks return date
    bool check_return_date(int modelId, date return_date)
    {
        int i;

        for (i = 0; i < employee_rented_cars.size(); i++)
        {
            if (employee_rented_cars[i].first == modelId)
            {
                break;
            }
        }
        if (getDifference(employee_rented_cars[i].second.first, return_date) < 0)
        {
            return false;
        }
        return true;
    }


     // implements returning of a car by a employee
    void car_return(int ModelName, int cond, date return_date)
    {

        for (int i = 0; i < employee_rented_cars.size(); i++)
        {
            if (employee_rented_cars[i].first == ModelName)
            {
                AvailableCars.push_back(ModelName);

                AllCarList[ModelName][1] = 1;

                if (AllCarList[ModelName][0] > cond)
                {
                    Employee_record = Employee_record - 1;
                }

                AllCarList[ModelName][0] = cond;

                // No. of days after due time
                int days = getDifference(employee_rented_cars[i].second.second, return_date);

                // if the number of days are more than 0, it means he is returning the car after the due date, so a fine of Rs 1(here) per day is imposed for this no. of days
                
                if (days > 0)
                {
                    emp_dues[ModelName] = days * fine;
                    Employee_record = Employee_record - 1;
                }

                employee_rented_cars.erase(employee_rented_cars.begin() + i);
                for (int i = 0; i < rented_Car.size(); i++)
                {
                    if (rented_Car[i] == ModelName)
                    {
                        break;
                    }
                }
                rented_Car.erase(rented_Car.begin() + i);
              
            }
        }
    }

     // prints available cars in the store
    void print_available_cars()
    {
        for (auto it : AvailableCars)
        {

            vector<int> temp_car = AllCarList[it];
            if (AllCarList[it][1] != 0)
            {
                cout << "Model name: " << it << ", Condition: " << temp_car[0] << ", Rent price: " << (temp_car[2] * (1 - discount)) << endl;
            }
        }
    }
};

class Manager
{
private:
    int Manager_id;
    string Manager_name;
    string Manager_password;

public:
    vector<int> Manager_ids;
    // Manager constructor
    Manager() {}
    Manager(int Manager_id, string Manager_name, string Manager_password)
    {
        this->Manager_id = Manager_id;
        this->Manager_name = Manager_name;
        this->Manager_password = Manager_password;
        Manager_ids.push_back(Manager_id);
    }
    // Manager Destructor
    ~Manager(){};

    // To add new car to the car database
    void AddNewCar(int ModelName, int condition, int availability, int rentalprice)
    {
        // /we are keeping the model numbers of the cars unique, so if manager tries to add a car with already present model we will notify him.

        if (CarList.find(ModelName) == CarList.end())
        {
            cout << "Car Successfully added" << endl;
            AllCarList[ModelName] = {condition, availability, rentalprice};
            AvailableCars.push_back(ModelName);
            Car obj(ModelName, condition, availability, rentalprice);
            CarList[ModelName] = obj;
        }

        else
        {
            cout << "Car with this model is already present in the database" << endl;
        }

    }

    // To update old car's details
    void UpdateOldCar(int ModelName, int updated_cond, int updated_aval, int updated_rentprice)
    {
        // deleting current customer with the id ModelName
        CarList.erase(ModelName);

        // Creating a new customer object with th eupdated details and now entering it into the database
        Car obj(ModelName, updated_cond, updated_aval, updated_rentprice);
        CarList[ModelName] = obj;

        AllCarList.erase(ModelName);
        AllCarList[ModelName] = {updated_cond, updated_aval, updated_rentprice};
        cout << "Successfully Updated!!" << endl;
    }

    // To delete a car from the database
    void DeleteCar(int ModelName)
    {
        int i = 0;

        AllCarList.erase(ModelName);
        for (i = 0; i < AvailableCars.size(); i++)
        {
            if (AvailableCars[i] == ModelName)
            {
                break;
            }
        }
        AvailableCars.erase(AvailableCars.begin() + i);
        CarList.erase(ModelName);
        cout << "Successfully deleted" << endl;
    }

    // To find a car by its id in the database
    int FindCar(int ModelName)
    {
        if (AllCarList.find(ModelName) != AllCarList.end())
        {
            cout << "The model name is " << ModelName << ", the condition of this car is " << AllCarList[ModelName][0] << ", the availability of this car is " << AllCarList[ModelName][1] << " and the rental price of this car is " << AllCarList[ModelName][2] << endl;
            cout<<endl;
            return 1;
        }
        // if car with that car id is not present in the database
        else
        {
            cerr << "Car not found!!" << endl;
            cout<<endl;
            return 0;
        }
    }

    // To add new employee to the database
    void add_employee(int id, string name, string password, int record)
    {
        
        if (EmployeeList.find(id) == EmployeeList.end())
        {

            cout << "Employee Successfully added" << endl;

            // creating new employee object
            Employee obj(id, name, password, record);
            EmployeeList[id] = obj;
            Emp_list.push_back({{id, name}, {password, record}});
        }
        else
        {
            cout << "This employee is already present in the database" << endl;
        }
    }


    // To add new customer to the database
    void add_customer(int id, string name, string password, int record)
    {
        if (CustomerList.find(id) == CustomerList.end())
        {

            cout << "Customer Successfully added" << endl;

            // creating new customer object
            Customer obj(id, name, password, record);
            CustomerList[id] = obj;
            Cus_list.push_back({{id, name}, {password, record}});
        }
        // if customer is already present with the given id
        else
        {
            cout << "This customer is already present in the database" << endl;
        }
    }

    // to update details of an existing customer
    void update_customer(int id, string name, string password, int record)
    {

        cout << "Successfully Updated!!" << endl;

        for (int i = 0; i < Cus_list.size(); i++)
        {
            if (id == Cus_list[i].first.first)
            {
                Cus_list[i].first.second = name;
                Cus_list[i].second.first = password;
                Cus_list[i].second.second = record;
            }
        }
    }

    // To update details of an existing employee
    void update_employee(int id, string name, string password, int record)
    {

        cout << "Successfully Updated!!" << endl;

        for (int i = 0; i < Emp_list.size(); i++)
        {
            if (id == Emp_list[i].first.first)
            {
                Emp_list[i].first.second = name;
                Emp_list[i].second.first = password;
                Emp_list[i].second.second = record;
            }
        }
    }

    // delete an existing customer with customer id: id
    void delete_customer(int id)
    {

        int i;
        cout << "Customer deleted Successfully!!" << endl;
        for (i = 0; i < Cus_list.size(); i++)
        {
            if (id == Cus_list[i].first.first)
            {
                break;
            }
        }
        Cus_list.erase(Cus_list.begin() + i);
        CustomerList.erase(id);
    }

    // delete an existing employee with employee id: id
    void delete_employee(int id)
    {

        int i;

        cout << "Employee deleted Successfully!!" << endl;
        for (i = 0; i < Emp_list.size(); i++)
        {
            if (id == Emp_list[i].first.first)
            {
                break;
            }
        }
        Emp_list.erase(Emp_list.begin() + i);
        EmployeeList.erase(id);
    }

    // to print those car which are rented to customers
    void print_rented_cars_to_cust()
    {
        for (auto it : car_rented_to_cust)
        {
            cout << "Car model is: " << it.first << " which is rented to Customer with Customer id: " << it.second << endl;
        }
        // if no cars are rented to any customer
        if (car_rented_to_cust.size() == 0)
        {
            cout << "No cars are currently rented to customers" << endl;
        }
    }

    // to print those car which are rented to employee
    void print_rented_cars_to_emp()
    {
        for (auto it : car_rented_to_emp)
        {
            cout << "Car model is: " << it.first << " which is rented to Employee with Employee id: " << it.second << endl;
        }
        // if no cars are rented to any employee
        if (car_rented_to_emp.size() == 0)
        {
            cout << "No cars are currently rented to employees" << endl;
        }
    }
};
// prints all available cars when manager asks to print all available cars. It has taken care of avaibility also.
void print_available_cars_manager()
{
    for (auto it : AvailableCars)
    {
        vector<int> temp_car = AllCarList[it];
        if (AllCarList[it][1] != 0)
        {

            cout << "Model name: " << it << ", Condition: " << temp_car[0] << ", Rent price: " << temp_car[2] << endl;
        }
    }
}

int main()
{
    /* Have created 5 car objects with availibility as true(1) initially and the rental price
    is also initialised as{100,200,300,400,500}. The condition of the car is taken as a
    int which can be good(3), average(2), bad(1). */

// Car obj(id,condition,avaibility,price)
    Car car1(1, 3, 1, 100);
    AllCarList[1] = {3, 1, 100};
    AvailableCars.push_back(1);
    CarList[1] = car1;

    Car car2(2, 3, 1, 200);
    AllCarList[2] = {3, 1, 200};
    AvailableCars.push_back(2);
    CarList[1] = car2;

    Car car3(3, 3, 1, 300);
    AllCarList[3] = {3, 1, 300};
    AvailableCars.push_back(3);
    CarList[1] = car3;

    Car car4(4, 3, 1, 400);
    AllCarList[4] = {3, 1, 400};
    AvailableCars.push_back(4);
    CarList[1] = car4;

    Car car5(5, 3, 1, 500);
    AllCarList[5] = {3, 1, 500};
    AvailableCars.push_back(5);
    CarList[1] = car5;

    /* Have created 5 customer objects initialised with customer_id as {1,2,3,4,5}, their
    respective name, their password and their customer_record which is initialised as 3
    which is best. */

    
 // Customer obj(id,name,password,record)


    Customer Cust1(1, "Kshitiz", "Cust1_password", 3);
    CustomerList[1] = Cust1;
    Cus_list.push_back({{1, "Kshitiz"}, {"Cust1_password", 3}});
    Customer Cust2(2, "Khushi", "Cust2_password", 3);
    CustomerList[2] = Cust2;
    Cus_list.push_back({{2, "Khushi"}, {"Cust2_password", 3}});
    Customer Cust3(3, "Saksham", "Cust3_password", 3);
    CustomerList[3] = Cust3;
    Cus_list.push_back({{3, "Saksham"}, {"Cust3_password", 3}});
    Customer Cust4(4, "Mayankit", "Cust4_password", 3);
    CustomerList[4] = Cust4;
    Cus_list.push_back({{4, "Mayankit"}, {"Cust4_password", 3}});
    Customer Cust5(5, "Anuraag", "Cust5_password", 3);
    CustomerList[5] = Cust5;
    Cus_list.push_back({{5, "Anuraag"}, {"Cust5_password", 3}});

    /* Have created 5 Employee objects initialised with Employee_id as {1,2,3,4,5}, their
    respective name, their password and their Employee_record which is initialised as 3
    which is best. */

    
 // Employee obj(id,name,password,record)

    Employee Emp1(1, "Apple", "Emp1_password", 3);
    EmployeeList[1] = Emp1;
    Emp_list.push_back({{1, "Apple"}, {"Emp1_password", 3}});
    Employee Emp2(2, "Mango", "Emp2_password", 3);
    EmployeeList[2] = Emp2;
    Emp_list.push_back({{2, "Mango"}, {"Emp2_password", 3}});
    Employee Emp3(3, "Banana", "Emp3_password", 3);
    EmployeeList[3] = Emp3;
    Emp_list.push_back({{3, "Banana"}, {"Emp3_password", 3}});
    Employee Emp4(4, "Grapes", "Emp4_password", 3);
    EmployeeList[4] = Emp4;
    Emp_list.push_back({{4, "Grapes"}, {"Emp4_password", 3}});
    Employee Emp5(5, "Watermelon", "Emp5_password", 3);
    EmployeeList[5] = Emp5;
    Emp_list.push_back({{5, "Watermelon"}, {"Emp5_password", 3}});

//  Managwr object created
// Manager object(id,name,password)
    Manager manager1(1, "king", "manager_password");
    ManagerList[1] = manager1;

    int y = 1;

    // Functioning Starts

    cout << "Welcome to our Car Rental Company!!" << endl;
    // an infinite loop for the program functioning
    while (y == 1)
    {
        cout << "Type 1 if you are a customer, Type 2 if you are an employee, Type 3 if you are the manager and Type 0 if you want to exit" << endl;
        int type, custID;
        cin >> type;
        int x = 0;
        // type==1 for customer
        if (type == 1)
        {
            cout << "Enter your customer ID. It should be an integer.\n";
            cin >> custID;
            if (CustomerList.find(custID) == CustomerList.end())
            {
                cerr << "You are not a customer. Please contact our manager.\n";
                break;
            }

            else
            {
                while (x != 1)
                {
                            // options for customers
                    cout << "Do you want to see all available cars in our store for rent? if Yes type 1" << endl;
                    cout << "Do you want to rent a car? if Yes type 2" << endl;
                    cout << "Do you want to see your rented cars? if Yes type 3" << endl;
                    cout << "Do you want to see due dates of all the cars that you have rented? if Yes type 4" << endl;
                    cout << "Do you want to return a car? if Yes type 5" << endl;
                    cout << "Do you want to see/clear dues? if Yes type 6" << endl;
                    cout << "Do you want to go to the Home Page? if Yes type 7" << endl;

                    int option1;
                    cin >> option1;

                    if (option1 == 1)
                    {
                        // print_available_cars();
                        CustomerList[custID].print_available_cars();

                        x = 0;
                        cout << endl;
                        continue;
                    }

                    else if (option1 == 2)
                    {
                        cout << "We have following available cars:\n";
                        // print_available_cars();
                        CustomerList[custID].print_available_cars();
                        cout << "Which model do you want to rent? Type the model name from above list..e.g.1, or 2\n";

                        int model_in, day, month, year;
                        cin >> model_in;

                        cout << "Rent date(format-(dd mm yyyy)): " << endl;
                        cin >> day >> month >> year;
                        // checking valid date 
                        while (!isValidDate(day, month, year))
                        {

                            cerr << "Not a valid date!! " << endl;

                            cerr << "Enter a valid date(format-(dd mm yyyy)): " << endl;
                            cin >> day >> month >> year;
                        }

                        CustomerList[custID].rentcar(custID, model_in, {day, month, year});
                        cout << endl;
 
                        continue;
                    }

                    else if (option1 == 3)
                    {
                        // printing rented car by this customer
                        CustomerList[custID].print_rented_cars();
                        cout << endl;
                        continue;
                    }

                    else if (option1 == 4)
                    {
                        // printing due dates of th erented cars
                        CustomerList[custID].print_due_dates();
                        cout << endl;
                        continue;
                    }
                    else if (option1 == 5)
                    {

                        int y = 0;
                        int day, month, year, con;
                        int return_car_model;

                        while (y != 1)
                        {
                            cout << "Which car do you want to return? Enter the car's model id: " << endl;
                            cin >> return_car_model;
                            // checking if this is actually rented or not
                            if ((CustomerList[custID].check_rented_car(return_car_model)))
                            {

                                cout << "Return date(format-(dd mm yyyy)): " << endl;
                                cin >> day >> month >> year;
                                // Checking valid date
                                while (!isValidDate(day, month, year))
                                {
                                    cerr << "Not a valid date" << endl;

                                    cerr << "Enter a valid Return date(format-(dd mm yyyy)): " << endl;
                                    cin >> day >> month >> year;
                                }
                                // checking return date correctness
                                while (!CustomerList[custID].check_return_date(return_car_model, {day, month, year}))
                                {

                                    cerr << "Invalid return date. Return date should be after booking date.Enter a valid return date" << endl;
                                    cout << "Return date(format-(dd mm yyyy)): " << endl;
                                    cin >> day >> month >> year;
                                }

                                cout << "The car condition when you rented the car was: " << AllCarList[return_car_model][0] << endl
                                     << "Enter current condition of the car honestly(scale- 1 to 3, where 3 is the best and your input should be less than or equal to the previous car condition): " << endl;

                                cin >> con;
                                // checking condition of the car before and after the return
                                while (con > AllCarList[return_car_model][0] && con < 1)
                                {
                                    cerr << "Enter a valid input as mentioned above\n";
                                    cin >> con;
                                }

                                CustomerList[custID].car_return(return_car_model, con, {day, month, year});
                                y = 1;
                                cout << "the car has been successfully returned!!" << endl;

                                car_rented_to_cust.erase(return_car_model);

                                cout << endl;
                                // continue;
                            }
                            else
                            {
                                cerr << "You have not rented this car\n"
                                     << endl;
                                break;
                            }
                        }
                    }
                    else if (option1 == 6)
                    {
                        // clearing dues and printing the dues
                        int input, carmodel;

                        cout << "Your dues are: " << endl;
                        cout << endl;
                        if (CustomerList[custID].print_dues() == 1)
                        {
                            // clearing dues
                            cout << "If you want to clear your dues right now type 1 else type 0 to return to main menu" << endl;
                            cin >> input;
                            if (input == 1)
                            {
                                cout << "Enter the Car model of which you want to clear dues: " << endl;
                                cin >> carmodel;
                                CustomerList[custID].clear_dues(carmodel);
                                continue;
                            }
                            // retunrning to the main mennu
                            else if (input == 0)
                            {
                                continue;
                            }

                            else
                            {
                                cerr << "Invalid Input!! Directing you to main menu" << endl;
                                continue;
                            }
                        }
                    }

                    else if (option1 == 7)
                    {
                        break;
                    }

                    else
                        cerr << "Invalid input!!\n";
                }
            }
        }
        else if (type == 2)
        {
            int empID;

            cout << "Enter your Employee ID. It should be an integer\n";
            cin >> empID;
            if (EmployeeList.find(empID) == EmployeeList.end())
            {
                cerr << "You are not an Employee. Please contact our manager.\n";
                break;
            }

            else
            {
                while (x != 1)
                {

                    cout << "Do you want to see all available cars in our store for rent? if Yes type 1" << endl;
                    cout << "Do you want to rent a car? if Yes type 2" << endl;
                    cout << "Do you want to see your rented cars? if Yes type 3" << endl;
                    cout << "Do you want to see due dates of all the cars that you have rented? if Yes type 4" << endl;
                    cout << "Do you want to return a car? if Yes type 5" << endl;
                    cout << "Do you want to see/clear dues? if Yes type 6" << endl;
                    cout << "Do you want to go to the Home Page? if Yes type 7" << endl;
                    // cout<<"Want to go to the Home Page Type 8"<<endl;

                    int option1;
                    cin >> option1;

                    if (option1 == 1)
                    {
                       
                        EmployeeList[empID].print_available_cars();

                        x = 0;
                        cout << endl;
                        continue;
                    }

                    else if (option1 == 2)
                    {
                        cout << "We have following available cars:\n";
                        EmployeeList[empID].print_available_cars();
                        
                        cout << "Which model do you want to rent? Type the model name from above list..e.g.1, or 2\n";

                        int model_in, day, month, year;
                        cin >> model_in;

                        cout << "Rent date(format-day(DD),month(MM),year(YYYY)): " << endl;
                        cin >> day >> month >> year;

                        while (!isValidDate(day, month, year))
                        {

                            cerr << "Not a valid date!! " << endl;

                            cerr << "Enter a valid date(format-(dd mm yyyy)): " << endl;
                            cin >> day >> month >> year;
                        }

                        EmployeeList[empID].rentcar(empID, model_in, {day, month, year});
                        cout << endl;

                        continue;
                    }

                    else if (option1 == 3)
                    {
                        EmployeeList[empID].print_rented_cars();
                        cout << endl;
                        continue;
                    }

                    else if (option1 == 4)
                    {
                        EmployeeList[empID].print_due_dates();
                        cout << endl;
                        continue;
                    }
                    else if (option1 == 5)
                    {
                        int y = 0;
                        int day, month, year, con;
                        int return_car_model;

                        while (y != 1)
                        {
                            cout << "Which car do you want to return? Enter the car's model id: " << endl;
                            cin >> return_car_model;
                            if ((EmployeeList[empID].check_rented_car(return_car_model)))
                            {

                                cout << "Return date(format-day(DD),month(MM),year(YYYY)): " << endl;
                                cin >> day >> month >> year;

                                while (!isValidDate(day, month, year))
                                {
                                    cerr << "Not a valid date" << endl;

                                    cerr << "Enter a valid Return date(format-(dd mm yyyy)): " << endl;
                                    cin >> day >> month >> year;
                                }

                                while (!EmployeeList[empID].check_return_date(return_car_model, {day, month, year}))
                                {
                                    cout << "Invalid return date. Return date should be after booking date" << endl;
                                    cout << "Return date(format-day(DD),month(MM),year(YYYY)): " << endl;
                                    cin >> day >> month >> year;
                                }

                                cout << "The car condition when you rented the car was: " << AllCarList[return_car_model][0] << endl
                                     << "Enter current condition of the car honestly(scale- 1 to 3, where 3 is the best and your input should be less than or equal to the previous car condition): " << endl;

                                cin >> con;
                                while (con > AllCarList[return_car_model][0] && con < 1)
                                {
                                    cerr << "Enter a valid input as mentioned above\n";
                                    cin >> con;
                                }

                                EmployeeList[empID].car_return(return_car_model, con, {day, month, year});
                                y = 1;
                                cout << "the car has been successfully returned!!" << endl;
                                cout << endl;

                                car_rented_to_emp.erase(return_car_model);

                                
                            }
                            else
                            {
                                cerr << "You have not rented this car\n"
                                     << endl;
                                break;
                            }
                        }
                    }
                    else if (option1 == 6)
                    {
                        int input, carmodel;

                        cout << "Your dues are: " << endl;
                        cout << endl;
                        if (EmployeeList[empID].print_dues() == 1)
                        {

                            cout << "If you want to clear your dues right now type 1 else type 0 to return to main menu" << endl;
                            cin >> input;
                            if (input == 1)
                            {
                                cout << "Enter the Car model of which you want to clear dues: " << endl;
                                cin >> carmodel;
                                EmployeeList[empID].clear_dues(carmodel);
                                continue;
                            }
                            else if (input == 0)
                            {
                                continue;
                            }

                            else
                            {
                                cerr << "Invalid Input!! Directing you to main menu" << endl;
                                continue;
                            }
                        }
                    }

                    else if (option1 == 7)
                    {
                        // x = 1;
                        // continue;
                        break;
                    }

                    else{
                        cerr << "Invalid input!!\n";
                        break;
                    }
                }
            }
        }
        else if (type == 3)
        {
            int Manager_id;
            // int option1;
            int x = 0;
            cout << "Enter your unique id" << endl;
            cin >> Manager_id;
            // checking manager id in the database
            if (ManagerList.find(Manager_id) == ManagerList.end())
            {
                cerr << "You are not a Manager. Please contact our manager.\n";
                break;
            }
            else
            {
                while (x == 0)
                {
                    int option1;
                    // options for a manager to do
                    cout << "Do you want to add a car to the store, if Yes type 1" << endl;
                    cout << "Do you want to update details of a existing car, if Yes type 2" << endl;
                    cout << "Do you want to delete a car form the store, if Yes type 3" << endl;
                    cout << "Do you want to add a Employee to the database, if Yes type 4" << endl;
                    cout << "Do you want to add a Customer to the database, if Yes type 5" << endl;
                    cout << "Do you want to update a customer's details in the database, if Yes type 6" << endl;
                    cout << "Do you want to update a employee's details in the database, if Yes type 7" << endl;
                    cout << "Do you want to delete a customer from the database, if Yes type 8" << endl;
                    cout << "Do you want to delete a employee from the database, if Yes type 9" << endl;
                    cout << "Do you want to see all the cars in the store, if Yes type 10" << endl;
                    cout << "Do you want to see all rented cars rented to the customers, if Yes type 11" << endl;
                    cout << "Do you want to see all rented cars rented to the employees, if Yes type 12" << endl;
                    cout << "Do you want to find a car, if Yes type 13" << endl;
                    cout << "Do you want to go to the Home Page Type 14" << endl;

                    cin >> option1;
                    int CarModel;
                    // add a car
                    if (option1 == 1)
                    {

                        cout << "Enter the Car model id: " << endl;
                        cin >> CarModel;
                        // checking if that car id is already present or not
                        if (AllCarList.find(CarModel) == AllCarList.end())
                        {
                            int newcond, newprice;
                            cout << "Enter New Car's condition (between 1 to 3) and the rental price you want to set: " << endl;
                            cin >> newcond >> newprice;
                        //    adding the car
                            ManagerList[Manager_id].AddNewCar(CarModel, newcond, 1, newprice);
                          
                        }
                        else
                        {
                            cerr << "Car already present" << endl;
                        }
                        
                    }
                    else if (option1 == 2)
                    {
                        // updating details of an existing car
                        int CarModel, newcond, newaval, newprice;
                        cout << "Enter existing car's model:" << endl;
                        cin >> CarModel;
                        // checking if the car is present or not
                        if (AllCarList.find(CarModel) == AllCarList.end())
                        {
                            cerr << "Car with model is not present!!" << endl;
                        }
                        else
                        {
                            cout << "Enter updated car condition (between 1 to 3), updated availibility, and updated rental price" << endl;
                            cin >> newcond >> newaval >> newprice;
                            // updating the car's details
                            ManagerList[Manager_id].UpdateOldCar(CarModel, newcond, newaval, newprice);
                        }
                    }
                    else if (option1 == 3)
                    {
                        // delete a car

                        int CarModel;
                        cout << "Enter car's model you want to delete:" << endl;
                        cin >> CarModel;

                        // checking if the car is present or not
                        if (AllCarList.find(CarModel) == AllCarList.end())
                        {
                            cerr << "Car with model is not present!!" << endl;
                        }
                        // deleting the car
                        else
                        {
                            ManagerList[Manager_id].DeleteCar(CarModel);
                           
                        }
                    }
                    else if (option1 == 4)
                    {
                        // add a employee
                        int emp_id, cusrecord;
                        string name, password;
                        cout << "Enter Employee's id: " << endl;
                        cin >> emp_id;
                        cout << "Enter Employee details" << endl
                             << "Enter Employee's Name: " << endl
                             << "Enter Employee's password: " << endl
                             << "Enter Employee's record: " << endl;
                        cin >> name >> password >> cusrecord;
                        // checking if the employee already exists or not and at same time adding it to the database if not present
                        ManagerList[Manager_id].add_employee(emp_id, name, password, cusrecord);
                    }

                    else if (option1 == 5)
                    {
                        // add a customer

                        int cust_id, cusrecord;
                        string name, password;
                        cout << "Enter Customer's id: " << endl;
                        cin >> cust_id;
                        cout << "Enter Customer details" << endl
                             << "Enter Customer's Name: " << endl
                             << "Enter Customer's password: " << endl
                             << "Enter Customer's record: " << endl;
                        cin >> name >> password >> cusrecord;
                        
                        // checking if the employee already exists or not and at same time adding it to the database if not present

                        ManagerList[Manager_id].add_customer(cust_id, name, password, cusrecord);
                    }
                    else if (option1 == 6)
                    {
                        // update a customer details
                        int cus_id, cusrecord;
                        string name, password;
                        cout << "Enter the customer's id of the customer whom you want to update the details" << endl;
                        cin >> cus_id;
                        // checking if that customer exists or not
                        if (CustomerList.find(cus_id) != CustomerList.end())
                        {

                            cout << "Enter Customer details" << endl
                                 << "Enter updated Customer's Name: " << endl
                                 << "Enter updated Customer's password: " << endl
                                 << "Enter updated Customer's record: " << endl;
                            cin >> name >> password >> cusrecord;
                            // updating the customer details
                            ManagerList[Manager_id].update_customer(cus_id, name, password, cusrecord);
                        }
                        else
                        {
                            cerr << "Customer with this is id is not in the database" << endl;
                        }
                    }
                    else if (option1 == 7)
                    {
                        // update a employee details
                        int emp_id, emprecord;
                        string name, password;
                        cout << "Enter the employee's id of the employee whom you want to update the details" << endl;
                        cin >> emp_id;
                        // checking if that employee exists or not
                        if (EmployeeList.find(emp_id) != EmployeeList.end())
                        {

                            cout << "Enter Employee details" << endl
                                 << "Enter updated Employee's Name: " << endl
                                 << "Enter updated Employee's password: " << endl
                                 << "Enter updated Employee's record: " << endl;
                            cin >> name >> password >> emprecord;
                            // updating the employee details
                            ManagerList[Manager_id].update_employee(emp_id, name, password, emprecord);
                        }
                        else
                        {
                            cerr << "Employee with this is id is not in the database" << endl;
                        }
                    }
                    else if (option1 == 8)
                    {
                        // delete a customer

                        int id;
                        cout << "Enter the customer's id of the customer whom you want to delete: " << endl;
                        cin >> id;
                        // checking if the customer is present or not in the database
                        if (CustomerList.find(id) != CustomerList.end())
                        {
                            // deleting the customer
                            ManagerList[Manager_id].delete_customer(id);
                        }
                        else
                        {
                            cerr << "Customer with this is id is not in the database" << endl;
                        }
                    }
                    else if (option1 == 9)
                    {
                        // delete a employee

                        int id;
                        cout << "Enter the employee's id of the employee whom you want to delete: " << endl;
                        cin >> id;

                        // checking if the employee is present or not in the database

                        if (EmployeeList.find(id) != EmployeeList.end())
                        {
                            // deleting the employee
                            ManagerList[Manager_id].delete_employee(id);
                        }
                        else
                        {
                            cerr << "Employee with this is id is not in the database" << endl;
                        }
                    }
                    else if (option1 == 10)
                    {
                        // printing all available cars in the store

                        print_available_cars_manager();

                        // x = 0;
                        cout << endl;
                        // continue;
                    }
                    else if (option1 == 11)
                    {
                        // printing rented cars to customers

                        ManagerList[Manager_id].print_rented_cars_to_cust();
                        cout << endl;
                    }
                    else if (option1 == 12)
                    {
                        // printing rented car to employees

                        ManagerList[Manager_id].print_rented_cars_to_emp();
                        cout << endl;
                    }

                    else if(option1==13){
                        // find a car
                        int carid;
                        cout<<"Enter the Car's model id"<<endl;
                        cin>>carid;
                        // checking if that presents or not
                        if(ManagerList[Manager_id].FindCar(carid)==0){
                            continue;
                        }
                        else{

                        }
                    }

                    else if (option1 == 14)
                    {
                        x = 1;
                        break;
                    }
                    else
                    {
                        cerr << "Invalid Input" << endl;
                        cout << endl;
                    }
                }
            }
        }

        else if (type == 0)
        {
            cout << "Thank You for Coming!! Have a great Day :)" << endl;
            y = 0;
            break;
        }

        else
        {
            cerr << "Invalid Input!!" << endl;
        }
    }
    return 0;
}