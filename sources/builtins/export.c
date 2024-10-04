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
	int	i;

	i = 0;
	if (ft_isdigit(key[i]) == 1)
	{
		ft_putstr_fd("export: `", fd);
		ft_putstr_fd(key, fd);
		ft_putendl_fd("': not a valid identifier", fd);
		return (false);
	}
	while (key[i] != '\0')
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
		{
			ft_putstr_fd("export: `", fd);
			ft_putstr_fd(key, fd);
			ft_putendl_fd("': not a valid identifier", fd);
			return (false);
		}
		i++;
	}
	return (true);
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
			if (ft_strchr(cmds[i], '=') != NULL)
				//add key with value if it does not exist yet or overwrite the value if it already exists
				// sort the new node if it starts with uppercase letter and put it in the end of the list if it starts with lowercase letter
			// else
				// add key with value NULL if it does not exist yet
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