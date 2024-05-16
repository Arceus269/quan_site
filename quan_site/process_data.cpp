#include "cgi.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Client {
    string surname;
    string gender;
    int age;
    string workplace;
    double income;
    string purpose;
};

void read_clients(const string& filename, vector<Client>& clients) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "<p>Error: Unable to open file</p>\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Client client;
        iss >> client.surname >> client.gender >> client.age >> client.workplace >> client.income >> client.purpose;
        clients.push_back(client);
    }
    file.close();
}

void display_clients(const vector<Client>& clients, const string& purpose) {
    cout << "<h2>" << purpose << " Queue</h2>\n";
    cout << "<table border='1'>\n";
    cout << "<tr><th>Surname</th><th>Gender</th><th>Age</th><th>Workplace</th><th>Income</th><th>Purpose</th></tr>\n";
    for (const auto& client : clients) {
        if (client.purpose == purpose) {
            cout << "<tr>";
            cout << "<td>" << client.surname << "</td>";
            cout << "<td>" << client.gender << "</td>";
            cout << "<td>" << client.age << "</td>";
            cout << "<td>" << client.workplace << "</td>";
            cout << "<td>" << client.income << "</td>";
            cout << "<td>" << client.purpose << "</td>";
            cout << "</tr>\n";
        }
    }
    cout << "</table>\n";
}

int main() {
    // Set content type
    cout << "Content-type: text/html\n\n";

    // Get form data
    char* filename = nullptr;
    cgi_utils::get_form_data(filename);

    // Read clients from file
    vector<Client> clients;
    read_clients(filename, clients);

    // Display clients with credit purpose
    display_clients(clients, "Credit");

    // Display clients with deposit purpose
    display_clients(clients, "Deposit");

    // Free memory
    delete[] filename;

    return 0;
}
