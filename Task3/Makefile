main: main.o  Figure.h Exeption.h Exeption.o Conus.o Conus.h Cilinder.o Cilinder.h Pyramid.o Pyramid.h Rectangle.o Rectangle.h Triangle.o Triangle.h Circle.o Circle.h
		g++ main.o Exeption.o Conus.o Cilinder.o Pyramid.o Rectangle.o Triangle.o Circle.o -o main
main.o: main.cpp Figure.h Exeption.h Exeption.o Conus.o Conus.h Cilinder.o Cilinder.h Pyramid.o Pyramid.h Rectangle.o Rectangle.h Triangle.o Triangle.h Circle.o Circle.h 


Exeption.o: Exeption.cpp
		g++ -c -g  Exeption.cpp

Rectangle.o: Rectangle.cpp Rectangle.h Figure.h
		g++ -c -g Rectangle.cpp
Triangle.o: Triangle.cpp Triangle.h Figure.h
		g++ -c -g Triangle.cpp
Circle.o: Circle.cpp Circle.h Figure.h
		g++ -c -g Circle.cpp


Conus.o: Conus.cpp Conus.h Figure.h
		g++ -g Conus.cpp
Cilinder.o: Cilinder.cpp Cilinder.h Figure.h
		g++ -c -g Cilinder.cpp
Pyramid.o: Pyramid.cpp Pyramid.h Figure.h
		g++ -c -g Pyramid.cpp


clean: 
		rm -rf *.o



