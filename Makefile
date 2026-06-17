CC = gcc
CFLAGS = -Wall -I src
SRC = src/main.c src/telas.c src/arquivos.c src/teclado.c
TARGET = volei_simulator.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	del /Q $(TARGET) 2>nul || echo ok

run: $(TARGET)
	$(TARGET)
