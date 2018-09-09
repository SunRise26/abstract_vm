#include "Factory.hpp"
#include "Operand.hpp"

IOperand const *	Factory::createOperand( eOperandType type, std::string const & value ) const {
	static const IOperand * (Factory::*fun[])( std::string const & value ) const = {
		&Factory::createInt8,
		&Factory::createInt16,
		&Factory::createInt32,
		&Factory::createFloat,
		&Factory::createDouble
	};
	return ((this->*fun[type])(value));
}

template <typename T>
void				Factory::valueTest( std::string const & value ) const  {
	double	val_test;

	val_test = std::strtod(value.c_str(), nullptr);
	if (val_test < std::numeric_limits<T>::lowest())
		throw (VMException::Underflow());
	if (val_test > std::numeric_limits<T>::max())
		throw (VMException::Overflow());
}

IOperand const *	Factory::createInt8( std::string const & value ) const {
	valueTest<int8_t>(value);
	return (new Operand<int>(Int8, value));
}

IOperand const *	Factory::createInt16( std::string const & value ) const {
	valueTest<int16_t>(value);
	return (new Operand<int>(Int16, value));
}

IOperand const *	Factory::createInt32( std::string const & value ) const {
	valueTest<int32_t>(value);
	return (new Operand<int>(Int32, value));
}

IOperand const *	Factory::createFloat( std::string const & value ) const {
	valueTest<float>(value);
	return (new Operand<float>(Float, value));
}

IOperand const *	Factory::createDouble( std::string const & value ) const {
	valueTest<double>(value);
	return (new Operand<double>(Double, value));
}
