#include "auxiliary_functions.h"
//AUXILIARY FUNCTIONS.

//return the next character without consuming it
char peek(std::istream& input) {
		if (input.eof()) { return 0;} //eof means end of stream
		return input.peek(); //this is not my function but a memberfunction of the istream. It returns the next character of "input" but does not consume it
}

//skips all whitespaces and then returns the next character without consuming it
char lookahead(std::istream& input)  {
		input >> std::ws; //skips all white spaces
		return peek(input); //this is my own function.
}

//this function consumes all characters that are not a number or a negative sign
void consume_non_numbers(std::istream& input) {
	char aux;

	// in chars we have '0' == 48 '1' == 49 ... '9' == 57.
	while (!(48 <= lookahead(input) && lookahead(input) <= 57) && lookahead(input) != '-' && !input.eof()) { //eof means end of stream.
		input >> aux;
	}
}

//this funciton consumes all non number characters and then converts the first encountered number into a double
double convert_to_double(std::istream& input) {
	consume_non_numbers(input);

	double x;

	input >> x;

	return x;
}

//END AUXILIARY FUNCTIONS
