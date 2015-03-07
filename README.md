# TCCLK (Tiny C Compiler in Linux Kernel)

Kernel development is difficult. Even creating the classic intro "Hello World!" kernel module involves a Makefile and a bunch of nonsensical amount of code. 

<a href="http://bellard.org/tcc">TCC</a> is a tiny C compiler written by Fabrice Bellard. It's only 300KB of executable, and it's small enough to be run anywhere, including the kernel.

Some cool things you might be able to do are:
- Make C "scripts" : TCC runs so fast. It can literally "run" C source code like scripts.
- You can invoke kernel functions from user space, enabling you to write a kernel specific program without having the need to go through the pain of writing a kernel module. 
- You could run C programs inside a C program. Kind of like the <a href="https://docs.python.org/2/library/functions.html#eval">eval function in Python</a>. 
<strong>Warning</strong> <i>We aren't responsible for any breach of security that may occur from using this</i>

## TCCLK Service
tcc_service is a user-level program that serves as a linker to the TCC module in Kernel. Type tcc_service -h for help.

## Using TCCLK
1. git clone https://github.com/jameswhang/tcclk.git
2. cd tcclk/tcc-0.9.26/modules/
3. make clean
4. make
5. insmod tcc_mod.ko
