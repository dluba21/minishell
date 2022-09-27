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
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "get_next_line/get_next_line.h"

typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler);

typedef struct sigaction t_sig;
//# include <>

//typedef struct s_sig
//{
//
//}				t_sig;


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
	int				key;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef	struct s_cmd t_cmd;
typedef	struct s_vars t_vars;
typedef int	(* t_builtin_ptr)(t_vars *vars, t_cmd *cmd);
//
//typedef struct s_llist //logic list для пайпов и бонусов мб
//{
//	
//}


struct s_vars
{
	
	
	char	**root_paths; //массив строк с путями к execve (мб убрать куда-то?)
	char	**envp; //массив скопированный переменныъ окружения (будет подаваться  execve)
	struct s_list **envp_lst; //список для переменных окружения (легко изменять, в отличие от массива)
	int		*pid_array; //массив пидов для закрытия их, мб запихать вотдельную структуру чисто для executor?
	char	envp_f; //флаг на то,изменилась ли переменная окружения и нужно ли пересоздавать массив
	char	exit_f; //флаг что нужен выход из ф-ции
	int		status; //мб убрать так как можно переменную отдельную создать в функции executor
	int		exit_status; //
	char	*term_pid; //пид терминала для $$
	struct sigaction sig;
	int		stdin_fd;
	int		stdout_fd;
	char	**reserved_words; //массив с названиями функций билтинов
//	t_builtin_ptr builtin_array[7]; //массив с указателяит на функции билтинов
//	int	(* t_builtin_ptr)(t_vars *vars, t_cmd *cmd);
	t_builtin_ptr *builtin_ptr_arr;

};

struct s_cmd
{
	struct s_list	**files_in; //файлы для считывания
	struct s_list	**files_out; // файлы для вывода
	struct s_list	**files_heredoc; //строки-разделители (нахуя надо, если последний только разделитель нужен?)
	struct s_list	**args_lst; //первый аргумент - сама программа(команда)!!! дальше аргументы команды
	char			**args_array; // первый аргумент - название команды, остальное - аргументы к команде
	struct s_vars	*vars; //отсюда переменные окруженя нужно вытащить
	int		in_fd;
	int		out_fd;
	int		len_args;
	
};

//typedef struct s_cmd_ // структура для билтов
//{
//	char	**args; // обьекты воздействия
//	int		len_args; // колл-во обьектов
//	int		out; // значение вывода
//}			t_cmd_;



//typedef struct files
//{
//	int		in_fd;
//	int		out_fd
//	int		i;
//	int		cmd_len;
//	int		heredoc_f;
//}				t_files;

//функции иницализации
int		envp_init(t_vars *vars, char **envp); //инициализирует и копирует в массив char **envp массив строк с аргумента main(..., char **env)
t_list	**lst_env_copy(char **envp); //копирует char **env в список
int		vars_initializing(t_vars *vars, char **envp); //делает верхние дев функции и зануляет остальное в структуре vars

//функции двусвязных списков
int	lst_clear(t_list **lst); //фришит весь список
t_list	*lst_elem_new(void	*value, int key); //создает элемент списка с ключом и значением
t_list	*lst_elem_copy(t_list *elem); //копирует элемент списка и его ключ со значением (leaks), указатели prev и next равны NULL
int		lst_len(t_list **lst);
void	lst_push_back(t_list **lst, t_list *new_node);
void	lst_push_front(t_list **lst, t_list *new_node);
t_list	**lst_new(int n);
int		lst_elem_print(t_list *node);
int		lst_print(t_list **lst);
int		lst_elem_print_token(t_list *node);
int		lst_print_tokens(t_list **lst);
t_list	*lst_get_last(t_list **lst);
t_list	*lst_get_first(t_list *tale);
int		lst_elem_free(t_list *node);
char	**convert_lst_to_str(t_list **lst);


