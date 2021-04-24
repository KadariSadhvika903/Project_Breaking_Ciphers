#include <iostream>
#include <string>
using namespace std;
 
string decrypt(string text, int shift) {
    for (int i = 0; i < text.length(); i++) {
        int charIndex = (text[i] - 'A');
        charIndex = (charIndex + 26 - shift) % 26;
        text[i] = charIndex + 'A';
    }
    return text;
}
 
int main() {
    // string text = "SHIFTMESSAGE";
    string text = "DCANIWDHTLWDPIITBEIIWTPQHJGSRPCPRWXTKTIWTXBEDHHXQAT";
    cout << "Text   : " << text << endl;
    for (int shift = 0; shift < 26; shift++) {
        cout << "Shift " << shift << " : " << decrypt(text, shift) << endl;
    }
    return 0;
}