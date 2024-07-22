/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analysis.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 15:18:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/07/22 15:18:43 by vbusekru      ########   odam.nl         */
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
		if (line[i] == '"')
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
	int		i = 0; //only used for printing out substrings of line

	line = clean_up_string(line);
	printf("Cleaned up string: %s\n", line); //  to be removed later
	tokens = ft_split(line, ' ');
	while (tokens[i] != NULL)
	{
		printf("Token: %s\n", tokens[i]); // Need to fix tokenization and not only use ft_split 
		i++;
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
	check_characters(line);
}

