#include "math/MathException.h"

namespace siege{
	namespace math{
		MathException::MathException() throw(){
			msg = std::string("MathException");
		}

		MathException::MathException(std::string message) throw(){
			msg = std::string("MathException: ");
			msg.append(message);
		}
		
		MathException::~MathException() throw(){
		}

		const char* MathException::what() const throw(){
			return msg.data();
		}
	};
};
