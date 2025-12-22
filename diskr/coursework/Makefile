CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = calculator

OBJS = main.o BigFiniteNumber.o arithmetic.o utils.o constants.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo ""
	@echo "✓ Калькулятор успешно скомпилирован!"
	@echo "  Запуск: ./$(TARGET)"

main.o: main.cpp BigFiniteNumber.h constants.h utils.h arithmetic.h
	$(CXX) $(CXXFLAGS) -c main.cpp

BigFiniteNumber.o: BigFiniteNumber.cpp BigFiniteNumber.h constants.h utils.h arithmetic.h
	$(CXX) $(CXXFLAGS) -c BigFiniteNumber.cpp

arithmetic.o: arithmetic.cpp arithmetic.h utils.h constants.h
	$(CXX) $(CXXFLAGS) -c arithmetic.cpp

utils.o: utils.cpp utils.h constants.h
	$(CXX) $(CXXFLAGS) -c utils.cpp

constants.o: constants.cpp constants.h
	$(CXX) $(CXXFLAGS) -c constants.cpp

run: $(TARGET)
	@echo ""
	@echo "Запуск калькулятора..."
	@echo ""
	./$(TARGET)

test: $(TARGET)
	@echo ""
	@echo "Запуск встроенных тестов..."
	@echo ""
	@echo "8" | ./$(TARGET)

quick-test: $(TARGET)
	@echo ""
	@echo "Быстрое тестирование..."
	@(echo "8"; echo "0") | ./$(TARGET)

clean:
	rm -f *.o $(TARGET)
	@echo ""
	@echo "✓ Очистка завершена"

rebuild: clean all
	@echo ""
	@echo "✓ Пересборка завершена"

rhelp:
	@echo "═══════════════════════════════════════════════════"
	@echo "  Makefile для калькулятора конечной арифметики"
	@echo "  Вариант 48 (Z₈)"
	@echo "═══════════════════════════════════════════════════"
	@echo ""
	@echo "Доступные команды:"
	@echo "  make              - собрать калькулятор"
	@echo "  make run          - собрать и запустить"
	@echo "  make test         - запустить тесты"
	@echo "  make quick-test   - быстрое тестирование"
	@echo "  make clean        - очистить файлы"
	@echo "  make rebuild      - пересобрать с нуля"
	@echo "  make help         - показать справку"
	@echo ""

.PHONY: all run test quick-test clean rebuild help
