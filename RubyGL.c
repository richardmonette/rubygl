#include "ruby.h"

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

VALUE RubyGL = Qnil;

void Init_rubygl();
VALUE method_initSDL(VALUE self);

void Init_rubygl() {
	RubyGL = rb_define_module("RubyGL");
	rb_define_method(RubyGL, "initSDL", method_initSDL, 0);
}

VALUE method_initSDL(VALUE self) {
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_SetVideoMode( 640, 480, 32, SDL_OPENGL );
	return 0;
}
