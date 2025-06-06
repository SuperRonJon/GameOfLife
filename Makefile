out/life-static: out/main.o
	g++ out/main.o -o out/life-static -Llib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lEGL_mesa -lfreetype -ludev -lX11 -lXcursor -lXrandr -lXi

out/life-dynamic: out/main.o
	g++ out/main.o -o out/life-dynamic -Llib -lsfml-graphics -lsfml-window -lsfml-system

out/main.o: main.cpp
	g++ -O2 -c main.cpp -o out/main.o -Iinclude

clean:
	rm out/*.o out/life*

clean-windows:
	del out\*.o out\*.exe
