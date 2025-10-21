#ifndef OTHER_H
#define OTHER_H

#include "gray.h"
#include "multiset.h"
#include <string>
#include <iostream>

using namespace std;

long long readLongInRange(const string& prompt, long long min, long long max);
string readLineNonEmpty(const string& prompt); // Добавляем объявление
bool parseLong(const string& str, long long& out);
void fillManual(MultiSet& ms, const GrayUniverse& U);
void fillAuto(MultiSet& ms, const GrayUniverse& U);

#endif // OTHER_H