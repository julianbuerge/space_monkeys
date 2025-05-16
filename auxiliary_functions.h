#include <iostream>
#include <fstream>
#include <string>

//AUXILIARY FUNCTIONS.

//return the next character without consuming it
char peek(std::istream& input);

//skips all whitespaces and then returns the next character without consuming it
char lookahead(std::istream& input);

//this function consumes all characters that are not a number or a negative sign
void consume_non_numbers(std::istream& input);

//this funciton consumes all non number characters and then converts the first encountered number into a double
double convert_to_double(std::istream& input);

//END AUXILIARY FUNCTIONS
