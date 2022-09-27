#include<stdio.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int main(int argc, char **argv){
    printf("Hello World!\n");
	
	int i = 11;
	i++;
	
	
	printf("len = %d\n", ft_strlen("aboba"));
    return 0;
}
