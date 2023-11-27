/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:52 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/11/24 23:22:44 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
*/

#include "get_next_line.h"

void	add_line_to_list(char *line)
{
	static t_list	*head;
	t_list			*new;
	t_list			*ptr;

	// printf("%s", "hello\n");
	// printf("line: %s", line);
	ptr = head;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return ;
	new->content = ft_strdup(line);
	new->next = NULL;
	if (head == NULL)
	{
		head = new;
	}
	else
	{
		ptr = head;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

char	*make_full_line(char *buff_line, char *line)
{
	int		i;
	char	*new_line;

	new_line = NULL;
	i = 0;
	if (line == NULL)
	{
		new_line = (char *)malloc(ft_strlen(buff_line) * sizeof(char) + 1);
		if (!new_line)
			return (NULL);
		while (buff_line[i] != '\0')
		{
			new_line[i] = buff_line[i];
			i++;
		}
		new_line[i] = '\0';
		// printf("new line1 %s\n", new_line);
		return (new_line);
	}
	else if (line != NULL)
	{
		new_line = ft_strjoin(line, buff_line);
		free(line);
		line = NULL;
	}
	// printf("new line2 %s\n", new_line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	char	*buff_line;
	int		byte_read;
	int		i;
	char	*line;
	
	line = NULL;
	i = 0;
	
	buff_line = (char *)malloc(BUFFER_S * sizeof(char) + 1);
	if (!buff_line)
		return (NULL);
	if (fd < 0 || fd > 4095 || BUFFER_S<= 0 || read(fd, buff_line, 0) < 0)
		return (NULL);
	while ((byte_read = read(fd, buff_line, BUFFER_S)) > 0)
	{
		printf("****buff_read %d\n", byte_read);
		buff_line[byte_read] = '\0';
		i = 0;
		
		while (buff_line[i] != '\0')
		{
			if (buff_line[i] == '\n')
			{
				buff_line[i] = '\0';
				printf("strlen %zu\n", ft_strlen(buff_line));
				printf("---buff_read %d\n", byte_read);
				add_line_to_list(line);
				
				break ;
			}
			i++;
		}
		line = make_full_line(buff_line, line);
		// printf("***line %s\n", line);
	}
	free(buff_line);
	// printf("line1: %s\n", line);
	/*
	if (byte_read < 1)
	{
		return (NULL);
	}*/
	// printf("line2: %s\n", line);
	return (line);
}

int	main(void)
{
	char	*r;
	int		fd;

	fd = open("instructions.txt", O_RDONLY);
	while ((r = get_next_line(fd)) != NULL)
	{
		printf("***---r %s", r);
	}
	close(fd);
	return (0);
}
