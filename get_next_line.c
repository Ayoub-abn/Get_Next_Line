/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:54:54 by aabdenou          #+#    #+#             */
/*   Updated: 2023/12/09 21:55:03 by aabdenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*all_buffer(int fd, char *str)
{
	char *buffer;
	int red;

	red = 1;
	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	while (red != 0 && !ft_strchr(str,'\n'))
	{
		red = read(fd,buffer,BUFFER_SIZE);
		if(red == -1)
		{
			free(str);
			free(buffer);
			return(NULL);
		}
		str = ft_strjoin(str,buffer);
		if(buffer == NULL)
			return(NULL);
	}
	free(buffer);
	return (str);
}
char	*show_line(char *str)
{
	char *line;
	int i;
	int j;

	if (str == '\n')
		return (NULL);
	while (str && str[i] != '\n')
		i++;
	if (str == NULL)
		i++;
	line = malloc(i + 1);
	if (line == NULL)
		return (NULL);

	i = 0;
	while (line[i] && line [i] != '\n')
		line [j++] = str[i++];
	if (str[i] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}

char *get_next_line(int fd)
{
    static char *str;
    char *line;

    if(fd <= 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
        return (NULL);
    str = all_buffer(fd,str);
	if(str == NULL)
		return (NULL);
	line = show_line(str);
	return (line);
}

