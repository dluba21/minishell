#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

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
char	*ft_strdup(const char *s); // читать в utils_builtin.c
int     ft_strncmp(const char *s1, const char *s2, size_t n); // читать в utils_builtin.c
int     ft_isdigit(int c); // читать в utils_builtin.c
int		ft_unstr(char *var, char *key); // функция для проверки совпадений в ft_unstr и ft_export
void	ft_putendl_fd(char *s, int fd); // читать в utils_builtin.c
char	**ft_free_mat(char **mat);
void	ft_free_line(char **line);
char	*ft_strjoin(char const *s1, char const *s2); // из либы
char	*ft_strchr(const char *string, int symbol); // из либы
char	*ft_var_find(char *var, char **ev);
char	*ft_find_env(char *key, char **ev);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len); // из либы

# endif