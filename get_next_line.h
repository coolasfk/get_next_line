/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:17:42 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/11/27 12:30:49 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
void				add_line_to_list(char *line);
char				*make_full_line(char *buff_line, char *line);
char				*get_next_line(int fd);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strdup(char *s1);
size_t				ft_strlen(char *str);
char				*ft_strrchr(char *s, int c);
void				*ft_memmove(void *dst, void *src, size_t len);
char				*ft_substr(char *s, unsigned int strt, size_t len);

#endif