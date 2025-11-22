# Autor: dherrerahe
# ============================================
# Makefile Proyecto Integral Triple
# ============================================
#
CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lm

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = .

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/densidades.c $(SRC_DIR)/integracion.c
HEADERS = $(INCLUDE_DIR)/densidades.h $(INCLUDE_DIR)/integracion.h
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/densidades.o $(OBJ_DIR)/integracion.o
EXECUTABLE = $(BIN_DIR)/programa

.PHONY: all clean distclean run help info

# Compilar todo
all: $(EXECUTABLE)

# Crear directorio de objetos
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compilar .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@
	@echo "Compilado: $<"

# Enlazar ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@ $(LIBS)
	@echo "Compilación exitosa: $(EXECUTABLE)"

# Ejecutar programa
run: $(EXECUTABLE)
	@./$(EXECUTABLE)

# Limpiar archivos objeto
clean:
	@rm -rf $(OBJ_DIR)
	@echo "Archivos compilados eliminados"

# Limpiar todo incluyendo ejecutable y CSV
distclean: clean
	@rm -f $(EXECUTABLE) resultados.csv
	@echo "Proyecto completamente limpio"

# Mostrar ayuda resumida
help:
	@echo "Uso:"
	@echo "  make        - Compila"
	@echo "  make run    - Compila y ejecuta"
	@echo "  make clean  - Limpiar objetos"
	@echo "  make distclean - Limpiar todo"
	@echo "  make help   - Mostrar ayuda"

# Información del proyecto
info:
	@echo "Proyecto: Integral Triple y Centro de Masa"
	@echo "Compilador: $(CC), Flags: $(CFLAGS), Librerías: $(LIBS)"
	@echo "Fuentes: $(SRC_DIR)/, Headers: $(INCLUDE_DIR)/, Objetos: $(OBJ_DIR)/"
	@echo "Ejecutable: $(EXECUTABLE)"

