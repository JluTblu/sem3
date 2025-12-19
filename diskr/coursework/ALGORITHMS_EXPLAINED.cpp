/*
 * ПОДРОБНЫЕ КОММЕНТАРИИ К КЛЮЧЕВЫМ АЛГОРИТМАМ
 * Калькулятор конечной арифметики (Вариант 48)
 * 
 * Этот файл содержит детальные объяснения реализации основных алгоритмов
 */

// ============================================================================
// 1. ПРАВИЛО "+1" (INCREMENT) - ОСНОВА МАЛОЙ АРИФМЕТИКИ
// ============================================================================

/*
 * Функция increment() - это БАЗОВАЯ операция, на которой строится всё остальное.
 * Она прибавляет единицу к числу в нашей буквенной системе счисления.
 * 
 * Алгоритм похож на обычное прибавление 1 в десятичной системе:
 * - Идём справа налево
 * - Увеличиваем текущую цифру
 * - Если получилось >= BASE (8), обнуляем и переносим 1 влево
 * 
 * Примеры:
 *   increment("b") = "c"    (1 + 1 = 2)
 *   increment("h") = "ba"   (7 + 1 = 8 = 1×8 + 0)
 *   increment("ag") = "ah"  (06 + 1 = 07)
 */

std::string FiniteArithmetic::increment(const std::string& num) const {
    // Особый случай: ноль
    if (num.empty() || isZero(num)) {
        return std::string(1, MULTIPLICATIVE_IDENTITY); // Возвращаем "b" (единицу)
    }
    
    std::string result = num;
    bool carry = true;  // Флаг переноса
    
    // Идём справа налево
    for (int i = result.length() - 1; i >= 0 && carry; --i) {
        int val = charToValue(result[i]);
        val++;  // Прибавляем 1
        
        if (val >= BASE) {
            // Переполнение разряда: обнуляем и переносим
            result[i] = ADDITIVE_IDENTITY;  // Ставим 'a' (ноль)
            carry = true;  // Продолжаем перенос
        } else {
            // Всё нормально: записываем и выходим
            result[i] = valueToChar(val);
            carry = false;
        }
    }
    
    // Если перенос остался, добавляем новый разряд слева
    if (carry) {
        result = std::string(1, MULTIPLICATIVE_IDENTITY) + result; // "b" + result
    }
    
    return result;
}

// ============================================================================
// 2. ПРАВИЛО "-1" (DECREMENT)
// ============================================================================

/*
 * Функция decrement() - обратная операция к increment().
 * Вычитает единицу из числа.
 * 
 * Алгоритм аналогичен вычитанию в десятичной системе:
 * - Идём справа налево
 * - Уменьшаем текущую цифру
 * - Если цифра была 0, занимаем из старшего разряда
 * 
 * Примеры:
 *   decrement("c") = "b"    (2 - 1 = 1)
 *   decrement("ba") = "h"   (8 - 1 = 7)
 *   decrement("b") = "a"    (1 - 1 = 0)
 */

std::string FiniteArithmetic::decrement(const std::string& num) const {
    // Особый случай: единица
    if (num.empty() || num == std::string(1, MULTIPLICATIVE_IDENTITY)) {
        return std::string(1, ADDITIVE_IDENTITY); // Возвращаем "a" (ноль)
    }
    
    std::string result = num;
    bool borrow = true;  // Флаг заёма
    
    // Идём справа налево
    for (int i = result.length() - 1; i >= 0 && borrow; --i) {
        int val = charToValue(result[i]);
        
        if (val == 0) {
            // Нужно занять из старшего разряда
            result[i] = valueToChar(BASE - 1);  // Ставим максимальную цифру ('h' = 7)
            borrow = true;  // Продолжаем занимать
        } else {
            // Просто уменьшаем
            result[i] = valueToChar(val - 1);
            borrow = false;
        }
    }
    
    // Убираем ведущие нули
    return removeLeadingZeros(result);
}

// ============================================================================
// 3. СЛОЖЕНИЕ ПОЛОЖИТЕЛЬНЫХ ЧИСЕЛ
// ============================================================================

/*
 * Сложение реализуется через ПОСЛЕДОВАТЕЛЬНОЕ ПРИБАВЛЕНИЕ ЕДИНИЦЫ.
 * Это ключевая идея: мы НЕ переводим числа в int!
 * 
 * Алгоритм:
 *   result = num1
 *   counter = 0
 *   while (counter != num2):
 *       result = result + 1
 *       counter = counter + 1
 *   return result
 * 
 * Пример: ba + c (8 + 2)
 *   Итерация 1: result = ba + 1 = bb, counter = a + 1 = b
 *   Итерация 2: result = bb + 1 = bc, counter = b + 1 = c
 *   Готово! counter == num2 (оба равны c)
 *   Результат: bc (10 в десятичной)
 * 
 * ВАЖНО: Счётчик тоже в буквенной системе!
 */

