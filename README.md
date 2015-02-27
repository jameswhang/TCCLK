# TCCLK (Tiny C Compiler in Linux Kernel)

Kernel development is difficult. Even creating the classic intro "Hello World!" kernel module involves a Makefile and a bunch of nonsensical amount of code. 

<a href="http://bellard.org/tcc">TCC</a> is a tiny C compiler written by Fabrice Bellard. It's only 300KB of executable, and it's small enough to be run anywhere.

Some cool things you might be able to do are:
- Make C "scripts" : TCC runs so fast. It can literally "run" C source code like scripts.
- You could technically invoke kernel functions from user space, enabling you to write a kernel specific program without really having the need to make a kernel module. 
- You could run C programs inside a C program. Kind of like the <a href="https://docs.python.org/2/library/functions.html#eval">eval function in Python</a>. 
<strong>Note</strong>: This is still a project in development. Don't use it in your kernel until this note disappears, unless you're a kernel hacker! :)

## Using TCCLK
1. git clone https://github.com/jameswhang/tcclk.git
2. cd tcclk/tcc-0.9.26/modules/
3. make clean
4. make
5. insmod tcc_mod.ko
