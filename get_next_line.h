/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:42 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/12/08 20:21:29 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);

char				*get_next_line(int fd);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strdup(char *s1);
size_t				ft_strlen(char *str);
char				*ft_strchr(const char *s, int c);
void				*ft_memmove(void *dst, void *src, size_t len);
char				*ft_substr(char *s, unsigned int strt, size_t len);
char				*extract_line(t_list **m_list, t_list **reminder);
char				*find_line(int fd, t_list **m_list,
						t_list **reminder);
// t_list				*create_list(void);
char				*find_n(char *entire_buff, t_list **reminder);
int					ft_strcpy(char *dst, char *src);
void				free_list(t_list **list);

#endif