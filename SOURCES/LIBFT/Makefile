CC = cc
CFLAGS = -Wall -Wextra -Werror
REMOVE = rm -rf
NAME = libft.a

MANDATORIO = ft_atoi.c \
	ft_bzero.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_strnstr.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_strchr.c \
	ft_memchr.c \
	ft_memset.c \
	ft_strrchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \

BONUS = 	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \

OBJ_BONUS = $(BONUS:.c=.o)

# ft_atoi.c -		convert ASCII string to integer
# ft_bzero.c -		write zeroes to a byte string
# ft_isalnum.c -	alphanumeric character test.
# ft_isalpha.c -	alphabetic character test
# ft_isascii.c -	test for ASCII character
# ft_strnstr.c -	locate a substring in a string (size-bounded)
# ft_isdigit.c -	decimal-digit character test
# ft_isprint.c -	printing character test (space character inclusive)
# ft_strlcat.c -	size-bounded string concatenation
# ft_strlcpy.c -	size-bounded string copying
# ft_strlen.c -		find length of string
# ft_strncmp.c -	compare strings (size-bounded)
# ft_tolower.c -	upper case to lower case letter conversion
# ft_toupper.c -	lower case to upper case letter conversion
# ft_strchr.c -		locate character in string (first occurrence)
# ft_memchr.c -		locate byte in byte string
# ft_memset.c -		write a byte to a byte string
# ft_strrchr.c -	locate character in string (last occurence)
# ft_memcmp.c -		compare byte string
# ft_memcpy.c -		copy memory area
# ft_memmove.c -	copy byte string
# ft_calloc.c -		memory allocation
# ft_strdup.c -		save a copy of a string (with malloc)
# ft_substr.c -		extract substring from string
# ft_strjoin.c -	concatenate two strings into a new string (with malloc)
# ft_strtrim.c -	trim beginning and end of string with the specified characters
# ft_itoa.c - 		convert integer to ASCII string.

OBJ_MAND = $(MANDATORIO:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_MAND)
	ar rc $(NAME) $(OBJ_MAND)

bonus: $(OBJ_MAND) $(OBJ_BONUS)
	ar rc $(NAME) $(OBJ_BONUS)

clean:
	$(REMOVE) $(OBJ_MAND) $(OBJ_BONUS)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all	
