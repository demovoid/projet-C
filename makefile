CC = gcc

ifeq ($(OS),Windows_NT)
	clr = del /s *.o
	propre = del /s *.exe
else
	clr = rm -rf *.o
	propre = find . -type f -executable -delete
endif

test: test.o graph.o
	${CC} $^ -o $@

graph.o: data/graph.c
	${CC} $< -c -o $@

test.o: test.c
	${CC} $< -c -o $@

clean:
	${clr}

mrproper: clean
	${propre}