# Название компилятора
CXX := g++
# Флаги компиляции
CXXFLAGS := -Wall 

# Имя исполняемого файла
TARGET := lab3

# Источники проекта
SRCS := lab3.cpp MyString.cpp MyVector.cpp

# Объектные файлы
OBJS := $(SRCS:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Правило сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# Правило для компиляции каждого файла
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка (удаление объектных файлов и исполняемого файла)
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
