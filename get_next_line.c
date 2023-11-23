/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:52 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/11/24 00:15:17 by eprzybyl         ###   ########.fr       */
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

	ptr = head;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return ;
	new->content = ft_strdup(line);
	new->next = NULL;
	if (head == NULL)
	{
		head = new->content;
	}
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
	}
	new->content = ptr;
	ptr = new;
}

char	*make_full_line(char *buff_line, char *line)
{
	ft_strjoin(line, buff_line);
    printf("%s", line);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buff_line;
	int			byte_read;
	static char	*line;

	if (fd == -1 || BUFFER_S < 1)
		return (NULL);
    buff_line = (char*)malloc(BUFFER_S * sizeof(char)+1);
    if(!buff_line)
    return NULL;
	while ((byte_read = read(fd, buff_line, BUFFER_S)) > 0)
	{
        
        
		if (buff_line[byte_read] == '\n')
		{
             printf("--yesss %s","yess");
			buff_line[byte_read] = '\0';
            printf("---buff_line %s", buff_line);
            printf("---buff_line %d", byte_read);
			add_line_to_list(line);
		}
		buff_line[byte_read] = '\0';
        
		line = make_full_line(buff_line, line);
	}
	free(buff_line);
	if (byte_read == -1)
		return (NULL);
	return (line);
}

int	main(void)
{
	char	*line;

	int fd = open("instructions.txt", O_RDONLY); // Open a file for reading
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line); // Print each line
		free(line);         // Free the line after use
	}
	close(fd); // Close the file descriptor
	return (0);
}
