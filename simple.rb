require 'rubygl'

include RubyGL

initSDL(640, 320, 32)
initGL()

looping = true

while looping do
	clear()
	drawQuad(-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5)
	swapBuffers()
	sleep(1.0)
	keyPressed = getKeyPressed()
	if keyPressed == 13 # escape key code
		looping = false
	end
end

cleanUp()
