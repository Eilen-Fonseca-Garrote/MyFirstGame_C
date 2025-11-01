# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2

# Directorios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Archivos fuente y objeto
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/programa

# Target principal
all: $(TARGET)

# Enlazar objeto para crear ejecutable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@

# Compilar cada archivo .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crear directorios si no existen
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilar en modo debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: all

# Compilar en modo release
release: CFLAGS += $(RELEASE_FLAGS)
release: all

# Limpiar archivos compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Recompilar desde cero
re: clean all

# Instalar (copiar a /usr/local/bin)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Ayuda
help:
	@echo "Targets disponibles:"
	@echo "  all     - Compilar proyecto (default)"
	@echo "  debug   - Compilar con símbolos de debug"
	@echo "  release - Compilar optimizado"
	@echo "  clean   - Eliminar archivos compilados"
	@echo "  re      - Recompilar desde cero"
	@echo "  install - Instalar en sistema"
	@echo "  help    - Mostrar esta ayuda"

.PHONY: all debug release clean re install help