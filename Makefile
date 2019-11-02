#******************************************************************************#
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pacovali <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/01 00:00:42 by pacovali      #+#    #+#                  #
#    Updated: 2019/01/01 00:01:42 by pacovali      ########   odam.nl          #
#                                                                              #
#******************************************************************************#

NAME = simple_opencl
SRCS = *.c
MKOBJ = @gcc -c -Wall -Wextra -Werror
HDRS = -I .
OBJS = *.o
OCL = -framework OpenCL
LFT = libft.a
MKEXE = @gcc -o

all: $(NAME)
$(NAME):
	$(MKOBJ) $(SRCS) $(HDRS)
	$(MKEXE) $(NAME) $(OBJS) $(LFT) $(OCL)

clean:
	@rm -f $(OBJS) *~

fclean: clean
	@rm -f $(NAME)

re: fclean all
