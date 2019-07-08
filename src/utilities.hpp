#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string> 

using std::string; 

int to_int(char c);
int str_to_int(string literal);

void to_lower(char* str); // changes str to its lowercase version 
char* make_lower(const char* str); // returns a malloc-ed lowercase version of str 

bool is_ws(char c);
bool is_integer(char c);
bool is_letter(char c); 
bool is_identifier(char c);
bool is_alphanumeric(char c);

#endif
