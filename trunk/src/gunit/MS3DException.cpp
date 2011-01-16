#include"gunit/MS3DException.h"

namespace siege{
	namespace gunit{

		MS3DException::MS3DException() throw(){
			msg = std::string("MS3DException!");
		}

		MS3DException::MS3DException(std::string s) throw(){
			msg = std::string("MS3DException: ");
			msg.append(s);
		}

		MS3DException::~MS3DException() throw(){};

		const char* MS3DException::what() const throw(){
			return msg.data();
		}

	}; //gunit
}; //siege
