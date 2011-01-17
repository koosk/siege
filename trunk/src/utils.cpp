#include"utils.h"
#include"SiegeException.h"
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<GL/glu.h>
#include<string>

namespace siege{
	
	GLuint loadImage(char* file, GLuint type){
			if(!glIsEnabled(GL_TEXTURE_2D))
				throw SiegeException("GL_TEXTURE_2D is disabled!");
			SDL_Surface* image = IMG_Load(file);
			if(!image){
				std::string ms("The file cannot be open: ");
				ms.append(file);
				throw SiegeException(ms);
			}
			glPushAttrib (GL_ALL_ATTRIB_BITS);
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			if(type == GL_LINEAR || type == GL_NEAREST){
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,type);	// Linear Filtering
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,type);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
			}else if(type == GL_LINEAR_MIPMAP_NEAREST){
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
				gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->w, image->h, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
			}else{
				throw SiegeException("Wrong texture type!");
			}
			glPopAttrib();
			return texture;
	}

}; //siege
