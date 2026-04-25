/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpildaer <vpildaer@student.42belgium.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:17:33 by vpildaer          #+#    #+#             */
/*   Updated: 2026/04/24 02:39:23 by vpildaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;

char	*get_next_line(int fd);

char	*get_line(t_list *stash);

void	get_stash(int fd, t_list **stash, int *readed);

int		is_new_line(t_list *stash);

t_list	*get_last_node(t_list *stash);

void	add_to_stash(t_list **stash, char *buffer, int readed);

void	count_chars(t_list *stash, int *line_len);

char	*copy_chars(t_list *stash, char *line);

void	clean_stash(t_list **stash, int readed);

void	free_stash(t_list **stash);

#endif
