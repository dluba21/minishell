#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>

typedef struct s_cmd // структура для билтов 
{
    char	**args; // обьекты воздействия
    int		len_args; // колл-во обьектов
	int		out; // значение вывода
	int		in; // значение ввода
}	t_cmd;

void	ft_putstr_fd(char *s, int fd); // читать в utils_builtin.c
int		ft_strcmp(char *s1, char *s2); // читать в utils_builtin.c
size_t	ft_strlen(const char *s); // читать в utils_builtin.c

# endif