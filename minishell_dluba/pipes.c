#include "minishell.h"

int	if_exist_files_in(t_cmd *cmd) //првоерка на сущетсвование файлов и права, надо до открытия файлов делать и форков
{
	t_list	*head;

	if (cmd->files_in && *cmd->files_in)
	{
		head = *cmd->files_in;
		while (head)
		{
			if (access(head->val, R_OK | F_OK) == -1)
				return (1);
			head = head->next;
		}
	}
	return (0);
}

int	cmd_files_len(t_cmd *cmd, int *i)
{
	*i += lst_len(cmd->files_in);
	*i += lst_len(cmd->files_out);
	if (cmd->files_heredoc)
		*i++; //так как один лишь хердок считается даэе если много их
}




int	pipes_len(t_list **llst) //количество всех файлов и тд(хуйня так как пайпы только между командами надо считать а не в файлы)
{
	char 	*llst_elem;
	int		i;

	if (!llst || !(*llst))
		return (printf("no lst in pipes len\n") - 20);
	i = 0;
	llst_elem = *llst;
	while (llst_elem)
	{
		if (!lst_len((llst_elem->val)->files_in))
			
		cmd_files_len(llst_elem->val, i);
		llst_elem = llst_elem->next;
	}
	return (i);
}

int	**pipes_open(t_list *llst) // занести в мега большой массив ли с элементами - pipes_fd?
{
	while ()
}


//
//
//void	filename_parser(int argc, char **argv, t_vars *vars)
//{
//	if (!vars->here_doc_flag)
//	{
//		if (access(argv[1], R_OK | F_OK) == -1)
//			print_error("infile doesn't exist\n", vars);
//		vars->in_fd = open(argv[1], O_RDONLY);
//	}
//	else
//	{
//		vars->in_fd = open("here_doc", O_RDWR | O_CREAT, 0644);
//		if (vars->in_fd < 0)
//			print_error("here_doc error: can't open file\n", vars);
//	}
//	if (vars->here_doc_flag == 1)
//		vars->out_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
//	else
//		vars->out_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
//	if (vars->in_fd < 0 || vars->out_fd < 0)
//		print_error("error: can't open", vars);
//}
//
//int	heredoc_p2(t_vars *vars)
//{
//	int	fd;
//
//	vars->here_doc_flag = 1;
//	fd = open("here_doc", O_RDWR | O_CREAT, 0644);
//	if (fd < 0)
//		print_error("here_doc error: can't open file\n", vars);
//	return (fd);
//}
//
//void	heredoc_parser(char **argv, t_vars *vars)
//{
//	char	*line;
//	char	*limiter;
//
//	vars->in_fd = heredoc_p2(vars);
//	limiter = ft_strjoin(argv[2], "\n");
//	while (1)
//	{
//		line = get_next_line(0);
//		if (!line)
//			print_error("here_doc error: gnl is null\n", vars);
//		if (ft_strcmp_ppx(line, limiter) == 1)
//		{
//			free(line);
//			free(limiter);
//			close(vars->in_fd);
//			return ;
//		}
//		if (write(vars->in_fd, line, ft_strlen(line)) == -1)
//			print_error("here_doc error: can't write", vars);
//		free(line);
//	}
//}
