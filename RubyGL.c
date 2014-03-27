#include "ruby.h"

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"

#include <GL/glu.h> 

VALUE RubyGL = Qnil;
GLuint texture;

void Init_rubygl();

VALUE method_initSDL(VALUE self, VALUE width, VALUE height, VALUE depth);
VALUE method_initGL(VALUE self);
VALUE method_initTexture(VALUE self);

VALUE method_cleanUp(VALUE self);

VALUE method_clear(VALUE self);
VALUE method_swapBuffers(VALUE self);

VALUE method_drawQuad(VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3);
VALUE method_drawTriangles(VALUE self, VALUE vertices, VALUE texcoords, VALUE normals,
	VALUE verticesIndices, VALUE texcoordsIndices, VALUE normalsIndices);

VALUE method_getKeyPressed(VALUE self);
VALUE method_getIsQuit(VALUE self);

void Init_rubygl() {
	RubyGL = rb_define_module("RubyGL");

	rb_define_method(RubyGL, "initSDL", method_initSDL, 3);
	rb_define_method(RubyGL, "initGL", method_initGL, 0);
	rb_define_method(RubyGL, "initTexture", method_initTexture, 0);

	rb_define_method(RubyGL, "cleanUp", method_cleanUp, 0);

	rb_define_method(RubyGL, "clear", method_clear, 0);
	rb_define_method(RubyGL, "swapBuffers", method_swapBuffers, 0);

	rb_define_method(RubyGL, "drawQuad", method_drawQuad, 8);
	rb_define_method(RubyGL, "drawTriangles", method_drawTriangles, 6);

	rb_define_method(RubyGL, "getKeyPressed", method_getKeyPressed, 0);
	rb_define_method(RubyGL, "getIsQuit", method_getIsQuit, 0);
}

VALUE method_initSDL(VALUE self, VALUE width, VALUE height, VALUE depth) {
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_SetVideoMode( NUM2INT(width), NUM2INT(height), NUM2INT(depth), SDL_OPENGL );
	return 0;
}

VALUE method_initGL(VALUE self) {
	// Setup a projection
	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(60., 1., 0.01, 100.);
	// Setup a default viewing
	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	// Camera position	
	gluLookAt(1., 1., 5., 0., 0., 0., 0., 1., 0.);
	// Rotate the scene
	glRotatef(45., 1., 1., 0.);
	// Basic color, depth
    glClearColor( 0.f, 0.f, 0.f, 0.f );
	glEnable( GL_DEPTH_TEST );
	return 0;
}

// TODO add parameters for texture index, etc.
VALUE method_initTexture(VALUE self) {
	SDL_Surface* surface = IMG_Load("logo.jpg");
	if ( surface == NULL) {
		printf("Error: \"%s\"\n",SDL_GetError());
		return 0;
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(surface);
	return 0;
}

VALUE method_clear(VALUE self) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	return 0;
}

VALUE method_swapBuffers(VALUE self) {
	SDL_GL_SwapBuffers();
	return 0;
}

VALUE method_drawQuad(VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3) {
	glBegin( GL_QUADS );
		glVertex2f( NUM2DBL(x0), NUM2DBL(y0) );
		glVertex2f( NUM2DBL(x1), NUM2DBL(y1) );
		glVertex2f( NUM2DBL(x2), NUM2DBL(y2) );
		glVertex2f( NUM2DBL(x3), NUM2DBL(y3) );
	glEnd();
	return 0;
}

VALUE method_drawTriangles(VALUE self, VALUE vertices, VALUE texcoords, VALUE normals, 
	VALUE verticesIndices, VALUE texcoordsIndices, VALUE normalsIndices) {
	int nVerticesIndices = RARRAY_LEN(verticesIndices);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glBegin( GL_TRIANGLES );
		int i = 0;
		for (i = 0; i < nVerticesIndices; i++) {
			int vertexId = NUM2INT(rb_ary_entry(verticesIndices, i)) * 3;
			int texcoordId = NUM2INT(rb_ary_entry(texcoordsIndices, i)) * 2;
			int normalId = NUM2INT(rb_ary_entry(normalsIndices, i)) * 3;
			glTexCoord2f( 
				NUM2DBL(rb_ary_entry(texcoords, texcoordId+0)),
				NUM2DBL(rb_ary_entry(texcoords, texcoordId+1))
			);
			glNormal3f(
				NUM2DBL(rb_ary_entry(normals, normalId+0)),
				NUM2DBL(rb_ary_entry(normals, normalId+1)),
				NUM2DBL(rb_ary_entry(normals, normalId+2))
			);
			glVertex3f(
				NUM2DBL(rb_ary_entry(vertices, vertexId+0)),
				NUM2DBL(rb_ary_entry(vertices, vertexId+1)),
				NUM2DBL(rb_ary_entry(vertices, vertexId+2))
			);
		}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	return 0;
}

VALUE method_cleanUp(VALUE self) {
	SDL_Quit();
	return 0;
}

VALUE method_getKeyPressed(VALUE self) {
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
		if ( event.type == SDL_KEYDOWN ) {
			return event.key.keysym.sym;
		}
	}
	return -1;
}

VALUE method_getIsQuit(VALUE self) {
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
		if ( event.type == SDL_QUIT ) {
			return 1;
		}
	}
	return 0;
}