std::string FiniteArithmetic::addPositive(const std::string& num1, 
                                          const std::string& num2) const {
    std::string result = num1;
    std::string counter(1, ADDITIVE_IDENTITY);  // Начинаем с нуля ('a')
    
    // Прибавляем единицу num2 раз
    while (counter != num2) {
        result = increment(result);
        counter = increment(counter);
        
        // Проверка переполнения
        if (result.length() > MAX_LENGTH) {
            throw std::overflow_error("Переполнение: результат превышает 8 разрядов");
        }
    }
    
    return result;
}

// ============================================================================
// 4. УМНОЖЕНИЕ ПОЛОЖИТЕЛЬНЫХ ЧИСЕЛ
// ============================================================================

/*
 * Умножение реализуется через ПОВТОРНОЕ СЛОЖЕНИЕ.
 * num1 * num2 = num1 + num1 + ... + num1 (num2 раз)
 * 
 * Алгоритм:
 *   result = 0
 *   counter = 0
 *   while (counter != num2):
 *       result = result + num1
 *       counter = counter + 1
 *   return result
 * 
 * Пример: c * d (2 * 3)
 *   Итерация 1: result = a + c = c, counter = b
 *   Итерация 2: result = c + c = e, counter = c
 *   Итерация 3: result = e + c = g, counter = d
 *   Готово! counter == num2
 *   Результат: g (6 в десятичной)
 */

std::string FiniteArithmetic::multiplyPositive(const std::string& num1, 
                                               const std::string& num2) const {
    // Особые случаи
    if (isZero(num1) || isZero(num2)) {
        return std::string(1, ADDITIVE_IDENTITY);
    }
    
    std::string result(1, ADDITIVE_IDENTITY);  // Начинаем с нуля
    std::string counter(1, ADDITIVE_IDENTITY);
    
    // Складываем num1 с собой num2 раз
    while (counter != num2) {
        result = addPositive(result, num1);
        counter = increment(counter);
        
        // Проверка переполнения
        if (result.length() > MAX_LENGTH) {
            throw std::overflow_error("Переполнение: результат превышает 8 разрядов");
        }
    }
    
    return result;
}

// ============================================================================
// 5. ДЕЛЕНИЕ ПОЛОЖИТЕЛЬНЫХ ЧИСЕЛ
// ============================================================================

/*
 * Деление реализуется через ПОВТОРНОЕ ВЫЧИТАНИЕ.
 * Вычитаем делитель из делимого, пока можем, считая количество вычитаний.
 * 
 * Алгоритм:
 *   quotient = 0    (частное)
 *   remainder = num1 (остаток)
 *   while (remainder >= num2):
 *       remainder = remainder - num2
 *       quotient = quotient + 1
 *   return (quotient, remainder)
 * 
 * Пример: h ÷ d (7 ÷ 3)
 *   Начало: quotient = a, remainder = h
 *   Итерация 1: remainder = h - d = e, quotient = b
 *   Итерация 2: remainder = e - d = b, quotient = c
 *   Стоп! remainder (b=1) < num2 (d=3)
 *   Результат: c(b), то есть 2 остаток 1
 */

std::pair<std::string, std::string> 
FiniteArithmetic::dividePositive(const std::string& num1, 
                                 const std::string& num2) const {
    // Деление на ноль
    if (isZero(num2)) {
        if (isZero(num1)) {
            // 0/0 - диапазон всех чисел
            std::string maxNum(MAX_LENGTH, ALPHABET[BASE - 1]);
            return {std::string(1, ADDITIVE_IDENTITY), 
                    "[-" + maxNum + "; " + maxNum + "]"};
        } else {
            // n/0 = Ø
            return {std::string(1, ADDITIVE_IDENTITY), "Ø"};
        }
    }
    
    if (isZero(num1)) {
        return {std::string(1, ADDITIVE_IDENTITY), 
                std::string(1, ADDITIVE_IDENTITY)};
    }
    
    std::string quotient(1, ADDITIVE_IDENTITY);
    std::string remainder = num1;
    
    // Вычитаем num2, пока возможно
    while (compareAbs(remainder, num2) >= 0) {
        remainder = subtractPositive(remainder, num2);
        quotient = increment(quotient);
    }
    
    return {quotient, remainder};
}

// ============================================================================
// 6. ОСОБЫЙ СЛУЧАЙ: ДЕЛЕНИЕ ОТРИЦАТЕЛЬНОГО НА ПОЛОЖИТЕЛЬНОЕ
// ============================================================================

