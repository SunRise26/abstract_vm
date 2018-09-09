#ifndef FACTORY_H
# define FACTORY_H
# include <iostream>
# include <string>
# include "eOperandType.hpp"
# include "IOperand.hpp"
# include "VMException.hpp"

class	Factory
{

	template <typename T>
	void				valueTest( std::string const & value ) const ;

	IOperand const *	createInt8( std::string const & value ) const ;
	IOperand const *	createInt16( std::string const & value ) const ;
	IOperand const *	createInt32( std::string const & value ) const ;
	IOperand const *	createFloat( std::string const & value ) const ;
	IOperand const *	createDouble( std::string const & value ) const ;

	Factory(const Factory & rhs);
	Factory &			operator=(const Factory & rhs);

public:
	IOperand const *	createOperand( eOperandType type, std::string const & value ) const ;
	Factory() {};
	virtual ~Factory() {};

};

#endif
