#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Calculator {
public:
    string evaluate(const string str1, const string str2, const char operation);
    string calculateWithSigns(string str1, string str2, char operation);
    string divideWithSigns(string str1, string str2);
    string divideStrings(const string& dividend, const string& divisor);
    string multiplyStrings(const string& str1, const string& str2);
    string addStrings(const string& str1, const string& str2);
    string subtractStrings(const string& str1, const string& str2);

private:
    char addLetters(char letter1, char letter2, int& carry);
    char subtractLetters(char letter1, char letter2, int& borrow);
    bool Compare(const string& str1, const string& str2);
    char getLetter(int index);
    int findIndex(char letter);
    char minimum(char letter1, char letter2);
    //char multiplyLetters(char letter1, char letter2, int& carry);
    string multiplyStrings(string str, char letter2);

    const string alphabet = "abdhcegf";
    const int BASE = alphabet.size(); 
    const string max_value = "ffffffff"; 
    bool metka = false;
};