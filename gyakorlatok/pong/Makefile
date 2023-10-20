CC:=gcc
LIBS:=-lm #-lOSIL
SRCS:=src/*
ASSETS:=assets/*
OUTPUT_FOLDER:=build
OUTPUT:=$(OUTPUT_FOLDER)/pong.exe
INCLUDES:=include/
IGNORE_WARNS:=-Wall -Wextra -Wpedantic

ifeq ($(OS),Windows_NT)
	LIBS:=-lglut32 -lopengl32 -lglu32 $(LIBS)
else
	LIBS:=-lGL -lGLU -lglut $(LIBS)
endif

all:
	@mkdir $(OUTPUT_FOLDER)
    #@cp $(ASSETS) $(OUTPUT_FOLDER)
	$(CC) -I$(INCLUDES) $(SRCS) $(LIBS) -o $(OUTPUT) $(IGNORE_WARNS)
