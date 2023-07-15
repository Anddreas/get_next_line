/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handrias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:49:04 by handrias          #+#    #+#             */
/*   Updated: 2023/05/24 16:49:09 by handrias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*erkrord_mek(char *str, int len, int l)
{
	int		i;
	char	*p;

	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (str[l] != '\0')
	{
		p[i] = str[l];
		i++;
		l++;
	}
	p[i] = '\0';
	free(str);
	str = 0;
	return (p);
}

static char	*erkrord(char *str)
{
	int		i;
	int		j;
	int		l;
	char	*p;

	i = 0;
	j = 0;
	l = 0;
	if (str == 0 || *str == 0)
		return (0);
	if (ft_strchr(str, '\n') != NULL)
	{
		while (str[i] != '\n' && str[i] != '\0')
			i++;
		if (str[i] == '\n')
			i++;
		l = i;
		while (str[i++] != '\0')
			j++;
		p = erkrord_mek(str, j, l);
		return (p);
	}
	return (NULL);
}

static char	*arajin_mek(char *str, int length)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)malloc(sizeof(char) * (length + 1));
	if (!p)
		return (NULL);
	while (i < length)
	{
		p[i] = str[i];
		i++;
	}
	p[length] = '\0';
	if (str[i - 1] == '\n')
	{
		p[i - 1] = '\n';
		p[i] = '\0';
	}
	else
	{
		p[i] = '\0';
		free(str);
	}
	return (p);
}

static char	*arajin(char *str)
{
	int		i;
	char	*p;

	i = 0;
	if (str == NULL || *str == '\0')
	{
		if (str)
			free(str);
		return (NULL);
	}
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	p = arajin_mek(str, i);
	return (p);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	int			l;
	static char	*str;
	char		*p;

	l = 0;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	while (1)
	{
		l = read(fd, buffer, BUFFER_SIZE);
		if (l <= 0)
			break ;
		buffer[l] = '\0';
		str = ft_strjoin(str, buffer);
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (l < 0)
		return (0);
	p = arajin(str);
	str = erkrord(str);
	return (p);
}
