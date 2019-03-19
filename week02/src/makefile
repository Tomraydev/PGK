CXX = g++
CXXFLAGS = -g -Wall -pedantic -fopenmp -O2
NAME = app
OBJS = main.o

all: $(NAME)

# Linking, $@ = left side :  $^ = right side, $< = first dependency
$(NAME): $(OBJS)
	$(CXX) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system -fopenmp

# Compiling source files to object files
main.o: main.cpp main.h Circle.h RGB.h CMY.h HSL.h HSV.h Slider.h makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

# The following are commands not files
.PHONY: all clean run

clean:
	rm *.o $(NAME)

run:
	./$(NAME)

