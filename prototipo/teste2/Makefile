CC_LINUX = x86_64-w64-mingw32-gcc
CC_NATIVE = gcc
CFLAGS = -Wall -I include
SRC = src/main.c src/telas.c src/arquivos.c
TARGET = volei_simulator.exe

# Detecta o sistema operacional
ifeq ($(OS), Windows_NT)
    CC = $(CC_NATIVE)
    RM = del /Q
    RUN = $(TARGET)
else
    CC = $(CC_LINUX)
    RM = rm -f
    RUN = wine $(TARGET)
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	$(RM) $(TARGET)

run: $(TARGET)
	$(RUN)
