#include "ruby.h"

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include <GL/glu.h> 

VALUE RubyGL = Qnil;

void Init_rubygl();

VALUE method_initSDL(VALUE self, VALUE width, VALUE height, VALUE depth);
VALUE method_initGL(VALUE self);

VALUE method_cleanUp(VALUE self);

VALUE method_clear(VALUE self);
VALUE method_swapBuffers(VALUE self);

VALUE method_drawQuad(VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3);
VALUE method_drawTriangles(VALUE self, VALUE vertices, VALUE faces);

VALUE method_getKeyPressed(VALUE self);
VALUE method_getIsQuit(VALUE self);

void Init_rubygl() {
	RubyGL = rb_define_module("RubyGL");

	rb_define_method(RubyGL, "initSDL", method_initSDL, 3);
	rb_define_method(RubyGL, "initGL", method_initGL, 0);

	rb_define_method(RubyGL, "cleanUp", method_cleanUp, 0);

	rb_define_method(RubyGL, "clear", method_clear, 0);
	rb_define_method(RubyGL, "swapBuffers", method_swapBuffers, 0);

	rb_define_method(RubyGL, "drawQuad", method_drawQuad, 8);
	rb_define_method(RubyGL, "drawTriangles", method_drawTriangles, 2);

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
	gluLookAt(2.5, 2.5, 5., 0., 0., 0., 0., 1., 0.);
	// Rotate the scene
	glRotatef(45., 1., 1., 0.);
	// Basic color, depth
    glClearColor( 0.f, 0.f, 0.f, 0.f );
	glEnable( GL_DEPTH_TEST );
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

VALUE method_drawTriangles(VALUE self, VALUE vertices, VALUE faces) {
	int nFaces = RARRAY_LEN(faces);
	glBegin( GL_TRIANGLES );
		int i = 0;
		for (i = 0; i < nFaces; i++) {
			int faceId = NUM2INT(rb_ary_entry(faces, i)) * 3;
			glVertex3f( 
				NUM2DBL(rb_ary_entry(vertices, faceId+0)),
				NUM2DBL(rb_ary_entry(vertices, faceId+1)),
				NUM2DBL(rb_ary_entry(vertices, faceId+2)) 
			);
			glColor3f( 
				NUM2DBL(rb_ary_entry(vertices, faceId+0))+0.5f,
				NUM2DBL(rb_ary_entry(vertices, faceId+1))+0.5f,
				NUM2DBL(rb_ary_entry(vertices, faceId+2))+0.5f 
			);
		}
	glEnd();
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
