/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/02 10:32:07 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:16 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s || !c)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[gnl_strlen((char *)s)]);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}

char	*read_buffer(int fd, char *line)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !gnl_strchr(line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free_there(&buffer);
			free_there(&line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (!line && buffer)
			line = gnl_strdup(buffer);
		else if (line && buffer)
			line = gnl_strjoin(line, buffer);
	}
	free_there(&buffer);
	return (line);
}

char	*take_line_left(char *line)
{
	size_t	i;
	size_t	j;
	char	*string;

	i = 0;
	j = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	if (i == 0 && line[i] == '\0')
		return (NULL);
	string = (char *)malloc(sizeof(char) * (i + 1));
	if (!string)
		return (NULL);
	while (j < i)
	{
		string[j] = line [j];
		j++;
	}
	string[j] = '\0';
	return (string);
}

char	*trim_line_right(char *line)
{
	int		i;
	int		j;
	char	*rest;

	if (line == NULL)
		return (free_there(&line));
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (free_there(&line));
	if (line[i] == '\n')
		i++;
	rest = (char *)malloc(sizeof(char) * (gnl_strlen(line) - i + 1));
	if (!rest)
		return (free_there(&line));
	j = 0;
	while (line[i])
		rest[j++] = line[i++];
	rest[j] = '\0';
	free_there(&line);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_there(&line));
	line = read_buffer(fd, line);
	if (!line)
		return (NULL);
	new_line = take_line_left(line);
	line = trim_line_right(line);
	if (!new_line)
		free_there(&line);
	return (new_line);
}

// int main()
// {
// 	char *result;
// 	int fd = open("short.txt", O_RDONLY);
// 	for (int i = 0; i < 10; i++) {
// 		result = get_next_line(fd);
// 		printf("%s", result);
// 		if (result != NULL)
// 			free_there(&result);
// 	}
// 	return (0);
// }

// // main helper function below
// void	print_lines(int fd)
// {
// 	char	*next;
// 	int		i = 8;

// 	next = get_next_line(fd);
// 	while (i--)
// 	{
// 		printf("%s", next);
// 		free_there(&next);
// 		next = get_next_line(fd);
// 		printf("\n");
// 	}
// 	if (next != NULL)
// 		free_there(&next);
// }

// int main(void)
// {
// 	int fd1 = 0;
// 	int fd2 = 0;
// 	int fd3 = 0;
// 	int fd4 = 0;

// 	printf("fd1\n");
// 	fd1 = open("empty.txt", O_RDONLY);
// 	if (fd1 == -1)
// 	{
// 		printf("fd1: fault");
// 		return (1);
// 	}
// 	print_lines(fd1);
// 	close(fd1);

// 	printf("fd2\n");
// 	fd2 = open("short.txt", O_RDONLY);
// 	if (fd2 == -1)
// 	{
// 		printf("fd2: fault");
// 		return (1);
// 	}
// 	print_lines(fd2);
// 	close(fd2);

// 	printf("fd3\n");
// 	fd3 = open("one.txt", O_RDONLY);
// 	if (fd3 == -1)
// 	{
// 		printf("fd3: fault");
// 		return (1);
// 	}
// 	print_lines(fd3);
// 	close(fd3);

// 	printf("fd4\n");
// 	fd4 = open("long.txt", O_RDONLY);
// 	if (fd4 == -1)
// 	{
// 		printf("fd4: fault");
// 		return (1);
// 	}
// 	print_lines(fd4);
// 	close(fd4);
// 	return (0);
// }
