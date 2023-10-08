#pragma once

#include <cstring>
#include <iostream>

class String {
  private:
    size_t sz = 0;
    size_t cap = 0;
    char* arr = new char[1];

    void swap(String& str);

  public:
    String(const char* cstr);
    String(size_t n, char c);
    String(const String& str);
    String(char symb);
    String();

    String& operator=(String str);
    size_t size() const;
    size_t capacity() const;
    size_t length() const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    const char& front() const;
    char& front();

    const char& back() const;
    char& back();

    static void memory_copy(size_t pos, size_t sz, char* to_copy,
                            char* place_to_copy);

    void pop_back();
    void push_back(char symb);

    String& operator+=(const String& str);
    String& operator+=(char a);

    void clear();
    bool empty() const;

    String substr(size_t pos, size_t cnt) const;
    bool check(size_t i, const String& sub) const;

    size_t find(const String& sub) const;
    size_t rfind(const String& sub) const;

    void shrink_to_fit();

    char* data();
    const char* data() const;

    ~String();
};

std::istream& operator>>(std::istream& in, String& str);
std::ostream& operator<<(std::ostream& out, const String& str);

bool operator==(const String& a, const String& b);
bool operator<(const String& a, const String& b);
bool operator!=(const String& a, const String& b);
bool operator>(const String& a, const String& b);
bool operator<=(const String& a, const String& b);
bool operator>=(const String& a, const String& b);
String operator+(const String& a, const String& b);
