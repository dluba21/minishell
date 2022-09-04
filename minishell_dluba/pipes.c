#include "minishell.h"


void	heredoc_parser(t_list **files, int *in_fd, int heredoc_f) //тупо записывает в файл что ввел
{
	char	*line;
	char	*limiter;
	t_list	*head;
	t_list	*tmp;
	char	*heredoc_name;
	int		fd;


	head = *files;
	tmp = NULL;
	while (head)
	{
		if (head->key == REDIR_HEREDOC)
			tmp = head;
		head = head->next;
	}
	if (!tmp) //не нашел heredoc
		return ;
	fd = open("heredoc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (heredoc_f)
		*in_fd = fd;
	limiter = ft_strjoin(tmp->val, "\n");
	if (write(fd, "abobus\n", 7) == -1)
		printf("here_doc error: can't write");
//	while (1)
//	{
////		printf("[%s]\n", limiter);
//		printf("insert:\n");
////
//		line = get_next_line(0);
//		if (!line)
//			printf("here_doc error: string is null\n");
//		if (!ft_strcmp(line, limiter))
//		{
//			free(line);
//			free(limiter);
//			//закрыть in_fd потом
////			unlink(tmp/here_doc); удалить надо файл в конце команды
//			return ;
//		}
//		if (write(fd, line, ft_strlen(line)) == -1)
//			printf("here_doc error: can't write");
//		free(line);
//	}
}
