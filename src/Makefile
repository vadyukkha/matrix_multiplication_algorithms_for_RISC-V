.PHONY: help all clean

all: main # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

main: main.c # Build main file
	riscv64-unknown-elf-gcc -I include -std=c17 -O3 main.c -o main && spike pk main

clean: # Delete all builded files
	rm -f main