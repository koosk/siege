#include"gunit/BSPException.h"

namespace siege{
	namespace gunit{

		BSPException::BSPException() throw(){
			msg = std::string("BSPException!");
		}

		BSPException::BSPException(std::string s) throw(){
			msg = std::string("BSPException: ");
			msg.append(s);
		}

		BSPException::~BSPException() throw(){};

		const char* BSPException::what() const throw(){
			return msg.data();
		}

	}; //gunit
}; //siege
