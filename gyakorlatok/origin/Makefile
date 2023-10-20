PROJECT:=origin
CC:=gcc
LIBS:=-lm #-lOSIL
SRCS:=src/*
ASSETS:=assets/*
OUTPUT_FOLDER:=build
INCLUDES:=include/
IGNORE_WARNS:=-Wall -Wextra -Wpedantic
BASH:=$(shell echo $$BASH)

ifeq ($(BASH),/usr/bin/sh) #check if it's a git-bash enviroment
	REMOVE_CMD:=rm
	OUTPUT:=$(OUTPUT_FOLDER)/$(PROJECT).exe
else
	REMOVE_CMD:=del
	OUTPUT:=$(OUTPUT_FOLDER)\$(PROJECT).exe
endif

ifeq ($(OS),Windows_NT)
	LIBS:=-lglut32 -lopengl32 -lglu32 $(LIBS)	
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