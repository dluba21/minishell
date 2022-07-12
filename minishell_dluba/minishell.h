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

//#define CMD 11

//2) WORD  то есть слово без спецсимволов внутри
//3) FIELD - (‘ ’)поле, которое надо будет потом раскрыть, например, ‘ ’ - обычные кавычки
//Все виды токенов запихать в дефайны и преобразовать в числа 1, 2, 3...
//4) EXP_FIELD  - (“ ”)поле в кавычках “ “, надо раскрыть будет
//5) REDIR_OUT - аутфайл >
//6) REDIR_IN - инфайл <
//7) REDIR_APPEND - аутфайл добавить >>
//8) REDIR_HEREDOC - ХЕРдок <<
//9) PIPE -  |

//typedef struct s_list
//{
//	void			*val;
////	void			*key;
//	int				key;
//	struct s_list	*next;
//}					t_list;

typedef struct s_list
{
	void			*val;
//	void			*key;
	int				key;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;


//
//typedef struct s_llist //logic list для пайпов и бонусов мб
//{
//	
//}

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

typedef	struct s_cmd
{
	struct s_list	**files_in;
	struct s_list	**files_out;
	struct s_list	**files_heredoc;
	char			**cmd_args;
	struct s_vars	*vars; //здесь переменные окружения
	
}				t_cmd;

int envp_init(t_vars *vars, char **envp);
int	vars_initializing(t_vars *vars, char **envp);

int	lst_clear(t_list **lst);
t_list	*lst_elem_new(void	*value, int key); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
t_list	*lst_elem_copy(t_list *elem);
int big_str_len(char **big_str);
int lst_len(t_list **lst);
void	lst_push_back(t_list **lst, t_list *new_node);
void	lst_push_front(t_list **lst, t_list *new_node);
t_list **lst_new(int n);
t_list	**lst_env_copy(char **envp);

int	lst_elem_print(t_list *node);
int	lst_print(t_list **lst);
int	lst_elem_print_token(t_list *node);
int	lst_print_tokens(t_list **lst);

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
t_list **bash_args_lst_lexer(char *bash_str);
t_list **bash_args_lst_parser(t_list **lst);
//int ft_strchr(char *str, char *c);
//int	ft_strcmp_n(char *s1, char *s2, int n);
int	ft_strcmp_n(const char *str1, const char *str2, size_t n);


t_list *lst_get_last(t_list **lst);
t_list *lst_get_first(t_list *tale);
int		lst_elem_free(t_list *node);



//t_list	**llst_elem_new(t_list **lst);
t_list	**llst_elem_new(t_list	*head_lst); 
t_list	**llst_new(t_list	**lst); //список списков команд и пайпов




#endif


