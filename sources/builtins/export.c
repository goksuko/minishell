#include "../../includes/minishell.h"

// Export add a new node to the linked list env.

// if the keyword doesn't have value, set it as NULL and it is not showed when is call env

// if the keyword received an = and a value, it will appear on env calls

// if only use the export command without argument gives an alphabetic ordered linked list with the node recent added not ordered, it will appear in the end of the list.

// if the keyword exist and it is possible to set a new value to it using =.

// EX:
// r@f1r6s9:~$ export
// declare -x COLORTERM="truecolor"
// declare -x DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/151977/bus"

// declare -x ZSH="/home/r/.oh-my-zsh"
// declare -x avocado

// declare -x ZSH="/home/r/.oh-my-zsh"
// declare -x avocado="abacate"
// declare -x edu

// declare -x ZSH="/home/edribeir/.oh-my-zsh"
// declare -x avocado="abacate"
// declare -x edu="eu"

// r@f1r6s9:$ export edu=tst
// r@f1r6s9:$ export

// declare -x ZSH="/home/r/.oh-my-zsh"
// declare -x avocado="abacate"
// declare -x edu="tst"


// First char cannot be numerical only alpha! If it is not alpha it will not create a node and it will print a error, for example '=' is not an alpha
// the new node will be sorted if it starts with uppercase, but lower case put it on the end of the list.
// idea to only print in the alph order, not sort the env

//_____________________________________________________

bool	verify_key(char *key, int fd)
{
	if (ft_isalpha(key[0]) == false && key[0] != '_')
	{
		ft_putstr_fd("export: `", fd);
		ft_putstr_fd(key, fd);
		ft_putendl_fd("': not a valid identifier", fd);
		return (false);
	}
	return (true);
}

char	*extract_key(char *command)
{
	int		i;
	char	*key;

	i = 0;
	while (command[i] != '=')
		i++;
	key = ft_substr(command, 0, i);
	if (key == NULL)
		return (NULL);
	return (key);
}

void	add_new_env_node(t_env **env_list, t_env *new_env)
{
	t_env	*current;

	current = *env_list;
	if (ft_strncmp(new_env->key, current->key, ft_strlen(new_env->key)) < 0)
	{
		new_env->next = current;
		*env_list = new_env;
	}
	else
	{
		current = *env_list;
		while (current->next != NULL && ft_strncmp(current->next->key, new_env->key, ft_strlen(new_env->key)) < 0)
			current = current->next;
		new_env->next = current->next;
		current->next = new_env;
		//current->next = NULL;
	}
}

void	create_new_env(t_data **shell_data, char *command)
{
	char	*new_key;
	char	*new_value;
	int		i;
	t_env	*new_env;

	i = 0;
	while (command[i] != '=' && command[i] != '\0')
		i++;
	new_key = ft_substr(command, 0, i);
	if (new_key == NULL)
	{
		free_shell_data(shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in create_new_env");
	}
	if (command[i] == '=')
	{
		i++;
		new_value = ft_substr(command, i, ft_strlen(command) - i);
		if (new_value == NULL)
		{
			free_shell_data(shell_data);
			ft_exit_perror(ERROR_ALLOCATION, "malloc in create_new_env");
		}
	}
	else
		new_value = NULL;
	new_env = ft_new_node(new_key, new_value);
	if (new_env == NULL)
	{
		free_shell_data(shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in create_new_env");
	}
	printf("new_env->key: %s\n", new_env->key);
	printf("new_env->value: %s\n", new_env->value);
	add_new_env_node(&(*shell_data)->env_list, new_env);
}

int	ft_export(char **cmds, t_data *shell_data)
{
	// int	return_value;
	int	i;

	printf("----EXPORT----\n");
	printf("%s\n", cmds[0]);
	if (cmds[0] == NULL)
		print_sorted_env_vars(&shell_data->env_list, shell_data->info->fd_out);
	else
	{
		i = 0;
		while (cmds[i] != NULL)
		{
			if (verify_key(cmds[i], shell_data->info->fd_out) == false)
				return (ERROR_INVALID_IDENTIFIER); // need to make sure that this error message does not get printed or else remove the print statements in the validation check
			create_new_env(&shell_data, cmds[i]);
			i++;
		}
	}
	printf("--++++++++++++++--EXPORT DONE!-+++++++++++++++---\n");
	return (SUCCESS);
}

// Example 1:
// export var45=sth -> declare -x var45="sth"

// Example 2:
// export "var45=sthoo" -> declare -x var45="sthoo"

// Example 3:
// export var45 = 
// bash: export: `=': not a valid identifier  -> declare -x var45

// Example 4:
// export export var45 "Hello"  -> declare -x var45, declare -x export, declare -x Hello

// Example 5:
// export HELLO=HELLo VANESSA=vbusekruuu
// declare -x HELLO="HELLo"
// declare -x VANESSA="vbusekruuu"

// Example 6:
// bash-3.2$ export 12lk
// bash: export: `12lk': not a valid identifier