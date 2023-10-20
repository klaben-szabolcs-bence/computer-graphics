#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glut.h>
#include <stdio.h>

typedef GLubyte Pixel[3];

/**
 * Load texture from file and returns with the texture name.
 */
GLuint load_texture(char* filename);

/**
 * Same as above, but simplified and using transparency.
 */
GLuint load_ogl_texture(const char* filename);

#endif /* TEXTURE_H */