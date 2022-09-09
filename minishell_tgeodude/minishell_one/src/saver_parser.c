//
//#include "minishell.h"
//
////t_list	**lst_elem_cmd_init(t_list **lst)
////{
////	t_list	**llist_elem;
////	t_list	*head_lst;
////	t_list	*head_llst_elem;
////
////
////	if (!lst)
////		return (NULL);
////	head_lst = *lst;
////	if (!head_lst)
////		return (NULL);
////	llist_elem = lst_new(0);
////	*llist_elem = head_lst; //сдвигаем вперед список и предыдущий элемент в нулл
////	while (head_lst && head_lst->key != PIPE)
////		head_lst = head_lst->next;
////	if (!head_lst) //конец списка старого, то есть заканчивается все
////		return (llist_elem);
////	head_lst->prev->next = NULL; //обрубаем список-элемент по пайпу
////	head_lst = head_lst->next;
////	return (llist_elem);
////}
//
////t_list	*llst_elem_new(t_list *head_lst)
//
//
//t_list	*llst_elem_new(t_list *head_lst)
//{
////	t_list	**llist_elem;
//	t_list	*llist_elem;
//	t_list	*head_llst_elem;
//
//	if (!head_lst)
//		return (NULL);
////	llist_elem = lst_new(0);
//	llist_elem = head_lst; // сохраняем голову
//	while (head_lst && head_lst->key != PIPE)
//		head_lst = head_lst->next;
//	if (!head_lst) //конец списка старого, то есть заканчивается все
//		return (llist_elem);
//	head_lst->prev->next = NULL; //обрубаем список-элемент по пайпу
//	head_lst = head_lst->next;
//	return (llist_elem);
//}
//
//
////
//t_list	**llst_new(t_list	**lst) //список списков команд и пайпов
//{
//	t_list	**llst;
//	t_list	**llist_elem;
//	t_list	*head_lst;
//	t_list	*head_llst;
//	t_list	*tmp;
////	if (check_pipes == -1)
////		exit(printf("pipe syntax error\n"));
//	head_lst = *lst;
//	
//	if (!head_lst)
//		return (NULL);
//	llst = lst_new(1);
//	head_llst = *llst;
//	while (head_lst)
//	{
//		tmp = head_lst; //сохраняю голову
//		while (head_lst && head_lst->key != PIPE)
//			head_lst = head_lst->next;
//		head_llst->val = llst_elem_new(tmp);
//		if (head_lst) //если не конец еще и встретился пайп
//		{
//			head_lst = head_lst->next; //пропускаем пайп
//			head_llst = head_llst->next;
//		}
//	}
//	//мб head_lst сразу ноль(проверка на один случай)
////	head_llst->next = NULL;
//	return (llst);
//}
//
//
//
////int	check_pipes(t_list **lst)
////{
////	t_list	*head_old_lst;
////	t_list	*head_llst; //голова логического списка
////	t_list	**logic_lst;
////	t_list	**lst_elem; //элемент логического списка
////
////	if (!lst)
////		return (-1);
////	head_lst = *lst;
////	if (!head_old_lst)
////		return (-1);
////	while (head_old_lst)
////	{
////		lst_elem = lst_init(0); //создаем элемент логического списка
////		head_llst = *lst_elem;
////		while (head_old_lst->key != PIPE)
////		{
////			head_llst = head_old_lst;
////			head_llst = head_llst->next;
////			head_old_lst = head_old_lst->next;
////		}
////
////		head_old_lst = head_old_lst->next; //пропускаю пайп
////	}
////	while (head)
////	{
////
////		if ()
////
////		head = head->next
////	}
////
////
////}
//
//
//
//
//
////t_list **bash_args_lst_parser(t_list **lst)
////{
////	t_list	*head;
////
////	if (!lst)
////	{
////		printf("no lst in parser\n");
////		return (NULL);
////	}
////	head = *lst;
////	if (!head)
////	{
////		printf("no elem in parser\n");
////		return (NULL);
////	}
////	while (head)
////	{
////
////		find_redirects_etc();
////		head = head->next;
////	}
////
////}
//
////логический список состоит из голов списков команд (все что между пайпами)
////нельзя головы, походу придется копировать списки и маллочить все заново и делать структуру логического списка, где списик в составе
////надо было делать как раньше, то есть хранятся списки в логическом списке, маллочить только надо было
//
////сначала чек на синтаксис пайпов, потом создаю список списков
//
////доллар обработать
////структуру команд сделать
////метод, который список разделяет на подсписки для пайпов
////проверка синтаксиса пайпов
////мб cat | < aboba
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//#ifndef MINISHELL_H
//# define MINISHELL_H
//# include <stdio.h>
//# include <unistd.h>
//# include <stdlib.h>
//# include <signal.h>
//# include <fcntl.h>
//# include <string.h> //ubrat'
//# include <readline/readline.h>
//# include <readline/history.h>
////# include <>
//
//
//
////typedef struct s_vars //в чем ошибка?
////{
////	void			*val;
////	struct s_list	*next:
////}				t_vars;
////int (* t_builtin_ptr)(struct s_list *, struct s_vars *); //????? как исправить?
//
//#define WORD 1
//#define FIELD 2
//#define EXP_FIELD 3
//#define REDIR_OUT 4
//#define REDIR_IN 5
//#define REDIR_APPEND 6
//#define REDIR_HEREDOC 7
//#define PIPE 8
//#define SPACE 9
//
////#define CMD 11
//
////2) WORD  то есть слово без спецсимволов внутри
////3) FIELD - (‘ ’)поле, которое надо будет потом раскрыть, например, ‘ ’ - обычные кавычки
////Все виды токенов запихать в дефайны и преобразовать в числа 1, 2, 3...
////4) EXP_FIELD  - (“ ”)поле в кавычках “ “, надо раскрыть будет
////5) REDIR_OUT - аутфайл >
////6) REDIR_IN - инфайл <
////7) REDIR_APPEND - аутфайл добавить >>
////8) REDIR_HEREDOC - ХЕРдок <<
////9) PIPE -  |
//
////typedef struct s_list
////{
////	void			*val;
//////	void			*key;
////	int				key;
////	struct s_list	*next;
////}					t_list;
//
//typedef struct s_list
//{
//	void			*val;
////	void			*key;
//	int				key;
//	struct s_list	*next;
//	struct s_list	*prev;
//}					t_list;
//
//
////
////typedef struct s_llist //logic list для пайпов и бонусов мб
////{
////
////}
//
//typedef	struct s_vars
//{
//	char *reserved_words[8];
////	t_builtin_ptr builtin_array[7];
//	
//	
//	char			**envp;
//	struct s_list **envp_lst;
//	char	envp_f;
//	char	exit_f;
//	int		status;
//
//}		t_vars;
//
//typedef	struct s_cmd
//{
//	struct s_list	**files_in;
//	struct s_list	**files_out;
//	struct s_list	**files_heredoc;
//	char			**cmd_args;
//	struct s_vars	*vars; //здесь переменные окружения
//	
//}				t_cmd;
//
//int envp_init(t_vars *vars, char **envp);
//int	vars_initializing(t_vars *vars, char **envp);
//
//int	lst_clear(t_list **lst);
//t_list	*lst_new_elem(void	*value, int key);
//int big_str_len(char **big_str);
//int lst_len(t_list **lst);
//void lst_push_back(t_list **lst, t_list *new_node);
//t_list **lst_new(int n);
//t_list	**lst_env_copy(char **envp);
//
//int	lst_elem_print(t_list *node);
//int	lst_print(t_list **lst);
//int	lst_elem_print_token(t_list *node);
//int	lst_print_tokens(t_list **lst);
//
//int ft_strlen(char *str);
//void free_big_str(char **big_str);
//char **big_string_copy(char **big_str);
//int envp_init(t_vars *vars, char **envp);
//int	vars_initializing(t_vars *vars, char **envp);
//
//char	*ft_strdup(char *str);
//int ft_isspace(char c);
//int	ft_strcmp(char *s1, char *s2);
//int pipe_len_and_check(char *bash_str);
//int ft_strchr(char *str, char *c);
//char *quote_str_trim(char *bash_str, char *sym_arr);
//t_list **bash_args_lst_lexer(char *bash_str);
//t_list **bash_args_lst_parser(t_list **lst);
////int ft_strchr(char *str, char *c);
////int	ft_strcmp_n(char *s1, char *s2, int n);
//int	ft_strcmp_n(const char *str1, const char *str2, size_t n);
//
//
//t_list *lst_get_last(t_list **lst);
//t_list *lst_get_first(t_list *tale);
//int		lst_elem_free(t_list *node);
//
//
//
//t_list	*llst_elem_new(t_list *head_lst);
////t_list	**logic_lst_init(t_list	**lst);
//t_list	**llst_new(t_list	**lst);
//
//
//#endif
//
//
