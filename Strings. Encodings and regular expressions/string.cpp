#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string str = " Hello, World! ";

    // String length
    cout << "Length: " << str.length() << endl;

    // Accessing individual characters
    cout << "Character at index 1: " << str[1] << endl;

    // Substring extraction
    string sub1 = str.substr(1, 5);
    cout << "Substring (1,5): " << sub1 << endl;

    // Concatenation
    string str2 = "Welcome";
    string result = str + " " + str2;
    cout << "Concatenated string: " << result << endl;

    // Case conversion
    transform(str2.begin(), str2.end(), str2.begin(), ::toupper);
    cout << "Uppercase: " << str2 << endl;

    // Trim whitespace
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
    cout << "Trimmed string: " << str << endl;

    // String comparison
    string str3 = "hello";
    if (str3.compare("hello") == 0) {
        cout << "Strings are equal" << endl;
    }

    // Searching substring
    size_t found = str.find("World");
    if (found != string::npos) {
        cout << "Substring found at index: " << found << endl;
    }

    // Replacing substring
    str.replace(7, 5, "Universe");
    cout << "Replaced string: " << str << endl;

    // Count occurrences
    size_t count = 0;
    size_t pos = 0;
    while ((pos = str.find("lo", pos)) != string::npos) {
        count++;
        pos += 2;
    }
    cout << "Occurrences of 'lo': " << count << endl;

    // Reversing string
    reverse(str2.begin(), str2.end());
    cout << "Reversed string: " << str2 << endl;

    return 0;
}
