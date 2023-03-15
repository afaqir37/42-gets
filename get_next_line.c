/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 01:48:48 by afaqir            #+#    #+#             */
/*   Updated: 2023/03/15 02:28:50 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_full_line(int fd, char *ptr)
{
	int		k;
	char	*buffer;

	k = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (k && !ft_strchr(ptr, '\n'))
	{
		k = read(fd, buffer, BUFFER_SIZE);
		if (k == -1)
		{
			free (ptr);
			free (buffer);
			return (NULL);
		}
	buffer[k] = '\0';
	ptr = ft_strjoin(ptr, buffer);
	}
	free(buffer);
	return (ptr);
}

char	*updated_line(char *ptr)
{
	char	*str;
	int		i;

	i = 0;
	if (!ptr[i])
		return (NULL);
	while (ptr[i] && ptr[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (ptr[i] && ptr[i] != '\n')
	{
		str[i] = ptr[i];
		i++;
	}
	if (ptr[i] == '\n')
	{
		str[i] = ptr[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_adjust_line(char *ptr)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (ptr[i] && ptr[i] != '\n')
		i++;
	if (ptr[i] == '\n')
	{
		str = (char *)malloc(sizeof(char) * (ft_strlen(ptr) - i + 1));
		if (!str)
			return (NULL);
		i++;
		j = 0;
		while (ptr[i])
			str[j++] = ptr[i++];
		str[j] = '\0';
		free(ptr);
		return (str);
	}
	else
	{
		free(ptr);
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*ptr;

	ptr = read_full_line(fd, ptr);
	if (!ptr)
		return (NULL);
	line = updated_line(ptr);
	ptr = ft_adjust_line(ptr);
	return (line);
}

// int main()
// {
//     int fd5 = open("t.txt", O_RDONLY);
//     printf("%s", get_next_line(fd5));
//     printf("%s", get_next_line(fd5));
//     printf("/////////////////////////\n");

//     int fd6 = open("l.txt", O_RDONLY);
//     printf("%s", get_next_line(fd6));
//     printf("/////////////////////////\n");
//     printf("%s", get_next_line(fd5));
//     // int fd7 = open("m.txt", O_RDONLY);
//     // printf("%s", get_next_line(fd));
//     // printf("%s", get_next_line(fd));
// }
