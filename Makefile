# Nome do executável final
TARGET = game

# Compilador C++
CXX = g++

# Padrão C++ (C++20)
CXXSTANDARD = -std=c++20

# Flags de compilação
# -Wall: Habilita todos os warnings comuns
# -Wextra: Habilita warnings adicionais
# -pedantic: Emite todos os warnings exigidos pelo padrão C++
# -O2: Otimização de nível 2
# -I.: Inclui o diretório atual para cabeçalhos
CXXFLAGS = $(CXXSTANDARD) -Wall -Wextra -pedantic -O2 -I.

# Flags do linker (se houver bibliotecas externas, adicione aqui, ex: -lSDL2)
LDFLAGS =

# Diretório para armazenar os arquivos objeto (.o)
OBJDIR = obj

# Diretórios onde os arquivos .cpp serão procurados recursivamente
# Adicione mais diretórios aqui se necessário
SRCDIRS = ASCII_Engine src

# Encontra todos os arquivos .cpp nos diretórios especificados, recursivamente
# A função 'wildcard' expande padrões de nome de arquivo.
# A função 'patsubst' substitui partes de strings.
# A função 'foreach' itera sobre uma lista.
SOURCES = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp $(dir)/**/*.cpp))

# Deriva os nomes dos arquivos objeto (.o) a partir dos arquivos fonte (.cpp)
# Os arquivos .o serão armazenados no diretório OBJDIR, mantendo a estrutura de subdiretórios.
# Ex: ASCII_Engine/file.cpp -> obj/ASCII_Engine/file.o
OBJECTS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Regra padrão: compila o projeto
all: $(TARGET)

# Garante que o diretório de objetos exista antes de compilar
$(OBJDIR):
	@echo "Creating object directory: $(OBJDIR)"
	@mkdir -p $(OBJDIR)

# Regra para linkar o executável
# Depende de todos os arquivos objeto.
$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build completed successfully!"

# Regra genérica para compilar arquivos .cpp em .o
# O alvo é $(OBJDIR)/%.o, e o pré-requisito é %.cpp.
# Isso significa que para criar obj/path/file.o, o make buscará path/file.cpp.
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@echo "Compiling $< to $@..."
	@mkdir -p $(@D) # Cria subdiretórios dentro de OBJDIR se necessário (ex: obj/ASCII_Engine)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados (objetos e executável)
clean:
	@echo "Cleaning up..."
	$(RM) -r $(OBJDIR) $(TARGET)
	@echo "Clean completed."

.PHONY: all clean
