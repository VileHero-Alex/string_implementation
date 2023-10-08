#include "string.h"

void String::swap(String& str) {
    std::swap(sz, str.sz);
    std::swap(cap, str.cap);
    std::swap(arr, str.arr);
}

String::String(const char* cstr)
    : sz(strlen(cstr)), cap(strlen(cstr)), arr(new char[strlen(cstr) + 1]) {
    memcpy(arr, cstr, sz);
    arr[sz] = '\0';
}

String::String(size_t n, char c) : sz(n), cap(n), arr(new char[n + 1]) {
    memset(arr, c, n);
    arr[n] = '\0';
}

String::String(const String& str)
    : sz(str.sz), cap(str.cap), arr(new char[str.cap + 1]) {
    memcpy(arr, str.arr, sz + 1);
}

String::String(char symb) : sz(1), cap(1), arr(new char[cap + 1]) {
    arr[0] = symb;
    arr[1] = '\0';
}

String::String() {
    arr[0] = '\0';
}

String& String::operator=(String str) {
    swap(str);
    return *this;
}

size_t String::size() const {
    return sz;
}

size_t String::capacity() const {
    return cap;
}

size_t String::length() const {
    return sz;
}

char& String::operator[](size_t index) {
    return arr[index];
}

const char& String::operator[](size_t index) const {
    return arr[index];
}

const char& String::front() const {
    return arr[0];
}

char& String::front() {
    return arr[0];
}

const char& String::back() const {
    return arr[sz - 1];
}

char& String::back() {
    return arr[sz - 1];
}

void String::pop_back() {
    arr[sz - 1] = '\0';
    --sz;
}

void String::memory_copy(size_t pos, size_t sz, char* to_copy,
                         char* place_to_copy) {
    memcpy(place_to_copy + pos, to_copy, sz);
}

void String::push_back(char symb) {
    if (cap + 1 <= sz + 1) {
        cap += 1;
        cap *= 2;
        char* newarr = new char[cap + 1];
        memory_copy(0, sz, arr, newarr);
        std::swap(arr, newarr);
        delete[] newarr;
    }
    arr[sz] = symb;
    ++sz;
    arr[sz] = '\0';
}

String& String::operator+=(char a) {
    push_back(a);
    return *this;
}

String& String::operator+=(const String& str) {
    if (cap + 1 >= sz + str.sz + 1) {
        memory_copy(sz, str.sz + 1, str.arr, arr);
        sz += str.sz;
        return *this;
    }
    cap = sz + str.sz;
    char* newarr = new char[cap + 1];
    memory_copy(0, sz, arr, newarr);
    memory_copy(sz, str.sz + 1, str.arr, newarr);
    std::swap(arr, newarr);
    delete[] newarr;
    sz += str.sz;
    return *this;
}

void String::clear() {
    sz = 0;
    arr[0] = '\0';
}

bool String::empty() const {
    return (sz == 0);
}

String String::substr(size_t pos, size_t cnt) const {
    String res(cnt, '\0');
    memcpy(res.arr, arr + pos, cnt);
    return res;
}

bool String::check(size_t i, const String& sub) const {
    for (size_t j = 0; j < sub.sz; ++j) {
        if (arr[i + j] != sub.arr[j]) {
            return false;
        }
    }
    return true;
}

size_t String::find(const String& sub) const {
    if (sz < sub.sz) {
        return sz;
    }
    for (size_t i = 0; i <= sz - sub.sz; ++i) {
        bool fl = check(i, sub);
        if (fl) {
            return i;
        }
    }
    return sz;
}

size_t String::rfind(const String& sub) const {
    if (sz < sub.sz) {
        return sz;
    }
    for (size_t i = sz - sub.sz + 1; i > 0; --i) {
        bool fl = check(i - 1, sub);
        if (fl) {
            return i - 1;
        }
    }
    return sz;
}

void String::shrink_to_fit() {
    if (cap == sz) {
        return;
    }
    cap = sz;
    char* newarr = new char[cap + 1];
    memory_copy(0, sz + 1, arr, newarr);
    std::swap(arr, newarr);
    delete[] newarr;
}

char* String::data() {
    return arr;
}

const char* String::data() const {
    return arr;
}

String::~String() {
    delete[] arr;
}

bool operator==(const String& a, const String& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const String& a, const String& b) {
    return !(a == b);
}

bool operator<(const String& a, const String& b) {
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return (a[i] < b[i]);
        }
    }
    return false;
}

bool operator>(const String& a, const String& b) {
    return b < a;
}

bool operator<=(const String& a, const String& b) {
    return !(a > b);
}

bool operator>=(const String& a, const String& b) {
    return !(a < b);
}

String operator+(const String& a, const String& b) {
    String temp = a;
    temp += b;
    return temp;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        out << str[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, String& str) {
    str.clear();
    char symb;
    in.get(symb);
    while ((std::isspace(symb) != 0) && in.good()) {
        in.get(symb);
    }
    while ((!std::isspace(symb, in.getloc())) && in.good()) {
        str += symb;
        in.get(symb);
    }
    return in;
}
