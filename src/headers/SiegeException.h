#ifndef SIEGE_EXCEPTION_H
#define SIEGE_EXCEPTION_H

#include<exception>
#include<string>

namespace siege{

	class SiegeException: public std::exception{
		private:
			std::string msg;
		public:
			SiegeException()throw();
			SiegeException(std::string)throw();
			virtual ~SiegeException()throw();
			virtual const char* what() const throw();
	}; //SiegeException

}; //siege

#endif //SIEGE_EXCEPTION_H
