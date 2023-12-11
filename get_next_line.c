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
 
char *all_buffer(char *str,int fd)
{
	char *buffer;
	int count;

	count = 1;
	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if(buffer == NULL)
		return (NULL);
	while (count != 0 && !ft_strchr(str, '\n'))
	{
		count = read(fd,buffer,BUFFER_SIZE);
		
		if(count == -1)
		{
			free(str);
			free(buffer);
			return NULL;
		}
		str = ft_strjoin(str,buffer);
		if(str == NULL)
			return NULL;
	}
	free(buffer);
	return(str);
}
char	*one_line(char *str)
{
	char *len;
	int i;
	int j;

	i = 0;
	j = 0;
	while (str && str[i] != '\n')
		i++;
	if(str)
		i++;
	len = malloc(i + 1);

	i = 0;
	while (str && str[i] != '\n')
		len[j++] = str[i++];
	len[j] = '\0';
	free(str);
	return (len);
}
char *get_next_line(int fd)
{
	static char *str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	str = all_buffer(str,fd);
	str = one_line(str);
	return (str);
}

// int main()
// {
// 	int i = open("text.txt",O_RDONLY);
// 	printf("%s\n", get_next_line(i));
// 	printf("%s\n", get_next_line(i));
// 	//printf("%s \n", get_next_line(i));
// }