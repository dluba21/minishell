#include "minishell.h"

int ft_readline(void) //ридайн применить и добавить в истории и проверить на нулл ридлайн
{
	
}

char	*ft_strdup(char *str)
{
	char	*ret_str;
	int		i;

	ret_str = (char *)(malloc(ft_strlen(str) + 1));
	if (!ret_str)
		return (NULL);
	i = 0;
	while (str[i])
		ret_str[i++] = str[i];
	ret_str[i] = 0;
	return (ret_str);
}

int ft_isspace(char c)
{
	if (c >= 9 && c <= 13 || c == 32)
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2) //сравнивает строки
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 == *s2 && *s1++ && *s2++)
		;
	return (*s1 - *s2);
}

int	ft_strcmp_n(char *s1, char *s2, int n) //сравнивает строки на n символов вперед вперед
{
	if (!s1 || !s2 || n < 0)
		return (-1);
	while (*s1 == *s2 && *s1++ && *s2++ && n--)
		;
	return (*s1 - *s2);
}
//char *
//	  readline (const char *prompt);
int pipe_len_and_check(char *bash_str) //чекает длину пайпов и синтакис его (а вообще переписать, так как говно)
{ //лучше сначала внести токены в список и потом уже проверять синтаксис
	int		i;
	int		n_pipes;
	int		isspace_f;

	i = 0;
	isspace_f = 0;
//	temp = bash_str
	while (*bash_str)
	{
		if (ft_isspace(*bash_str)) //чекаю есть ли пробелы вообще, важно для синтаксиса
			isspace_f = 1;
		else if (*bash_str == "|" && !ft_strcmp_n(bash_str, "||", 2) \
			&& *(bash_str + 1)); //последнее если aboba |
		{
			bash_str += 2;
			isspace_f = 0;
			n_pipes++;
			if (!ft_isspace(*(bash_str + 2))) //проверка на синтаксис, есть ли пробел после слова
				return (-1); //выдать в верхней функции ошибку и написать
		}
		else
			isspace_f = 0;
		bash_str++;
	}
}

//int	bash_args_len(char **argv) //считает количество элементов в списке токенов
//{
//
//}

int ft_strchr(char *str, char c) //длина пути до нужного символа (если пустая строка или не маллок то -1)
{//сделать по не char c, а массив символов
	int	i;

	i = 0;
	if (!str) //вот мб убрать
		return (-1);
	while (*str)
	{
		if (*str == c)
			return (i);
		str++;
	}
	return (-1);
}

char *quote_str_trim(char *bash_str, char quote_sym)
{
	int		len;
	int		i;
	char	*trimmed_str;
	
	len = ft_strchr(bash_str, quote_sym);
	if (len == -1)
		return (NULL);
	trimmed_str = (char *)(malloc(len + 1));
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (i < len)
		trimmed_str[i++] = bash_str[i];
	trimmed_str[i] = 0;
	return (trimmed_str);
}

t_list **bash_args_first_lst_init(char *bash_str)
{
	t_list	**lst;
	char	*str;

	lst = lst_new(0);
	if (!lst || !bash_str)
		return (NULL);
	while (*bash_str)
	{
		if (*bash_str++ == '\'')
		{
			if (!*bash_str)) //дальше конец строки и ошибка значит
				return (NULL);
			str = quote_str_trim(bash_str, '\'');
			if (!str)
				return (NULL); //не нашел вторую кавчку, значит ошибку надо выдать и список зафришить созданный уже
			lst_push_back(lst, lst_new_elem(str, FIELD));
			*bash_str += ft_strchr(bash_str, '\'') + 1; // +1 чтобы выйти за кавычку
		}
		else if (*bash_str++ == 34) //двойная кавычка
		{
			if (!*bash_str))
				return (NULL);
			str = quote_str_trim(bash_str, 34);
			if (!str)
				return (NULL); //не нашел вторую кавчку, значит ошибку надо выдать и список зафришить созданный уже
			lst_push_back(lst, lst_new_elem(str, EXP_FIELD));
			*bash_str += ft_strchr(bash_str, 34) + 1;
		}
		else if (ft_strcmp_n(*bash_str, "<<", 2)) //можно ли *bash_str += 2?? вроде нет
		{
			bash_str += 2; //или лучше сначала разделитель привератить в токен какой-либо а потом обрабатывать?
			while (!ft_isspace(*bash_str)) //проверка на ноль в конце или другой спец символ
				bash_str++;
			str = quote_str_trim(bash_str, isspace_array); //ноль в конце будет нормальным так что хз про функцию
			if (!str)
				return (NULL);
//			while (!ft_is)//ищу слово для разделения
			lst_push_back(lst, lst_new_elem(str, REDIR_HEREDOC));
			str += quote_str_trim(bash_str, isspace_array) + 1;
		}
	}
}

//2) WORD  то есть слово без спецсимволов внутри
//3) FIELD - (‘ ’)поле, которое надо будет потом раскрыть, например, ‘ ’ - обычные кавычки
//Все виды токенов запихать в дефайны и преобразовать в числа 1, 2, 3...
//4) EXP_FIELD  - (“ ”)поле в кавычках “ “, надо раскрыть будет
//5) REDIR_OUT - аутфайл >
//6) REDIR_IN - инфайл <
//7) REDIR_APPEND - аутфайл добавить >>
//8) REDIR_HEREDOC - ХЕРдок <<
//9) PIPE -  |
