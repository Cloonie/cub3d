/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:15:53 by mliew             #+#    #+#             */
/*   Updated: 2022/06/02 10:15:53 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstnew(char **cmd)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->args = cmd;
	lst->append = 0;
	lst->fdpipe[0] = -1;
	lst->fdpipe[1] = -1;
	lst->delimiter = NULL;
	lst->infile = NULL;
	lst->outfile = NULL;
	lst->next = NULL;
	return (lst);
}
