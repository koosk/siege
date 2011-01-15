#include"BadIndexException.h"

namespace siege{

	BadIndexException::BadIndexException() throw(){
		msg = std::string("BadIndexException!");
	}

	BadIndexException::BadIndexException(std::string s) throw(){
		msg = std::string("BadIndexException: ");
		msg.append(s);
	}

	BadIndexException::~BadIndexException() throw(){};

	const char* BadIndexException::what() const throw(){
		return msg.data();
	}

}; //siege
