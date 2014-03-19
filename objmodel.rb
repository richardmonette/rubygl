class ObjModel
	
	def initialize(filepath)
		@vertices = []
		@faces = []
		File.open(filepath, 'r') do |file|
			while line = file.gets()
				chunks = line.split()
				if chunks[0] == 'v'
					@vertices.push(Float(chunks[1]))
					@vertices.push(Float(chunks[2]))
					@vertices.push(Float(chunks[3]))
				elsif chunks[0] == 'f'
					@faces.push(Integer(chunks[1])-1)
					@faces.push(Integer(chunks[2])-1)
					@faces.push(Integer(chunks[3])-1)
				end
			end
		end
	end

	def vertices
		@vertices
	end

	def faces
		@faces
	end	

end
