#!/usr/bin/env bash

libasm_path='../'
libasm=$libasm_path'libasm.a'
incl_path=$libasm_path

test_files='test.c unit_tests.c performed_tests.c utils.c'

recompile () {
	if ! make bonus -C $libasm_path 1>/dev/null 2>/dev/null ; then
		printf "\e[0;91m\t\tCOULD'T COMPILE BONUS !!\e[0m\n" >&2
		if ! make -C $libasm_path 1>/dev/null ; then
			printf "\e[0;91m\t\tCOULD'T COMPILE !!\e[0m\n" >&2  && return 1
		fi
	fi
	if ! clang -Wall -Wextra -Werror -I $incl_path $test_files $libasm ; then
		printf "\e[0;91m\t\tCOULD'T COMPILE BINARY !!\e[0m\n" >&2  && return 1
	fi
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

recompile && ./a.out;

make fclean -C $libasm_path > /dev/null
