# Nome do executável
TARGET = main

# Diretórios
SRC_DIR = src
INC_DIR = include

# Lista de todos os .c na pasta src
SRC = $(wildcard $(SRC_DIR)/*.c)

# Caminho Raylib via Homebrew
RAYLIB_PATH = /opt/homebrew/opt/raylib
CFLAGS = -I$(RAYLIB_PATH)/include -I$(INC_DIR) -w
LDFLAGS = -L$(RAYLIB_PATH)/lib -lraylib \
    -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo

# Regra padrão
all: $(TARGET)

$(TARGET): $(SRC)
	gcc $^ -o $@ $(CFLAGS) $(LDFLAGS)

# Limpeza
clean:
	rm -f $(TARGET)
