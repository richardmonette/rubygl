class ObjModel
	
	def initialize(filepath)
		@vertices = []
		@texcoords = []
		@normals = []
		@verticesIndices = []
		@texcoordsIndices = []
		@normalsIndices = []
		File.open(filepath, 'r') do |file|
			while line = file.gets()
				chunks = line.split()
				if chunks[0] == 'v'
					@vertices.push(Float(chunks[1]))
					@vertices.push(Float(chunks[2]))
					@vertices.push(Float(chunks[3]))
				elsif chunks[0] == 'vt'
					@texcoords.push(Float(chunks[1]))
					@texcoords.push(Float(chunks[2]))
				elsif chunks[0] == 'vn'
					@normals.push(Float(chunks[1]))
					@normals.push(Float(chunks[2]))
					@normals.push(Float(chunks[3]))
				elsif chunks[0] == 'f'
					for i in 1..3
						x = chunks[i].split('/')
						@verticesIndices.push(Integer(x[0])-1)
						@texcoordsIndices.push(Integer(x[1])-1)
						@normalsIndices.push(Integer(x[2])-1)
					end
				end
			end
		end
	end

	def vertices
		@vertices
	end

	def texcoords
		@texcoords
	end	

	def normals
		@normals
	end

	def verticesIndices
		@verticesIndices
	end

	def texcoordsIndices
		@texcoordsIndices
	end

	def normalsIndices
		@normalsIndices
	end

end
