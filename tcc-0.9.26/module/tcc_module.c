#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/slab.h>

#include "../libtcc.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Northwestern University");
MODULE_DESCRIPTION("TCC_Module");


static char my_program[] =
"int fib(int n)\n"
"{\n"
"    if (n <= 2)\n"
"        return 1;\n"
"    else\n"
"        return fib(n-1) + fib(n-2);\n"
"}\n"
;


static int __init tcc_module_init(void)
{
    printk(KERN_INFO "TCC Module Inited\n");

    TCCState *s;
    int (*func)(int);

    printk("Starting tcc_new\n");

    s = tcc_new();
    if (!s) {
        printk("Could not create tcc state\n");
	return 0;
    }

#if 0
    /* if tcclib.h and libtcc1.a are not installed, where can we find them */
    if (argc == 2 && !memcmp(argv[1], "lib_path=",9))
        tcc_set_lib_path(s, argv[1]+9);

#endif

    printk("Starting tcc_set_output_type\n");

    /* MUST BE CALLED before any compilation */
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

    printk("Starting tcc_compile_string\n");

    if (tcc_compile_string(s, my_program) == -1) {
      printk("Cannot compile program!\n");
      return 0;
    }

#if 0
    /* as a test, we add a symbol that the compiled program can use.
       You may also open a dll with tcc_add_dll() and use symbols from that */
    tcc_add_symbol(s, "add", add);
#endif

    printk("Starting tcc_relocate\n");

    /* relocate the code */
    if (tcc_relocate(s, TCC_RELOCATE_AUTO) < 0) {
      printk("Cannot relocate program\n");
      return 0;
    }

    printk("Starting tcc_get_symbol\n");
    /* get entry symbol */

    Section *hs = s->hash;
    if (!hs) {
        printk("Cannot find the hash table\n");
        return 0;
    }
    ElfW(Sym) *sym;
    h = elf_hash("fib") % nbuckets;
    sym_index = ((int*)hs->data[2+h]);
    nbuckets = ((int*)hs->data)[0];
    while(sym_index != 0) {
        sym = &((ElfW(Sym) *)s->data)[sym_index];
        name1 = s->link->data + sym->st_name;
        printk("Symbol: %s", name1);
        sym_index = ((int*)hs->data)[2 + nbuckets + sym_index];
    }
    
    func = tcc_get_symbol(s, "fib");
    if (!func) {
      printk("Cannot find program...\n");
      return 0;
    }

    printk("Calling the code!\n");

    /* run the code */
    func(32);

    printk("Deleting state\n");

    /* delete the state */
    tcc_delete(s);


    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit tcc_module_deinit(void)
{
    printk(KERN_INFO "TCC Module Deinited\n");
}

void * tcc_kmalloc(size_t n)
{
  return kmalloc(n,GFP_ATOMIC);
}

void * tcc_krealloc(void *p, size_t n)
{
  return krealloc(p,n,GFP_ATOMIC);
}


module_init(tcc_module_init);
module_exit(tcc_module_deinit);
