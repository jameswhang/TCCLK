#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

// print_flags:
// prints off the flag information
void print_flags()
{
    printf("Flags:\n");
    printf("\t-f\tRead from file [file_path]\n");
    printf("\t-u\tRead directly from stdin \n");
}

// wrong_usage:
// prints off the correct usage and quits the program
void wrong_usage()
{
    printf("Usage: tcc_service flags parameter\n");
    printf("tcc_service -h for help\n");
    exit(-1);
}

// print_error_and_quit:
// prints off the appropriate error message and quits
void print_error_and_quit(char mode)
{
    printf("tcc_service : ");
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
    fgets(buffer, 1000, fd);
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
    unsigned int i = 14;
    strcpy(buf, "int main() {\n");
    while ((c = getchar()) != EOF) {
        buf[i++] = (char)c;
        if (i == maxlen) {
            maxlen = i + maxlen;
            buf = realloc(buf, maxlen);
        }
    }
    buf[i] = '\0';
    strcpy(buf+i+1, "return 0;\n}\n");
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

    dev_fd = open("/dev/tcc_dev", O_RDWR);

    if (dev_fd < 0) {
        printf("Couldn't open the device\n");
        exit(-1);
    }
    
    if (argc < 2) {
        wrong_usage();
    } else if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_flags(); // print help page
        return 0;
    } else {
        int file_index = check_flags(argc, argv, 'u');
        if (file_index > 0) { // read input directly from user
            printf("Type your code below:\n");
            user_program = get_user_code_input(user_program, max_buf_len);
        } else {
	    file_index = check_flags(argc, argv, 'f'); 
            if (file_index > 0) { // read input from file
                input_fd = fopen(argv[file_index+1], "r");
                if (input_fd < 0) {
                    print_error_and_quit('f');
                } else {
                    user_program = get_user_code_file(user_program, input_fd, max_buf_len);
                    fclose(input_fd);
                }
            } else { 
	        wrong_usage();
	    }
	}
	// Write to the device
	// This does the compilation and execution at the same time
        write(dev_fd, user_program, sizeof(user_program));
    }
    return 0;
}
