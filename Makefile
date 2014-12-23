TARGET 		= opendb_tut1
#TARGET_SRC2 = createtbl_tut2
#TARGET_SRC3 = inserttbl_tut3
#TARGET_SRC4 = querytbl_tut4
#TARGET_SRC5 = bindparam_tut5
#TARGET_SRC6 = exec_tut6

INC_PATH	= /usr/include
LIB_PATH	= /usr/lib/x86_64-linux-gnu

SRC_PATH 	= ./src
OBJ_PATH 	= $(SRC_PATH)/obj
BIN_PATH 	= $(SRC_PATH)/bin
VPATH 		= $(SRC_PATH)
SRC_EXT		= .c
SRC_FILE	= $(TARGET)

SRCS		= $(addsuffix $(SRC_EXT), $(SRC_FILE))
INCLUDES	= $(addprefix -I, $(INC_PATH))
OBJS		= $(patsubst %, $(OBJ_PATH)/%, $(SRCS:$(SRC_EXT)=.o))
LDPATHS		= $(addprefix -L, $(LIB_PATH))

CFLAGS		= -Wall -o2 -g
LDFLAGS		= -lsqlite3
CC 			= gcc

all: $(BIN_PATH)/$(TARGET)

$(BIN_PATH)/$(TARGET): $(OBJS)
	@-mkdir -p $(BIN_PATH)
	$(CC) $(LDPATHS) $(LDFLAGS) -o $@ $^
	@echo "make $@ finished on `date`"
	@echo "-------------------- build $(TARGET) finished ------------------------------"

$(OBJ_PATH)/%.o: %$(SRC_EXT)
	@-mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_PATH) $(BIN_PATH)
	@echo "-------------------- clean $(OBJ_PATH) $(BIN_PATH) finished ------------------------------"

install:
	@-mkdir -p ../$(BIN_PATH)
	@cp -f $(BIN_PATH)/$(TARGET) ../$(BIN_PATH)
	@echo "-------------------- copy $(TARGET) finished ------------------------------"
