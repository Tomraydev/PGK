CXX = g++
CXXFLAGS = -g #-Wall  -pedantic
NAME = sfml-app
OBJS = main.o

all: $(NAME)

# Linking, $@ = left side :  $^ = right side, $< = first dependency
$(NAME): $(OBJS)
	$(CXX) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

# Compiling source files to object files
main.o: main.cpp font.h Menu.h Shapes_container.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# The following are commands not files
.PHONY: all clean run

clean:
	rm *.o $(NAME)

run:
	./$(NAME)

