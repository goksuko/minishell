/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/09/04 23:09:23 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//static char	*line_read = (char *)NULL; NOT SURE IF ACTUALLY NEEDED!We should only have one global variable in the whole project that is used for the signal handling

int	check_pipe(char *line)
{
	int	i;
	int	count;

	ft_printf("check_pipe\n");
	i = 0;
	count = 0;
	while (line && line[i])
	{
		if (line[i] == '|')
			count++;
		i++;
	}
	return (count);
}

int	find_path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("envp[%d]: %s\n", i, envp[i]);
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (0);
}




// int check_args(char *line, char **envp)
// {
// 	int		exit_code;

// 	exit_code = 0;
// 	ft_printf("check_args\n");
// 	exit_code = check_characters(line);
// 	if (exit_code)
// 		return (ft_print_error(exit_code));
// 	if (check_pipe(line))
// 		return (pipex(line, envp));
// 	return (exit_code);
// }

void	init_data(t_data *data, char *line, char **envp)
{
	ft_printf("init_data\n");
	data->line = line;
	data->envp = envp;
	data->exit_code = 0;
	return ;
}

int	find_first_eq(char *envp_i)
{
	int	i;

	i = 0;
	while (envp_i && envp_i[i] && envp_i[i] != '=')
		i++;
	if (envp_i[i] == '\0')
		return (0);
	return (i);
}

bool	key_rules(char c, int index)
{
	if (index == 0)
	{
		if (ft_isalpha(c) || c == '_')
			return (true);
	}
	if (index > 0)
	{
		if (ft_isalnum(c) || c == '_')
			return (true);
	}
	return (false);
}

