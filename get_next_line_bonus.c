/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habovyan <habovyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:43:01 by habovyan          #+#    #+#             */
/*   Updated: 2022/05/12 16:33:31 by habovyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_stash(int fd, char *buffer)
{
	char	*buff;
	int		readed;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	readed = 1;
	while (!ft_strchr(buffer, '\n') && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[readed] = '\0';
		buffer = ft_strjoin(buffer, buff);
	}
	free(buff);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[65535];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer[fd] = read_and_stash(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = extract_line(buffer[fd]);
	buffer[fd] = clean_stash(buffer[fd]);
	return (line);
}

// int	main()
// {
// 	int		fd1;
// 	int		fd2;
// 	char	*line;

// 	fd1 = open("first.txt", O_RDONLY);
// 	line = get_next_line(fd1);
// 	printf("%s", line);
// 	fd2 = open("second.txt", O_RDONLY);
// 	line = get_next_line(fd2);
// 	printf("%s", line);
// 	line = get_next_line(fd1);
// 	printf("%s", line);
// 	line = get_next_line(fd2);
// 	printf("%s", line);
// }
