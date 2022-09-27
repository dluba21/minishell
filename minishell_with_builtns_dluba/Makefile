all:
	gcc -g *.c get_next_line/*.c builtins/*.c -lreadline -o minishell 
clean:
	@rm -rf *.f heredoc_file test
test:
	gcc test.c -lreadline  && ./a.out
	
