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
	buffer = malloc(BUFFER_SIZE + 1);
	if(buffer == NULL)
		return (NULL);
	while (count != 0 && *str != '\n')
	{
		count = read(fd,buffer,BUFFER_SIZE);
		buffer[BUFFER_SIZE] = '\0';
		if(count == -1)
		{
			free(buffer);
			free(str);
			str = NULL;
		}
		str = ft_strjoin(str,buffer);
		if(str == NULL)
			return NULL;
	}
	free(buffer);
	return(str);
}
char *get_next_line(int fd)
{
	static char *str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	str = all_buffer(str,fd);
	return (str);
}

int main()
{
	int i = open("text.txt",O_RDONLY);
	printf("%d",i);
	//ft_putstr_fd("ayoub\nrca\nabdenour",i);
	printf("%s \n", get_next_line(i));
}