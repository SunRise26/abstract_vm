#include "VM.hpp"

const std::regex	VM::spec_symb("[ \t]*;;[ \t]*");
const std::regex	VM::empty_line("[ \t]*(;.*)?");

const std::string	VM::op[reg_num] = {
	"push : ",
	"pop : ",
	"dump : ",
	"assert : ",
	"add : ",
	"sub : ",
	"mul : ",
	"div : ",
	"mod : ",
	"print : ",
	"exit : ",
	"println : "
};

const std::string	VM::val_type[val_num] = {
	"int8_t : ",
	"int16_t : ",
	"int32_t : ",
	"float : ",
	"double : "
};

const std::regex	VM::reg[reg_num] = {
	std::regex("[ \t]*push([ \t]+)?.*"),
	std::regex("[ \t]*pop[ \t]*(;.*)?"),
	std::regex("[ \t]*dump[ \t]*(;.*)?"),
	std::regex("[ \t]*assert([ \t]+)?.*"),
	std::regex("[ \t]*add[ \t]*(;.*)?"),
	std::regex("[ \t]*sub[ \t]*(;.*)?"),
	std::regex("[ \t]*mul[ \t]*(;.*)?"),
	std::regex("[ \t]*div[ \t]*(;.*)?"),
	std::regex("[ \t]*mod[ \t]*(;.*)?"),
	std::regex("[ \t]*print[ \t]*(;.*)?"),
	std::regex("[ \t]*exit[ \t]*(;.*)?"),
	std::regex("[ \t]*println[ \t]*(;.*)?"),
	std::regex("[ \t]*pow[ \t]*(;.*)?"),
	std::regex("[ \t]*log2[ \t]*(;.*)?"),
	std::regex("[ \t]*range[ \t]*(;.*)?"),
	std::regex("[ \t]*cout[ \t]*(;.*)?")
};

const std::regex	VM::op_val[val_num] = {
	std::regex("[ \t]+int8[ \t]*\\([ \t]*-?[0-9]+[ \t]*\\)[ \t]*(;.*)?"),
	std::regex("[ \t]+int16[ \t]*\\([ \t]*-?[0-9]+[ \t]*\\)[ \t]*(;.*)?"),
	std::regex("[ \t]+int32[ \t]*\\([ \t]*-?[0-9]+[ \t]*\\)[ \t]*(;.*)?"),
	std::regex("[ \t]+float[ \t]*\\([ \t]*-?[0-9]+(\\.-?[0-9]*)?[ \t]*\\)[ \t]*(;.*)?"),
	std::regex("[ \t]+double[ \t]*\\([ \t]*-?[0-9]+(\\.-?[0-9]*)?[ \t]*\\)[ \t]*(;.*)?")
};

eOperandType		VM::lexer_val(const int id, std::string ln) {
	if (id == 0)
		ln = ln.substr(ln.find('h') + 1);
	else if (id == 3)
		ln = ln.substr(ln.find('t') + 1);
	if (regex_match(ln, std::regex("[ \t]*")))
		throw (VMException::NoValue());
	for (int i(0); i < val_num; ++i)
		if (regex_match(ln, op_val[i]))
			return (static_cast<eOperandType>(i));
	throw (VMException::WrongValue());
}

void				VM::lexer(const std::string & ln, int & id, eOperandType & value) {
	if (regex_match(ln, spec_symb))
		_file_read ? id = -1 : id = -2;
	else if (regex_match(ln, empty_line))
		id = -1;
	else {
		for (id = 0; id < reg_num; ++id) {
			if (regex_match(ln, reg[id])) {
				if (id == 0 || id == 3)
					value = lexer_val(id, ln);
				return ;
			}
		}
		throw (VMException::UnknownInstr());
	}
}

std::string			VM::num_parse(const std::string & ln) {
	std::string		num(ln.substr(ln.find('(') + 1, ln.find(')') - ln.find('(') - 1));

	num.erase(remove_if(num.begin(), num.end(), isspace), num.end());
	return (num);
}

void				VM::push(eOperandType op_type, const std::string & value) {
	_stack.push_back(createOperand(op_type, value));
}

void				VM::pop() {
	if (_stack.empty())
		throw (VMException::EmptyStack());
	delete _stack.back();
	_stack.pop_back();
}

void				VM::dump() {
	for (std::vector<const IOperand *>::reverse_iterator rit = _stack.rbegin(); rit != _stack.rend(); ++rit)
		_out << (*rit)->toString() << std::endl;
}

void				VM::assert(eOperandType op_type, const std::string & value) {
	const IOperand *	cmp;

	if (_stack.empty())
		throw (VMException::EmptyStack());
	cmp = createOperand(op_type, value);
	if (cmp->toString() != _stack.back()->toString() || cmp->getType() != _stack.back()->getType()) {
		delete cmp;
		throw (VMException::False());
	}
	delete cmp;
}

void				VM::add() {
	const IOperand *	op1;
	const IOperand *	op2;
	const IOperand *	res;

	if (_stack.size() < 2)
		throw (VMException::NotEnoughValue());
	op1 = _stack.back();
	op2 = _stack.at(_stack.size() - 2);
	res = *op2 + *op1;
	_stack.pop_back();
	_stack.pop_back();
	delete op1;
	delete op2;
	_stack.push_back(res);
}

void				VM::sub() {
	const IOperand *	op1;
	const IOperand *	op2;
	const IOperand *	res;

	if (_stack.size() < 2)
		throw (VMException::NotEnoughValue());
	op1 = _stack.back();
	op2 = _stack.at(_stack.size() - 2);
	res = *op2 - *op1;
	_stack.pop_back();
	_stack.pop_back();
	delete op1;
	delete op2;
	_stack.push_back(res);
}

