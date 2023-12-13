/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:54:54 by aabdenou          #+#    #+#             */
/*   Updated: 2023/12/12 16:13:52 by aabdenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*all_buffer(char *str, int fd)
{
	char	*buffer;
	int		count;

	count = 1;
	buffer = malloc(BUFFER_SIZE);
	if (buffer == NULL)
		return (NULL);
	while (count != 0 && !ft_strchr(str, '\n'))
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
			return (free(str), free(buffer),NULL);
		buffer[count] = '\0';
		str = ft_strjoin(str, buffer);
		//str == 111111111e\0
		if (str == NULL)
			return (NULL);
	}
	// printf("----------------------");
	// printf("\nstr -------->%s",buffer);
	return (free(buffer),str);
}

char	*one_line(char *str)
{
	char	*len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	//!!!!!!!!!!!!!!!!!!!!!---------------------------------------------->tanchof malha!!!!!!!!!!!!!!!!!!!
	//if (str[i] != '\0')
	//	i++;
	len = malloc(i + 1);
	if (len == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		len[j++] = str[i++];
	if (str[i] == '\n')
		len[j++] = '\n';
	len[j] = '\0';
	return (len);
}
char	*rest(char *str)
{
	char	*s;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	// printf("----------------------");
	// printf("\nstr -------->%s",str);
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	// printf("\n-------->i :%zu\n",i);
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	s = malloc(ft_strlen(str) - i + 1);
	if (s == NULL)
		return (NULL);
	if (str[i] != '\n')
		i++;
	i++;
	while (str[i] != '\0')
		s[j++] = str[i++];
	// printf("\n-------->j :%d\n",j);
	// printf("\n-------->i :%zu\n",i);
	s[j] = '\0';
	free(str);
	//printf("last:%s\n",s);
	//printf("----------------------");
	return (s);
}
char	*get_next_line(int fd)
{
	static char	*str;
	char		*aff;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	str = all_buffer(str, fd);
	if (str == NULL)
		return (NULL);
	aff = one_line(str);
	str = rest(str);
	return (aff);
}

// int	main(void)
// {
// 	int	f;

// 	f = open("text.txt", O_RDONLY);
// 	//   get_next_line(f);
// 	//   get_next_line(f);
// 	int i = 0;
// 	while(i < 13)
// 	{
// 		printf("line %d: %s\n",i + 1, get_next_line(f));
// 		i++;
// 	}
// }
