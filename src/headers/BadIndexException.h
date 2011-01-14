#ifndef BADINDEXEXCEPTION_H
#define BADINDEXEXCEPTION_H

#include<exception>
#include<string>

namespace siege{

	class BadIndexException: public std::exception{
		private:
			std::string msg;
		public:
			BadIndexException()throw();
			BadIndexException(std::string)throw();
			virtual ~BadIndexException()throw();
			virtual const char* what() const throw();
	}; //BadIndexException

}; //siege

#endif //BADINDEXEXCEPTION_H
