cc = g++
exe = main
objects = main.o calc_exp.o float.o long_int.o rational.o 

$(exe) : $(objects)
			$(cc) -o $(exe) $(objects)

main.o : main.cpp calc_exp.h
		g++ -c main.cpp
calc_exp.o : calc_exp.cpp calc_exp.h opt.h compare.h next_token.h
		g++ -c calc_exp.cpp
float.o : float.cpp float.h rational.h
		g++ -c float.cpp
long_int.o : long_int.cpp long_int.h
		g++ -c long_int.cpp
rational.o : rational.cpp rational.h
		g++ -c rational.cpp

clean : 
		rm $(objects) $(exe)