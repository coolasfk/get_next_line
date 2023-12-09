/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:52 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/12/09 14:39:47 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



int	read_line(int fd, char *buffer, int *bytes_read)
{
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read < 0)
		return (-1);
	buffer[*bytes_read] = '\0';
	*bytes_read = (int)ft_strlen(buffer);
	return (*bytes_read > 0);
}

int	append_to_list(t_list **m_list, char *buffer, t_list **reminder)
{
	t_list	*temp;
	t_list	*last;

	temp = (t_list *)malloc(sizeof(t_list));
	if (!temp)
		return (-1);
	if (ft_strchr(buffer, '\n'))
		temp->content = find_n(buffer, reminder);
	else
		temp->content = ft_substr(buffer, 0, ft_strlen(buffer));
	if (!temp->content)
	{
		free(temp);
		return (-1);
	}
	temp->next = NULL;
	last = *m_list;
	if (!last)
		*m_list = temp;
	else
	{
		while (last->next)
			last = last->next;
		last->next = temp;
	}
	return (0);
}

char	*find_line(int fd, t_list **m_list, t_list **reminder)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*temp_content;

	temp_content = NULL;
	while (1)
	{
		if (*m_list != NULL && ft_strchr((*m_list)->content, '\n'))
		{
			temp_content = find_n((*m_list)->content, reminder);
			free((*m_list)->content);
			(*m_list)->content = temp_content;
			break ;
		}
		if (read_line(fd, buffer, &bytes_read) < 0)
		{
			free(*reminder);
			free_list(m_list);
			return (NULL);
		}
		if (bytes_read == 0)
			return (*m_list == NULL ? NULL : extract_line(m_list, reminder));
		if (append_to_list(m_list, buffer, reminder) < 0)
			return (NULL);
		if (ft_strchr(buffer, '\n') || bytes_read < BUFFER_SIZE)
			break ;
	}
	return (extract_line(m_list, reminder));
}

size_t	calculate_total_length(t_list *m_list)
{
	size_t	total_length;

	total_length = 0;
	while (m_list != NULL)
	{
		total_length += ft_strlen(m_list->content);
		m_list = m_list->next;
	}
	return (total_length);
}

void	construct_line(char *line, t_list *m_list)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (m_list != NULL)
	{
		j = 0;
		while (m_list->content[j] != '\0')
		{
			line[i++] = m_list->content[j++];
		}
		m_list = m_list->next;
	}
	line[i] = '\0';
}

char	*extract_line(t_list **m_list, t_list **reminder)
{
	size_t	total_length;
	char	*line;

	total_length = calculate_total_length(*m_list);
	line = (char *)malloc(total_length + 1);
	if (!line)
	{
		return (NULL);
	}
	construct_line(line, *m_list);
	free_list(m_list);
	if (*reminder)
	{
		*m_list = *reminder;
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
	static t_list	*reminder;

	reminder = NULL;
	line = NULL;
	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	line = find_line(fd, &m_list, &reminder);
	return (line);
}
