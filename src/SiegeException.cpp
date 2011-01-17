#include"SiegeException.h"

namespace siege{

	SiegeException::SiegeException() throw(){
		msg = std::string("SiegeException!");
	}

	SiegeException::SiegeException(std::string s) throw(){
		msg = std::string("SiegeException: ");
		msg.append(s);
	}

	SiegeException::~SiegeException() throw(){};

	const char* SiegeException::what() const throw(){
		return msg.data();
	}

}; //siege
