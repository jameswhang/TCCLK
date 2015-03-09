#include <stdio.h>
#include <stdlib.h>
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
    exit(-1);
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
    fgets(buffer, fd, 1000);
    return 1;
}

// check_flags
// returns index of argv if the target flag is inside the flags given by the user
// returns -1 if flag is not found
int check_flags(int argc, char * argv[], char target_flag) {
    int i;
    for(i = 0; i < argc; i++) {
        if(argv[i][0] == '-' && argv[i][1] == target_flag)
            return i;
    }
    return -1;
}

// get_user_code
// dynamically reallocs the buffer if user puts in more than 1000 characters long code
char * get_user_code_input(char * buf, int maxlen) {
    int c = EOF;
    unsigned int i = 0;
    while ((c = getchar()) != EOF) {
        buf[i++] = (char)c;
        if (i == maxlen) {
            maxlen = i + maxlen;
            buf = realloc(buf, maxlen);
        }
    }
    buf[i] = '\0';
    return buf;
}

char * get_user_code_file(char * buf, FILE * fs, int maxlen) {
    int c = EOF;
    unsigned int i = 0; 
    while ((c = fgetc(fs)) != EOF) {
        buf[i++] = (char)c;
        if (i == maxlen) {
            maxlen = i + maxlen;
            buf = realloc(buf, maxlen);
        }
    }
    buf[i] = '\0';
    return buf;
}

// main
int main(int argc, char * argv[])
{
    int max_buf_len = 1000;
    int dev_fd;
    int i;
    int flag_len = 0;
    char user_flags[5];
    FILE * input_fd;
    FILE * output_fd;
    char * user_program = malloc(max_buf_len);
    char * output_buffer = malloc(max_buf_len);
    
    if (argc < 2) {
        wrong_usage();
    } else if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_flags(); // print help page
        return 0;
    } else {
        int file_index = check_flags(argc, argv, 'f');
        if (file_index < 0) { // read input directly from user
            printf("Type your code below:\n");
            user_program = get_user_code_input(user_program, max_buf_len);
            //write(dev_fd, user_program, sizeof(user_program));
        } else { // read input from file
            input_fd = fopen(argv[file_index+1], "r");
            if (input_fd < 0) {
                print_error_and_quit('f');
            } else {
                user_program = get_user_code_file(user_program, input_fd, max_buf_len);
                fclose(input_fd);
            }
        }

        // TODO:
        // WRITE / READ FROM KERNEL MODULE 

        int output_index = check_flags(argc, argv, 'o');
        if (output_index < 0) { // print directly to the console
            printf("%s\n", output_buffer);
        } else { // writes to an output file whose path is specified by user
            output_fd = fopen(argv[ouput_index+1], "w");
            fputs(output_buffer, output_fd);
            fclose(output_fd);
        }
    }
    return 0;
}
