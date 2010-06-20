CXX             =       g++
CXXFLAGS        =       -Wall -Wextra -Werror -I.

NAME            =       huffman

SRC             =       sources/node.cpp	\
                        sources/decompression.cpp   \
												sources/compression.cpp	\
												sources/common.cpp	\
                        sources/main.cpp

OBJ             =       $(SRC:.cpp=.o)

RM              =       rm -vf


all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re