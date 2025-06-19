#include "calculator.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


int Calculator::findIndex(char letter) {
    return alphabet.find(letter);
}


char Calculator::getLetter(int index) {
    return alphabet[index % BASE];
}

char Calculator::minimum(char letter1, char letter2) {
    if (findIndex(letter1) > findIndex(letter2)) return letter2;
    else return letter1;
}


bool Calculator::Compare(const string& str1, const string& str2) {
    
    string s1 = str1;
    string s2 = str2;

    s1.erase(0, s1.find_first_not_of('a'));
    s2.erase(0, s2.find_first_not_of('a'));

    
    if (s1.size() != s2.size()) {
        return s1.size() < s2.size(); 
    }

    
    for (size_t i = 0; i < s1.size(); ++i) {
        if (findIndex(s1[i]) != findIndex(s2[i])) {
            return findIndex(s1[i]) < findIndex(s2[i]); 
        }
    }

    return false; 
}

char Calculator::addLetters(char letter1, char letter2, int& carry) {
    size_t pos1 = alphabet.find(letter1);
    size_t pos2 = alphabet.find(letter2);

    
    string result = alphabet;

    if (carry > 0) {
        pos2++;
        carry = 0;
    }

    
    for (size_t i = 0; i < pos2; ++i) {
        result = result.substr(1) + result[0];
    }

    char m = minimum(letter1, letter2);

    if (minimum(result[pos1], m) == result[pos1]) {
        carry++;
    }

    return result[pos1];
}

char Calculator::subtractLetters(char letter1, char letter2, int& borrow) {
    size_t pos1 = alphabet.find(letter1);
    size_t pos2 = alphabet.find(letter2);

    
    string result = alphabet;
    char m = minimum(letter1, letter2);

    if (borrow > 0 && m == letter1 && letter1 == 'a') {
        pos1 = pos1 + BASE - 1;
    }
    else if (borrow > 0 && m == letter1) {
        pos2--;
        borrow = 0;
    }
    else if (borrow > 0 && m == letter2) {
        pos1--;
        borrow = 0;
    }

    if (m == letter1 && pos1 != pos2) {
        for (size_t i = 0; i < pos2; ++i) {
            result = result.substr(BASE - 1) + result.substr(0, BASE - 1);
        }

        borrow++;
        return result[pos1];
    }
    else {
        for (size_t i = 0; i < pos2; ++i) {
            result = result.substr(BASE - 1) + result.substr(0, BASE - 1);
        }

        return result[pos1];
    }

    return result[pos1];
}


string Calculator::subtractStrings(const string& str1, const string& str2) {
    string larger = str1;
    string smaller = str2;
    bool resultIsNegative = false;

    string result = "";
    int borrow = 0;

    
    int len1 = larger.size(), len2 = smaller.size();
    string s1 = string(max(len1, len2) - len1, 'a') + larger;
    string s2 = string(max(len1, len2) - len2, 'a') + smaller;

    
    bool com = Compare(s1, s2);

    if (com == false && !metka) {
        for (int i = s1.size() - 1; i >= 0; --i) {
            result += subtractLetters(s1[i], s2[i], borrow); 
        }
    }
    else {
        for (int i = s1.size() - 1; i >= 0; --i) {
            result += subtractLetters(s2[i], s1[i], borrow); 
        }
        metka = true;
    }

    
    reverse(result.begin(), result.end());
    result.erase(0, result.find_first_not_of('a'));

    
    if (result.empty()) result = "a";

    
    if (result.size() > BASE) {
        
        result = result.substr(1); 

        
        result = subtractStrings(result, max_value); 
        metka = true;
    }

    if (metka || resultIsNegative) {
        result = "-" + result;
    }

    metka = false;
    return result;
}

string Calculator::addStrings(const string& str1, const string& str2) {
    string result = "";
    int carry = 0;

    
    int len1 = str1.size(), len2 = str2.size();
    string s1 = string(max(len1, len2) - len1, 'a') + str1;
    string s2 = string(max(len1, len2) - len2, 'a') + str2;

    
    for (int i = s1.size() - 1; i >= 0; --i) {
        result += addLetters(s1[i], s2[i], carry);
    }

    
    if (carry > 0) {
        result += getLetter(carry);
    }

    
    reverse(result.begin(), result.end());
    result.erase(0, result.find_first_not_of('a'));
    
    if (result.empty()) result = "a";

    
    if (result.size() > BASE) {
        
        result = result.substr(1); 

        
        result = subtractStrings(max_value, result); 
        metka = true;
    }

    if (metka) {
        result = "-" + result;
    }

    metka = false;
    return result;
}

/*char Calculator::multiplyLetters(char letter1, char letter2, int& carry) {
    size_t pos1 = alphabet.find(letter1);  
    size_t pos2 = alphabet.find(letter2);  

    
    char result = 'a';
    int carry2 = carry;

    
    for (size_t i = 0; i < pos2; ++i) {
        result = addLetters(result, letter1, carry);
        if (carry > 0) {
            carry2 += carry;
            carry = 0;
        }  
    }

    carry = carry2;

    return result;
}*/

string Calculator::multiplyStrings(string str, char letter2) {
    string result = "a";

    
    for (size_t i = 0; i < alphabet.find(letter2); ++i) {
        result = addStrings(result, str);
    }

    return result;
}

