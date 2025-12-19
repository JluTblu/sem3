# Makefile для калькулятора конечной арифметики
# Вариант 48

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = calculator
EXAMPLES = examples
TEST_DIV = test_division
TEST_VERIFY = verify_div

# Объектные файлы
OBJ = finite_arithmetic.o

# Главная цель - собрать калькулятор
all: $(TARGET)

# Компиляция калькулятора
$(TARGET): main.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo ""
	@echo "✓ Калькулятор успешно скомпилирован!"
	@echo "  Запуск: ./$(TARGET)"

# Компиляция примеров
$(EXAMPLES): examples.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo ""
	@echo "✓ Примеры успешно скомпилированы!"
	@echo "  Запуск: ./$(EXAMPLES)"

# Компиляция тестов деления
$(TEST_DIV): test_division.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_VERIFY): verify_div.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Компиляция объектных файлов
%.o: %.cpp finite_arithmetic.h
	$(CXX) $(CXXFLAGS) -c $<

# Сборка всех целей
build-all: $(TARGET) $(EXAMPLES)
	@echo ""
	@echo "✓ Все программы успешно скомпилированы!"

# Запуск калькулятора
run: $(TARGET)
	@echo ""
	@echo "Запуск калькулятора..."
	@echo ""
	./$(TARGET)

# Запуск примеров
run-examples: $(EXAMPLES)
	@echo ""
	@echo "Запуск примеров..."
	@echo ""
	./$(EXAMPLES)

# Запуск тестов
test: $(TARGET)
	@echo ""
	@echo "Запуск встроенных тестов..."
	@echo ""
	@echo "5" | ./$(TARGET)

# Быстрый тест (компиляция и запуск тестов)
quick-test: $(TARGET)
	@echo ""
	@echo "Быстрое тестирование..."
	@(echo "5"; echo "0") | ./$(TARGET)

# Очистка
clean:
	rm -f *.o $(TARGET) $(EXAMPLES) $(TEST_DIV) $(TEST_VERIFY)
	@echo ""
	@echo "✓ Очистка завершена"

# Полная пересборка
rebuild: clean all
	@echo ""
	@echo "✓ Пересборка завершена"

# Справка
help:
	@echo "═══════════════════════════════════════════════════"
	@echo "  Makefile для калькулятора конечной арифметики"
	@echo "  Вариант 48 (Z₈)"
	@echo "═══════════════════════════════════════════════════"
	@echo ""
	@echo "Доступные команды:"
	@echo "  make              - собрать калькулятор"
	@echo "  make run          - собрать и запустить калькулятор"
	@echo "  make examples     - собрать примеры"
	@echo "  make run-examples - собрать и запустить примеры"
	@echo "  make test         - запустить встроенные тесты"
	@echo "  make quick-test   - быстрое тестирование"
	@echo "  make build-all    - собрать всё"
	@echo "  make clean        - очистить скомпилированные файлы"
	@echo "  make rebuild      - пересобрать с нуля"
	@echo "  make help         - показать эту справку"
	@echo ""
	@echo "Примеры использования:"
	@echo "  make && ./calculator    # Собрать и запустить"
	@echo "  make run                # То же самое"
	@echo "  make quick-test         # Быстрая проверка"
	@echo ""

.PHONY: all run run-examples test quick-test clean rebuild help build-all
