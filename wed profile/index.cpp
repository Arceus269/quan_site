#include "cgi.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace cgi_utils;
using namespace std;

/*/
int main(){
	setlocale(LC_ALL, "rus");
	cout << "Content-type: text/html; charset=windows-1251\n\n";

	ifstream file("login.tmpl");
	if (!file.is_open()) return -1;

	char* line = new char[1024];
	while (!file.eof())
	{
		file.getline(line, 1024);
		if (!strcmp(line, "<!--CONTENT-->"))
		{
			cout << "<div class='info'>";
			cout << "<p>Fill in the form</p>";
			cout << "<form method='post' action='index.cgi' class='login-form'>\n";
			cout << "<input type=\"text\" name='user-name' placeholder=\"username\" required>";
			cout << "<input type=\"password\" name='passw' placeholder=\"Password\">";
			cout << "<input type=\"submit\" id='btn-submit' value=\"Sign In\"></form>" << endl;

			if (get_request_method() == post)
			{
				char* data = nullptr;

				get_form_data(data);

				char* user_name = nullptr;
				char* password = nullptr;
				const char* filename = "data.txt";

				get_param_value(data, "user-name", user_name);
				get_param_value(data, "passw", password);
				if (user_name && password)
				{
					if (!strcmp(user_name, "quan") && !strcmp(password, "q"))
					{
						cout << "<script>alert(Welcome, " << user_name << ")</script>";
						cout << "<meta http-equiv='refresh' content='0;URL=profile.cgi'>\n";
					}
				}

				
				cout << "</div>" << endl;

				// log all data to a file before cleaning
				//write_to_file_2(filename, 3, first_name, last_name, password);
				delete[] data;
			}
		}
		else
			cout << line << endl;
	}
	delete[] line;
	file.close();
	return 0;
}
*/