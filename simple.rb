require 'rubygl'
require 'objmodel'

include RubyGL

initSDL(512, 512, 32)
initGL()
initTexture()

looping = true

objModel = ObjModel.new('cube.obj')

while looping do
	clear()
	#drawQuad(-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5)
	drawTriangles(
		objModel.vertices, 
		objModel.texcoords,
		objModel.normals,
		objModel.verticesIndices,
		objModel.texcoordsIndices,
		objModel.normalsIndices
	)
	swapBuffers()
	sleep(1.0)
	keyPressed = getKeyPressed()
	if keyPressed == 13 # escape key code
		looping = false
	end
end

cleanUp()
