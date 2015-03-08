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
int read_from_file(FILE * fd, char * buffer)
{
    if(fgets(buffer, fd, 1000) != NULL) 
        return 1;
    else
        return 0;
}

// main
int main(int argc, char * argv[])
{
    int dev_fd;
    FILE * input_fd;
    FILE * output_fd;
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
        char input_mode = argv[1][1];
        char output_mode = argv[3][1];
        switch(input_mode)
        {
            case 'f': // read input from file
                {
                    input_fd = fopen(argv[2], "r");
                    if (input_fd < 0) 
                        print_error_and_quit('f');
                    else {
                        if (read_from_file(input_fd, user_program)) {
                            write(fd, user_program, sizeof(user_program));
                        } else {
                            print_error_and_quit('f');
                        }
                    }
                }
            case 'u': // read input directly from user
                {
                    printf("Your code below:\n");
                    scanf("%s", user_program);
                    write(fd, user_program, sizeof(user_program));
                }
        }
        fclose(input_fd);
        read(fd, output_buffer, sizeof(output_buffer));
        if (output_mode == 'o') { // output to a file
            output_fd = fopen(argv[4], "w");
            fputs(output_buffer, output_fd);
        } else {
            printf("%s", output_buffer);
        }
        fclose(output_fd);
    }
    return 0;
}
