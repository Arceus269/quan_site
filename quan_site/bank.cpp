#include "cgi.h"
#include "../quan_site/utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Khai báo cấu trúc dữ liệu của mỗi khách hàng
struct Customer {
    string surname;
    string gender;
    int age;
    string workplace;
    double income;
    string purpose;
    Customer* prev, * next;
};

// A structure to represent a queue of elements
struct queue_t
{
    Customer* first = nullptr;
    Customer* last = nullptr;

};


void enqueue(queue_t& q, string first_name, string work_place, string gender, int age, double income, string purpose)
{
    auto* new_client = new Customer;
    new_client->surname = first_name;
    new_client->age = (age);
    new_client->workplace = (work_place);
    new_client->gender = (gender);
    new_client->purpose = (purpose);
    if (!q.first)
        q.first = q.last = new_client;
    else
    {
        q.last->next = new_client;
        new_client->prev = q.last;
        q.last = new_client;
    }
}



void clear(queue_t& q)
{
    Customer* curr = q.first;
    while (curr)
    {
        auto* temp = curr->next;
        delete curr;
        curr = temp;
    }
    q.first = q.last = nullptr;
}

bool dequeue(queue_t& q)
{
    if (!q.first) return false;

    Customer* temp = q.first;
    q.first = q.first->next;
    if (q.first)
        q.first->prev = nullptr;
    else
        q.last = nullptr;
    delete temp;
    return true;
}

// Hàm để chuyển đổi dữ liệu từ form sang cấu trúc dữ liệu khách hàng
/*/Customer parseFormData(char* data) {
    Customer customer;
    cgi_utils::get_param_value(data, "surname", customer.surname);
    cgi_utils::get_param_value(data, "gender", customer.gender);
    cgi_utils::get_param_value(data, "age", customer.age);
    cgi_utils::get_param_value(data, "workplace", customer.workplace);
    cgi_utils::get_param_value(data, "income", customer.income);
    cgi_utils::get_param_value(data, "purpose", customer.purpose);
    return customer;
}*/

// Hàm để ghi dữ liệu khách hàng vào tệp
void writeCustomerToFile(const Customer& customer, const string& filename) {
    ofstream file(filename, ios::app);
    if (file.is_open()) 
    {
        file << customer.surname << "\n"
             << customer.gender << "\n"
             << customer.age << "\n"
             << customer.workplace << "\n"
             << customer.income << "\n"
             << customer.purpose << endl;
        file.close();
    }
}

queue_t readCustomerFromFile(const string& filename)
{
    ifstream file(filename);
    if (file)
    {
        string name, age, gender, income, wkplace, purpose;
        queue_t _Customers;
        while (!file.eof())
        {
            getline(file, name);
            getline(file, gender);
            getline(file, age);
            getline(file, wkplace);
            getline(file, income);
            getline(file, purpose);

            double _income = stod(income);
            int _age = stoi(age);

            enqueue(_Customers, name, wkplace, gender, _age, _income, purpose);
        }
        file.close();
        return _Customers;
    }
}

void print_queue(queue_t q, const string& _c_purpose)
{
    for (auto* curr = q.first; curr != NULL; curr = curr->next)
    {
        if (curr->purpose == _c_purpose)
        {
            cout << "<div class=\"row\">";
            cout << "<div class=\"cell\" data-title=\"Full Name\">";
            cout << curr-> surname << "</div>";
            cout << "<div class=\"cell\" data-title=\"Sex\">";
            cout << curr->gender << "</div>";
            cout << "<div class=\"cell\" data-title=\"Age\">";
            cout << curr->age << "</div>";
            cout << "<div class=\"cell\" data-title=\"Location\">";
            cout << curr->workplace << "</div></div>";
            cout << "<div class=\"cell\" data-title=\"Salary\">";
            cout << curr->income << "</div>";
            cout << "<div class=\"cell\" data-title=\"Job Title\">";
            cout << curr->purpose << "</div>" << endl;
        }
    }
}

int main()
{
    // Set content type
    cout << "Content-type: text/html\n\n";

    ifstream file("bank.tmpl");

    if (file.is_open())
    {
        char* line = new char[1024];
        while (!file.eof())
        {
            file.getline(line, 1024);
            if (!strcmp(line, "<!--DATA-->"))
            {
                cout << "<form action=\"bank.cgi\"method=\"post\">";
                cout << "<label for=\"surname\">Surname:</label>";
                cout << "<input type =\"text\" id=\"surname\" name='surname' required><br>";

                cout << "<label for=\"gender\">Gender:</label>";
                cout << "<select name=\"gender\" title=\"gender-droplist\" required>";
                cout << "<option value=\"male\">Male</option>";
                cout << "<option value=\"female\">Female</option></select>";

                cout << "<label for=\"age\">Age:</label>";
                cout << "<input type =\"number\" id=\"age\" name='age' required><br>";

                cout << "<label for=\"workplace\">Workplace:</label>";
                cout << "<input type =\"text\" id=\"workplace\" name='workplace' required><br>";

                cout << "<label for=\"income\">Income:</label>";
                cout << "<input type=\"number\" id=\"purpose\" name='income' required><br>";

                cout << "<label for=\"purpose\"><p>Purpose</p></label>";
                cout << "<select name=\"purpose\" title=\"purpose-droplist\" required>";
                cout << "<option value=\"credit\">Credit</option>";
                cout << "<option value=\"debit\">Debit</option></select>";

                cout << "<input type=\"submit\" value=\"Submit\"></form>";

                if (cgi_utils::get_request_method() == cgi_utils::post) {
                    char* data = nullptr;
                    cgi_utils::get_form_data(data);

                    // Allocate memory for variables to store form data
                    char* name = new char[10000];
                    char* gender = new char[10000];
                    char* age = new char[10000];
                    char* wplace = new char[10000];
                    char* income = new char[10000];
                    char* purpose = new char[10000];

                    // If form data is available, process and save it
                    if (data != nullptr) {
                        // Get form data and store in variables
                        cgi_utils::get_param_value(data, "surname", name);
                        cgi_utils::get_param_value(data, "gender", gender);
                        cgi_utils::get_param_value(data, "age", age);
                        cgi_utils::get_param_value(data, "workplace", wplace);
                        cgi_utils::get_param_value(data, "income", income);
                        cgi_utils::get_param_value(data, "purpose", purpose);

                        // Convert age and income to appropriate types
                        int _age = atoi(age);
                        double _income = atof(income);

                        // Create a new customer instance
                        Customer customer;
                        customer.surname = name;
                        customer.gender = gender;
                        customer.age = _age;
                        customer.workplace = wplace;
                        customer.income = _income;
                        customer.purpose = purpose;

                        // Write customer data to file
                        writeCustomerToFile(customer, "customers.txt");

                        // Clean up memory
                        delete[] data;
                    }

                    // Clean up memory for form data variables
                    delete[] name;
                    delete[] gender;
                    delete[] age;
                    delete[] wplace;
                    delete[] income;
                    delete[] purpose;
                }

                // After processing form data, read data from file and print it

                // Read customer data from file
                queue_t customer_data = readCustomerFromFile("customers.txt");

                // Print customer data to HTML page
                print_queue(customer_data, "credit"); // Print credit data
                cout << "<br>"; // Line break
                print_queue(customer_data, "debit"); // Print debit data
            }
            else
                cout << line << endl;
        }
        delete[] line;
        file.close();
    }
    return 0;
}

