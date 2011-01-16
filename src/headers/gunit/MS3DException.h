#ifndef MS3D_EXCEPTION_H
#define MS3D_EXCEPTION_H

#include<exception>
#include<string>

namespace siege{
	namespace gunit{

		class MS3DException: public std::exception{
			private:
				std::string msg;
			public:
				MS3DException()throw();
				MS3DException(std::string)throw();
				virtual ~MS3DException()throw();
				virtual const char* what() const throw();
		}; //MS3DException

	}; //gunit
}; //siege

#endif //MS3D_EXCEPTION_H
