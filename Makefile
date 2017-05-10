# Giraphe: Makefile

default: build

all: clean build

build:
	cd compiler; make

test: clean build
	cd tests; make

.PHONY: clean
clean:
	cd compiler; make clean
	cd tests; make clean
