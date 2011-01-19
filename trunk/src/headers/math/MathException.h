#ifndef MATHEXCEPTION_H
#define MATHEXCEPTION_H
#include <exception>
#include <string>
namespace siege{
	namespace math{
		class MathException:public std::exception{
			private:
				std::string msg;
			public:
				MathException() throw();
				MathException(std::string) throw();
				virtual ~MathException() throw();
				virtual const char* what() const throw();
		};
	};
};
#endif
