#ifndef MINISHELL1_H
# define MINISHELL1_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../minishell.h"

//typedef struct s_cmd_ // структура для билтов
//{
//    char	**args; // обьекты воздействия
//    int		len_args; // колл-во обьектов
//	int		out; // значение вывода
//}	t_cmd_;

void	ft_putstr_fd_(char *s, int fd); // читать в utils_builtin.c
int		ft_strcmp_(char *s1, char *s2); // читать в utils_builtin.c
size_t	ft_strlen_(const char *s); // читать в utils_builtin.c
char	*ft_strdup_(const char *s); // читать в utils_builtin.c
int     ft_strncmp_(const char *s1, const char *s2, size_t n); // читать в utils_builtin.c
int     ft_isdigit_(int c); // читать в utils_builtin.c
int		ft_unstr(char *var, char *key); // функция для проверки совпадений в ft_unstr и ft_export
void	ft_putendl_fd_(char *s, int fd); // читать в utils_builtin.c
char	**ft_free_mat(char **mat);
void	ft_free_line(char **line);
char	*ft_strjoin_(char const *s1, char const *s2); // из либы
char	*ft_strchr_(const char *string, int symbol); // из либы
char	*ft_var_find(char *var, char **ev);
char	*ft_find_env(char *key, char **ev);
char	*ft_strnstr_(const char *haystack, const char *needle, size_t len); // из либы
char	**change_value(char *var, char **ev);
char	**add_value(char *var, char **ev);
int		ft_atoi(const char *str);

# endif
//(t_vars *vars, t_cmd *cmd)
