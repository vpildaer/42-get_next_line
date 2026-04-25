/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpildaer <vpildaer@student.42belgium.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:27:44 by vpildaer          #+#    #+#             */
/*   Updated: 2026/04/25 14:15:18 by vpildaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*stash[1024];
	char			*line;
	int				readed;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	readed = 1;
	get_stash(fd, &stash[fd], &readed);
	if (stash[fd] == NULL)
		return (NULL);
	line = get_line(stash[fd]);
	if (line == NULL)
	{
		free_stash(&stash[fd]);
		return (NULL);
	}
	if (readed == -1)
		return (line);
	if (readed != 0)
		clean_stash(&stash[fd], readed);
	else
		free_stash(&stash[fd]);
	return (line);
}

void	get_stash(int fd, t_list **stash, int *readed)
{
	char	*buffer;

	while (!(is_new_line(*stash)))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
		{
			free_stash(stash);
			return ;
		}
		*readed = read(fd, buffer, BUFFER_SIZE);
		if (*readed == 0)
		{
			free(buffer);
			return ;
		}
		if (*readed == -1)
		{
			free(buffer);
			free_stash(stash);
			return ;
		}
		buffer[*readed] = 0;
		add_to_stash(stash, buffer, *readed);
	}
}

void	add_to_stash(t_list **stash, char *buffer, int readed)
{
	t_list	*new;
	t_list	*last;

	if (readed <= 0 || buffer[0] == '\0')
	{
		free(buffer);
		return ;
	}
	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		free(buffer);
		return ;
	}
	last = get_last_node(*stash);
	if (last == NULL)
		*stash = new;
	else
		last->next = new;
	new->content = buffer;
	new->next = NULL;
}

char	*get_line(t_list *stash)
{
	int		line_len;
	char	*line;

	if (stash == NULL)
		return (NULL);
	line_len = 0;
	count_chars(stash, &line_len);
	if (line_len == 0)
		return (NULL);
	line = malloc(sizeof(char) * (line_len + 1));
	if (line == NULL)
		return (NULL);
	line = copy_chars(stash, line);
	return (line);
}

void	clean_stash(t_list **stash, int readed)
{
	t_list	*last;
	char	*residue;
	size_t	i;
	size_t	k;

	if (stash == NULL)
		return ;
	last = get_last_node(*stash);
	residue = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (residue == NULL)
	{
		free_stash(stash);
		return ;
	}
	k = 0;
	while (last->content[k] && last->content[k] != '\n')
		k++;
	i = 0;
	while (last->content[k] && last->content[++k])
		residue[i++] = last->content[k];
	residue[i] = 0;
	free_stash(stash);
	add_to_stash(stash, residue, readed);
}
