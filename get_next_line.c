/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:47:23 by moel-idr          #+#    #+#             */
/*   Updated: 2024/11/19 20:56:13 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_join(char *buffer, char *added_string)
{
	char	*temp;

	temp = ft_strjoin(buffer, added_string);
	free(buffer);
	buffer = NULL;
	return (temp);
}

char	*take_line(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!buffer || !*buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		j = i + 1;
	else
		j = i;
	line = (char *)ft_calloc(j + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*leftovers(char *buffer)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	next = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		next[j++] = buffer[i++];
	free(buffer);
	return (next);
}

char	*read_line(char *outcome, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		num_of_bytes;

	num_of_bytes = 1;
	while (num_of_bytes > 0)
	{
		num_of_bytes = read(fd, buf, BUFFER_SIZE);
		if (num_of_bytes < 0)
		{
			free(outcome);
			free(buf);
			outcome = NULL;
		}
		buf[num_of_bytes] = 0;
		outcome = free_join(outcome, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (outcome);
}

char	*get_next_line(int fd)
{
	char *line;
	static char *buffer = NULL;

	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0 || fd < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_line(buffer, fd);
	if (!buffer || !*buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = take_line(buffer);
	buffer = leftovers(buffer);
	return (line);
}