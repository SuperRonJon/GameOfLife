life: main.o
	g++ out/main.o -o out/life -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp -o out/main.o

clean:
	rm out/*.o out/life

clean-windows:
	del out\*.o out\*.exe