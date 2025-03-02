main: main.o
	g++ out/main.o -o out/main.exe -L"C:\Users\patri\dev\libraries\SFML-3.0.0\lib" -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp -I"C:\Users\patri\dev\libraries\SFML-3.0.0\include" -o out/main.o

clean:
	del out\*.o out\*.exe