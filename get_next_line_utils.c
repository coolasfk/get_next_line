/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:48 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/12/04 11:49:01 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*s2;
	int		len;

	len = ft_strlen(s1);
	i = 0;
	s2 = (char *)malloc(len * sizeof(char) + 1);
	if (!s2)
		return (NULL);
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*new;
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	// printf("s1, s2: %s %s\n", s1, s2);
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(len * sizeof(char) + 1);
	if (!new)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		new[i] = s1[i];
		i++;
	}
	while (i < len)
	{
		new[i] = s2[c++];
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

/*
The	strdup(void) function creates a duplicate of the string pointed to by src,
and returns a pointer to the new copy.
The		strdup(void) function allocates the memory for the new string by calling malloc();
it's up to you to release the memory by calling free().
*/

void	*ft_memmove(void *dst, void *src, size_t len)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (d < s)
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (d > s)
	{
		while (len > 0)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	return (d);
}

char	*ft_substr(char *s, unsigned int strt, size_t len)
{
	size_t			i;
	char			*new;
	unsigned int	s_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s[i] == '\0' || strt > s_len)
		return (ft_strdup(""));
	if (s_len - strt < len)
		len = s_len - strt;
	new = (char *)malloc(len * sizeof(char) + 1);
	if (!new)
		return (NULL);
	while (len > i)
	{
		new[i] = s[strt + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
int	ft_strcpy(char *dst, char *src)
{
	char *d;
	char *s;
	size_t i;

	i = 0;
	d = (char *)dst;
	s = (char *)src;

	while (src[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';

	return (ft_strlen(src));
}