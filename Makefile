# Created by Blackneeed

SOURCES_C:=$(shell find -path ./src/*.c)
OBJECTS_C:=$(patsubst ./src/%.c, ./build/%.c.o, $(SOURCES_C))
SOURCES_CPP:=$(shell find -path ./src/*.cpp)
OBJECTS_CPP:=$(patsubst ./src/%.cpp, ./build/%.cpp.o, $(SOURCES_CPP))
SOURCES_ASM:=$(shell find -path ./src/*.asm)
OBJECTS_ASM:=$(patsubst ./src/%.asm, ./build/%.asm.o, $(SOURCES_ASM))
BUILD_NUMBER:=$(shell python3 scripts/get_build_num.py)
ISO_OUTPUT=dist/BlackOS2-Build$(BUILD_NUMBER).iso
STD_C=gnu99
STD_CPP=c++17
CFLAGS=
CXXFLAGS=
CCFLAGS=-m32 -I src/kernel -ffreestanding
LDFLAGS=-static -m elf_i386 -nostdlib 
LDS=src/linker/linker.ld

$(PHONY): make_dirs link increment_build_num run clean make_iso
all: make_dirs $(OBJECTS_ASM) $(OBJECTS_C) link make_iso increment_build_num run clean

make_dirs:
	mkdir -p build
	mkdir -p build/iso
	mkdir -p build/iso/boot
	mkdir -p build/iso/boot/BlackOS2
	mkdir -p build/iso/boot/grub

build/%.asm.o: src/%.asm
	mkdir -p $(shell dirname '$@')
	nasm -f elf32 -o '$@' '$^'

build/%.c.o: src/%.c
	mkdir -p $(shell dirname '$@')
	gcc -c -o '$@' '$^' $(CCFLAGS) $(CFLAGS) -std=$(STD_C)

build/%.cpp.o: src/%.cpp
	mkdir -p $(shell dirname '$@')
	g++ -c -o '$@' '$^' $(CCFLAGS) $(CXXFLAGS) -std=$(STD_CPP)

link:
	ld -o build/iso/boot/BlackOS2/entry.elf -T $(LDS) $(OBJECTS_ASM) $(OBJECTS_C) $(OBJECTS_CPP) $(LDFLAGS)

make_iso:
	mkdir -p $(shell dirname $(ISO_OUTPUT))
	cp src/boot/grub.cfg build/iso/boot/grub
	grub-mkrescue -o $(ISO_OUTPUT) build/iso

clean:
	rm -rf build

increment_build_num:
	python3 scripts/increment_build_num.py

run:
	qemu-system-i386 -cdrom $(ISO_OUTPUT) -boot d -debugcon file:/dev/stdout