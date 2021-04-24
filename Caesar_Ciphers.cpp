#include <iostream>
#include <string>
using namespace std;
 
string decrypt(string text) {
    for (int i = 0; i < text.length(); i++) {
        int charIndex = (text[i] - 'A');
        charIndex = (charIndex + 26 - 3) % 26;
        text[i] = charIndex + 'A';
    }
    return text;
}
 
int main() {
    string text = "WROLYHLVWKHUDUHVWWKLQJLQWKHZRUOGPRVWSHRSOHMXVWHALVW";
    cout << '\n' << "Encrypted: " << text << '\n' << endl;
    cout << "Decrypted: " << decrypt(text) << '\n' << endl;
    return 0;
}