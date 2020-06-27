#!/usr/bin/env bash

libasm_path='../'
libasm=$libasm_path'libasm.a'
incl_path=$libasm_path

mlibasm_srcs='./srcs'

do_test () {
	for i in "$@"; do
		if clang -Wall -Wextra -Werror -I./ $libasm mlibasm.a $mlibasm_srcs/$i \
			2>/dev/null 1>&2 ; then
			./a.out
		fi
	done
}

recompile () {
	do_bonus=0
	if ! make bonus -C $libasm_path 1>/dev/null 2>/dev/null ; then
		do_bonus=1
		printf "\e[0;91m\t\tCOULD'T COMPILE BONUS !!\e[0m\n" >&2
		if ! make -C $libasm_path 1>/dev/null ; then
			printf "\e[0;91m\t\tCOULD'T COMPILE !!\e[0m\n" >&2  && return 1
		fi
	fi

	if ! make ; then
		echo "Oopsi"
		return 1
	fi

	do_test write.c read.c strlen.c strcmp.c strcpy.c strdup.c
	if [ $do_bonus -eq 0 ]; then
		do_test atoi_base.c list_push_front.c list_size.c list_sort.c list_remove_if.c
	fi
	rm -f a.out
	make fclean
}

printf "\e[0;1;94m"
printf "# ****************************************************************************** #\n"
printf "#                                                                                #\n"
printf "#                   :::   :::   :::     :::                                      #\n"
printf "#                 :+:+: :+:+:  :+: :+: :+:                                       #\n"
printf "#               +:+ +:+:+ +:+ +:+     +:+                                        #\n"
printf "#              +#+  +:+  +#+ +#+ +#+ +#+#+#+  +#+#+#+  +#+#+#+ +#+#+#+#+         #\n"
printf "#             +#+       +#+ +#+ #+# #+#  #+#     +#+# #+#+    #+#  +  #+#        #\n"
printf "#            #+#       #+# #+# #+# #+#  #+# #+#  #+#    +#+# +#+  +  #+#         #\n"
printf "#           ###       ### ### ### #######   ####### ####### ###  #  ###          #\n"
printf "#                                                                                #\n"
printf "# ****************************************************************************** #\n\n"
printf "\e[0m"

recompile

make fclean -C $libasm_path > /dev/null
