#ifndef OPERAND_H
# define OPERAND_H
# include <string>
# include <sstream>
# include <iomanip>
# include <limits>
# include <cmath>
# include "eOperandType.hpp"
# include "IOperand.hpp"
# include "Factory.hpp"
# include "VMException.hpp"

template <typename T>
class Operand : public IOperand
{
	eOperandType	_type;
	std::string		_value;
	int				_precision;

public:

	int					getPrecision( void ) const {
		return (_precision);
	}

	eOperandType		getType( void ) const {
		return (_type);
	}

	IOperand const *	operator+( IOperand const & rhs ) const {
		double				op1, op2;
		std::ostringstream	res;

		op1 = std::strtod(_value.c_str(), nullptr);
		op2 = std::strtod(rhs.toString().c_str(), nullptr);
		res.precision(_precision < rhs.getPrecision() ? rhs.getPrecision() : _precision);
		res << op1 + op2;
		return (Factory().createOperand((_type < rhs.getType() ? rhs.getType() : _type), res.str()));
	}

	IOperand const *	operator-( IOperand const & rhs ) const {
		double				op1, op2;
		std::ostringstream	res;

		op1 = std::strtod(_value.c_str(), nullptr);
		op2 = std::strtod(rhs.toString().c_str(), nullptr);
		res.precision(_precision < rhs.getPrecision() ? rhs.getPrecision() : _precision);
		res << op1 - op2;
		return (Factory().createOperand((_type < rhs.getType() ? rhs.getType() : _type), res.str()));
	}

	IOperand const *	operator*( IOperand const & rhs ) const {
		double				op1, op2;
		std::ostringstream	res;

		op1 = std::strtod(_value.c_str(), nullptr);
		op2 = std::strtod(rhs.toString().c_str(), nullptr);
		res.precision(_precision < rhs.getPrecision() ? rhs.getPrecision() : _precision);
		res << op1 * op2;
		return (Factory().createOperand((_type < rhs.getType() ? rhs.getType() : _type), res.str()));
	}

	IOperand const *	operator/( IOperand const & rhs ) const {
		double				op1, op2;
		std::ostringstream	res;

		op1 = std::strtod(_value.c_str(), nullptr);
		op2 = std::strtod(rhs.toString().c_str(), nullptr);
		if (op2 == 0)
			throw (VMException::DivisionByZero());
		res.precision(_precision < rhs.getPrecision() ? rhs.getPrecision() : _precision);
		if (_type < Float && rhs.getType() < Float)
			res << static_cast<int>(op1 / op2);
		else
			res << op1 / op2;
		return (Factory().createOperand((_type < rhs.getType() ? rhs.getType() : _type), res.str()));
	}

	IOperand const *	operator%( IOperand const & rhs ) const {
		double				op1, op2;
		std::ostringstream	res;

		op1 = std::strtod(_value.c_str(), nullptr);
		op2 = std::strtod(rhs.toString().c_str(), nullptr);
		if (op2 == 0)
			throw (VMException::ModuleByZero());
		res.precision(_precision < rhs.getPrecision() ? rhs.getPrecision() : _precision);
		res << fmod(op1, op2);
		return (Factory().createOperand((_type < rhs.getType() ? rhs.getType() : _type), res.str()));
	}

	std::string const &	toString( void ) const {
		return (_value);
	}

	Operand(eOperandType type, std::string value) : _type(type), _precision(std::numeric_limits<T>::digits10) {
		std::ostringstream	oss;

		oss.precision(_precision);
		oss << static_cast<T>(std::strtod(value.c_str(), nullptr));
		_value = oss.str();
	}

	Operand(const Operand & rhs) : _type(rhs.getType()), _value(rhs.toString()),
	_precision(rhs.getPrecision()) {}

	Operand &			operator=(const Operand & rhs) {
		_type = rhs.getType();
		_value = rhs.toString();
		_precision = rhs.getPrecision();
		return *this;
	}

	~Operand(void) {}

};

#endif
