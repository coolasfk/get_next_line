/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:52 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/12/08 20:38:50 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_n(char *entire_buff, t_list **reminder)
{
	int		i;
	char	*new_content;
	int		count;

	i = 0;
	count = 0;
	while (entire_buff[i] != '\n' && entire_buff[i] != '\0')
		i++;
	if (entire_buff[i] == '\0')
	{
		return (ft_substr(entire_buff, 0, i));
	}
	new_content = ft_substr(entire_buff, 0, i + 1);
	if (entire_buff[i] == '\0')
		return (new_content);
	i++;
	if (BUFFER_SIZE > i && entire_buff[i] != '\0')
	{
		*reminder = (t_list *)malloc(sizeof(t_list));
		if (!*reminder)
			return (NULL);
		(*reminder)->content = (char *)malloc(BUFFER_SIZE - i + 1);
		if (!(*reminder)->content)
		{
			free(new_content);
			free(*reminder);
			return (NULL);
		}
		while (entire_buff[i] != '\0')
		{
			(*reminder)->content[count++] = entire_buff[i++];
		}
		(*reminder)->content[count] = '\0';
		(*reminder)->next = NULL;
	}
	return (new_content);
}

char	*find_line(int fd, t_list **m_list, t_list **reminder)
{
	int		bytes_read;
	char	buffer[BUFFER_SIZE + 1];
	t_list	*temp;
	t_list	*last;
	char	*temp_content;

	temp_content = NULL;
	while (1)
	{
		/*
		if (*m_list != NULL && (*m_list)->content[0] == '\n')
		{
			if((*m_list)->content[0] == '\n')
			temp_content = find_n((*m_list)->content, reminder,
					(int)ft_strlen((*m_list)->content));
			free((*m_list)->content); // Free the old content
			(*m_list)->content = temp_content ? temp_content : ft_strdup("\n");
			break ;
		}*/
		/*
		else if (*m_list != NULL)
		{
			temp_content = find_n((*m_list)->content, reminder,
			(int)ft_strlen((*m_list)->content));
			free((*m_list)->content); // Free the old content
			(*m_list)->content = temp_content ? temp_content : ft_strdup("\n");
			break ;
		}
*/
		if (*m_list != NULL && ft_strchr((*m_list)->content, '\n'))
		{
			temp_content = find_n((*m_list)->content, reminder);
			free((*m_list)->content);
			(*m_list)->content = temp_content;
			break ;
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			
			free(*reminder);
			free_list(m_list);
			return (NULL);
		}
		if (bytes_read == 0)
		{
			if (*m_list == NULL)
			{
				return (NULL);
			}
			break ;
		}
		buffer[bytes_read] = '\0';
		bytes_read = (int)ft_strlen(buffer);
		temp = (t_list *)malloc(sizeof(t_list));
		if (!temp)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
		{
			temp->content = find_n(buffer, reminder);
		}
		else
		{
			temp->content = ft_strdup(buffer);
		}
		temp->next = NULL;
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
			break ;
		}
	}
	return (extract_line(m_list, reminder));
}

char	*extract_line(t_list **m_list, t_list **reminder)
{
	char	*line;
	int		i;
	t_list	*ptr;
	t_list	*next;
	int		count;

	count = 0;
	i = 0;
	ptr = *m_list;
	while (ptr != NULL)
	{
		count = 0;
		while (ptr->content[count] != '\0')
		{
			count++;
			i++;
		}
		ptr = ptr->next;
	}
	ptr = *m_list;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	count = 0;
	while (ptr != NULL)
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
			*m_list = (t_list *)malloc(sizeof(t_list));
			if (!*m_list)
			{
				return (NULL);
			}
			(*m_list)->content = ft_strdup((*reminder)->content);
			(*m_list)->next = NULL;
			free((*reminder)->content);
			free(*reminder);
			*reminder = NULL;
		}
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
	static t_list	*reminder;

	reminder = NULL;
	line = NULL;
	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	line = find_line(fd, &m_list, &reminder);
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