string Calculator::multiplyStrings(const string& str1, const string& str2) {

    string sa1 = str1, sa2 = str2;
    if (sa1[0] == '-') {
        sa1 = sa1.substr(1);
    }
    if (sa2[0] == '-') {
        sa2 = sa2.substr(1);
    }
    sa1.erase(0, sa1.find_first_not_of('a'));
    sa2.erase(0, sa2.find_first_not_of('a'));
    if (sa1.empty()) sa1 = "a";
    if (sa2.empty()) sa2 = "a";
   
    if (sa1 == "a" || sa2 == "a") return "a";

    //string result(str1.size() + str2.size() + 1, 'a'); 
    string result = "";
    bool resultIsNegative = false;

    string s1 = str1, s2 = str2;
        

    if (s1[0] == '-') {
        resultIsNegative = !resultIsNegative;
        s1 = s1.substr(1);
    }
    if (s2[0] == '-') {
        resultIsNegative = !resultIsNegative;
        s2 = s2.substr(1);
    }

    //reverse(s1.begin(), s1.end());
    //reverse(s2.begin(), s2.end());

    int carry = 0, m = 0;
    char c = 'a';
    string temp = "a";

    for (size_t i = 0; i < s1.size(); ++i) {
        result += "a";
        temp = multiplyStrings(s2, s1[i]);
        result = addStrings(result, temp);
    }
   
    //reverse(result.begin(), result.end());
    result.erase(0, result.find_first_not_of('a'));
    
    if (result.empty()) result = "a";
    
    if (result.size() > BASE) {
        result = result.substr(1); 
        result = subtractStrings(result, max_value); 
        resultIsNegative = true;
    }
   
    result.erase(0, result.find_first_not_of('-'));
    if (resultIsNegative) {
        result = "-" + result;
    }
    if (result == "-a") {
        result = result.substr(1);
    }

    return result;
}


string Calculator::divideStrings(const string& dividend, const string& divisor) {
    
    string div = divisor;
    while (div == "a") {
        cout << "Деление на ноль невозможно, введите строку:" << endl;
        cin >> div;
        for (size_t i = 0; i < div.length(); ++i) {
            if (div[i] < 'a' || div[i] > 'g') {
                div = "a";
            }
        }
        cout << dividend << endl;
        cout << div << endl;
        cin.ignore();
    }

    string result = "";    
    string current = ""; 

    
    for (char digit : dividend) {
        
        current += digit;

        
        current.erase(0, current.find_first_not_of('a'));
        if (current.empty()) current = "a";

        
        if (Compare(current, div)) {
            result += 'a';
        }
        else {
            
            int count = 0;
            while (!Compare(current, div)) {
                current = subtractStrings(current, div); 
                ++count;
            }
            
            result += getLetter(count);
        }
    }

    
    result.erase(0, result.find_first_not_of('a'));
    if (result.empty()) result = "a";

    return result;
}

string Calculator::divideWithSigns(string str1, string str2) {
    bool isNegative1 = str1[0] == '-';
    bool isNegative2 = str2[0] == '-';

    if (isNegative1) str1 = str1.substr(1);
    if (isNegative2) str2 = str2.substr(1);

    string s = str1;
    s.erase(0, s.find_first_not_of('a'));
    if (s.empty()) return "a";

    string result = divideStrings(str1, str2);
    string remainder = subtractStrings(str1, multiplyStrings(result, str2));

    if (isNegative1) { 
        result = addStrings(result, "b");
        remainder = subtractStrings(multiplyStrings(result, str2), str1);
    }

    if (remainder[0] == '-' || remainder[1] == '-') {
        remainder = "b";
    }

    
    if (isNegative1 ^ isNegative2) {
        result = "-" + result;
    }

    return result + " + " + remainder;
}


string Calculator::calculateWithSigns(string str1, string str2, char operation) {
    bool isNegative1 = str1[0] == '-';
    bool isNegative2 = str2[0] == '-';

    if (isNegative1) str1 = str1.substr(1);
    if (isNegative2) str2 = str2.substr(1);

    string s1 = str1;
    string s2 = str2;
    s1.erase(0, s1.find_first_not_of('a'));
    s2.erase(0, s2.find_first_not_of('a'));

    string result = "";

    if (!isNegative1 && !isNegative2) {
        if (s1.size() >= s2.size()) {
            result = (operation == '+') ? addStrings(str1, str2) : subtractStrings(str1, str2);
        }
        else {
            result = (operation == '+') ? addStrings(str1, str2) : "-" + subtractStrings(str2, str1);
        }
    }
    else if (isNegative1 && isNegative2) {
        if (s1.size() >= s2.size()) {
            result = (operation == '+') ? "-" + addStrings(str1, str2) : "-" + subtractStrings(str1, str2);
        }
        else {
            result = (operation == '+') ? "-" + addStrings(str1, str2) : subtractStrings(str2, str1);
        }
    }
    else if (isNegative1 && !isNegative2) {
        result = (operation == '+') ? subtractStrings(str2, str1) : "-" + addStrings(str1, str2);
    }
    else if (!isNegative1 && isNegative2) {
        result = (operation == '+') ? subtractStrings(str1, str2) : addStrings(str1, str2);
    }

    if (result[0] == '-' && result[1] == '-') {
        result = result.substr(2);
    }
    else if (result == "-a") {
        result = result.substr(1);
    }

    return result;
}

string Calculator::evaluate(const string str1, const string str2, const char operation) {
    string result;
    if (operation == '+' || operation == '-') {
        result = calculateWithSigns(str1, str2, operation);
    }
    else if (operation == '*') {
        result = multiplyStrings(str1, str2);
    }
    else if (operation == '/') {
        result = divideWithSigns(str1, str2);
    }

    return result;
}
