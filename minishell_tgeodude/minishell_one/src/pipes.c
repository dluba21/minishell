#include "minishell.h"


void	heredoc_parser(t_list **files)
{
	char	*line;
	char	*limiter;
	t_list	*head;
	//t_list	*tmp;
	char	*heredoc_name;
	int		i;
	int	fd;


	head = *files;
	//tmp = NULL;
	i = -1;
	while (++i, head)
	{
		if (head->key == REDIR_HEREDOC)
		{
			//tmp = head;
			heredoc_name = ft_strjoin("tmp/heredoc_", ft_itoa(i)); //leaks itoa and strjoin
			fd = open(heredoc_name, O_RDWR | O_CREAT, 0644); //и закрывать фдшники надо лишние
			free(heredoc_name);
			if (fd < 0)
				printf("here_doc error: can't open file\n");
		}
		head = head->next;
	}
	limiter = ft_strjoin(head->val, "\n");
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			printf("here_doc error: string is null\n");
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			free(limiter);
			close(fd);
//			unlink(tmp/here_doc); удалить надо файл в конце команды
			return ;
		}
		if (write(fd, line, ft_strlen(line)) == -1)
			printf("here_doc error: can't write");
		free(line);
	}
}
