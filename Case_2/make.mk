all:
	g++ Main.cpp Node.h List.h Box.h
	a.exe
	del a.exe
	del *.gch
clean:
	del a.exe