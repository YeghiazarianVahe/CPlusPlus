#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

class MyString {
	private: 
		char* data;
		size_t length;
	
	public:
		MyString();
		MyString(const char* str);
		MyString(const MyString& other);
		MyString(MyString&& other) noexcept;

		MyString& operator=(const MyString& other);
		MyString& operator=(MyString&& other) noexcept;

		~MyString();

		MyString operator+(const MyString& other) const;
		bool operator==(const MyString& other) const;
		char& operator[](size_t index);
		const char& operator[](size_t index) const;
		friend std::ostream& operator<<(std::ostream& os, const MyString& str);
		friend std::istream& operator>>(std::istream& is, MyString& str);

		size_t size() const;
		const char* c_str() const;
		MyString substr(size_t pos, size_t len) const;
		void clear();
};

#endif // MYSTRING
