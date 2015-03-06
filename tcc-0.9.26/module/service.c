#include <stdio.h>
#include <string.h>
#include <fcntl.h>

// print_flags:
// prints off the flag information
void print_flags()
{
    printf("Flags:\n");
    printf("\t-e\tExecute\n");
    printf("\t-f\tRead from file [file_path]\n");
    printf("\t-o\tOutput result to file [file_path]\n");
}

// wrong_usage:
// prints off the correct usage and quits the program
void wrong_usage()
{
    printf("Usage: tcc_kernel_run flags parameter\n");
    printf("tcc_kernel_run -h for help\n");
}

// print_error_and_quit:
// prints off the appropriate error message and quits
void print_error_and_quit(char mode)
{
    printf("tcc_kernel_run : ");
    switch(mode)
    {
        case 'd':
            {
                printf("Failed to open the device. Quitting.\n");
                break;
            }
        case 'f':
            {
                printf("Failed to open file. Quitting.\n");
                break;
            }
    }
    exit(-1);
}

// read_from_file
int read_from_file(int fd, char * buffer)
{
    while(fscanf(fd, )) {
        
    }
}

// main
int main(int argc, char * argv[])
{
    int dev_fd;
    char * user_program;
    
    // Open the tcc device
    dev_fd = open("/dev/tcc_mod", O_RDWR);
    if (dev_fd < 0) {
        print_error_and_quit('d'); 
    }

    if (argc < 2) {
        wrong_usage();
        exit(-1);
    } else if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_flags(); // print help page
    } else if (argc == 3) {
        char mode = argv[1][1];
        switch(mode)
        {
            case 'f':
                {
                    int file_fd = open(argv[2]);
                    if (fd < 0) 
                        print_error_and_quit('f');
                    else {
                        read_from_file(file_fd, user_program);
                        /// TODO: make file handler
                    }
                }
        }
    }
    return 0;
}
