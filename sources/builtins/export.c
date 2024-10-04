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

void	ft_swap(t_env *a, t_env *b)
{
	t_env	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

void	ft_bubble_sort(t_env **temp_env_list)
{
	t_env	*temp;
	t_env	*temp2;

	temp = *temp_env_list;
	while (temp != NULL)
	{
		temp2 = temp->next;
		while (temp2 != NULL)
		{
			if (ft_strcmp(temp->key, temp2->key) > 0)
				ft_swap(temp, temp2);
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}

void	print_sorted_env_list(t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	ft_bubble_sort(&temp);
	while (temp != NULL)
	{
		if (temp->value != NULL)
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		else
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
}

int	ft_export(char **cmds, t_data *shell_data)
{
	// int	return_value;

	if (cmds[0] == NULL)
		print_sorted_env_list(shell_data->env_list);
		// print out SORTED env list that includes all keys, even those without values in them 
	// else
	// {
	// 	if *
	// 	// verify that the key does not start with a number but only alphabetial values, else print "export: `key_entered': not a valid identifier

	// }
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