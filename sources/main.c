/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/02 12:56:25 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_pipe(int argc, char *argv[])
{
	int i;
	int	j;

	ft_printf("check_pipe\n");
	i = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '|')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

int	check_characters(int argc, char *argv[])
{
	int	i;
	int	j;
	int count;

	ft_printf("check_characters\n");
	count = 0;
	i = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '"')
				count++;
			if (argv[i][j] == '\\' || argv[i][j] == ';')
				return (ERROR_WRONG_CHAR);
			j++;
		}
		i++;
	}	
	if (count % 2 != 0)
		return (ERROR_QUOTE);
	return (0);
}

int check_args(int argc, char *argv[], char **envp)
{
	int		exit_code;

	ft_printf("check_args\n");
	exit_code = 0;
	if (check_pipe(argc, argv))
		return (pipex(argc, argv, envp));
	exit_code = check_characters(argc, argv);
	if (exit_code)
		return (ft_print_error(exit_code));
	return (exit_code);
}

void	init_info(t_info *info, int argc, char *argv[], char **envp)
{
	info->argc = argc;
	info->argv = argv;
	info->envp = envp;
	info->exit_code = 0;
	return ;
}

int	main(int argc, char *argv[], char **envp)
{
	t_info	*info;

	info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (info == NULL || errno == ENOMEM)
		ft_exit_perror(ERROR_ALLOCATION, "info in main");
	init_info(info, argc, argv, envp);
	info->exit_code = check_args(argc, argv, envp);
	ft_printf("exit code: %d\n", info->exit_code);
	return (info->exit_code);
}
