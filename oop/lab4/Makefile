# Название компилятора
CXX := g++
# Флаги компиляции
CXXFLAGS := -Wall -std=c++17

# Имя исполняемого файла
TARGET := lab4

# Источники проекта
SRCS := lab4.cpp ../lab3/MyString.cpp ../lab3/MyVector.cpp Point.cpp

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