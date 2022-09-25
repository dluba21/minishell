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
//# include "get_next_line/get_next_line.h"
//# include <readline/readline.h>
////#include "minishell.h"
////
//////enum Token
//////{
//////	SYMBOL,         //0
//////	NUMBER,         //1
//////	EXPRESSION, //0
//////	OPERATOR,       //1
//////	UNDEFINED,       //2
//////	D,
////////	W,
////////	E,
////////	T,
////////	Y,
////////	U,
////////	I,
////////	O,
////////	G,
////////	P,
////////	L,
////////	N,
////////	B,
////////	V,
////////	J
////////};
////////
//////int main()
//////{
//////	enum Token a, b, c, d, e;
//////	a = SYMBOL;
//////	b = NUMBER;
//////	c = EXPRESSION;
//////	d = OPERATOR;
//////	e = UNDEFINED;
//////	printf("a = %d\n", a);
//////	printf("b = %d\n", b);
//////	printf("c = %d\n", c);
//////	printf("d = %d\n", d);
//////	printf("e = %d\n", e);
//////	printf("%d", sizeof(enum Token));
//////}
////int ft_strlen(char *str)
////{
////	int	i;
////
////	i = 0;
////	if (!str)
////		return (-1);
////	while (str[i])
////		i++;
////	return (i);
////}
////
////int	ft_putstr_fd(char *s, int fd)
////{
////	if (s)
////		return (write(fd, s, ft_strlen(s)));
////}
////
//
//
//int main()
//{
////	(void)sig;
////	if (write(1, "\n", 1) == -1)
////		return ;
//	
////	readline("aboba");
////	rl_replace_line("", 0);
////	rl_on_new_line();
////	rl_redisplay();
//	printf("{%s}\n", 	readline("aboba: "));
//	return (0);
//}
