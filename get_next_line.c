/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 05:06:40 by skalkan           #+#    #+#             */
/*   Updated: 2025/03/21 13:05:47 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(char *line, int fd)
{
	ssize_t	read_len;
	char	*buffer;
	char	*temp;

	if (!line)
		line = ft_strdup("");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_len = 1;
	while (!ft_strchr(line, '\n') && read_len > 0)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len > 0)
		{
			buffer[read_len] = '\0';
			temp = line;
			line = ft_strjoin2(line, buffer);
			free(temp);
		}
	}
	free(buffer);
	if (read_len == -1)
		return (free(line), NULL);
	return (line);
}

char	*ft_get_next_line(char *line)
{
	int		i;
	char	*str;

	if (!line || !*line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	ft_strncpy(str, line, i + (line[i] == '\n'));
	str[i + (line[i] == '\n')] = '\0';
	return (str);
}

char	*new_line(char *line)
{
	char	*remain;
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	remain = ft_strdup(&line[i + 1]);
	free(line);
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(line, fd);
	if (!line)
		return (NULL);
	next_line = ft_get_next_line(line);
	line = new_line(line);
	if (!line || line[0] == '\0' || line[0] == '\n')
	{
		free(line);
		line = NULL;
	}
	return (next_line);
}
