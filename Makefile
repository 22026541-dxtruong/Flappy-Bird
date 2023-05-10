all: 
	g++ main.cpp LTexture.cpp Pipe.cpp Bird.cpp -ISDL_include -LSDL_lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o main