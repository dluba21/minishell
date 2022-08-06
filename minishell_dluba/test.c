//////#include <conio.h>
//# include <stdio.h>
//# include <unistd.h>
//# include <stdlib.h>
//# include <signal.h>
//# include <fcntl.h>
//# include <string.h> //ubrat'
//# include <readline/readline.h>
//# include <readline/history.h>
//# include <sys/types.h>
//# include <sys/wait.h>
//# include <errno.h>
//# include <string.h>
////
//////enum Token
//////{
//////	SYMBOL,         //0
//////	NUMBER,         //1
//////	EXPRESSION, //0
//////	OPERATOR,       //1
//////	UNDEFINED,       //2
//////	D,
//////	W,
//////	E,
//////	T,
//////	Y,
//////	U,
//////	I,
//////	O,
//////	G,
//////	P,
//////	L,
//////	N,
//////	B,
//////	V,
//////	J
//////};
//////
////int main()
////{
////	enum Token a, b, c, d, e;
////	a = SYMBOL;
////	b = NUMBER;
////	c = EXPRESSION;
////	d = OPERATOR;
////	e = UNDEFINED;
////	printf("a = %d\n", a);
////	printf("b = %d\n", b);
////	printf("c = %d\n", c);
////	printf("d = %d\n", d);
////	printf("e = %d\n", e);
////	printf("%d", sizeof(enum Token));
////}
//int ft_strlen(char *str)
//{
//	int	i;
//
//	i = 0;
//	if (!str)
//		return (-1);
//	while (str[i])
//		i++;
//	return (i);
//}
//
//int	ft_putstr_fd(char *s, int fd)
//{
//	if (s)
//		return (write(fd, s, ft_strlen(s)));
//}
//
//
//
//int main()
//{
//	char *a;
//	char *b = NULL;
////	if (!b || *a)
//	int c;
//	int d;
////	printf("str = {%d}", c);
//	printf("%d\n", getpid());
//	close(1);
//	close(0);
//	close(2);
//	int fd = open ("kek", O_TRUNC);
//	dup2(3, 0);
//	sleep(1000);
////	int pid = fork();
////	if (!pid)
////	{
//////		printf("%d", getpid());
//////		sleep(1);
//////		close(0);
//////		close(1);
//////				ft_putstr_fd("kek", 1);
//////		printf("kek");
////		sleep(1000);
//////		while (1)
//////		{
////////			scanf("%d", &c);
//////			printf("%d\n", c);
//////		}
////
////	}
////	if (pid != 0)
////	{
////
////
//////		errno = -1;
////
//////		perror("asfsaf");
//////		printf("%d\n", pid);
////		waitpid(-1, &d, 0);
////	}
//
////	int fd = open("asffsafa", O_RDONLY, 0644);
////	printf("fd = %d\n", fd);
//////	printf("%s", strerror(errno));
////	errno = 1;
////	perror("error");
////	if (b || 1)
////		printf("ok!\n");
//}
////if (head->key == PIPE)
////{
////	if (!head->prev || (head->prev && head->prev->key == PIPE))
////		return (1);
////	if (!head->next || (head->next && head->next->key == PIPE))
////		return (1);
////}
////if (head->key == REDIR_APPEND && (!head->next || head->next->key != WORD)
////{
////	if (!head->prev || (head->prev && head->prev->key == PIPE))
////		return (1);
////	if (!head->next || (head->next && head->next->key == PIPE))
////		return (1);
////}
////head = head->next;