// int	check_key(char *key, char *cmd)
int	check_key(char *key)
{
	int		i;
	// char	*new_key;

	i = 0;
	// new_key = NULL;
	if (key && key[0] == '\0')
		ft_exit_str_fd(ERROR_INVALID_IDENTIFIER, STDERR_FILENO);
	while (key && key[i])
	{
		if (!key_rules(key[i], i))
		{
			// new_key = ft_trip_join("`", key, "'");
			// ft_write_error(2, cmd, new_key, "not a valid identifier");
			ft_exit_str_fd(ERROR_INVALID_IDENTIFIER, STDERR_FILENO);
			// free(new_key);
			// return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

t_env	*ft_new_node(char *key, char *value)
{
	t_env	*node;

	node = ft_calloc(sizeof(t_env), 1);
	if (errno == ENOMEM || node == NULL)
		ft_exit_perror(1, "node in ft_new_node");
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

// int	find_data_if_no_pos(t_data *shell_data, char *envp, char **key, char **value)
int	find_data_if_no_pos(char *envp_i, char **key, char **value)
{
	*key = ft_substr(envp_i, 0, ft_strlen(envp_i));
	if (errno == ENOMEM || key == NULL)
		ft_exit_perror(1, "key in find data");
	// if (check_key(*key, ""))
	if (check_key(*key))
		return (free(*key), EXIT_FAILURE);
	*value = NULL;
	return (EXIT_SUCCESS);
}

// t_env	*create_node(t_data *shell_data, char *envp, int pos)
t_env	*create_node(char *envp_i, int pos)
{
	char	*key;
	char	*value;

	if (pos)
	{
		key = ft_substr(envp_i, 0, pos);
		if (errno == ENOMEM || key == NULL)
			ft_exit_perror(1, "key in create node");
		// if (check_key(key, ""))
		if (check_key(key))
			return (free(key), NULL);
		value = ft_substr(envp_i, pos + 1, ft_strlen(envp_i));
		if (errno == ENOMEM || value == NULL)
		{
			free(key);
			ft_exit_perror(1, "value in create node");
		}
	}
	else
	{
		if (find_data_if_no_pos(envp_i, &key, &value))
		// if (find_data_if_no_pos(shell_data, envp, &key, &value))
			return (NULL);
	}
	return (ft_new_node(key, value));
}

void	ft_free_prev(t_env *head)
{
	t_env	*tmp;

	tmp = NULL;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

// t_env	*ft_envp_node(t_data *shell_data, char *envp)
t_env	*ft_envp_node(char *envp_i)
{
	int		first_eq;
	t_env	*new_node;

	first_eq = find_first_eq(envp_i);
	// new_node = create_node(shell_data, envp, first_eq);
	new_node = create_node(envp_i, first_eq);
	return (new_node);
}

void	ft_update_shell(t_env **env_list)
{
	t_env	*env;
	t_env	*start;
	char	*cwd;

	start = *env_list;
	env = *env_list;
	cwd = getcwd(0, 0);
	while (env)
	{
		if (!ft_strncmp("SHELL", env->key, 5))
		{
			free(env->value);
			env->value = cwd;
			return ;
		}
		env = env->next;
	}
	env_list = &start;
	free(cwd);
}

void	make_initial_path_checks(char **envp, t_data *shell_data)
{
	t_env	*head;
	t_env	*node;
	int		i;
	
	ft_printf("make_initial_path_checks\n");
	if (!envp && !(*envp))
		ft_printf("there is no envp\n"); // think of memory management
	i = 1;
	head = ft_envp_node(envp[0]);

	// printf("head->key: %s\n", head->key);
	// printf("head->value: %s\n", head->value);
	// printf("envp[0]: %s\n", envp[0]);

	// head->key: SHELL
	// head->value: /bin/bash
	// envp[0]: SHELL=/bin/bash
	
	if (errno == ENOMEM || head == NULL)
		ft_exit_perror(1, "head in initial path check");
	shell_data->env_list = head;
	node = head;
	while (envp[i])
	{
		// node->next = ft_envp_node(shell_data, envp[i]);
		node->next = ft_envp_node(envp[i]);
		if (!node->next)
		{
			ft_free_prev(head); // rewrite memory stuff
		}
		node = node->next;
		i++;
	}
	shell_data->env_list = head;
	ft_update_shell(&shell_data->env_list);


	// path_no = find_path_index(envp);
	// printf("path_no: %d\n", path_no);
	// if (envp[path_no] == NULL)
	// {
	// 	ft_print_error(ERROR_NULL_PATH);
	// 	exit(ERROR_NULL_PATH);
	// }
	// if (path_no == 0)
	// {
	// 	ft_print_error(ERROR_CMD_NOT_FOUND);
	// 	exit(ERROR_CMD_NOT_FOUND);
	// }
	// ft_printf("path_no: %d\n", path_no);
	// ft_printf("envp[path_no]: %s\n", envp[path_no]);
	return ;
}

// void	initial_path_checks(char **array) //useless function only written to overcome error in main as envp was not used. still need to write proper path check
// {
// 	int	i;

// 	i = 0;
// 	while (array[i] != NULL)
// 	{
// 		printf("%s\n", array[i]);
// 		i++;
// 	}
// }

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_token *token;
	t_tree	*ast;
	t_data	*shell_data;

	(void)argv;
	if (argc != 1)
		return (ft_print_error(ERROR_ARGUMENT_COUNT));
	shell_data = ft_calloc(sizeof(t_data), 1);
	if (errno == ENOMEM || shell_data == NULL)
		ft_exit_perror(1, "shell_data in main");
	make_initial_path_checks(envp, shell_data);
	// signal_handling(); LATER V
	line = NULL;
	while (1)
	{
		if ((line = rl_gets()) == NULL)
			break;
		token = lexical_analysis(line);
		ft_print_tokens(token); // only for testing purposes
		ast = syntax_analysis(token);
		print_ast(ast); // only for testing purposes
		// semantic_analysis(data); G
		execute_shell(&ast); // includes builtins
		// if (check_pipe(line))
			// data->exit_code = pipex(data); // to be put in semantic analysis
		// 
		// free_system(data);
	}
	// return (data->exit_code);
}

// int main(int argc, char *argv[], char **envp)
// {
//     int i = 0;
// 	(void)argc;
// 	(void)argv;
//     while (envp[i] != NULL) {
//         printf("%s\n\n", envp[i]);
//         i++;
//     }
// 	return (0);

// }
