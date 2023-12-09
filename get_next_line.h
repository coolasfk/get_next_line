/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:42 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/12/09 19:35:14 by eprzybyl         ###   ########.fr       */
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
char				*ft_substr(char *s, unsigned int start, size_t len);
size_t				ft_strlen(char *str);
char				*ft_strchr(const char *s, int c);
t_list				*set_reminder(t_list **reminder, int i, char *entire_buff);
char				*find_n(char *entire_buff, t_list **reminder);
int					read_line(int fd, char *buffer, int *bytes_read);
int					append_to_list(t_list **m_list, char *buffer,
						t_list **reminder);
char				*find_line(int fd, t_list **m, t_list **rem, char *temp);
size_t				calculate_len(t_list *m_list);
void				construct_line(char *line, t_list *m_list);
char				*extract_line(t_list **m_list, char *line, int i, int len);
void				free_list(t_list **list);
char				*get_next_line(int fd);
#endif