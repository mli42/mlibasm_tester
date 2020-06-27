/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlibasm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 18:06:51 by mli               #+#    #+#             */
/*   Updated: 2020/06/27 22:54:31 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLIBASM_H
# define MLIBASM_H

// #include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libasm.h"

// # define MAKEITABORT 0
# define CHECKLEAKS 1
# define STRCPY_SIZE 30

typedef struct	s_tests
{
	char	*fct_name;
	int		done;
	int		all;
}				t_tests;

enum			e_fct
{
	TOTAL,
	WR, RD, STRCMP, STRLEN, STRCPY, STRDUP,
	ATOI_BASE, LIST_PUSH_FRONT, LIST_SIZE, LIST_SORT, LIST_REMOVE_IF,
	e_end
};

extern t_tests test[e_end];

extern int wrfd, rdfd, rdfd_true, g_fail;
extern char err_buff[1024];

int		same_sign(int num1, int num2);
void	done_on_all(char *str, int done, int all);
void	ft_destructor(void);
void	ft_signal(int sign);
char	*tf_str(const int eq);
void	truefalse(const int all_good, const int ret[2], const int err[2]);
char	*which_fd(int fd);


void	wr_tests(void);
void	rd_tests(void);
void	strcmp_tests(void);
void	strcpy_tests(void);
void	strdup_tests(void);
void	strlen_tests(void);


int		test_write(const int fd, const char * const str, const int size);
int		test_read(const int fd_me, const int fd_true, const int size);
int		test_strcmp(const char * const s1, const char * const s2);
int		test_strcpy(char const * const dst, char const * const srcs);
int		test_strdup(char const *str);
int		test_strlen(char const *str);

void	check_leaks(void);

void	ft_print_list(t_list *lst);
t_list	*ft_list_push_strs(int size, char **strs);
void	ft_lstclear(t_list **lst, void (*del)(void *));
int		ft_lstcmp(t_list *lst1, t_list *lst2);

#endif
