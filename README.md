Flouronix
=========
![alt tag](http://i.imgur.com/LQnc3Gz.png)
The Flouronix system is written to run the Flouronix Virtual Machine (https://github.com/Benderx2/FVM) <br>
It's currently in the babystep stages but much of the early steps have been accomplished. <br>
The system is written in C (which is a language is choice by most system developers) <br>
and certain bits of x86 assembly (mainly architecture specific code and intialization). <br>
Flouronix is designed to run FVM (as stated previously), and thus would to be used to <br>
run cross platform applications written for the VM. Both the VM and the OS are in their pri-<br>
-mitive stages, but the VM is far more ahead.... :) <br>

<h1>Compiling</h1>
I've only tested the build using the GNU C (Cross) Compiler build for <i>i686-elf</i>, if you've<br>
already built a cross compiler and the required tools (<i>i686-elf-ar</i> and <i>i686-elf-ld</i>)<br>
then you can simply run the <i>build.sh</i> script provided through a bash-compatible shell. <br>

<h1>Testing</h1>
You may test the emulator on real hardware or using virtualization software (e.g. Bochs, QEMU, VMWare).<br>
Currently this system is tested on QEMU, QEMU-X86-64, Bochs 2.6.2, Bochs 2.6.6, KVM, and on real hardware <br>
(Pentium IV, 64 MB RAM, Phoenix BIOS 4.0, with a VGA-compatible controller.)<br>
There are two scripts which are related to testing, one is "qemu.sh" (you can run it if you've qemu-system-i386)<br>
or ./bochsrc which is for Bochs. <br>
 
<h1>LICENSE and CREDITS</h1>
See ./LICENSE and ./credits.md
