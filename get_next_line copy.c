/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:52 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/12/06 14:08:47 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_n(char *entire_buff, int *len, t_list **reminder)
{
	int		i;
char *new_content;
	int		count;

	(void)*len;
	i = 0;
	count = 0;
	while (entire_buff[i] != '\n' && entire_buff[i] != '\0')
		i++;
	//*len += i;
new_content = ft_substr(entire_buff, 0, i+1);

	if (entire_buff[i] == '\n')
	{
		//i++;
		if (BUFFER_SIZE > i && entire_buff[i] != '\0')
		{
			*reminder = (t_list *)malloc(sizeof(t_list));
			if (!*reminder)
				return NULL;
			(*reminder)->content = (char *)malloc(BUFFER_SIZE - i + 1);
			if (!(*reminder)->content)
			{
				free(*reminder);
				return NULL;
			}
			while (entire_buff[i] != '\0')
			{
				(*reminder)->content[count++] = entire_buff[i++];
			}
			(*reminder)->content[count] = '\0';
			(*reminder)->next = NULL;
			//*len += count;
			//printf("(*reminder)->content[count] %s\n", (*reminder)->content);
		}
	}
	//printf("........new_content %s\n", new_content);
	return (new_content);
}

char	*find_line(int fd, t_list **m_list, int *len, t_list **reminder)
{
	int		bytes_read;
	char	buffer[BUFFER_SIZE + 1];

	t_list *temp, *last;
	
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free_list(m_list);
			return (NULL); 
		}
		
		if (bytes_read == 0)
		{
			if (*m_list == NULL)
			{
				return (NULL); 
			}
			break; 
		}

		buffer[bytes_read] = '\0';
		
		temp = (t_list *)malloc(sizeof(t_list));
		if (!temp)
			return (NULL);
		
		if(ft_strchr(buffer, '\n'))
		{
			temp->content = find_n(buffer, len, reminder);
		}
		else
		{
			temp->content = ft_strdup(buffer);
		}
			
			temp->next = NULL;
			//printf("temp_content %s\n", temp->content);
	
		
		
		if (!temp->content)
		{
			free(temp);
			return (NULL);
		}

		if (!*m_list)
		{
			*m_list = temp;
		}
		else
		{
			last = *m_list;
			while (last->next)
				last = last->next;
			last->next = temp;
		}
		if (ft_strchr(buffer, '\n') || bytes_read < BUFFER_SIZE)
		{
			
			
		break; 
		}
	
	}
	
	return (extract_line(m_list, len, reminder));
}


char	*extract_line(t_list **m_list, int *len, t_list **reminder)
{
	char	*line;
	int		i;
	t_list	*ptr;
	t_list	*next;
	int		count;

	count = 0;
	i = 0;
	ptr = *m_list;
	*len = 0;
	
	while (ptr != NULL)
	{
		i = 0;
		//printf("ptr->content[i] %s\n", ptr->content);
		while (ptr->content[i] != '\0')
		{
					//printf("-------ptr->content[i] %c\n", ptr->content[i]);
			(*len)++;
			i++;
		}
		ptr = ptr->next;
	}
	i = 0;
	ptr = *m_list;
	line = (char *)malloc((*len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < *len && ptr != NULL)
	{
		if (ptr->content[count] == '\0')
		{
			ptr = ptr->next;
			count = 0;
			continue ;
		}
		line[i++] = ptr->content[count++];
	}
	line[i] = '\0';
	ptr = *m_list;
	while (ptr != NULL)
	{
		next = ptr->next;
		free(ptr->content);
		free(ptr);
		ptr = next;
	}
	*m_list = ptr;
	i = 0;
	if (*reminder)
	{
		if (*m_list == NULL)
		{
			*m_list = *reminder;
		}
		else
		{
			ptr = *m_list;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = *reminder;
		}
		*reminder = NULL;
	}
	return (line);
}
void	free_list(t_list **list)
{
	t_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = temp;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*m_list = NULL;
	char			*line;
	static int		len;
	static t_list	*reminder;

	reminder = NULL;
	len = 0;
	line = NULL;
	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	
	line = find_line(fd, &m_list, &len, &reminder);
	// printf("228-aaaaaaLINE %s", line);
	return (line);
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