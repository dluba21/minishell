#include "minishell.h"

void	delete_heredocs(t_list **files_in)
{
	t_list	*head;

	if (!files_in || !(*files_in))
		return ;
	head = *files_in;
	while (head)
	{
		if (head->key == REDIR_HEREDOC)
			unlink(head->val);
		head = head->next;
	}
}

void	heredoc_parser(t_list *file_in, int i) //тупо записывает в файл что ввел
{
	char	*line;
	char	*limiter;
//	t_list	*head;
//	t_list	*tmp;
	char	*heredoc_name;
	int		fd;


//	head = *files;
//	while (head)
//	{
//		if (head->key == REDIR_HEREDOC)
//			tmp = head;
//		head = head->next;
//	}

	heredoc_name = ft_strjoin("/tmp/heredoc_file_", ft_itoa(i));

//	printf("name = %s\n", heredoc_name);
	
//	if (!tmp) //не нашел heredoc
//		return ;
	fd = open(heredoc_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	limiter = ft_strjoin(file_in->val, "\n");
	while (1)
	{
		printf("insert:\n");
		line = get_next_line(0);
		if (!line)
		{
			free(line);
			free(limiter);
			close(fd);
			return ;
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			free(limiter);
			close(fd);
//			if (heredoc_f) //хердоки надо открыть по-любомуб если есть но мб не из него ввод
//				*in_fd = open("/tmp/heredoc_file", O_RDONLY); //открываю заново так как курсор сдвинулся
//			unlink(""); //удалить надо файл, дескриптор остается
			free(file_in->val);
			file_in->val = heredoc_name;
			return ;
		}
		if (write(fd, line, ft_strlen(line)) == -1)
			printf("here_doc error: can't write");
		free(line);
	}
}

int	open_heredocs(t_list *llst_elem)
{
	t_list	*head;
	int		i;

	i = -1;
	while (llst_elem)
	{
		if (((t_cmd *)llst_elem->val)->files_in) //проверка мб нет файлов на воод вообще
		{
			head = *(((t_cmd *)llst_elem->val)->files_in);
			while (head)
			{
//				printf("i = %d\n", i);
				if (head->key == REDIR_HEREDOC)
					heredoc_parser(head, ++i);
				head = head->next;
			}
//			printf("ok\n");
		}
		
		llst_elem = llst_elem->next;
	}
	return (0);
}
