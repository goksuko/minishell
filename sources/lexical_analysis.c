/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analysis.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 15:18:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/07/29 18:09:20 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_characters(char *line)
{
	int	i;
	int	count;
	int	wrong_char;

	ft_printf("check_characters\n");
	count = 0;
	i = 0;
	wrong_char = 0;
	while (line && line[i])
	{
		if (line[i] == '"') // make sure it does not handle unclosed quotes
			count++;
		if (line[i] == '\\' || line[i] == ';')
			wrong_char++;
		i++;
	}
	if (count % 2 != 0)
		ft_exit_str_free_fd((ERROR_QUOTE), line, STDERR_FILENO);
	if (wrong_char)
		ft_exit_str_free_fd((ERROR_WRONG_CHAR), line, STDERR_FILENO);
	return ;
}



// void	tokenize(char *line, t_token *tokens)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i] != '\0' && (line[i] != ';' || line[i] != '\\'))
// 	{
// 		if (line)
// 		i++;
// 	}


// }

bool	command_check(char *str)
{
		if (ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "cd", 2) == 0 \
		|| ft_strncmp(str, "pwd", 3) == 0 || ft_strncmp(str, "export", 6) == 0 \
		|| ft_strncmp(str, "unset", 5) == 0 || ft_strncmp(str, "env", 3) == 0 \
		|| ft_strncmp(str, "exit", 4) == 0)
			return (true);
		return (false);
}

char **tokenize(char *line)
{
	char	**split_line;
	t_token *new_token;
	int	i;

	split_line = ft_split(line, ' ');
	if (split_line == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	// print substrings here for checking
	new_token = NULL;
	i = 0;
	free(line);
	while (split_line[i] != NULL) // && line[i] != '\\' || line[i] != ';')
	{
		// check if string is command
		if (command_check(split_line[i]) == true)
		{
			new_token = ft_token_new(split_line[i], TOKEN_COMMAND);
			//if (new_token == NULL)
			//free substrings and exit program
		}
		i++;
	}
	return (new_token);
}

bool	metacharacter_check(char *line) // to finish
{
	int		i;
	char	quote;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || '\"')
		{
			quote = quote_check(line[i]); // to be added
		}
	}	
}

char	*clean_up_string(char *line)
{
	char	*clean_string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean_string = malloc((ft_strlen(line) + 1) * sizeof(char));
	if (clean_string == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	while (is_whitespace(line[i]) == true)
		i++;
	while (line[i] != '\0')
	{
		if (is_whitespace(line[i]) == false)
			clean_string[j++] = line[i++];
		else
		{
			if (line[i] != '\0')
				clean_string[j++] = ' ';
			while (is_whitespace(line[i]) == true)
				i++;
		}
	}
	clean_string[j] = '\0';
	free(line);
	return (clean_string);
}

void	lexical_analysis(char *line)
{
	char	**tokens;
	int		number_tokens;
	// char			**tokens;
	//int		i = 0; //only used for printing out substrings of line

	if (line[0] == '\0')
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	line = clean_up_string(line);
	printf("Cleaned up string: %s\n", line); //  to be removed later
	//check meta data here
	if (metacharacter_check(line) == false)
		ft_exit_str_free_fd(ERROR_SYNTAX, line, STDERR_FILENO); // should maybe change to meta error
	// number of tokens
	tokens = (char **)malloc((number_tokens + 1) * sizeof(char *));
	if (tokens == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	tokens = tokenize(line);
	if (tokens == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	while (tokens != NULL)
	{
		ft_print_tokens(tokens);
		tokens++;
	}
	//during the tokenization nclude in the while loop that while() it is not ';' or '\' 

	//check_characters(line);
}


// 1. Input preprocessing: cleaning up the input text and preparing it for
	// the lexical analysis. E.g. removing comments, whitespaces and other non-essential characters
	// 2. Tokenization: breaking the input text into a sequence of tokens. Usually done by
	// matching the characters in the input text against a set of patterns or regular expressions
	// that define the different types of tokens
	// 3. Token classification: lexer determines the type of each token. 
	// E.g., keywords, identifiers, operators, and punctuation 
	// 4. Token validation: lexer checks that each token is valid according to the rules of the programming languague
	// E.g. migt check that a variable name is a valid identifier, or that an operator has correct syntax
	// 5. Output generation: lexer generates the output of the lexical analysis process, which is typically a list of tokens
	// list of tokens can be passed to the next stage, such as compilation or interpretation
	// 6. Lexical analyzer identifies the error with the help of the grammar of the C language, and gives
	// it row number and column number of the error