/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:24:33 by ncastell          #+#    #+#             */
/*   Updated: 2023/05/05 12:02:16 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **str)
{
	free (*str);
	*str = NULL;
	return (NULL);
}

char	*read_buff(int fd, char *buff)
{
	char	*buffer;
	int		reader;

	buffer = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buffer)
		return (ft_free(&buff));
	buffer[0] = '\0';
	reader = 1;
	while (!ft_strchr(buffer, '\n') && reader != 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buffer);
			return (ft_free(&buff));
		}
		if (reader > 0)
		{
			buffer[reader] = '\0';
			buff = ft_strjoin(buff, buffer);
		}
	}
	free(buffer);
	return (buff);
}

char	*save_reminder(char *buff)
{
	int		i;
	int		j;
	char	*reminder;

	i = 0;
	j = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	if (!buff[i])
		return (ft_free(&buff));
	reminder = (char *)malloc((ft_strlen(buff) - i + 1) * sizeof(char));
	if (!reminder)
		return (ft_free(&buff));
	while (buff[++i] != '\0')
		reminder[j++] = buff[i];
	if (j > 0)
		reminder[j] = '\0';
	else
	{
		free(reminder);
		return (ft_free(&buff));
	}
	ft_free(&buff);
	return (reminder);
}

char	*get_next_line(int fd)
{
	static char	*buff[OPEN_MAX] = {NULL};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff[fd] = read_buff(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	line = ft_strcpyc(buff[fd], '\n');
	if (!line)
		return (ft_free(&buff[fd]));
	buff[fd] = save_reminder(buff[fd]);
	return (line);
}
