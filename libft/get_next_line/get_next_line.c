/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:24:41 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/12/03 12:29:24 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_remaining(char *storage)
{
	char	*leftover;

	leftover = ft_strndup(storage + ft_strclen(storage, '\n')
			+ 1, ft_strclen(storage, '\0') - ft_strclen(storage, '\n'));
	free (storage);
	if (!leftover)
		return (NULL);
	return (leftover);
}

char	*read_text(int fd, char *storage)
{
	ssize_t	b_read;
	char	*buffer;

	b_read = 1;
	buffer = (char *)malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	*buffer = 0;
	while (b_read > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
			return (free_data(buffer, storage));
		buffer[b_read] = '\0';
		storage = ft_strjoin_gnl(storage, buffer);
	}
	if (*storage == '\0')
		return (free_data(buffer, storage));
	free(buffer);
	return (storage);
}

char	*free_data(char *buffer, char *storage)
{
	free(buffer);
	free(storage);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage)
		storage = NULL;
	storage = read_text(fd, storage);
	if (!storage)
		return (NULL);
	result = ft_strndup(storage, ft_strclen(storage, '\n') + 1);
	if (!result)
		return (NULL);
	storage = save_remaining(storage);
	if (!storage)
		free(storage);
	return (result);
}

/* int	main(void)
{
	char *line;
	int fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
} */