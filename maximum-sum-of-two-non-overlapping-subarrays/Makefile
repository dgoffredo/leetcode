.PHONY: run

run: linear input
	./linear <input

linear: linear.cpp driver.cpp
	g++ -fsanitize=address -o linear driver.cpp
