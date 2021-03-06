# Build Script for Flouronix
# Run from a Bash-Compatible Shell
# You may need to do a chmod +x build.sh
#!/bin/bash  
export KLIB_INCLUDE=./klib/
export F_INCLUDE=.
# Compiling for...
export TARGET=i686-elf
# Compiler location
export CC=$HOME/opt/cross/bin/$TARGET-gcc
export LD=$HOME/opt/cross/bin/$TARGET-ld
export AR=$HOME/opt/cross/bin/$TARGET-ar
export AS=nasm
set -o verbose
# Compile RME
$CC -c arch/x86/emulator/rme.c -o rme.o  -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99 
# Compile libk
$CC -O0 -c ./klib/string.c -o klib_string.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99 -fno-builtin
$CC -O0 -c ./klib/kmath.c -o klib_math.o -I$KLIB_INCLUDE -I$F_INCLUDE -fno-builtin
$CC -O0 -c ./klib/stdio.c -o klib_stdio.o -I$KLIB_INCLUDE -I$F_INCLUDE -fno-builtin
$AR rcs libk.a klib_string.o klib_math.o klib_stdio.o rme.o
# Compile Kernel
$AS -f elf ./arch/x86/boot/multiboot/boot.asm -o boot.o
$AS -f elf ./arch/x86/idt.asm -o idt.o
$AS -f elf ./arch/x86/irq.asm -o irq.o
$CC -O0 -c ./arch/x86/exceptions.c -o exceptions.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99
$CC -O0 -c ./arch/x86/irq.c -o irq_c.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99
$CC -O0 -c ./arch/x86/x86.c -o x86.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99
$CC -O0 -c ./arch/x86/interrupts.c -o interrupt.o -I$KLIB_INCLUDE -I$F_INCLUDE
$CC -O0 -c ./arch/x86/pit0.c -o pit0.o -I$KLIB_INCLUDE -I$F_INCLUDE
$CC -O0 -c ./arch/x86/paging.c -o paging.o -I$KLIB_INCLUDE -I$F_INCLUDE
$CC -O0 -c ./arch/x86/loader.c -o loader.o -I$KLIB_INCLUDE -I$F_INCLUDE
$CC -O0 -c ./kernel/console/VGA/VGA.c -o VGA.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99
$CC -O0 -c ./kernel/console/PS2.c -o ps2.o -I$KLIB_INCLUDE -I$F_INCLUDE
$CC -O0 -c ./kernel/console/VGA_console.c -o VGA_CON.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99
$CC -O0 -c ./kernel/fs/vfs.c -o VFS.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99
$CC -O0 -c ./kernel/fs/ramfs/ramfs.c -o ramfs.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99
$CC -O0 -c ./kernel/heap/kheap.c -o kheap.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99
$CC -O0 -c ./kernel/kernel.c -o kernel.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99 
$CC -O0 -c ./kernel/multiboot/multiboot.c -o mboot.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99
$CC -O0 -c ./kernel/exec/exec.c -o exec.o -I$KLIB_INCLUDE -I$F_INCLUDE -std=gnu99
# Link it
$LD -T ./arch/x86/boot/multiboot/hhlink.ld -o kernel.bin boot.o kernel.o VGA.o x86.o VGA_CON.o interrupt.o idt.o irq.o irq_c.o ps2.o kheap.o exceptions.o VFS.o ramfs.o mboot.o pit0.o paging.o loader.o exec.o libk.a
# Build using GNU GRUB
cp kernel.bin ./bin/boot
grub-mkrescue -o flouronix.iso ./bin/
# Remove Object Files
rm *.o
