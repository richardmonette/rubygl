require 'mkmf'
extension_name = 'rubygl'
dir_config(extension_name)
find_library('SDL', 'SDL_Init')
find_library('SDL_image', 'IMG_Load');
find_library('GLU', 'gluPerspective')
create_makefile(extension_name)
