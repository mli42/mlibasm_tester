/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 13:06:31 by mli               #+#    #+#             */
/*   Updated: 2020/03/27 22:45:08 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>

size_t		ft_strlen(const char *s);
char		*ft_strcpy(char *dst, const char *src);
int			ft_strcmp(const char *s1, const char *s2);

ssize_t		ft_write(int fd, const void *buff, size_t count);
ssize_t		ft_read(int fd, void *buff, size_t count);

char		*ft_strdup(const char *s1);

typedef struct	s_list
{
	void			*data;
	struct s_list	*next;
}				t_list;

int			ft_list_size(t_list *begin_list);
void		ft_list_push_front(t_list **begin_list, void *data);

#endif
