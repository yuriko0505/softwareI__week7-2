SRCS   = main.c Utility.c Tile.c Field.c Judge.c Title.c Ranking.c
OBJ    = mahjong
CC     = gcc
CFLAGS = -std=c11 -O2 -Wall

$(OBJ) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(OBJ)

run :
	make $(OBJ)
	./$(OBJ)

clean :
	rm -f $(OBJ)