CC:=gcc
LIBS:=-lm #-lOSIL
SRCS:=src/*
ASSETS:=assets/*
OUTPUT_FOLDER:=build
OUTPUT:=$(OUTPUT_FOLDER)/circle.exe

ifeq ($(OS),Windows_NT)
	#LIBS:=-lglut32 -lopengl32 -lglu32 $(LIBS)
else
	#LIBS:=-lGL -lGLU -lglut $(LIBS)
endif

all:
	@mkdir -p $(OUTPUT_FOLDER)
    #@cp $(ASSETS) $(OUTPUT_FOLDER)
	$(CC) $(SRCS) $(LIBS) -o $(OUTPUT)
