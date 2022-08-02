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
#define NILL 0
#define WORD 1
#define FIELD 2
#define EXP_FIELD 3
#define REDIR_OUT 4
#define REDIR_IN 5
#define REDIR_APPEND 6
#define REDIR_HEREDOC 7
#define PIPE 8
#define SPACEX 9
#define TRUNC 10
#define APPEND 11

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
	char *reserved_words[8]; //массив с названиями функций билтинов
//	t_builtin_ptr builtin_array[7]; //массив с указателяит на функции билтинов
	
	char	**root_paths; //массив строк с путями к execve (мб убрать куда-то?)
	char	**envp; //массив скопированный переменныъ окружения (будет подаваться  execve)
	struct s_list **envp_lst; //список для переменных окружения (легко изменять, в отличие от массива)
	int		*pid_array; //массив пидов для закрытия их, мб запихать вотдельную структуру чисто для executor?
	char	envp_f; //флаг на то,изменилась ли переменная окружения и нужно ли пересоздавать массив
	char	exit_f; //флаг что нужен выход из ф-ции
	int		status; //мб убрать так как можно переменную отдельную создать в функции executor
	int		exit_status; //
	char	*term_pid; //пид терминала для $$

}		t_vars;

typedef	struct s_cmd
{
	struct s_list	**files_in; //файлы для считывания
	struct s_list	**files_out; // файлы для вывода
	struct s_list	**files_heredoc; //строки-разделители (нахуя?)
	struct s_list	**args_lst; //первый аргумент - сама программа(команда)!!! дальше аргументы команды
	char			**args_array; // первый аргумент - название команды, остальное - аргументы
	struct s_vars	*vars; //отсюда переменные окруженя нужно вытащить
	
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
t_list **bash_args_lst_lexer(char *bash_str, t_vars *vars);
t_list **bash_args_lst_parser(t_list **lst);
//int ft_strchr(char *str, char *c);
//int	ft_strncmp(char *s1, char *s2, int n);
//int		ft_strcmp_n(const char *str1, const char *str2, size_t n);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		find_spec_char(char *str);
char	*ft_strset(int n);
void	big_str_print(char **big_str);
int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(char *s1, char *s2, int n);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);


int	root_paths_init(t_vars *vars); //создает массив строк с путями к командам, надо зачиситить от ликов потом, это вызвать в дочернем процессе
char	*compose_cmd_args(t_cmd *cmd_elem, char **root_paths);



void	is_null(void *ptr);
void	*ft_memcpy(void *src_0, int n); //вставить в lst_elem_cpy
void	llst_cmd_elem_print(t_list *llst_elem);
void	llst_cmd_n_elem_print(t_list **llst, int n);
void	llst_cmd_print(t_list **llst);


t_list *lst_get_last(t_list **lst);
t_list *lst_get_first(t_list *tale);
int		lst_elem_free(t_list *node);



//t_list	**llst_elem_new(t_list **lst);
//t_list	**llst_elem_new(t_list	*head_lst);
t_list	*llst_elem_new(t_list *head_lst);
t_list	**llst_new(t_list	**lst); //список списков команд и пайпов

t_list	*cmd_parser(t_list *head_lst, t_list *llst_elem, t_cmd *cmd);
t_list	*cmd_init(void);



int		dollar_parser(t_list **lst, t_vars *vars);
char	*dollar_expansion(char *str, t_vars *vars);
void	not_dollar_part(char **str, char **ret_str);
void	expand_dollar_var(char **str, char **ret_str, t_vars *vars);
char	*find_env_var(char *str, char **env);

void	env_var_trimmer(char *env_elem, char **buffer);
char	*env_key_trimmer(char *env_elem);

#endif


