main: testing.cpp matrix.o vector.o
	g++ -o $@ $^

%.o: %.cpp %.hpp
	g++ -c $<

clean:
	rm main *.o
