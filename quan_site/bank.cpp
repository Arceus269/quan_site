#include "cgi.h"
#include "../quan_site/utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using std::endl;
using namespace cgi_utils;

// Khai báo cấu trúc dữ liệu của mỗi khách hàng
struct Customer {
    string surname;
    string gender;
    int age;
    string workplace;
    int income;
    string purpose;
    Customer* prev = nullptr, *next = nullptr;
};

// A structure to represent a queue of elements
struct queue_t
{
    Customer* first = nullptr;
    Customer* last = nullptr;

};


void enqueue(queue_t& q, string first_name, string work_place, string gender, int age, int income, string purpose)
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

// Hàm để ghi dữ liệu khách hàng vào tệp
void writeCustomerToFile(const Customer& customer, const string& filename) {
    ofstream file(filename, std::ios::app);
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
    queue_t _Customers;

    ifstream file(filename);
    if (file)
    {
        string name, age, gender, income, wkplace, purpose;    
        while (!file.eof())
        {
            getline(file, name);
            getline(file, gender);
            getline(file, age);
            getline(file, wkplace);
            getline(file, income);
            getline(file, purpose);

            int _income = stoi(income);
            int _age = stoi(age);

            enqueue(_Customers, name, wkplace, gender, _age, _income, purpose);
        }
        file.close();
    }
    return _Customers;
}

void print_queue(queue_t q, const string& _c_purpose)
{
    cout << "<table cellspacing='0' style='margin-top: 40px'><thead><tr>" \
        "<th>Full name</th><th>Gender</th><th>Age</th><th>Workplace</th><th>Income</th><th>Purpose</th></tr></thead>\n";
    cout << "<tbody>";
    for (auto* curr = q.first; curr != NULL; curr = curr->next)
    {
        if (curr->purpose == _c_purpose)
        {
            cout << "<tr>";
            cout << "<td class=\"cell\" data-title=\"Full Name\">";
            cout << curr-> surname << "</td>";
            cout << "<td class=\"cell\" data-title=\"Sex\">";
            cout << curr->gender << "</td>";
            cout << "<td class=\"cell\" data-title=\"Age\">";
            cout << curr->age << "</td>";
            cout << "<td class=\"cell\" data-title=\"Location\">";
            cout << curr->workplace << "</td>";
            cout << "<td class=\"cell\" data-title=\"Salary\">";
            cout << curr->income << "</td>";
            cout << "<td class=\"cell\" data-title=\"Job Title\">";
            cout << curr->purpose << "</td></tr>" << endl;
        }
    }
    cout << "</tbody></table>" << endl;
}
void menu();

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
            if (!strcmp(line, "<!--FORM-->"))
            {
                menu();
            }
            else
                cout << line << endl;
        }
        delete[] line;
        file.close();
    }
    return 0;
}

void menu()
{
    queue_t customer_data;

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

        cgi_utils::get_param_value(data, "surname", name);
        cgi_utils::get_param_value(data, "gender", gender);
        cgi_utils::get_param_value(data, "age", age);
        cgi_utils::get_param_value(data, "workplace", wplace);
        cgi_utils::get_param_value(data, "income", income);
        cgi_utils::get_param_value(data, "purpose", purpose);

        // Convert age and income to appropriate types
        if (atoi(age) <= 0 || atof(income) < 0)
        {
            cout << "<dialog open='open' id='modal' aria-labelledby='eror' style='top: 500px'>";
            cout << "<h2 id='eror'> Error! </h2>";
            cout << "<p> The entered data is invalid! </p>";
            cout << "<form method='dialog'><button>Close</button></form>";
            cout << "</dialog>";
        }
        else
        {
            int _age = atoi(age);
            int _income = atoi(income);

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
        }

        delete[] name;
        delete[] gender;
        delete[] age;
        delete[] wplace;
        delete[] income;
        delete[] purpose;
        delete[] data;
    }
    customer_data = readCustomerFromFile("customers.txt");

    print_queue(customer_data, "credit"); // Print credit data
    std::cout << "<br>"; // Line break
    print_queue(customer_data, "debit"); // Print debit data
}
