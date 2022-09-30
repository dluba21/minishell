////#include "minishell.h"
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
//typedef	struct s_vars
//{
//	char *reserved_words[8]; //массив с названиями функций билтинов
////	t_builtin_ptr builtin_array[7]; //массив с указателяит на функции билтинов
//
//	char **big_str;
//;
//
//	char	**root_paths; //массив строк с путями к execve (мб убрать куда-то?)
//	char	**envp; //массив скопированный переменныъ окружения (будет подаваться  execve)
//	struct s_list **envp_lst; //список для переменных окружения (легко изменять, в отличие от массива)
//	int		*pid_array; //массив пидов для закрытия их, мб запихать вотдельную структуру чисто для executor?
//	char	envp_f; //флаг на то,изменилась ли переменная окружения и нужно ли пересоздавать массив
//	char	exit_f; //флаг что нужен выход из ф-ции
//	int		status; //мб убрать так как можно переменную отдельную создать в функции executor
//	int		exit_status; //
//	char	*term_pid; //пид терминала для $$
//	struct sigaction sig;
//
//}		t_vars;
//
//typedef	struct s_cmd
//{
//	struct s_list	**files_in; //файлы для считывания
//	struct s_list	**files_out; // файлы для вывода
//	struct s_list	**files_heredoc; //строки-разделители (нахуя надо, если последний только разделитель нужен?)
//	struct s_list	**args_lst; //первый аргумент - сама программа(команда)!!! дальше аргументы команды
//	char			**args_array; // первый аргумент - название команды, остальное - аргументы к команде
//	struct s_vars	*vars; //отсюда переменные окруженя нужно вытащить
//
//}				t_cmd;
//
////
////char (*pFun)(int)
//
//int	ft_strcmp(char *s1, char *s2) //сравнивает строки
//{
//	if (!s1 || !s2)
//		return (-1);
//	while (*s1 == *s2 && *s1++ && *s2++)
//		;
//	return (*s1 - *s2);
//}
//
//int a(t_vars *vars, t_cmd *cmd)
//{
//	printf("kek!\n");
//	return (0);
//}
//int b(t_vars *vars, t_cmd *cmd)
//{
//	printf("lol!\n");
//	return (0);
//}
//
//typedef int	(* t_builtin_ptr)(t_vars *vars, t_cmd *cmd);
//
//
//int main()
//{
//	char	*reserved_words[8];
//	t_builtin_ptr aboba[8];
//	t_cmd *cmd;
//	t_vars *vars;
//
////	reserved_words[0] = "lol";
////	reserved_words[1] = "kek";
//	char *values[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
//	vars->reserved_words[0] = "ft_echo";
//	vars->reserved_words[1] = "ft_cd";
//	vars->reserved_words[2] = "ft_pwd";
//	vars->reserved_words[3] = "ft_export";
//	vars->reserved_words[4] = "ft_unset";
//	vars->reserved_words[5] = "ft_env";
//	vars->reserved_words[6] = "ft_exit";
//	vars->reserved_words[7] = "ft_echo";
////	printf("%s", typeof(vars->big_str));
////	reserved_words
////	aboba = (t_builtin_ptr *)malloc(sizeof(t_builtin_ptr) * 8);
//
//	aboba[0] = a;
//
//	printf("%d", ft_strcmp("~", "aboba"));
////	aboba[0](vars, cmd);
////	printf("%s\n", values[3]);
////	readline("aboba");
////	rl_replace_line("", 0);
////	rl_on_new_line();
////	rl_redisplay();
////	printf("{%s}\n", 	readline("aboba: "));
//	return (0);
//}