//функции со списком команд
void	llst_cmd_elem_print(t_list *llst_elem);  //вывести файлы и аргументы конкретной команды
void	llst_cmd_n_elem_print(t_list **llst, int n); //вывести файлы и аргументы итой команды
void	llst_cmd_print(t_list **llst); //вывести файлы и аргументы всех команд


//функции со строками и остальные
char	*ft_readline(void);
int		ft_strlen(char *str);
void	free_big_str(char **big_str);
char	**big_string_copy(char **big_str);
char	*ft_strdup(char *str);
int ft_isspace(char c);
int	ft_strcmp(char *s1, char *s2);
int pipe_len_and_check(char *bash_str);
int ft_strchr(char *str, char *c);
char *quote_str_trim(char *bash_str, char *sym_arr);
t_list **bash_args_lst_lexer(char *bash_str, t_vars *vars);
t_list **bash_args_lst_parser(t_list **lst);
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
char	*ft_strcpy(char *src);
void	*ft_memcpy(void *src_0, int n); //вставить в lst_elem_cpy
void	is_null(void *ptr); //не ннужна потом
int		big_str_len(char **big_str);
int		ft_perror(char *str); //возвращает int = 0 в отличие от perror, поэтому можно писать return(ft_perror)
int		ft_putstr_fd(char *s, int fd);



//функции для сборки пути для execve
int	root_paths_init(t_vars *vars); //создает массив строк со всеми путями из переменной окружения PATH, уже сделав сплит по ':', (надо зачиситить от ликов потом, это вызвать в дочернем процессе)
char	*compose_cmd_args(t_cmd *cmd_elem, char **root_paths); //создает путь до команды используя root_paths




//создает логический список - это список llst, элементы которого - структура команд (t_cmd *), он лежит в head_llst->val; в cmd есть списки t_list ** с файлами на ввод,вывод, разделители heredoc, список с командой и аргументами (то есть голова последнего списка - сама команда, остальное - аргументы)
t_list	*llst_elem_new(t_list *head_lst); //составная функция внутри llst_elem - она добваляет новый элемент в llst и одновременно меняет голову в первоначальном списке токенов lst
t_list	**llst_new(t_list	**lst); //список списков команд и пайпов
t_list	*cmd_parser(t_list *head_lst, t_list *llst_elem, t_cmd *cmd);
t_list	*cmd_init(void);


//раскрытие доллара
int		dollar_parser(t_list **lst, t_vars *vars);
char	*dollar_expansion(char *str, t_vars *vars);
void	not_dollar_part(char **str, char **ret_str);
void	expand_dollar_var(char **str, char **ret_str, t_vars *vars);
char	*find_env_var(char *str, char **env);
void	env_var_trimmer(char *env_elem, char **buffer);
char	*env_key_trimmer(char *env_elem);


//executor часть
int	exec_cmd(t_list **llst, t_vars *vars);
int	root_paths_init(t_vars *vars);
//void	heredoc_parser(t_list **files);
//void	heredoc_parser(t_list **files, int *in_fd, int heredoc_f);


//открытие файлов и пайпы
int	open_heredocs(t_list *llst_elem);
int	**open_pipes(int len);
int	open_files(t_cmd *cmd, int **pipe_array, int i, int n);
void	close_all_pipes(int **pipe_array);
void	delete_heredocs(t_list **files_in);
int		open_files_out(t_list **files_out);

//лишние функции
void pipe_print(int **big_array);

//билтины
int	ft_cd(t_vars *vars, t_cmd *cmd);
int	ft_echo(t_vars *vars, t_cmd *cmd);
int	ft_env(t_vars *vars, t_cmd *cmd);
int	ft_exit(t_vars *vars, t_cmd *cmd);
int	ft_export(t_vars *vars, t_cmd *cmd);
int	ft_pwd(t_vars *vars, t_cmd *cmd);
int	ft_unset(t_vars *vars, t_cmd *cmd);


//cигналы
void	sig_init(void);

#endif


