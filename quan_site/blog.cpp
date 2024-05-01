#include "../quan_site/utils.h"
#include "cgi.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace cgi_utils;
using namespace std;

void get_form();
void make_comment();

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Content-type: text/html; charset=windows-1251\n\n";

	ifstream file("blog.tmpl");
	if (file.is_open())
	{
		char* line = new char[1024];
		while (!file.eof())
		{
			file.getline(line, 1024);
			
			if (!strcmp(line, "<!--FORM-->"))
			{
				get_form();
			}
			if (!strcmp(line, "<!--CONTENT-->"))
			{
				make_comment();
			}
			else
				cout << line << endl;
		}
		file.close();
		delete[] line;
	}
	return 0;
}

void get_form()
{
	cout << "<form action='blog.cgi' method='post' id=\"new-comment-form\">";
	cout << "<div>";
	cout << "<label for=\"comment-name\">Name:</label>";
	cout << "<input type=\"text\" id=\"comment-name\" name=\"name\" required>";
	cout << "</div>";
	cout << "<div>";
	cout << "<label for=\"comment-text\">Comment : </label>";
	cout << "<textarea id=\"comment-text\" name=\"comment\" rows=\"4\" required></textarea>";
	cout << "</div>";
	cout << "<div>";
	cout << "<input type=\"submit\" value=\"Submit Comment\">";
	cout << "</div>";
	cout << "</form>";

	if (get_request_method() == post)
	{
		char* data = nullptr;

		get_form_data(data);

		char* user_name = nullptr;
		char* user_comment = nullptr;
		const char* filename = "blog_data.txt";

		get_param_value(data, "name", user_name);
		get_param_value(data, "comment", user_comment);
		if (user_name && user_comment)
		{
			write_to_file(filename, user_name, user_comment);
		}
		delete[] data;
	}
}

	void make_comment()
	{
		ifstream infile("blog_data.txt");

		if (infile)
		{
			char* name = new char[1000000];
			char* comment = new char[1000000];

			while (!infile.eof())
			{
				infile.getline(name, 1000000);
				infile.getline(comment, 1000000);
				cout << "<p><strong>" << name << ": </strong>" << comment << "</p></div>";
			}
			infile.close();
		}
	}
