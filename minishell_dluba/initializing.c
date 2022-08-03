#include "minishell.h"

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

void free_big_str(char **big_str) //освобождает массив строк
{
	char	**temp;

	temp = big_str;
	while (*big_str)
		free(*big_str++);
	free(temp);
}

//char **big_string_copy(char **big_str) //копирует массив строк //старая версия
//{
//	int	i;
//	int	j;
//	char **ret_str;
//
//	i = 0;
//	ret_str = NULL;
//	while (big_str[i])
//		i++;
//	ret_str = (char **)malloc(sizeof(char *) * (i + 1));
//	if (!ret_str) //mozhno udalit'  esle chto dlya normi
//		return (NULL);
//	i = 0;
//	while (big_str[i])
//	{
//		ret_str[i] = (char *)malloc(ft_strlen(big_str[i])); //leaks mb with exit
//		if (!ret_str[i])
//			return (NULL);
//		j = 0;
//		while (big_str[i][j])
//		{
//			ret_str[i][j] = big_str[i][j];
//			j++;
//		}
//		i++;
//	}
//	ret_str[i] = NULL;
//	return (ret_str);
//}

char **big_string_copy(char **big_str) //копирует массив строк
{
	int	i;
	int	j;
	char **ret_str;

	i = 0;
	ret_str = NULL;
	while (big_str[i])
		i++;
	ret_str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret_str) //mozhno udalit'  esle chto dlya normi
		return (NULL);
	i = 0;
	while (big_str[i])
	{
		ret_str[i] = ft_strcpy(big_str[i]);
		if (!ret_str[i])
			return (NULL);
		i++;
	}
	ret_str[i] = NULL;
	return (ret_str);
}




//int envp_init(t_vars *vars, char **envp)

int envp_init(t_vars *vars, char **envp) //инициализация переменных оркжуения в структуре
{
	int	i;
	int	j;

//	char **envp;
//	struct s_list envp_lst;
	i = 0;
	vars->envp = big_string_copy(envp);
	if (!vars->envp)
		return (write(2, "envp malloc error\n", 18) - 19);
	vars->envp_lst = lst_env_copy(envp); 
	if (!vars->envp_lst)
		return (write(2, "envp_lst malloc error\n", 18) - 23);
	
//	while (vars->envp[i])
//		printf("%s\n", vars->envp[i++]);
//	printf("ok");
	
	return (0);
}
//
//void builtin_array_creator(t_vars *vars) //инициализация массива с указателями на функции в структуре
//{
//	vars->builtin_array = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
//{
	

//◦ echo with option -n
//◦ cd with only a relative or absolute path
//◦ pwd with no options
//◦ export with no options
//◦ unset with no options
//◦ env with no options or arguments
//◦ exit with no options

int	vars_initializing(t_vars *vars, char **envp)
{
//	builtin_array_creator(vars);
	envp_init(vars, envp);
	vars->exit_status = 0;
	vars->status = 0;
	vars->term_pid= ft_itoa(1234); //leaks и дописать
//	lst_print(vars->envp_lst);
	
	
	return (0);
}
