all:
	g++ -I src/include -L src/lib main.cpp game.cpp board.cpp piece.cpp track.cpp take.cpp -o checkers.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

run:
	./main.exe