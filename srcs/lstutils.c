/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:00:58 by mli               #+#    #+#             */
/*   Updated: 2020/06/27 20:49:59 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlibasm.h"

void    ft_print_list(t_list *begin_list)
{
    while (begin_list != NULL)
    {
        printf("%s", begin_list->data);
            if (begin_list->next)
                printf(" -> ");
        begin_list = begin_list->next;
    }
    printf("\n");
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		if (del)
			del(lst->data);
		free(lst);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*then;

	current = *lst;
	while (current)
	{
		then = current->next;
		ft_lstdelone(current, del);
		current = then;
	}
	*lst = NULL;
}

t_list	*ft_create_elem(void *data)
{
	t_list	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->data = data;
	new->next = NULL;
	return (new);
}

t_list	*ft_list_push_strs(int size, char **strs)
{
	int i;
	t_list *after;
	t_list *before;

	i = 0;
	after = ft_create_elem(strs[i++]);
	while (i < size)
	{
		before = ft_create_elem(strs[i]);
		before->next = after;
		after = before;
		i++;
	}
	return (after);
}
