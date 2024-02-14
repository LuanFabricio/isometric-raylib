CLINKS=-lraylib
CFLAGS=-Wall -Wextra

BUILD_FOLDER=build

MAIN_OUT=./build/main.out
MAIN_IN=main.c

all: main.out

build:
	mkdir -p $(BUILD_FOLDER)

main.out: main.c $(BUILD_FOLDER)
	gcc $(CFLAGS) -o $(MAIN_OUT) $(MAIN_IN) $(CLINKS)

run: main.out
	$(MAIN_OUT)

clean:
	rm -r $(BUILD_FOLDER)
