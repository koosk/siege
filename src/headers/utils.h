#ifndef UTILS_H
#define UTILS_H

#include<GL/gl.h>

#ifndef byte
	typedef unsigned char byte;
#endif //byte

#ifndef word
	typedef unsigned short word;
#endif //word

namespace siege{

	GLuint loadImage(char*, GLuint);	

}; //siege

#endif //UTILS_H
