/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpildaer <vpildaer@student.42belgium.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:20:27 by vpildaer          #+#    #+#             */
/*   Updated: 2026/04/24 16:02:11 by vpildaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*get_last_node(t_list *stash)
{
	if (stash == NULL)
		return (NULL);
	while (stash->next != NULL)
		stash = stash->next;
	return (stash);
}

int	is_new_line(t_list *stash)
{
	t_list	*last;
	size_t	i;

	if (stash == NULL)
		return (0);
	last = get_last_node(stash);
	i = 0;
	while (last->content[i] && i <= BUFFER_SIZE)
	{
		if (last->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	count_chars(t_list *stash, int *line_len)
{
	size_t	i;

	if (stash == NULL || line_len == NULL)
		return ;
	while (stash != NULL)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line_len)++;
				return ;
			}
			(*line_len)++;
			i++;
		}
		stash = stash->next;
	}
}

char	*copy_chars(t_list *stash, char *line)
{
	size_t	i;
	size_t	k;

	if (stash == NULL || line == NULL)
		return (NULL);
	i = 0;
	while (stash != NULL)
	{
		k = 0;
		while (stash->content[k])
		{
			if (stash->content[k] == '\n')
			{
				line[i++] = '\n';
				line[i] = 0;
				return (line);
			}
			line[i++] = stash->content[k++];
		}
		stash = stash->next;
	}
	line[i] = 0;
	return (line);
}

void	free_stash(t_list **stash)
{
	t_list	*temp;

	while (*stash != NULL)
	{
		temp = (*stash)->next;
		free((*stash)->content);
		free(*stash);
		*stash = temp;
	}
}
