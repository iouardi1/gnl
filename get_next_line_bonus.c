/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 22:23:58 by iouardi           #+#    #+#             */
/*   Updated: 2021/11/30 16:53:31 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_readline(char *str, char *buffer, int fd)
{
	char	*temp;
	int		buffer_len;

	temp = NULL;
	buffer_len = 1;
	if (!str)
		str = ft_strdup("");
	while (buffer_len > 0 && !ft_strchr(str, '\n'))
	{
		buffer_len = read(fd, buffer, BUFFER_SIZE);
		buffer[buffer_len] = '\0';
		temp = ft_strjoin(str, buffer);
		free(str);
		str = temp;
	}
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_memcpy(s2, s1, sizeof(char) * (ft_strlen(s1) + 1));
	return (s2);
}

char	*get_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	line = malloc((++i + 1) * sizeof(char));
	ft_memcpy(line, str, i);
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*str[OPEN_MAX];
	char		*line;
	size_t		buffer_len;
	char		*temp;

	line = NULL;
	temp = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) == -1)
		return (NULL);
	buffer_len = 1;
	str[fd] = ft_readline(str[fd], buffer, fd);
	line = get_line(str[fd]);
	if (ft_strchr(str[fd], '\n'))
		temp = ft_strdup(ft_strchr(str[fd], '\n'));
	else
		temp = NULL;
	free(str[fd]);
	str[fd] = temp;
	if (!ft_strlen(line))
		return (free(str[fd]), free(line), NULL);
	return (line);
}
