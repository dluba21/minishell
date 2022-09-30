#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "get_next_line/get_next_line.h"

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

typedef	struct s_cmd t_cmd;
typedef	struct s_vars t_vars;
typedef int	(* t_builtin_ptr)(t_vars *vars, t_cmd *cmd);

typedef struct s_list
{
	void			*val;
	int				key;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

struct s_vars
{
	char				**root_paths;
	char				**envp;
	struct s_list		**envp_lst;
	char				envp_f;
	char				exit_f;
	int					status;
	int					exit_status;
	char				*term_pid;
	struct sigaction	sig;
	int					stdin_fd;
	int					stdout_fd;
	char				**reserved_words;
	int					pipe_fd[2];
	int					*pid_array;
	int					**pipe_array;
	int					llst_len;
	t_builtin_ptr		*builtin_ptr_arr;

};

struct s_cmd
{
	struct s_list	**files_in;
	struct s_list	**files_out;
	struct s_list	**files_heredoc;
	struct s_list	**args_lst;
	struct s_vars	*vars;
	char			**args_array;
	int				in_fd;
	int			out_fd;
	int			len_args;
	
};

int		envp_init(t_vars *vars, char **envp);
t_list	**lst_env_copy(char **envp);
int		vars_initializing(t_vars *vars, char **envp);
int		lst_clear(t_list **lst);
t_list	*lst_elem_new(void	*value, int key);
t_list	*lst_elem_copy(t_list *elem);
int		lst_len(t_list **lst);
void	lst_push_back(t_list **lst, t_list *new_node);
void	lst_push_front(t_list **lst, t_list *new_node);
t_list	**lst_new(int n);
t_list	*lst_get_last(t_list **lst);
t_list	*lst_get_first(t_list *tale);
int		lst_elem_free(t_list *node);
int 	lst_del_elem(t_list **lst, int n);
char	**convert_lst_to_str(t_list **lst);
char	*ft_readline(void);
int		ft_strlen(char *str);
void	free_big_str(char **big_str);
char	**big_string_copy(char **big_str);
char	*ft_strdup(char *str);
int		ft_isspace(char c);
int		ft_strcmp(char *s1, char *s2);
int		pipe_len_and_check(char *bash_str);
int		ft_strchr(char *str, char *c);
char	*quote_str_trim(char *bash_str, char *sym_arr);
t_list	**bash_args_lst_lexer(char *bash_str, t_vars *vars);
t_list	**bash_args_lst_parser(t_list **lst);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		find_spec_char(char *str);
void	big_str_print(char **big_str);
int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(char *s1, char *s2, int n);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);
char	*ft_strcpy(char *src);
int		big_str_len(char **big_str);
int		ft_perror(char *str);
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		root_paths_init(t_vars *vars);
char	*compose_cmd_args(t_cmd *cmd_elem, char **root_paths);
t_list	*llst_elem_new(t_list *head_lst);
t_list	**llst_new(t_list	**lst);
t_list	*cmd_parser(t_list *head_lst, t_cmd *cmd);
t_list	*cmd_init(void);
int		dollar_parser(t_list **lst, t_vars *vars);
char	*dollar_expansion(char *str, t_vars *vars);
void	expand_dollar_var_in_brace(char **str, char **ret_str, t_vars *vars);
void	not_dollar_part(char **str, char **ret_str);
void	expand_dollar_var(char **str, char **ret_str, t_vars *vars);
char	*find_env_var(char *str, char **env);
char	*env_var_trimmer(char *env_elem);
void	recreate_envp(t_vars *vars);
char	*env_key_trimmer(char *env_elem);
char	*env_var_trimmer(char *env_elem);
int		is_var_in_env(t_list **env_lst, char *key);
void	add_env_value(t_vars *vars, char *key, char *value);
void	change_env_val_key(t_vars *vars, char *old_key, char *new_key, char *value);
int		exec_cmd(t_list **llst, t_vars *vars);
int		root_paths_init(t_vars *vars);
void	sig_init(void);
int		open_heredocs(t_list *llst_elem);
int		**open_pipes(int len);
int		open_files(t_vars *vars, t_cmd *cmd, int i);
void	close_all_pipes(int **pipe_array);
void	delete_heredocs(t_list **files_in);
int		open_files_out(t_list **files_out);
int		ft_cd(t_vars *vars, t_cmd *cmd);
int		ft_echo(t_vars *vars, t_cmd *cmd);
int		ft_env(t_vars *vars, t_cmd *cmd);
int		ft_exit(t_vars *vars, t_cmd *cmd);
int		ft_export(t_vars *vars, t_cmd *cmd);
int		ft_pwd(t_vars *vars, t_cmd *cmd);
int		ft_unset(t_vars *vars, t_cmd *cmd);
int		child_process(t_list *llst_elem, t_vars *vars);
int		is_builtin(t_vars *vars, t_cmd *cmd);
int		exec_builtin(t_vars *vars, t_cmd *cmd);
#endif
