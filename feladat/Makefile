PROJECT:=golf
CC:=gcc
LIBS:= -lm -lobj -lSOIL
SRCS:=src/*
ASSETS:=assets/*
OUTPUT_FOLDER:=build
INCLUDES:=include/
WARNS:=-Wall -Wextra -Wpedantic
BASH:=$(shell echo $$BASH)

ifeq ($(OS),Windows_NT)
	LIBS:=$(LIBS) -lglut32 -lopengl32 -lglu32
	EXTENSION:=.exe	
else
	LIBS:=-lGL -lGLU -lglut $(LIBS)
	REMOVE_CMD:=rm
	EXTENSION:=
endif

ifeq ($(BASH),/usr/bin/sh) #check if it's a git-bash enviroment
	REMOVE_CMD:=rm
	SEP:=/
else
	REMOVE_CMD:=del
	SEP:=$(shell echo \)
endif

OUTPUT:=$(OUTPUT_FOLDER)$(SEP)$(PROJECT)$(EXTENSION)

all:
	@mkdir $(OUTPUT_FOLDER)
	@cp $(ASSETS) $(OUTPUT_FOLDER)
	$(CC) -I$(INCLUDES) $(SRCS) $(LIBS) -o $(OUTPUT) $(WARNS)

clean:
	$(REMOVE_CMD) $(OUTPUT_FOLDER)$(SEP)*
	rmdir $(OUTPUT_FOLDER)