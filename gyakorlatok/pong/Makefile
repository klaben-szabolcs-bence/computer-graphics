CC:=gcc
LIBS:=-lm #-lOSIL
SRCS:=src/*
ASSETS:=assets/*
OUTPUT_FOLDER:=build
OUTPUT:=$(OUTPUT_FOLDER)\pong.exe
INCLUDES:=include/
IGNORE_WARNS:=-Wall -Wextra -Wpedantic

ifeq ($(OS),Windows_NT)
	LIBS:=-lglut32 -lopengl32 -lglu32 $(LIBS)
	REMOVE_CMD:=del
else
	LIBS:=-lGL -lGLU -lglut $(LIBS)
	REMOVE_CMD:=rm
endif

all:
	@mkdir $(OUTPUT_FOLDER)
    #@cp $(ASSETS) $(OUTPUT_FOLDER)
	$(CC) -I$(INCLUDES) $(SRCS) $(LIBS) -o $(OUTPUT) $(IGNORE_WARNS)

clean:
	@$(REMOVE_CMD) $(OUTPUT)
	rmdir $(OUTPUT_FOLDER)