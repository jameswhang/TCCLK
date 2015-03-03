#include <stdio.h>
#include <fcntl.h>
int main ()
{
	int lock, i,fd;
	char ch, write_buf[100], read_buf[100];
	fd = open("/dev/char_dev", O_RDWR);
	if (fd == -1)
	{
		printf("Error in opening file \n");
		exit(-1);
	}
	lock = 1;
	while(lock != 'q')
	{
		printf ("Press (w,r,q) w: write to mem; r-read from mem; q: Exit: ");
		scanf ("%c", &ch);

		switch (ch) 
		{
			case 'w':
				printf ("Enter the data to be written into device: ");
				scanf (" %[^\n]", write_buf);
				write(fd, write_buf, sizeof(write_buf));
				break;

			case 'r':
				read(fd, read_buf, sizeof(read_buf));
				printf ("The data in the device is: %s\n", read_buf);
				break;
			case 'q':
				lock = 'q';
				printf ("\n Good bye...\n");
				break;

			default:
				printf("Wrong choice \n");
				break;
		} // switch
	} // while
	close(fd);
	return 0;
} // main
