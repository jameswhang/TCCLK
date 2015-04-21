# TCCLK (Tiny C Compiler in Linux Kernel)

Kernel development is difficult. Even creating the classic intro "Hello World!" kernel module involves a Makefile and a bunch of nonsensical amount of code. 

<a href="http://bellard.org/tcc">TCC</a> is a tiny C compiler written by Fabrice Bellard. It's only 300KB of executable, and it's small enough to be run anywhere, including the kernel.

Some cool things you might be able to do are:
- Make C "scripts" : TCC runs so fast. It can literally "run" C source code like scripts.
- You can invoke kernel functions from user space, enabling you to write a kernel specific program without having the need to go through the pain of writing a kernel module. 
- You could run C programs inside a C program. Kind of like the <a href="https://docs.python.org/2/library/functions.html#eval">eval function in Python</a>. 
- <strong>Warning</strong> <i>We aren't responsible for any breach of security that may occur from using this</i>

## TCCLK Service
tcc_service is a user-level program that serves as a linker to the TCC module in Kernel. Type tcc_service -h for help.

## Using TCCLK
- <i> Note that TCCLK only works on Linux machines for now.</i>
- <i> Note again that you can only use TCCLK if you are the root user (because you have to insert a new kernel module into the kernel </i>
1. git clone https://github.com/jameswhang/tcclk.git
2. cd tcclk
3. ./configure
4. cd modules
5. make clean
6. make
7. Either run the shell script ./start.sh OR insmod tcc_module.ko
8. dmesg  will tell you the major number
9. mknod /dev/tcc_dev c (major num) 0 
10. ./service -f (source code filename)

## Trello
I have a <a href="https://trello.com/b/PatvBplZ/tcclk">Trello board</a> to keep all the TODOs. Initially I kept this in the TODO file under module directory but that is now deprecated. Trello is awesome.
