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
	fd = open("/tmp/heredoc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	limiter = ft_strjoin(tmp->val, "\n");
	while (1)
	{
		printf("insert:\n");
		line = get_next_line(0);
		if (!line)
			printf("here_doc error: string is null\n");
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			free(limiter);
			close(fd);
			if (heredoc_f) //хердоки надо открыть по-любомуб если есть но мб не из него ввод
				*in_fd = open("/tmp/heredoc_file", O_RDONLY); //открываю заново так как курсор сдвинулся
			unlink("/tmp/heredoc_file"); //удалить надо файл, дескриптор остается
			return ;
		}
		if (write(fd, line, ft_strlen(line)) == -1)
			printf("here_doc error: can't write");
		free(line);
	}
}
