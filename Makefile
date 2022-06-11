program = isotol

extern_lib = 

compiler = gcc

source_dir = src
object_dir = obj
binary_dir = bin
test_dir = tests

source = $(wildcard $(source_dir)/*.c)
object = $(patsubst $(source_dir)/%.c,$(object_dir)/%.o,$(source))
binary = $(binary_dir)/$(program)

all: $(object) $(binary)

$(binary): $(object)
	$(compiler) -o $(binary) $(object) $(extern_lib)

$(object_dir)/%.o: $(source_dir)/%.c
	$(compiler) -c -o $@ $<

run: all
	./$(binary)

clean:
	rm $(object)
	rm $(binary)

print:
	@echo $(source)
	@echo $(object)

init:
	mkdir -p $(source_dir) $(object_dir) $(binary_dir) $(test_dir)/bin

install: all
	sudo cp $(binary) /usr/bin/

test:
	gcc -o tests/bin/passungenTest tests/passungenTest.c obj/passung.o -lunicki -lm
	./tests/bin/passungenTest
