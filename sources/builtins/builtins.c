#include "../../includes/minishell.h"

char	*builtin_substr(char *str, int *i)
{
	int		start;
	int		len;
	char	*substr;

	start = *i;
	while (str[*i] != '\0' && str[*i] != ' ')
		(*i)++;
	len = *i - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	substr = ft_strcpy(substr, &str[start], len + 1);
	return (substr);
}

int	builtins(t_data *shell_data, char *command)
{
	printf("------IS BUILTIN CHECK-----\n");
	int		i;
	char	*substr;

	i = 0;
	while (command[i] != '\0')
	{
		substr = builtin_substr(&command[i], &i);
		if (substr == NULL)
		printf("Substring from built in check: %s\n", substr);
		// free_shell_data
		if (ft_strncmp(substr, "echo", 4) == 0)
			return (ft_echo(&command[i], shell_data->info)); // need to know which token type I have here or keep updating i. e.g. if I have "echo echo" it should create a substr of the first echo and then print the following echo
				// or update the exit code of the child??
		// if (ft_strncmp(command, "cd", 3) == 0)
		// 	return (true);
		if (ft_strncmp(substr, "pwd", 3) == 0)
			return (ft_pwd(&command[i], shell_data->info, shell_data->env_list)); // or update the exit code of the child??
		// if (ft_strncmp(command, "export", 7) == 0)
		// 	return (true);
		// if (ft_strncmp(command, "unset", 6) == 0)
		// 	return (true);
		// if (ft_strncmp(command, "env", 4) == 0)
		// 	return (true);
		// if (ft_strncmp(substr, "exit", 4) == 0)
		// 	ft_exit(shell_data, shell_data->env_list);  Need to review the exit function
		free(substr);
		// i++; //already updated in substr need to check
	}
	return (1);
}

// Only for testing purposes!
void	execute_builtins(t_data *shell_data, char **commands)
{
	
	printf("----EXECUTE BUILTINS----\n");	
	int	i;

	i = 0;
	while (commands[i] != NULL)
	{
		builtins(shell_data, commands[i]);
		i++;
	}
}

// remove later. just to visualize the commands
// echo Hello | cat test.txt | cat txt_file.sh
// < echo "hello"


// need to loop through the string. 
// if echo was found then I need to pass the string part afterwards to ft_echo
// however, I need to check 