main: testing.cpp matrix.o vector.o polynomial.o
	g++ -o $@ $^

%.o: %.cpp %.hpp
	g++ -c $<

clean:
	rm main *.o