void				VM::mul() {
	const IOperand *	op1;
	const IOperand *	op2;
	const IOperand *	res;

	if (_stack.size() < 2)
		throw (VMException::NotEnoughValue());
	op1 = _stack.back();
	op2 = _stack.at(_stack.size() - 2);
	res = *op2 * *op1;
	_stack.pop_back();
	_stack.pop_back();
	delete op1;
	delete op2;
	_stack.push_back(res);
}

void				VM::div() {
	const IOperand *	op1;
	const IOperand *	op2;
	const IOperand *	res;

	if (_stack.size() < 2)
		throw (VMException::NotEnoughValue());
	op1 = _stack.back();
	op2 = _stack.at(_stack.size() - 2);
	res = *op2 / *op1;
	_stack.pop_back();
	_stack.pop_back();
	delete op1;
	delete op2;
	_stack.push_back(res);
}

void				VM::mod() {
	const IOperand *	op1;
	const IOperand *	op2;
	const IOperand *	res;

	if (_stack.size() < 2)
		throw (VMException::NotEnoughValue());
	op1 = _stack.back();
	op2 = _stack.at(_stack.size() - 2);
	res = *op2 % *op1;
	_stack.pop_back();
	_stack.pop_back();
	delete op1;
	delete op2;
	_stack.push_back(res);
}

void				VM::print() {
	const IOperand *	op;
	char				c;

	if (_stack.empty())
		throw (VMException::EmptyStack());
	op = _stack.back();
	if (op->getType() != Int8)
		throw (VMException::NotInt8());
	c = static_cast<char>(stoi(op->toString()));
	if (!isprint(c))
		throw (VMException::NotPrintable());
	_out << c << std::endl;
}

void				VM::exit() {
	_exit = true;
}

void				VM::println() {
	char	c;

	for (std::vector<const IOperand *>::reverse_iterator rit = _stack.rbegin();
	rit != _stack.rend() && (*rit)->getType() == Int8; ++rit) {
		c = static_cast<char>(stoi((*rit)->toString()));
		if (!isprint(c))
			break ;
		_out << c;
	}
	_out << std::endl;
}

void				VM::pow() {
	const IOperand *	op1;
	const IOperand *	op2;
	const IOperand *	res;

	if (_stack.size() < 2)
		throw (VMException::NotEnoughValue());
	op1 = _stack.back();
	op2 = _stack.at(_stack.size() - 2);
	res = createOperand(op1->getType() > op2->getType() ? op1->getType() : op2->getType(),
	std::to_string(std::pow(stod(op2->toString()), stod(op1->toString()))));
	_stack.pop_back();
	_stack.pop_back();
	delete op1;
	delete op2;
	_stack.push_back(res);
}

void				VM::log2() {
	const IOperand *	op;
	const IOperand *	res;

	if (_stack.empty())
		throw (VMException::EmptyStack());
	op = _stack.back();
	res = createOperand(Double, std::to_string(std::log2(stod(op->toString()))));
	_stack.pop_back();
	delete op;
	_stack.push_back(res);
}

template <typename T>
void				VM::print_range(eOperandType e) {
	_out << val_type[e] << static_cast<double>(std::numeric_limits<T>::min()) <<
	" : " << static_cast<double>(std::numeric_limits<T>::max()) << std::endl;
}

void				VM::range() {
	eOperandType	e;

	if (_stack.empty())
		throw (VMException::EmptyStack());
	e = _stack.back()->getType();
	if (e == Int8)
		print_range<int8_t>(e);
	else if (e == Int16)
		print_range<int16_t>(e);
	else if (e == Int32)
		print_range<int32_t>(e);
	else if (e == Float)
		print_range<float>(e);
	else if (e == Double)
		print_range<double>(e);
}

void				VM::cout() {
	_cout = _cout == true ? false : true;
}

void				VM::do_op(const int id, eOperandType op_type, const std::string & ln) {
	static void (VM::*op_fun[reg_num])(void) = {
		&VM::pop,
		&VM::pop,
		&VM::dump,
		&VM::dump,
		&VM::add,
		&VM::sub,
		&VM::mul,
		&VM::div,
		&VM::mod,
		&VM::print,
		&VM::exit,
		&VM::println,
		&VM::pow,
		&VM::log2,
		&VM::range,
		&VM::cout
	};

	if (id == 0)
		push(op_type, num_parse(ln));
	else if (id == 3)
		assert(op_type, num_parse(ln));
	else
		(this->*op_fun[id])();
}

void				VM::out() {
	std::cout << _out.str();
	std::cerr << _err.str();
	_out.str(std::string());
	_err.str(std::string());
}

void				VM::read() {
	std::string		ln;
	unsigned int	ln_num(1);
	int				token_id;
	eOperandType	value;

	while (std::getline(_input, ln)) {
		try {
			token_id = -1;
			lexer(ln, token_id, value);
			if (token_id == -2)
				break ;
			else if (!_exit && token_id >= 0)
				do_op(token_id, value, ln);
		} catch (std::exception & e) {
			_err << "Line " << ln_num << " : Error : ";
			if (token_id >= 0 && token_id < reg_num)
				_err << op[token_id];
			_err << e.what() << std::endl;
		}
		++ln_num;
		if (_cout)
			out();
	}
	if (!_exit)
		_err << "Error : No exit statement" << std::endl;
	out();
}

VM::VM() : _input(std::cin), _file_read(false), _exit(false), _cout(false) {}

VM::VM(std::ifstream & ifs) : _input(ifs), _file_read(true), _exit(false), _cout(false) {}

VM::~VM() {
	while (!_stack.empty()) {
		delete _stack.back();
		_stack.pop_back();
	}
}
