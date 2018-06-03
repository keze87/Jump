CC=LC_ALL=C gcc -g -std=c11 -Wall -pedantic -pedantic-errors
IMPRIMIRLINEAS=printf "\n\n"

all: pre-build main-build

pre-build:
	@$(MAKE) --no-print-directory clean
	$(IMPRIMIRLINEAS)
	which cppcheck || true && cppcheck --language=c --enable=all *.c |& grep -v "is never used."

post-build:
	$(IMPRIMIRLINEAS)
	./main || echo "ERROR: $$?"

main-build: main

main: $(OBJS)
	$(IMPRIMIRLINEAS)
	$(CC) -o $@ *.c -lm
	@$(MAKE) --no-print-directory post-build

clean:
	rm main *.o || true
