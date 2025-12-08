CC = cc -Wall -Wextra -Werror -g
AR = ar rcs

FT_PRINTF_FILES = ft_printf/ft_printf.c

GET_NEXT_LINE = get_next_line/get_next_line.c

FT_IS_FILES = ft_is/ft_isalnum.c ft_is/ft_isapha.c ft_is/ft_isascii.c ft_is/ft_isdigit.c ft_is/ft_isprint.c

FT_PUT_FILES = ft_put/put/ft_putnbr_hex.c ft_put/put/ft_putnbr_hexl.c ft_put/put/ft_putnbr_unsigned.c \
			ft_put/put/ft_putnbr.c ft_put/put/ft_putptr.c ft_put/put/ft_putstr.c \
			ft_put/putfd/ft_putchar_fd.c ft_put/putfd/ft_putendl_fd.c ft_put/putfd/ft_putnbr_fd.c \
			ft_put/putfd/ft_putstr_fd.c

LIST_FILES = lst/ft_lstnew.c lst/ft_lstadd_front.c lst/ft_lstsize.c \
			lst/ft_lstlast.c lst/ft_lstadd_back.c lst/ft_lstdelone.c \
			 lst/ft_lstclear.c lst/ft_lstiter.c lst/ft_lstmap.c

MEMUSE_FILES = memuse/ft_bzero.c memuse/ft_calloc.c memuse/ft_memchr.c \
			memuse/ft_memcmp.c memuse/ft_memcpy.c memuse/ft_memmove.c \
			memuse/ft_memset.c

STRMANIP_FILES =  strmanip/ft_strdup.c strmanip/ft_striteri.c \
			strmanip/ft_strjoin.c strmanip/ft_strlcat.c strmanip/ft_strlcpy.c \
			strmanip/ft_strmapi.c strmanip/ft_tolower.c strmanip/ft_toupper.c

STRUSE_FILES = struse/ft_strchr.c struse/ft_strlen.c struse/ft_strncmp.c \
			struse/ft_strnstr.c struse/ft_strrchr.c struse/ft_strtrim.c \
			struse/ft_substr.c

OTHER_FILES =  other/ft_atoi.c  other/ft_split.c other/ft_itoa.c other/free_array.c 

OBJECTS = $(FT_PRINTF_FILES:.c=.o) $(FT_IS_FILES:.c=.o) $(FT_PUT_FILES:.c=.o) $(LIST_FILES:.c=.o) \
		$(MEMUSE_FILES:.c=.o) $(STRMANIP_FILES:.c=.o) $(STRUSE_FILES:.c=.o) $(OTHER_FILES:.c=.o) \
		$(GET_NEXT_LINE:.c=.o)

NAME = libft.a

all: $(NAME)
	
%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)

clean:
	rm -rf $(OBJECTS)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: clean re fclean all
