#ifndef VMEXCEPTION_HPP
# define VMEXCEPTION_HPP
# include <exception>

struct VMException
{
	struct UnknownInstr		: public std::exception {const char * what() const throw() {return "Unknown instruction";}};
	struct NoValue			: public std::exception {const char * what() const throw() {return "No value";}};
	struct WrongValue		: public std::exception {const char * what() const throw() {return "Wrong value";}};
	struct Overflow			: public std::exception {const char * what() const throw() {return "Value overflow";}};
	struct Underflow		: public std::exception {const char * what() const throw() {return "Value underflow";}};
	struct EmptyStack		: public std::exception {const char * what() const throw() {return "Empty stack";}};
	struct NotEnoughValue	: public std::exception {const char * what() const throw() {return "Not enough values on the stack";}};
	struct False			: public std::exception {const char * what() const throw() {return "False";}};
	struct DivisionByZero	: public std::exception {const char * what() const throw() {return "Division by zero";}};
	struct ModuleByZero		: public std::exception {const char * what() const throw() {return "Module by zero";}};
	struct NotInt8			: public std::exception {const char * what() const throw() {return "Not int8 type";}};
	struct NotPrintable		: public std::exception {const char * what() const throw() {return "Unprintable character";}};
};

#endif
