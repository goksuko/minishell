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

char	*get_new_key(char *command)
{
	int	i;

	i = 0;
	while (command[i] != '=' && command[i] != '\0')
		i++;
	return (ft_substr(command, 0, i));
}

char	*get_new_value(char *command, int start)
{
	return (ft_substr(command, start, ft_strlen(command) - start));
}

void	handle_allocation_error_env(t_data **data)
{
	free_data(data);
	ft_exit_perror(ERROR_ALLOCATION, "malloc in create_new_env");
}

void	create_new_env(t_data **data, char *command)
{
	char	*new_key;
	char	*new_value;
	int		i;
	t_env	*new_env;

	new_key = get_new_key(command);
	if (new_key == NULL)
		handle_allocation_error_env(data);
	i = ft_strlen(new_key);
	if (command[i] == '=')
	{
		i++;
		new_value = get_new_value(command, i);
		if (new_value == NULL)
			handle_allocation_error_env(data);
	}
	else
		new_value = NULL;
	new_env = ft_new_node(new_key, new_value);
	if (new_env == NULL)
		handle_allocation_error_env(data);
	printf("new_env->key: %s\n", new_env->key);
	printf("new_env->value: %s\n", new_env->value);
	add_new_env_node(&(*data)->env_list, new_env);
}

int	ft_export(char **cmds, t_data *data)
{
	int	i;

	printf("----EXPORT----\n");
	printf("%s\n", cmds[0]);
	if (cmds[0] == NULL)
		print_sorted_env_vars(&data->env_list, data->info->fd_out);
	else
	{
		i = 0;
		while (cmds[i] != NULL)
		{
			if (verify_key(cmds[i], data->info->fd_out) == false)
				return (ERROR_INVALID_IDENTIFIER); // need to make sure that this error message does not get printed or else remove the print statements in the validation check
			create_new_env(&data, cmds[i]);
			i++;
		}
	}
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