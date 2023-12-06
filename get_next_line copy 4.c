/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:52 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/12/04 14:08:31 by eprzybyl         ###   ########.fr       */
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
		(*reminder)->content = (char *)malloc(BUFFER_SIZE - i * sizeof(char)
				+ 1);
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
		// printf("--------------------*reminder: %s\n", (*reminder)->content);
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

char	*find_line(int fd, t_list **m_list, int *len, t_list **reminder)
{
	t_list	*temp;
	int		bytes_read;
	t_list	*ptr;

	if (*m_list == NULL || (*m_list)->content == NULL)
	{
		temp = (*m_list == NULL) ? (t_list *)malloc(sizeof(t_list)) : *m_list;
		if (!temp)
			return (NULL);
		temp->content = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!temp->content)
			return (NULL);
		bytes_read = read(fd, temp->content, BUFFER_SIZE);
		/*if (bytes_read <= 0)
		{
			printf("temp=>content %s", "temp->content");
			free(temp->content);
			if (*m_list == NULL)
				free(temp);
			return (NULL);
		}
*/
		if (bytes_read == 0) // Check for EOF
		{
			if (*len > 0) // There's data in the buffer
			{
				printf("check %s", "yes");
				// Process the remaining data as the last line
				return (extract_line(m_list, len, reminder));
			}
			else
			{
				// No more data to read, return NULL
				return (NULL);
			}
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
			temp->content = find_n(temp->content, len, reminder);
			// printf("$$$$$$$$$$$$$temp->content: %s\n", temp->content);
			// printf("------------r-------*reminder: %s\n", reminder->content);
			// printf("-----r--------------*reminder: %s\n",
			return (extract_line(m_list, len, reminder));
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
		temp->content[bytes_read] = '\0';
		
		if (bytes_read == 0) 
		{
			if (*len > 0) 
			{
				
				return (extract_line(m_list, len, reminder));
			}
			else
			{
				
				return (NULL);
			}
		}
		
		*len += bytes_read;
		ptr = *m_list;
		while (ptr->next != NULL)
			ptr = ptr->next;
		if(*reminder != NULL)
		{
			ptr->next = *reminder;
			ptr = ptr->next;
		}
		ptr->next = temp;
		temp->next = NULL;
		if (ft_strchr(temp->content, '\n'))
		{
			temp->content = find_n(temp->content, len, reminder);
			
			return (extract_line(m_list, len, reminder));
		}
	}
	return (find_line(fd, m_list, len, reminder));
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
	printf("&&len %d\n", *len);
	if (*reminder != NULL)
	{
		while ((*reminder)->content[i] != '\0')
		{
			i++;
			(*len)++;
		}
		//*len -= 1;
		i = 0;
		printf("--------------------*reminder: %s\n", (*reminder)->content);
		printf("^^len %d\n", *len);
		printf("i %d\n", i);
	}
	line = (char *)malloc((*len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < *len && ptr != NULL)
	{
		if (*reminder != NULL)
		{
			while (ft_strlen((*reminder)->content) > (size_t)i)
			{
				printf("test %c\n", (*reminder)->content[i]);
				line[i] = (*reminder)->content[i];
				i++;
			}
			free((*reminder)->content);
			free(*reminder);
			*reminder = NULL;
		}
		// printf("$$$$$$$$$$$$$$$ptr->content %s\n", ptr->content);
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
	// printf("244aaaaaaLINE %s\n", line);
	// printf("245check %d\n", *len);
	// check = 1;
	return (line);
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
