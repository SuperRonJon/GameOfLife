out/life: out/main.o
	g++ out/main.o -o out/life -Llib -lsfml-graphics -lsfml-window -lsfml-system

out/main.o: main.cpp
	g++ -O2 -c main.cpp -o out/main.o -Iinclude

clean:
	rm out/*.o out/life

clean-windows:
	del out\*.o out\*.exe
