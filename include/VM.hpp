#ifndef VM_HPP
# define VM_HPP
# include <iostream>
# include <sstream>
# include <fstream>
# include <vector>
# include <regex>
# include <cmath>
# include "eOperandType.hpp"
# include "Factory.hpp"
# include "VMException.hpp"

struct VMException;

class VM : public Factory
{
	const static int			reg_num = 16;
	const static std::regex		reg[reg_num];
	const static std::string	op[reg_num];

	const static int			val_num = 5;
	const static std::regex		op_val[val_num];
	const static std::string	val_type[val_num];

	const static std::regex		spec_symb;
	const static std::regex		empty_line;

	std::vector<const IOperand *>	_stack;

	std::istream &				_input;
	std::ostringstream			_out;
	std::ostringstream			_err;
	bool						_file_read;
	bool						_exit;
	bool						_cout;

	eOperandType				lexer_val(const int id, std::string ln);
	void						lexer(const std::string & ln, int & id, eOperandType & value);

	std::string					num_parse(const std::string & ln);
	void						do_op(const int id, eOperandType op_type, const std::string & ln);
	void						push(eOperandType op_type, const std::string & value);
	void						pop();
	void						dump();
	void						assert(eOperandType op_type, const std::string & value);
	void						add();
	void						sub();
	void						mul();
	void						div();
	void						mod();
	void						print();
	void						exit();

	void						println();
	void						pow();
	void						log2();
	template <typename T> void	print_range(eOperandType e); // range func
	void						range();
	void						cout();

	void						out();

	VM(const VM & rhs);
	VM &						operator=(const VM & rhs);

public:

	void						read();
	VM();
	VM(std::ifstream & ifs);
	~VM();

};

#endif