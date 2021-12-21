/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:55:54 by mangheli          #+#    #+#             */
/*   Updated: 2021/12/21 10:35:11 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include "stdio.h"

static	char	*buffupdate(char *s1, const char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	ft_strdel(&s1);
	return (temp);
}

static	char	*nextline(char *savebuff, int size)
{
	char	*temp;
	int		index;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(savebuff) - size));
	index = 0;
	temp = ft_strsub(savebuff, size + 1, ft_strlen(savebuff) - size);
	ft_strdel(&savebuff);
	savebuff = ft_strdup(temp);
	ft_strdel(&temp);
	if (savebuff[0] == '\0')
		ft_strdel(&savebuff);
	return (savebuff);
}

static	char	*read_line(char *savebuff, char **line, int *error)
{
	int	index;
	int	linesize;

	index = 0;
	linesize = 0;
	while (savebuff[linesize] != '\n' && savebuff[linesize] != '\0')
	{
		linesize++;
	}
	if (linesize != 0 || savebuff[linesize] == '\n')
		*error = 1;
	if (line == NULL)
		*line = (char *)malloc(sizeof(char) * (linesize + 1));
	else
	{
		ft_strdel(line);
		*line = (char *)malloc(sizeof(char) * (linesize + 1));
	}
	if (!line)
		*error = -1;
	*line = ft_strncpy(*line, savebuff, linesize);
	savebuff = nextline(savebuff, linesize);
	return (savebuff);
}

static	char	*open_file(char *savebuff, char **line, int fd, int *error)
{
	int		ret;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		if (savebuff == NULL && buf != NULL)
			savebuff = ft_strjoin(buf, "\0");
		else
			savebuff = buffupdate(savebuff, buf);
	}
	if (ret == -1)
	{
		*error = -1;
		ft_strdel(&savebuff);
	}
	ft_strdel(&buf);
	savebuff = read_line(savebuff, line, error);
	return (savebuff);
}

int	get_next_line(const int fd, char **line)
{
	static char	*savebuff[MAX_FD];
	int			error;

	error = 0;
	printf("savebuff before func %s\n",savebuff[fd]);
	if (line == NULL || fd < 0 || BUFF_SIZE <= 0 || fd > MAX_FD)
		return (-1);
	if (savebuff[fd])
		savebuff[fd] = read_line(savebuff[fd], line, &error);
	else
		savebuff[fd] = open_file(savebuff[fd], line, fd, &error);
	printf("savebuff after func %s\n",savebuff[fd]);
	return (error);
}
