#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
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
#define PIpE 8

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
	void			*key;
	struct s_list	*next;
}					t_list;


typedef	struct s_vars
{
	char *reserved_words[8];
//	t_builtin_ptr builtin_array[7];
	
	
	char **envp;
	struct s_list envp_lst;
	char	envp_f;
	char	exit_f;
	int		status;

}		t_vars;


int envp_init(t_vars *vars, char **envp);
int	vars_initializing(t_vars *vars, char **envp);

#endif