/*
 * ЭТО САМЫЙ ВАЖНЫЙ И СЛОЖНЫЙ МОМЕНТ!
 * 
 * Проблема: -7 ÷ 3 ≠ -(7 ÷ 3)
 * 
 * Если просто взять результат деления и поменять знак:
 *   7 ÷ 3 = 2(1)
 *   -(2(1)) = -2(1)
 *   Проверка: 3 × (-2) + 1 = -6 + 1 = -5 ≠ -7 ✗
 * 
 * Правильный подход:
 *   -7 ÷ 3 = -3(2)
 *   Проверка: 3 × (-3) + 2 = -9 + 2 = -7 ✓
 * 
 * Алгоритм (лайфхак):
 *   1. Делим модули: 7 ÷ 3 = 2(1)
 *   2. Если остаток != 0:
 *      - Увеличиваем частное: 2 + 1 = 3
 *      - Пересчитываем остаток: 3 - 1 = 2
 *   3. Ставим минус: -3(2)
 * 
 * Почему это работает?
 * Нужно, чтобы: a = b × q + r, где 0 ≤ r < b
 * Для -7 ÷ 3: -7 = 3 × q + r
 * Если q = -2, r = 1: 3×(-2)+1 = -6+1 = -5 ✗
 * Если q = -3, r = 2: 3×(-3)+2 = -9+2 = -7 ✓
 * 
 * Остаток ВСЕГДА должен быть неотрицательным!
 */

std::string FiniteArithmetic::divide(const std::string& num1, 
                                    const std::string& num2) const {
    // ... парсинг знаков ...
    
    auto [quotient, remainder] = dividePositive(n1, n2);
    
    // ДЕЛЕНИЕ ОТРИЦАТЕЛЬНОГО НА ПОЛОЖИТЕЛЬНОЕ
    if (sign1 && !sign2) {
        if (!isZero(remainder)) {
            // ВАЖНО! Корректируем результат:
            quotient = increment(quotient);           // Увеличиваем частное
            remainder = subtractPositive(n2, remainder); // Пересчитываем остаток
        }
        std::string qSign = isZero(quotient) ? "" : "-";
        return qSign + quotient + "(" + remainder + ")";
    }
    
    // Остальные случаи проще...
}

// ============================================================================
// 7. СЛОЖЕНИЕ С УЧЁТОМ ЗНАКОВ
// ============================================================================

/*
 * Сложение чисел с разными знаками сводится к одному из случаев:
 * 
 * 1. (+a) + (+b) = +(a + b)           [Обычное сложение]
 * 2. (-a) + (-b) = -(a + b)           [Сложить и поставить минус]
 * 3. (+a) + (-b) = a - b или -(b - a) [Вычитание, знак зависит от модулей]
 * 4. (-a) + (+b) = b - a или -(a - b) [То же самое]
 * 
 * Для случаев 3 и 4 нужно сравнить модули и выбрать правильный порядок вычитания.
 */

std::string FiniteArithmetic::add(const std::string& num1, 
                                 const std::string& num2) const {
    bool sign1 = !num1.empty() && num1[0] == '-';
    bool sign2 = !num2.empty() && num2[0] == '-';
    
    std::string n1 = sign1 ? num1.substr(1) : num1;
    std::string n2 = sign2 ? num2.substr(1) : num2;
    
    if (!sign1 && !sign2) {
        // Оба положительные: просто складываем
        return addPositive(n1, n2);
    } 
    else if (sign1 && sign2) {
        // Оба отрицательные: складываем и ставим минус
        return "-" + addPositive(n1, n2);
    } 
    else {
        // Разные знаки: нужно вычитать
        int cmp = compareAbs(n1, n2);
        if (cmp > 0) {
            // |n1| > |n2|: вычитаем n2 из n1, знак от n1
            std::string result = subtractPositive(n1, n2);
            return sign1 ? "-" + result : result;
        } 
        else if (cmp < 0) {
            // |n2| > |n1|: вычитаем n1 из n2, знак от n2
            std::string result = subtractPositive(n2, n1);
            return sign2 ? "-" + result : result;
        } 
        else {
            // Равны по модулю: результат ноль
            return std::string(1, ADDITIVE_IDENTITY);
        }
    }
}

// ============================================================================
// КЛЮЧЕВЫЕ ИДЕИ РЕАЛИЗАЦИИ
// ============================================================================

/*
 * 1. НЕТ ПРЕОБРАЗОВАНИЙ В INT
 *    - Все операции работают в буквенной системе
 *    - Даже счётчики используют буквы
 *    - int используется только для длины строк и индексов
 * 
 * 2. ИЕРАРХИЯ ОПЕРАЦИЙ
 *    increment/decrement → add/subtract → multiply → divide
 *    Каждый уровень строится на предыдущем
 * 
 * 3. ОСОБЫЙ СЛУЧАЙ ДЕЛЕНИЯ
 *    Деление отрицательного на положительное требует коррекции остатка
 * 
 * 4. ПЕРЕПОЛНЕНИЕ
 *    Проверяем длину результата на каждой итерации
 *    Выбрасываем исключение, а не циклическое переполнение
 * 
 * 5. ЗНАКИ
 *    Сначала разбираем знаки, потом работаем с модулями,
 *    в конце собираем результат с правильным знаком
 */
