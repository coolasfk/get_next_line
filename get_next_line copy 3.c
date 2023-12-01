/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:52 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/11/29 22:37:44 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_n(char *entire_buff, int *len, t_list **reminder)
{
	int		i;
	char	*new_content;
	int		count;


	i = 0;
	count = 0;
	// printf("^^^^^^^21entire buff: %s\n", entire_buff);
	while (entire_buff[i] != '\n' && entire_buff[i] != '\0')
		i++;
	*len += i;
	new_content = ft_substr(entire_buff, 0, i);
	if (BUFFER_SIZE > i)
	{
		*reminder = (t_list *)malloc(sizeof(t_list));
		if (!*reminder)
			return (NULL);
		(*reminder)->content = (char *)malloc(BUFFER_SIZE - i * sizeof(char) + 1);
		if (!(*reminder)->content)
			return (NULL);
		i += 1;
		while (BUFFER_SIZE > i)
		{
			(*reminder)->content[count] = entire_buff[i];
			count++;
			i++;
		}
		(*reminder)->content[count] = '\0';
		//printf("--------------------*reminder: %s\n", *reminder->content);
	}
	// printf("^^^^^^^27new_content %s\n", new_content);
	return (new_content);
}
void	print_list_and_count(t_list **m_list)
{
	int		count;
	t_list	*current;

	if (m_list == NULL || *m_list == NULL)
	{
		printf("List is empty or not initialized.\n");
		return ;
	}
	count = 0;
	current = *m_list;
	while (current != NULL)
	{
		if (current->content != NULL)
		{
			printf("Node %d content: %s\n", count, current->content);
		}
		else
		{
			printf("Node %d content is NULL.\n", count);
		}
		current = current->next;
		count++;
	}
	printf("Total number of nodes in the list: %d\n", count);
}

char	*find_line(int fd, t_list **m_list, int *len)
{
	t_list			*temp;
	int				bytes_read;
	t_list			*ptr;
	static t_list	*reminder;
	reminder = NULL;

	if (*m_list == NULL || (*m_list)->content == NULL)
	{
		temp = (*m_list == NULL) ? (t_list *)malloc(sizeof(t_list)) : *m_list;
		if (!temp)
			return (NULL);
		temp->content = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!temp->content)
			return (NULL);
		bytes_read = read(fd, temp->content, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(temp->content);
			if (*m_list == NULL)
				free(temp);
			return (NULL);
		}
		temp->content[bytes_read] = '\0';
		*len += bytes_read;
		if (*m_list == NULL)
		{
			*m_list = temp;
			temp->next = NULL;
		}
		if (ft_strchr(temp->content, '\n'))
		{
			temp->content = find_n(temp->content, len, &reminder);
			printf("$$$$$$$$$$$$$temp->content: %s\n", temp->content);
			//printf("--------------------*reminder: %s\n", *reminder->content);
			return (extract_line(m_list, len, &reminder));
		}
	}
	else
	{
		// Handle the creation of subsequent nodes
		temp = (t_list *)malloc(sizeof(t_list));
		if (!temp)
			return (NULL);
		temp->content = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!temp->content)
		{
			free(temp);
			return (NULL);
		}
		bytes_read = read(fd, temp->content, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(temp->content);
			free(temp);
			return (NULL);
		}
		temp->content[bytes_read] = '\0';
		*len += bytes_read;
		ptr = *m_list;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = temp;
		temp->next = NULL;
		if (ft_strchr(temp->content, '\n'))
		{
			temp->content = find_n(temp->content, len, &reminder);
			return (extract_line(m_list, len, &reminder));
		}
	}
	return (find_line(fd, m_list, len));
}

t_list	*create_list(void)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = NULL;
	new_node->next = NULL;
	return (new_node);
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
	if (*reminder)
	{
		while ((*reminder)->content[i] != '\0')
			len++;
		i = 0;
		printf("--------------------*reminder: %s\n", (*reminder)->content);
	}
	
	line = (char *)malloc((*len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < *len && ptr != NULL)
	{
		if (*reminder)
		{
			while ((*reminder)->content[i] != '\0')
			{
				line[i] = (*reminder)->content[i];
				i++;
			}
		}
		if (ptr->content == NULL || ptr->content[count] == '\0')
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
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*m_list = NULL;
	char			*line;
	static int		len;

	len = 0;
	line = NULL;
	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	if (m_list == NULL)
	{
		m_list = create_list();
		if (!m_list)
			return (NULL);
	}
	line = find_line(fd, &m_list, &len);
	return (line);
}

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
