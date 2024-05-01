#pragma once
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdarg.h>

// This function is just for reading static tmpl files.
void readTmplFile(const char* filename);
void write_to_file(const char* filename, char* _username, char* _comment);
