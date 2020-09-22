CC = gcc

ifeq ($(OS),Windows_NT)
	clr = del /s *.o
	propre = del /s *.exe
else
	clr = rm -rf *.o
	propre = find . -type f -executable -delete
endif

main: main.o graph.o
	${CC} $^ -o $@

%.o: %.c
	${CC} $< -c -o $@

clean:
	${clr}

mrproper: clean
	${propre}