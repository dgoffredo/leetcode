.PHONY: test

test: solution test-input
	./solution <test-input

solution: driver.cpp solution.cpp
	g++ -o solution driver.cpp