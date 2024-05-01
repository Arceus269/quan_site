#include "utils.h"

using namespace std;;

// This function is just for reading static tmpl files.
void readTmplFile(const char* filename) {
	ifstream file(filename);

	if (file.is_open()) {
		char* line = new char[1024];
		while (!file.eof())
		{
			file.getline(line, 1024);
			cout << line << endl;
		}
		delete[] line;
		file.close();
	}
}

void write_to_file(const char* filename, char* _username, char* _comment)
{
	ofstream out(filename, ios_base::app);

	if (out.is_open())
	{
		out << _username << "\n";
		out << _comment << "\n";

		out.close();
	}
}
