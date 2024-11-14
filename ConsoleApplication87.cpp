#include <iostream>

class String {
protected:
    char* data;
    size_t length;

public:
    String() : data(nullptr), length(0) {}

    String(const char* str) {
        length = 0;
        while (str[length] != '\0') {
            length++;
        }

        data = new char[length + 1];
        for (size_t i = 0; i < length; i++) {
            data[i] = str[i];
        }
        data[length] = '\0';
    }

    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        for (size_t i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
        data[length] = '\0';
    }

    String& operator=(const String& other) {
        if (this == &other) return *this;

        delete[] data;
        length = other.length;
        data = new char[length + 1];
        for (size_t i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
        data[length] = '\0';

        return *this;
    }

    size_t getLength() const {
        return length;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        length = 0;
    }

    virtual ~String() {
        delete[] data;
    }

    String operator+(const String& other) const {
        String result;
        result.length = length + other.length;
        result.data = new char[result.length + 1];

        for (size_t i = 0; i < length; i++) {
            result.data[i] = data[i];
        }

        for (size_t i = 0; i < other.length; i++) {
            result.data[length + i] = other.data[i];
        }

        result.data[result.length] = '\0';
        return result;
    }

    String& operator+=(const String& other) {
        char* newData = new char[length + other.length + 1];

        for (size_t i = 0; i < length; i++) {
            newData[i] = data[i];
        }

        for (size_t i = 0; i < other.length; i++) {
            newData[length + i] = other.data[i];
        }

        newData[length + other.length] = '\0';

        delete[] data;
        data = newData;
        length += other.length;

        return *this;
    }

    bool operator==(const String& other) const {
        if (length != other.length) return false;

        for (size_t i = 0; i < length; i++) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    void display() const {
        if (data) {
            for (size_t i = 0; i < length; i++) {
                std::cout << data[i];
            }
        }
        else {
            std::cout << "(empty)";
        }
    }

    const char* getData() const {
        return data;
    }
};

class BitString : public String {
private:
    bool isValidBitString(const char* str) const {
        for (size_t i = 0; str[i] != '\0'; i++) {
            if (str[i] != '0' && str[i] != '1') {
                return false;
            }
        }
        return true;
    }

public:
    BitString() : String() {}

    BitString(const char* str) {
        if (isValidBitString(str)) {
            length = 0;
            while (str[length] != '\0') {
                length++;
            }

            data = new char[length + 1];
            for (size_t i = 0; i < length; i++) {
                data[i] = str[i];
            }
            data[length] = '\0';
        }
        else {
            data = nullptr;
            length = 0;
        }
    }

    BitString(const BitString& other) : String(other) {}

    BitString& operator=(const BitString& other) {
        if (this == &other) return *this;
        String::operator=(other);
        return *this;
    }

    void negate() {
        for (size_t i = 0; i < length; i++) {
            data[i] = (data[i] == '0') ? '1' : '0';
        }

        for (int i = length - 1; i >= 0; i--) {
            if (data[i] == '0') {
                data[i] = '1';
                break;
            }
            else {
                data[i] = '0';
            }
        }
    }

    BitString operator+(const BitString& other) const {
        int num1 = toInt();
        int num2 = other.toInt();
        int sum = num1 + num2;

        return BitString(toBinaryString(sum));
    }

    BitString& operator+=(const BitString& other) {
        *this = *this + other;
        return *this;
    }

    bool operator==(const BitString& other) const {
        return String::operator==(other);
    }

    bool operator!=(const BitString& other) const {
        return !(*this == other);
    }

private:
    int toInt() const {
        int result = 0;
        for (size_t i = 0; i < length; i++) {
            result = result * 2 + (data[i] - '0');
        }
        return result;
    }

    const char* toBinaryString(int num) const {
        static char buffer[33];
        buffer[32] = '\0';
        for (int i = 31; i >= 0; i--) {
            buffer[i] = (num % 2) ? '1' : '0';
            num /= 2;
        }
        return buffer;
    }

};

int main() {
    String str1("Hello");
    String str2("World");
    String str3 = str1 + str2;
    str3.display();

    BitString bitStr1("1010");
    BitString bitStr2("0101");
    BitString bitStr3 = bitStr1 + bitStr2;
    bitStr3.display();

    bitStr1.negate();
    bitStr1.display();

    return 0;
}
