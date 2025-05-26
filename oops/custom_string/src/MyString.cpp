#include "../include/MyString.h"
#include <cstring>

MyString::MyString() : data(new char[1]), length(0) {
	data[0] = '\0';
}

MyString::MyString(const char* str) {
	length = std::strlen(str);
	data = new char[length +1];
	std::strcpy(data, str);
}

MyString::MyString(const MyString& other) {
	length = other.length;
	data = new char[length + 1];
	std::strcpy(data, other.data);
}

MyString::MyString(MyString&& other) noexcept {
	data = other.data;
	length = other.length;
	other.data = nullptr;
	other.length = 0;
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }
    return *this;
}

// Move assignment
MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        length = other.length;
        other.data = nullptr;
        other.length = 0;
    }
    return *this;
}

MyString::~MyString(){
	delete[] data;
}

MyString MyString::operator+(const MyString& other) const {
    size_t newLength = length + other.length;
    char* newData = new char[newLength + 1];  
    std::memcpy(newData, data, length);
    std::memcpy(newData + length, other.data, other.length);
    newData[newLength] = '\0';
    MyString result(newData);
    delete[] newData;
    return result;
}

bool MyString::operator==(const MyString& other) const {
	return std::strcmp(data, other.data) == 0;
}

char& MyString::operator[](size_t index) {
	return data[index];
}

const char& MyString::operator[](size_t index) const {
	return data[index];
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << str.data;
    return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
    char buffer[1024];
    is >> buffer;
    str = MyString(buffer); 
    return is;
}

size_t MyString::size() const {
	return length;
}

const char* MyString::c_str() const {
	return data;
}

MyString MyString::substr(size_t pos, size_t len) const {
	if(pos >= length) return MyString("");
	if(pos + len > length) len = length - pos;
	char* sub = new char[len + 1];
	std::strncpy(sub, data + pos, len);
	sub[len] = '\0';
	MyString result(sub);
	delete[] sub;
	return result;
}

void MyString::clear() {
    delete[] data;
    data = new char[1];
    data[0] = '\0';
    length = 0;
}

