#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <map>
#include <utility>
#include <vector>
#include <string>
using namespace std;

// decrypts text as per given keyword
string decrypt(string text, string key) {
    int j = 0;
    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            // pick letter from keyword
            char keyChar = key[j % key.length()];
            int shift = keyChar - 'A';
            j++;
 
            // apply shift
            int charIndex = (text[i] - 'A');
            charIndex = (charIndex + 26 - shift) % 26;
            text[i] = charIndex + 'A';
        }
    }
    return text;
}
 
// reads letter frequency table from file
map <char, double> read_frequency_table() {
    map <char, double> frequency_map;
    char letter;
    double frequency;
 
    fstream file;
    file.open("letter_frequency_table.txt");
    while (file >> letter >> frequency) {
        frequency_map[letter] = frequency;
    }
    file.close();
 
    return frequency_map;
}
 
// calculate letter frequency given text
map <char, double> calculate_frequency(string text) {
    map <char, double> frequency_map;
 
    // count number of times each alphabet appears
    int count = 0;
    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            frequency_map[text[i]] += 1.0;
            count++;
        }
    }
 
    // convert counts to percentage
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        frequency_map[letter] = (100.0 * frequency_map[letter]) / count;
    }
 
    return frequency_map;
}
 
double mismatch(string text) {
    // get the two frequency tables
    map <char, double> frequency = read_frequency_table();
    map <char, double> text_frequency = calculate_frequency(text);
 
    // calculate the mismatch
    double mismatch = 0;
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        mismatch += abs(frequency[letter] - text_frequency[letter]);
        // cout << frequency[letter] << ' ' << text_frequency[letter] << endl; // for debugging
    }
 
    return mismatch;
}
 
string read_file(string filename) {
    fstream file;
    file.open(filename);
 
    // read line by line, and keep concatenating to text.
    string text = "";
    string line;
    while (getline(file, line))
        text += line + "\n";
    file.close();
 
    // cout << text << endl; // for debugging
    return text;
}
 
int main() {
    // read encrypted text
    string encrypted = read_file("encrypted.txt");
 
    // open keys file
    fstream keys_file;
    keys_file.open("keys.txt");
    vector < pair <double, string> > mismatches;
 
    // for each key, calculate the mismatch
    string key;
    while (keys_file >> key) {
        double m = mismatch(decrypt(encrypted, key));
        mismatches.push_back(make_pair(m, key));
    }
    keys_file.close();
 
    // Sort mismatches and output the mismatch, key for the top 25.
    sort(mismatches.begin(), mismatches.end());
    for (int i = 0; i < 25; i++) {
        cout << mismatches[i].first << ' ' << mismatches[i].second << endl;
    }
 
    // Print the answer
    key = mismatches[0].second;
    cout << decrypt(encrypted, key) << endl;
 
    return 0;
}