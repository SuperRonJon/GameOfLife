# Old makefile here for reference, should use cmake to build now.

life: out/main.o
	g++ out/main.o -o out/life-static -Llib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lEGL_mesa -lfreetype -ludev -lX11 -lXcursor -lXrandr -lXi

windows: out/main.o
	g++ out/main.o -o out/life-static-windows -Llib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lwinmm -lopengl32 -lgdi32 

life-dynamic: out/main.o
	g++ out/main.o -o out/life-dynamic -Llib -lsfml-graphics -lsfml-window -lsfml-system

out/main.o: src/main.cpp
	g++ -O2 -c src/main.cpp -o out/main.o -Iinclude

clean:
	rm out/*.o out/life*

clean-windows:
	del out\*.o out\*.exe
