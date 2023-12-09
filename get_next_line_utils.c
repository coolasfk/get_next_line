/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:48 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/12/09 14:38:39 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len || !len)
		len = 0;
	else if (s_len - start < len)
		len = s_len - start;
	new = (char *)malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	c = c % 256;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == c)
		return ((char *)s + i);
	return (NULL);
}

t_list	*set_reminder(t_list **reminder, int i, char *entire_buff)
{
	int	count;

	count = 0;
	*reminder = (t_list *)malloc(sizeof(t_list));
	if (!*reminder)
		return (NULL);
	(*reminder)->content = (char *)malloc(BUFFER_SIZE - i + 1);
	if (!(*reminder)->content)
	{
		free(*reminder);
		return (NULL);
	}
	while (entire_buff[i] != '\0')
		(*reminder)->content[count++] = entire_buff[i++];
	(*reminder)->content[count] = '\0';
	(*reminder)->next = NULL;
	return (*reminder);
}

char	*find_n(char *entire_buff, t_list **reminder)
{
	int		i;
	char	*new_content;

	i = 0;
	while (entire_buff[i] != '\n' && entire_buff[i] != '\0')
		i++;
	new_content = ft_substr(entire_buff, 0, i + 1);
	if (BUFFER_SIZE > i + 1 && entire_buff[i + 1] != '\0')
	{
		*reminder = (t_list *)malloc(sizeof(t_list));
		if (!*reminder)
			return (NULL);
		(*reminder)->content = ft_substr(entire_buff, i + 1, BUFFER_SIZE - i
				- 1);
		if (!(*reminder)->content)
		{
			free(*reminder);
			return (NULL);
		}
		(*reminder)->next = NULL;
	}
	return (new_content);
}
