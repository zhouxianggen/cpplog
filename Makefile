
run_test : test.o
	g++ -o $@ $^
	rm -rf *.o
