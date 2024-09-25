#include "../../includes/minishell.h"

void define_token_fd(t_token *token)
{
	if (token->type == T_SMALLER)
		define_smaller(token);
	else if (token->type == T_GREATER)
		define_greater(token);
//	else if (token->type == T_DSMALLER)
//		define_dsmaller(token);
	else if (token->type == T_DGREATER)
		define_dgreater(token);
}

//buradan devam
void define_smaller(t_token *token)
{
	int temp_fd;

	temp_fd = open(token->next->value, O_RDONLY, 0777);
	if (temp_fd == -1)
		ft_exit_str_free_fd(ERROR_FILE_OPEN, token->next->value, STDERR_FILENO);
	else
	token->next->fd_in = temp_fd;
	printf("< fd_in: %d, infile: %s\n", temp_fd, token->next->value);

}

void define_greater(t_token *token)
{
	int temp_fd;

	temp_fd = open(token->next->value, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (temp_fd == -1)
		ft_exit_str_free_fd(ERROR_FILE_OPEN, token->next->value, STDERR_FILENO);
	token->next->fd_out = temp_fd;
	printf("> fd_out: %d, outfile: %s\n", temp_fd, token->next->value);
}

//void define_dsmaller(t_token *token)
//{
//	int temp_fd;
	
	// temp_fd = open("our_here_doc", O_CREAT | O_APPEND | O_WRONLY, 0777);
	// if (temp_fd == -1)
	// 	ft_exit_str_free_fd(ERROR_FILE_OPEN, token->next->value, STDERR_FILENO);
	// token->next->fd_out = temp_fd;
	// token->next->limiter = ft_strdup(limiter);
	// printf("<< fd_out: %d, outfile: %s\n", info->fd_out, info->outfile);
	// printf("limiter: %s\n", info->limiter);
//}

void define_dgreater(t_token *token)
{
	int temp_fd;

	temp_fd = open(token->next->value, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (temp_fd == -1)
		ft_exit_str_free_fd(ERROR_FILE_OPEN, token->next->value, STDERR_FILENO);
	token->next->fd_out = temp_fd;
	printf(">> fd_out: %d, outfile: %s\n", temp_fd, token->next->value);
}