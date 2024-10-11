#include "../../includes/minishell.h"

void limiter_check(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (current->limiter)
		{
			data->info->limiter = ft_strdup(current->limiter);
			printf("limiter in limiter_check: %s\n", data->info->limiter);
		}	
		current = current->next;
	}
}

int here_doc_fd_check(t_data *data)
{
	t_token	*current;
	int temp_fd;

	current = data->tokens;
	while (current)
	{
		if (current->limiter)
		{
			temp_fd = current->here_doc_fd;
			printf("here_doc_fd_check: %d\n", temp_fd);
		}	
		current = current->next;
	}
	return (temp_fd);
}

t_token *redir_first(t_token *current)
{
	t_token	*temp;
	t_token	*smaller;
	t_token *file;
	t_token *next_token;

	if (current->next == NULL || current->next->next == NULL)
		return (NULL);
	smaller = current;
	file = current->next;
	temp = current->next->next;
	next_token = temp->next;
	temp->next = smaller;
	temp->prev = NULL;
	smaller->prev = temp;
	file->next = next_token;
	return (temp);
}

char *do_cat_addition(t_token *current, char *cmd)
{
	cmd = ft_strjoin(cmd, " ");
	cmd = ft_strjoin(cmd, current->next->value);
	// printf("cmd: %s\n", cmd);
	return (cmd);
}

bool is_first_after_pipe(t_token *current)
{
	if (current && \
		(current->prev == NULL || current->prev->type == T_PIPE))
		return (true);
	return (false);
}

// char **find_cmd_of_heredoc(t_token *current)
// {
// 	char	**array;

// 	while (current && current->type != T_DSMALLER)
// 		current = current->next;
// 	array = (char **)malloc(sizeof(char *) * 50);
// 	if (array == NULL)
// 	{
// 		ft_exit_perror(ERROR_ALLOCATION, "malloc in find_cmd_of_heredoc");
// 	}
// 	printf("---find_cmd_of_heredoc---\n");
// 	if (current->next && current->next->next)
// 		current = current->next->next;
// 	else
// 	{
// 		printf("current->next->next is NULL\n");
// 		return (NULL);
// 	}
// 	printf("current->value: %s\n", current->value);	
// 	array[0] = ft_strdup(current->value);
// 	printf("cmds[0]: %s\n", array[0]);
// 	current = current->next;
// 	while (current && current->type != T_PIPE)
// 	{
// 		array[0] = ft_strjoin(array[0], " ");
// 		array[0] = ft_strjoin(array[0], current->value);
// 		current = current->next;
// 	}
// 	array[1] = NULL;
// 	return (array);
// }


// char **init_heredoc(t_data *data, t_token *current)
void init_heredoc(t_data *data)
{
	char	*limiter;
	char	*line;
	char	*temp;
	int		here_doc_fd;

	printf("---init_heredoc---\n");
	here_doc_fd = here_doc_fd_check(data);
	printf("here_doc_fd: %d\n", here_doc_fd);
	// dup2_safe(here_doc_fd, STDOUT_FILENO, data->info);
	limiter_check(data);
	limiter = data->info->limiter;
	printf("limiter: %s\n", limiter);
	// do_heredoc_child(data->info);
	line = readline("> ");
	temp = NULL;
	while (line)
	{
		if ((ft_strlen(line) == ft_strlen(limiter)) && ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break;
		if (temp == NULL)
			temp = ft_strdup(line);
		else
			temp = ft_strjoin(temp, line);
		temp = ft_strjoin(temp, "\n");
		write(here_doc_fd, line, ft_strlen(line));
		write(here_doc_fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	// here_doc_fd = here_doc_fd_check(data);
	// dup2_safe(here_doc_fd, STDOUT_FILENO, data->info);
	data->here_doc = ft_strdup(temp); // to be deleted
	free(temp);
	close_safe(here_doc_fd, data->info);
}

char **cmds_between_pipes(t_data *data, char **cmds)
{
	int		j;
	t_token	*current;
	bool	cat_cmd;

	printf("---cmds_between_pipes---\n");
	cat_cmd = false;
	j = 0;
	current = data->tokens;
	while (current && current->type != T_PIPE)
	{
		while (current && current->type != T_PIPE)
		{
			if (is_heredoc(current))
			{
				if (current->next && current->next->next)
					current = current->next->next;
				cmds[j] = ft_strdup(current->value);
				// printf("cmds[j]: %s\n", cmds[j]);
				current = current->next;
				while (current && current->type != T_PIPE)
				{
					cmds[j]  = ft_strjoin(cmds[j] , " ");
					cmds[j]  = ft_strjoin(cmds[j] , current->value);
					current = current->next;
				}
			}
			if (is_redir_except_heredoc(current) && is_first_after_pipe(current))
			{
				current = redir_first(current);
				if (!current)
					return (NULL);
			}
			if (current && ft_strncmp(current->value, "cat", 4) == 0)
				cat_cmd = true;
			if (is_first_after_pipe(current))
			{
				cmds[j] = ft_strdup(current->value);
				current = current->next;
			}
			if (current && is_redir_except_heredoc(current))
			{
				if (cat_cmd)
				{
					cmds[j] = do_cat_addition(current, cmds[j]);
					cat_cmd = false;
				}
				current = current->next->next;
			}
			else if (current && current->type != T_PIPE)
			{
				cmds[j] = ft_strjoin(cmds[j], " ");
				cmds[j] = ft_strjoin(cmds[j], current->value);
				current = current->next;
			}
		}
		printf("cmds[j]: %s\n", cmds[j]);
		if (current && current->type == T_PIPE)
			current = current->next;
		j++;
	}
	cmds[j] = NULL;
	return (cmds);
}

// pid_t finish_heredoc(t_data *data)
// {

// 	printf("---finish_heredoc---\n");
// 	char **matrix;
// 	// int heredoc_fd;
// 	pid_t pid;

// 	// heredoc_fd = here_doc_fd_check(data);
// 	// data->info->fd_in = heredoc_fd;
// 	// data->info->fd_out = STDOUT_FILENO;
// 	matrix = ft_split("cat", ' ');
// 	pid = heredoc_child_process(data->info, matrix, "/bin/cat");
// 	// pid = heredoc_child_process(data->info, data->cmds, "/bin/cat");
// 	unlink("0ur_h3r3_d0c");
// 	return (pid);
// }

char **cmds_from_tokens(t_data *data)
{
	char	**cmds;
	// int		i;
	// int		j;

	printf("---cmds_from_tokens---\n");
	// i = 0;
	// j = 0;
	cmds = (char **)malloc(sizeof(char *) * (data->nbr_of_pipes + 2));
	if (cmds == NULL)
	{
		free_data(&data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in cmds_from_tokens");
	}
	cmds = cmds_between_pipes(data, cmds);
	// printf("cmds are ready\n");
	// printf_array(cmds);
	return(cmds);
}
