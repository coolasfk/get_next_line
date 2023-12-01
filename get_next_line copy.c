/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:52 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/11/29 19:59:24 by eprzybyl         ###   ########.fr       */
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
static t_list	*head;
void	add_line_to_list(char *line)
{
	
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

void free_list(t_list **head) {
    t_list *current;
    t_list *next;

    current = *head;
    while (current != NULL) {
        next = current->next;
        free(current->content);
        free(current); 
        current = next;
    }
    *head = NULL; 
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
		return (new_line);
	}
	else if (line != NULL)
	{
		i = 0;
		while (buff_line[i] != '\0')
		{
			if (buff_line[i] == '\n')
			{
				buff_line[i] = '\0';
				break ;
			}
			i++;
		}
		new_line = ft_strjoin(line, buff_line);
		
		line = NULL;
	}
	// printf("new line2 %s\n", new_line);
	return (new_line);
}
char	*find_*reminder(char *buff_line)
{
	int		i;
	char	*reminder;

	*reminder = NULL;
	i = 0;
	// printf("=====buff_line: %s\n\n", buff_line);
	while (buff_line[i] != '\0')
	{
		if (buff_line[i] == '\n')
		{
			*reminder = ft_substr(buff_line, i+1, BUFFER_SIZE - i - 1);
			// printf("=====*reminder %s\n\n", *reminder);
			return (*reminder);
		}
		i++;
	}
	// printf("new line2 %s\n", new_line);
	return (*reminder);
}

char	*get_next_line(int fd)
{
	char		*buff_line;
	int			bytes_read;
	static char	*line;
	static char	*reminder;
if (fd < 0  || BUFFER_SIZE <= 0)
		return (NULL);
	if (*reminder != NULL)
	{
		line = *reminder;
		free(*reminder);
		*reminder = NULL;
	}
	
	buff_line = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buff_line)
		return (NULL);
	bytes_read = read(fd, buff_line, BUFFER_SIZE);
	if (bytes_read == 0)
	{
free_list(&head);
		return (NULL);
	}
		
	buff_line[bytes_read] = '\0';
	// printf("buff_line %s\n", buff_line);
	if (ft_strrchr(buff_line, '\n') == NULL)
	{
		line = make_full_line(buff_line, line);
	}
	else if (ft_strrchr(buff_line, '\n') != NULL)
	{
		*reminder = find_*reminder(buff_line);
		line = make_full_line(buff_line, line);
		add_line_to_list(line);
		free(buff_line);
		
		return (line);
	}
	free(buff_line);
	return (get_next_line(fd));
}
/*
int	main(void)
{
	char	*r;
	int		fd;

	fd = open("instructions.txt", O_RDONLY);
	while ((r = get_next_line(fd)) != NULL)
	{
		printf("***---r %s\n", r);
	}
	close(fd);
	return (0);
}
*/