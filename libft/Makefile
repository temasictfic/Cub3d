# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 04:05:07 by sciftci           #+#    #+#              #
#    Updated: 2023/05/06 05:09:24 by sciftci          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER			=	libft.h

NAME			=	libft.a

SRCS			=	ft_max_min.c\
					ft_isdigit.c\
					ft_isspace.c\
					ft_isnumber.c\
					ft_arrlen.c\
					ft_strlen.c\
					ft_bzero.c\
					ft_strcpy.c\
					ft_strchr.c\
					ft_strcmp.c\
					ft_strrstr.c\
					ft_atoi.c\
					ft_calloc.c\
					ft_free.c\
					ft_strdup.c\
					ft_substr.c\
					ft_strnadd.c\
					ft_split.c\
					ft_push_str.c\
					get_next_line.c

OBJS			=	$(SRCS:.c=.o)

GCC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

RM				=	rm -f

.c.o:
				$(GCC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				ar rc $@ $^
				ranlib $@

all:			$(NAME)

clean:
				$(RM) $(OBJS)
			
fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re