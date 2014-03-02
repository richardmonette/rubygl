require 'mkmf'
extension_name = 'rubygl'
dir_config(extension_name)
find_library('SDL', 'SDL_Init')
create_makefile(extension_name)
