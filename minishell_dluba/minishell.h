#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h> //ubrat'
# include <readline/readline.h>
# include <readline/history.h>
//# include <>



//typedef struct s_vars //в чем ошибка?
//{
//	void			*val;
//	struct s_list	*next:
//}				t_vars;
//int (* t_builtin_ptr)(struct s_list *, struct s_vars *); //????? как исправить?

#define WORD 1
#define FIELD 2
#define EXP_FIELD 3
#define REDIR_OUT 4
#define REDIR_IN 5
#define REDIR_APPEND 6
#define REDIR_HEREDOC 7
#define PIPE 8
#define SPACE 9

//2) WORD  то есть слово без спецсимволов внутри
//3) FIELD - (‘ ’)поле, которое надо будет потом раскрыть, например, ‘ ’ - обычные кавычки
//Все виды токенов запихать в дефайны и преобразовать в числа 1, 2, 3...
//4) EXP_FIELD  - (“ ”)поле в кавычках “ “, надо раскрыть будет
//5) REDIR_OUT - аутфайл >
//6) REDIR_IN - инфайл <
//7) REDIR_APPEND - аутфайл добавить >>
//8) REDIR_HEREDOC - ХЕРдок <<
//9) PIPE -  |

typedef struct s_list
{
	void			*val;
//	void			*key;
	int				key;
	struct s_list	*next;
}					t_list;


typedef	struct s_vars
{
	char *reserved_words[8];
//	t_builtin_ptr builtin_array[7];
	
	
	char			**envp;
	struct s_list **envp_lst;
	char	envp_f;
	char	exit_f;
	int		status;

}		t_vars;


int envp_init(t_vars *vars, char **envp);
int	vars_initializing(t_vars *vars, char **envp);

int	lst_clear(t_list **lst);
t_list	*lst_new_elem(void	*value, int key);
int big_str_len(char **big_str);
int lst_len(t_list **lst);
void lst_push_back(t_list **lst, t_list *new_node);
t_list **lst_new(int n);
t_list	**lst_env_copy(char **envp);
int	lst_print(t_list **lst);
int	lst_elem_print(t_list *node);

int ft_strlen(char *str);
void free_big_str(char **big_str);
char **big_string_copy(char **big_str);
int envp_init(t_vars *vars, char **envp);
int	vars_initializing(t_vars *vars, char **envp);

char	*ft_strdup(char *str);
int ft_isspace(char c);
int	ft_strcmp(char *s1, char *s2);
int pipe_len_and_check(char *bash_str);
int ft_strchr(char *str, char *c);
char *quote_str_trim(char *bash_str, char *sym_arr);
t_list **bash_args_first_lst_init(char *bash_str);
//int ft_strchr(char *str, char *c);
//int	ft_strcmp_n(char *s1, char *s2, int n);
int	ft_strcmp_n(const char *str1, const char *str2, size_t n);


#endif
