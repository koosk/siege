#ifndef BSP_EXCEPTION_H
#define BSP_EXCEPTION_H

#include<exception>
#include<string>

namespace siege{
	namespace gunit{

		class BSPException: public std::exception{
			private:
				std::string msg;
			public:
				BSPException()throw();
				BSPException(std::string)throw();
				virtual ~BSPException()throw();
				virtual const char* what() const throw();
		}; //BSPException

	}; //gunit
}; //siege

#endif //BSP_EXCEPTION_H
