require 'rubygl'

include RubyGL

initSDL(640, 320, 32)
initGL()

while true do
	clear()
	drawQuad(-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5)
	swapBuffers()
	sleep(1.0)
end
