SRC      = $(wildcard source/*.c)
DEPS     = $(wildcard source/*.h)
OBJ      = $(addsuffix .o,$(subst source/,bin/,$(basename $(SRC))))
LIBS     = -lSDL3
FLAGS    = -std=c99 -Wall -Wextra -pedantic -g -I./lib
EMBEDDED = $(addsuffix .h,$(subst assets/,source/assets/,$(basename $(wildcard assets/*))))

compile: $(EMBEDDED) ./bin $(OBJ) $(SRC) $(DEPS)
	$(CC) $(OBJ) $(LIBS) -o yterm

./bin:
	mkdir -p bin

source/assets/%.h: assets/%.bmp ./source/assets
	xxd -i $< > $@

./source/assets:
	mkdir -p source/assets

bin/%.o: source/%.c $(DEPS)
	$(CC) -c $< $(FLAGS) -o $@

clean:
	rm bin/*.o yterm

