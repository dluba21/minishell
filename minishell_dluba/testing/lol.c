#include <stdio.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "../get_next_line/get_next_line.h"

int main()
{
	printf("%d\n", getpid());
	int fd = open("kek_file", O_RDWR | O_CREAT, 0644);
	
	char *line = get_next_line(0);
	write(fd, line, strlen(line));
	printf("%s\n", get_next_line(fd));
//	unlink("kek_file");
//	sleep(100);
}
