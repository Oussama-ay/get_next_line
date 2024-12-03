/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:17:43 by oayyoub           #+#    #+#             */
/*   Updated: 2024/11/04 11:46:58 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strndup(const char *s, int n)
{
	char	*dest;
	int		i;

	if (!s)
		return (NULL);
	dest = malloc(n + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*get_line(char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '\n')
			return ((char *)str);
		str++;
	}
	return (NULL);
}

static char	*read_and_store(int fd, char **save)
{
	char		*buffer;
	int			nbr_byts;
	char		*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	nbr_byts = 1;
	while (!get_line(*save) && nbr_byts > 0)
	{
		nbr_byts = read(fd, buffer, BUFFER_SIZE);
		if (nbr_byts <= 0)
			return (free(buffer), NULL);
		buffer[nbr_byts] = '\0';
		tmp = *save;
		if (*save)
			*save = ft_strjoin(*save, buffer);
		else
			*save = ft_strdup(buffer);
		free(tmp);
	}
	return (free(buffer), get_line(*save));
}

static char	*extract_line(char **save, char *newline)
{
	char	*line;
	char	*tmp;

	if (newline)
	{
		line = ft_strndup(*save, newline - *save + 1);
		tmp = ft_strdup(newline + 1);
		free(*save);
		if (*tmp == '\0')
		{
			free(tmp);
			*save = NULL;
		}
		else
			*save = tmp;
	}
	else
	{
		line = ft_strdup(*save);
		free(*save);
		*save = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*line;
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	newline = read_and_store(fd, &save[fd]);
	line = extract_line(&save[fd], newline);
	return (line);
}
/*
int main()
{
	int fd = open("get_next_line_utils.c", O_RDONLY);
	printf("fd = %d\n", fd);
	int fd2 = open("get_next_line.h", O_RDONLY);
	printf("fd = %d\n", fd2);
	if (fd == -1 || fd2 == -1)
		return (0);
	// file 1
	char *tmp = get_next_line(fd);
	int i = 0;
	while (tmp)
	{
		printf(":file 1 | line %d : %s\n",i++ + 1, tmp);
		free(tmp);
		tmp = get_next_line(fd);
		getchar();
	}
	// file 2
	char *tmp2 = get_next_line(fd2);
	i = 0;
	while (tmp2)
	{
		printf(":file 2 | line %d : %s\n",i++ + 1, tmp2);
		free(tmp2);
		tmp2 = get_next_line(fd2);
		getchar();
	}
	printf(":line %d : %s\n",i++ + 1, tmp2);
	close(fd);
	close(fd2);
	return (0);
}*/