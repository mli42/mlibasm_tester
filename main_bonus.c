/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:00:58 by mli               #+#    #+#             */
/*   Updated: 2020/03/27 23:22:29 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include <stdlib.h>

int		ft_printf(const char *str, ...);

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

int     main(void)
{
    t_list  *list;
    char *strs[] = {"R", "4", "3", "2", "1"};

//  00 create elem + 05 push strs
    list = ft_list_push_strs(5, strs);
    printf("List Content [%d]:\n", ft_list_size(list));
    ft_print_list(list);
//  lstsize + push front
	ft_list_push_front(&list, "0");
    printf("\nList Content [%d]:\n", ft_list_size(list));
    ft_print_list(list);
	return (0);
}
