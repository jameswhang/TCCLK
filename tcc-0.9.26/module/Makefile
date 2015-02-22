obj-m := tcc_mod.o

tcc_mod-objs := tcc_module.o ../libtcc.a

# We can probably get these in a smarter way than this... 
# (copy+pasted from build)
#  gcc -Wp,-MD,/441/pdinda/tcc/tcc-0.9.26/module/.tcc_module.o.d  -nostdinc -isystem /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include -I/usr/src/kernels/2.6.38.6-26.rc1.fc15.x86_64/arch/x86/include -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -m64 -mtune=generic -mno-red-zone -mcmodel=kernel -funit-at-a-time -maccumulate-outgoing-args -fstack-protector -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_FXSAVEQ=1 -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -Wframe-larger-than=2048 -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO  -DMODULE  -D"KBUILD_STR(s)=#s" -D"KBUILD_BASENAME=KBUILD_STR(tcc_module)"  -D"KBUILD_MODNAME=KBUILD_STR(tcc_mod)" -c -o /441/pdinda/tcc/tcc-0.9.26/module/tcc_module.o /441/pdinda/tcc/tcc-0.9.26/module/tcc_module.c

KERNEL_CFLAGS =   -D__KERNEL__ -I/usr/src/kernels/2.6.38.6-26.rc1.fc15.x86_64/include -I/usr/src/kernels/2.6.38.6-26.rc1.fc15.x86_64/arch/x86/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -m64 -mtune=generic -mno-red-zone -mcmodel=kernel -funit-at-a-time -maccumulate-outgoing-args -fstack-protector -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -Wframe-larger-than=2048 -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack

all: 
	(cd ..; make libtcc.a KERNEL=1 KERNEL_CFLAGS='$(KERNEL_CFLAGS)')
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	(cd ..; make clean)

flags:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) script 'SCRIPT=@echo $$(CFLAGS))'



