#include "secret.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <sstream>
#include <fstream> 

std::string encryptByCipher(int cipherNum, const std::string& key, const std::string& text);
std::string decryptByCipher(int cipherNum, const std::string& key, const std::string& cipherText);



void test()
{

    // Example 1: Caesar Cipher
    std::string caesarText = "HELLO";
    int shift = 3;
    std::string caesarEncrypted = caesarEncrypt(caesarText, shift);
    std::string caesarDecrypted = caesarDecrypt(caesarEncrypted, shift);
    std::cout << "Caesar Cipher:\n";
    std::cout << "Original: " << caesarText << "\n";
    std::cout << "Encrypted: " << caesarEncrypted << "\n";
    std::cout << "Decrypted: " << caesarDecrypted << "\n\n";


    Sleep(100);

    // Example 2: Vigenère Cipher
    std::string vigenereText = "ATTACKATDAWN";
    std::string vigenereKey = "LEMON";
    std::string vigenereEncrypted = vigenereEncrypt(vigenereText, vigenereKey);
    std::string vigenereDecrypted = vigenereDecrypt(vigenereEncrypted, vigenereKey);
    std::cout << "Vigenère Cipher:\n";
    std::cout << "Original: " << vigenereText << "\n";
    std::cout << "Encrypted: " << vigenereEncrypted << "\n";
    std::cout << "Decrypted: " << vigenereDecrypted << "\n\n";

    Sleep(100);

    // Example 3: Playfair Cipher
    std::string playfairText = "HIDETHEGOLD";
    std::string playfairKey = "KEYWORD";
    std::cout << "Playfair Cipher:\n";
    std::cout << "Original: " << playfairText << "\n";
    std::cout << "Encrypted: " << playfairEncrypt(playfairText, playfairKey) << "\n";
    std::cout << "Decrypted: " << playfairDecrypt(playfairEncrypt(playfairText, playfairKey), playfairKey) << "\n\n";

    Sleep(100);

    // Example 4: Rail Fence Cipher
    std::string railText = "WEAREDISCOVEREDFLEEATONCE";
    int rails = 3;
    std::string railEncrypted = railFenceEncrypt(railText, rails);
    std::string railDecrypted = railFenceDecrypt(railEncrypted, rails);
    std::cout << "Rail Fence Cipher:\n";
    std::cout << "Original: " << railText << "\n";
    std::cout << "Encrypted: " << railEncrypted << "\n";
    std::cout << "Decrypted: " << railDecrypted << "\n\n";


    Sleep(100);

    // Example 5: Substitution Cipher
    std::string subText = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string subKey = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    std::string subEncrypted = substitutionEncrypt(subText, subKey);
    std::string subDecrypted = substitutionDecrypt(subEncrypted, subKey);
    std::cout << "Substitution Cipher:\n";
    std::cout << "Original: " << subText << "\n";
    std::cout << "Encrypted: " << subEncrypted << "\n";
    std::cout << "Decrypted: " << subDecrypted << "\n\n";


    Sleep(100);

    // Example 6: Atbash Cipher
    std::string atbashText = "ABCDEFG";
    std::string atbashEncrypted = atbashEncrypt(atbashText);
    std::string atbashDecrypted = atbashDecrypt(atbashEncrypted);
    std::cout << "Atbash Cipher:\n";
    std::cout << "Original: " << atbashText << "\n";
    std::cout << "Encrypted: " << atbashEncrypted << "\n";
    std::cout << "Decrypted: " << atbashDecrypted << "\n\n";


    Sleep(100);

    // Example 7: Scytale Cipher
    std::string scytaleText = "HELLOWORLD";
    size_t scytaleDiameter = 2;
    std::cout << "Scytale Cipher:\n";
    std::cout << "Original: " << scytaleText << "\n";
    std::cout << "Encrypted: " << scytaleEncrypt(scytaleText, scytaleDiameter) << "\n";
    std::cout << "Decrypted: " << scytaleDecrypt(scytaleEncrypt(scytaleText, scytaleDiameter), scytaleDiameter) << "\n\n";


    Sleep(100);

    // Example 8: Hill Cipher



    std::string hillText = "ACT";
    std::vector<std::vector<int>> hillKey = { {6, 24, 1}, {13, 16, 10}, {20, 17, 15} };
    std::string hillEncrypted = hillEncrypt(hillText, hillKey);
    std::string hillDecrypted = hillDecrypt(hillEncrypted, hillKey);
    std::cout << "Hill Cipher:\n";
    std::cout << "Original: " << hillText << "\n";
    std::cout << "Encrypted: " << hillEncrypted << "\n";
    std::cout << "Decrypted: " << hillDecrypted << "\n\n";

    Sleep(100);

    // Example 9: Beaufort Cipher
    std::string beaufortText = "HELLOWORLD";
    std::string beaufortKey = "KEY";
    std::string beaufortEncrypted = beaufortEncrypt(beaufortText, beaufortKey);
    std::string beaufortDecrypted = beaufortDecrypt(beaufortEncrypted, beaufortKey);
    std::cout << "Beaufort Cipher:\n";
    std::cout << "Original: " << beaufortText << "\n";
    std::cout << "Encrypted: " << beaufortEncrypted << "\n";
    std::cout << "Decrypted: " << beaufortDecrypted << "\n\n";

    Sleep(100);

    // ADFGVX Cipher
    std::string adfgvxText = "ATTACK";
    std::string adfgvxKey = "GERMAN";
    //std::string adfgvxSquare = "PH0QGI6NU4A1Y7L5V3R2Z8WXSTB9CDFEKMJB";
     const std::string adfgvxSquare =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";   // simplest valid square

    std::cout << "ADFGVX Cipher:\n";
    std::cout << "Original: " << adfgvxText << "\n";
    std::cout << "Encrypted: " << adfgvxEncrypt(adfgvxText, adfgvxKey, adfgvxSquare) << "\n";
    std::cout << "Decrypted: " << adfgvxDecrypt(adfgvxEncrypt(adfgvxText, adfgvxKey, adfgvxSquare), adfgvxKey, adfgvxSquare) << "\n\n";


    Sleep(100);

    // Example 11: Polybius Square Cipher
    std::string polybiusText = "HELLOWORLD";
    std::string polybiusSquare = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    std::string polybiusEncrypted = polybiusEncrypt(polybiusText, polybiusSquare);
    std::string polybiusDecrypted = polybiusDecrypt(polybiusEncrypted, polybiusSquare);
    std::cout << "Polybius Square Cipher:\n";
    std::cout << "Original: " << polybiusText << "\n";
    std::cout << "Encrypted: " << polybiusEncrypted << "\n";
    std::cout << "Decrypted: " << polybiusDecrypted << "\n\n";

    Sleep(100);

    // Example 12: Grille Cipher
    std::string grilleText = "SECRETMESSAGE";
    std::vector<std::vector<int>> grille = {
        {1, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1}
    };
    size_t grilleSize = 4;
    std::cout << "Grille Cipher:\n";
    std::cout << "Original: " << grilleText << "\n";
    std::cout << "Encrypted: " << grilleEncrypt(grilleText, grille, grilleSize) << "\n";
    std::cout << "Decrypted: " << grilleDecrypt(grilleEncrypt(grilleText, grille, grilleSize), grille, grilleSize) << "\n\n";


    Sleep(100);

    // Example 13: One-Time Pad
    std::string otpText = "ATTACK";
    std::string otpKey = "XMCKLB";
    std::string otpEncrypted = oneTimePadEncrypt(otpText, otpKey);
    std::string otpDecrypted = oneTimePadDecrypt(otpEncrypted, otpKey);
    std::cout << "One-Time Pad:\n";
    std::cout << "Original: " << otpText << "\n";
    std::cout << "Encrypted: " << otpEncrypted << "\n";
    std::cout << "Decrypted: " << otpDecrypted << "\n\n";

    Sleep(100);

    // Example 14: Autokey Cipher
    std::string autokeyText = "ATTACK";
    std::string autokeyKey = "QUEENLY";
    std::string autokeyEncrypted = autokeyEncrypt(autokeyText, autokeyKey);
    std::string autokeyDecrypted = autokeyDecrypt(autokeyEncrypted, autokeyKey);
    std::cout << "Autokey Cipher:\n";
    std::cout << "Original: " << autokeyText << "\n";
    std::cout << "Encrypted: " << autokeyEncrypted << "\n";
    std::cout << "Decrypted: " << autokeyDecrypted << "\n\n";

    Sleep(100);

    // Example 15: Four-Square Cipher
    std::string fourSquareText = "HELP";
    std::string fourSquareKey1 = "EXAMPLE";
    std::string fourSquareKey2 = "KEYWORD";
    std::string fourSquareEncrypted = fourSquareEncrypt(fourSquareText, fourSquareKey1, fourSquareKey2);
    std::string fourSquareDecrypted = fourSquareDecrypt(fourSquareEncrypted, fourSquareKey1, fourSquareKey2);
    std::cout << "Four-Square Cipher:\n";
    std::cout << "Original: " << fourSquareText << "\n";
    std::cout << "Encrypted: " << fourSquareEncrypted << "\n";
    std::cout << "Decrypted: " << fourSquareDecrypted << "\n\n";

    Sleep(100);

    // Example 16: Bazeries Cipher
    std::string bazeriesText = "CRYPTO";
    std::string bazeriesKey = "CIPHER";
    size_t bazeriesNumber = 3;
    std::string bazeriesEncrypted = bazeriesEncrypt(bazeriesText, bazeriesKey, bazeriesNumber);
    std::string bazeriesDecrypted = bazeriesDecrypt(bazeriesEncrypted, bazeriesKey, bazeriesNumber);
    std::cout << "Bazeries Cipher:\n";
    std::cout << "Original: " << bazeriesText << "\n";
    std::cout << "Encrypted: " << bazeriesEncrypted << "\n";
    std::cout << "Decrypted: " << bazeriesDecrypted << "\n\n";

    Sleep(100);

    // Example 17: Columnar Transposition
    std::string columnarText = "WEAREDISCOVEREDFLEEATONCE";
    std::string columnarKey = "CANO";
    std::cout << "Columnar Transposition:\n";
    std::cout << "Original: " << columnarText << "\n";
    std::cout << "Encrypted: " << columnarTranspositionEncrypt(columnarText, columnarKey) << "\n";
    std::cout << "Decrypted: " << columnarTranspositionDecrypt(columnarTranspositionEncrypt(columnarText, columnarKey), columnarKey) << "\n\n";

    Sleep(100);

    // Example 18: Bacon Cipher
    std::string baconText = "HELLO";
    std::string baconEncrypted = baconEncrypt(baconText);
    std::string baconDecrypted = baconDecrypt(baconEncrypted);
    std::cout << "Bacon Cipher:\n";
    std::cout << "Original: " << baconText << "\n";
    std::cout << "Encrypted: " << baconEncrypted << "\n";
    std::cout << "Decrypted: " << baconDecrypted << "\n\n";

    Sleep(100);

    // Example 19: Porta Cipher
    std::string portaText = "ATTACKATDAWN";
    std::string portaKey = "KEY";
    std::cout << "Porta Cipher:\n";
    std::cout << "Original: " << portaText << "\n";
    std::cout << "Encrypted: " << portaEncrypt(portaText, portaKey) << "\n";
    std::cout << "Decrypted: " << portaDecrypt(portaEncrypt(portaText, portaKey), portaKey) << "\n\n";


    Sleep(100);

    // Example 20: Chaocipher
    std::string chaoText = "HELLOWORLD";
    std::string leftKey = "HXUCZVAMDSLKPEFJRIGTWOBNYQ";
    std::string rightKey = "PTLNBQDEOYSFAVZKGJRIHWXUMC";
    std::string chaoEncrypted = chaocipherEncrypt(chaoText, leftKey, rightKey);
    std::string chaoDecrypted = chaocipherDecrypt(chaoEncrypted, leftKey, rightKey);
    std::cout << "Chaocipher:\n";
    std::cout << "Original: " << chaoText << "\n";
    std::cout << "Encrypted: " << chaoEncrypted << "\n";
    std::cout << "Decrypted: " << chaoDecrypted << "\n\n";

    Sleep(100);


    // Example 21: Alberti Cipher Disk
    std::string albertiText = "HELLOWORLD";
    std::string albertiKey = "CIPHER";
    int albertiShift = 3;
    std::string albertiEncrypted = albertiEncrypt(albertiText, albertiKey, albertiShift);
    std::string albertiDecrypted = albertiDecrypt(albertiEncrypted, albertiKey, albertiShift);
    std::cout << "Alberti Cipher Disk:\n";
    std::cout << "Original: " << albertiText << "\n";
    std::cout << "Encrypted: " << albertiEncrypted << "\n";
    std::cout << "Decrypted: " << albertiDecrypted << "\n\n";

    Sleep(100);

    // Example 22: Two-Square Cipher
    std::string twoSquareText = "HELP";
    std::string twoSquareKey1 = "EXAMPLE";
    std::string twoSquareKey2 = "KEYWORD";
    std::string twoSquareEncrypted = twoSquareEncrypt(twoSquareText, twoSquareKey1, twoSquareKey2);
    std::string twoSquareDecrypted = twoSquareDecrypt(twoSquareEncrypted, twoSquareKey1, twoSquareKey2);
    std::cout << "Two-Square Cipher:\n";
    std::cout << "Original: " << twoSquareText << "\n";
    std::cout << "Encrypted: " << twoSquareEncrypted << "\n";
    std::cout << "Decrypted: " << twoSquareDecrypted << "\n\n";

    Sleep(100);

    // Example 23: Bifid Cipher
    std::string bifidText = "HELLOWORLD";
    std::string bifidKey = "PLAYFAIREXAMPLE";
    std::string bifidEncrypted = bifidEncrypt(bifidText, bifidKey);
    std::string bifidDecrypted = bifidDecrypt(bifidEncrypted, bifidKey);
    std::cout << "Bifid Cipher:\n";
    std::cout << "Original: " << bifidText << "\n";
    std::cout << "Encrypted: " << bifidEncrypted << "\n";
    std::cout << "Decrypted: " << bifidDecrypted << "\n\n";


    Sleep(100);

    // Example 24: Trifid Cipher
    // Example 24: Trifid Cipher
    std::string trifidText = "HELLO";
    std::string trifidKey = "CIPHER";
    int trifidPeriod = 5;
    std::string trifidEncrypted = trifidEncrypt(trifidText, trifidKey, trifidPeriod);
    std::string trifidDecrypted = trifidDecrypt(trifidEncrypted, trifidKey, trifidPeriod);
    std::cout << "Trifid Cipher:\n";
    std::cout << "Original: " << trifidText << "\n";
    std::cout << "Encrypted: " << trifidEncrypted << "\n";
    std::cout << "Decrypted: " << trifidDecrypted << "\n\n";



    Sleep(100);

    // Example 25: Nihilist Cipher
    std::string nihilistText = "ATTACK";
    std::string nihilistKey = "CIPHER";
    std::string nihilistSquare = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    std::string nihilistEncrypted = nihilistEncrypt(nihilistText, nihilistKey, nihilistSquare);
    std::string nihilistDecrypted = nihilistDecrypt(nihilistEncrypted, nihilistKey, nihilistSquare);
    std::cout << "Nihilist Cipher:\n";
    std::cout << "Original: " << nihilistText << "\n";
    std::cout << "Encrypted: " << nihilistEncrypted << "\n";
    std::cout << "Decrypted: " << nihilistDecrypted << "\n\n";

    Sleep(100);

    // Example 26: Homophonic Substitution
    std::string homophonicText = "HELLO";
    std::vector<std::vector<std::string>> homophonicSubstitutes(26);
    // Assign some substitute values (in practice, this would be more comprehensive)
    homophonicSubstitutes['H' - 'A'] = { "23", "45" };
    homophonicSubstitutes['E' - 'A'] = { "12", "34", "56" };
    homophonicSubstitutes['L' - 'A'] = { "78", "90" };
    homophonicSubstitutes['O' - 'A'] = { "11", "22" };
    std::string homophonicEncrypted = homophonicEncrypt(homophonicText, homophonicSubstitutes);
    std::string homophonicDecrypted = homophonicDecrypt(homophonicEncrypted, homophonicSubstitutes);
    std::cout << "Homophonic Substitution:\n";
    std::cout << "Original: " << homophonicText << "\n";
    std::cout << "Encrypted: " << homophonicEncrypted << "\n";
    std::cout << "Decrypted: " << homophonicDecrypted << "\n\n";

    Sleep(100);

    // Example 27: Checkerboard Cipher
    std::string checkerboardText = "HELLO";
    std::string checkerboardKey = "CIPHER";
    std::string checkerboardDigits = "1234567890";
    std::string checkerboardEncrypted = checkerboardEncrypt(checkerboardText, checkerboardKey, checkerboardDigits);
    std::string checkerboardDecrypted = checkerboardDecrypt(checkerboardEncrypted, checkerboardKey, checkerboardDigits);
    std::cout << "Checkerboard Cipher:\n";
    std::cout << "Original: " << checkerboardText << "\n";
    std::cout << "Encrypted: " << checkerboardEncrypted << "\n";
    std::cout << "Decrypted: " << checkerboardDecrypted << "\n\n";

    Sleep(100);

    // Example 28: Fractionated Morse
    std::string morseText = "HELLO";
    std::string morseKey = "CIPHER";
    std::string morseEncrypted = fractionatedMorseEncrypt(morseText, morseKey);
    std::string morseDecrypted = fractionatedMorseDecrypt(morseEncrypted, morseKey);
    std::cout << "Fractionated Morse:\n";
    std::cout << "Original: " << morseText << "\n";
    std::cout << "Encrypted: " << morseEncrypted << "\n";
    std::cout << "Decrypted: " << morseDecrypted << "\n\n";

    Sleep(100);

    // Example 29: Kama-Sutra Cipher
    std::string kamaText = "ABCDEFG";
    std::string kamaEncrypted = kamaSutraEncrypt(kamaText);
    std::string kamaDecrypted = kamaSutraDecrypt(kamaEncrypted);
    std::cout << "Kama-Sutra Cipher:\n";
    std::cout << "Original: " << kamaText << "\n";
    std::cout << "Encrypted: " << kamaEncrypted << "\n";
    std::cout << "Decrypted: " << kamaDecrypted << "\n\n";

    Sleep(100);

    // Example 30: Pollux Cipher
    std::string polluxText = "SOS";
    std::string polluxDigits = "123456789";
    std::string polluxEncrypted = polluxEncrypt(polluxText, polluxDigits);
    std::string polluxDecrypted = polluxDecrypt(polluxEncrypted, polluxDigits);
    std::cout << "Pollux Cipher:\n";
    std::cout << "Original: " << polluxText << "\n";
    std::cout << "Encrypted: " << polluxEncrypted << "\n";
    std::cout << "Decrypted: " << polluxDecrypted << "\n\n";


    Sleep(1000 * 100);

    
}
















// Command interpreter
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <command> [args]\n";
        std::cout << "Commands:\n";
        std::cout << "  help                - Display this help message\n";
        std::cout << "  show                - Show source code (not implemented)\n";
        std::cout << "  test                - Run all cipher tests\n";
        std::cout << "  select <number> <key> <text> - Run cipher <number> with <key> and <text>\n";
        std::cout << "  e <number> <key> <text> [output_file] - Encrypt text with cipher <number>\n";
        std::cout << "  d <number> <key> <text> [output_file] - Decrypt text with cipher <number>\n";
        std::cout << "Ciphers:\n";
        std::cout << "  1: Caesar\n"; // Add more ciphers as implemented
        return 1;
    }

    std::string command = argv[1];

 

    if (command == "help") {
        std::cout << "Usage: " << argv[0] << " <command> [args]\n";
        std::cout << "Commands:\n";
        std::cout << "  help                - Display this help message\n";
        std::cout << "  show                - Show source code (not implemented)\n";
        std::cout << "  test                - Run all cipher tests\n";
        std::cout << "  select <number> <key> <text> - Run cipher <number> with <key> and <text>\n";
        std::cout << "  e <number> <key> <text> [output_file] - Encrypt text with cipher <number>\n";
        std::cout << "  d <number> <key> <text> [output_file] - Decrypt text with cipher <number>\n";
        std::cout << "Ciphers:\n";
        std::cout << "  1: Caesar\n"; // Add more ciphers as implemented
    }

    if (command == "test") {
        test();
        return 0;
    }

    if (command == "select") {
        if (argc < 5) {
            std::cout << "Usage: " << argv[0] << " select <number> <key> <text>\n";
            return 1;
        }

        int cipherNum;
        try {
            cipherNum = std::stoi(argv[2]);
        }
        catch (...) {
            std::cout << "Error: Cipher number must be an integer (1-30)\n";
            return 1;
        }

        if (cipherNum < 1 || cipherNum > 30) {
            std::cout << "Error: Cipher number must be between 1 and 30\n";
            return 1;
        }

        std::string key = argv[3];
        std::string text = argv[4];

        std::string encrypted, decrypted;
        switch (cipherNum) {
        case 1: { // Caesar
            int shift;
            try {
                shift = std::stoi(key);
            }
            catch (...) {
                std::cout << "Error: Key must be an integer shift\n";
                return 1;
            }
            encrypted = caesarEncrypt(text, shift);
            decrypted = caesarDecrypt(encrypted, shift);
            std::cout << "Caesar Cipher:\n";
            break;
        }
        case 2: { // Vigenère
            encrypted = vigenereEncrypt(text, key);
            decrypted = vigenereDecrypt(encrypted, key);
            std::cout << "Vigenère Cipher:\n";
            break;
        }
        case 3: { // Playfair
            encrypted = playfairEncrypt(text, key);
            decrypted = playfairDecrypt(encrypted, key);
            std::cout << "Playfair Cipher:\n";
            break;
        }
        case 4: { // Rail Fence
            int rails;
            try {
                rails = std::stoi(key);
            }
            catch (...) {
                std::cout << "Error: Key must be an integer number of rails\n";
                return 1;
            }
            encrypted = railFenceEncrypt(text, rails);
            decrypted = railFenceDecrypt(encrypted, rails);
            std::cout << "Rail Fence Cipher:\n";
            break;
        }
        case 5: { // Substitution
            if (key.length() != 26) {
                std::cout << "Error: Key must be 26 unique letters\n";
                return 1;
            }
            encrypted = substitutionEncrypt(text, key);
            decrypted = substitutionDecrypt(encrypted, key);
            std::cout << "Substitution Cipher:\n";
            break;
        }
        case 6: { // Atbash
            encrypted = atbashEncrypt(text);
            decrypted = atbashDecrypt(encrypted);
            std::cout << "Atbash Cipher:\n";
            break;
        }
        case 7: { // Scytale
            size_t diameter;
            try {
                diameter = std::stoi(key);
            }
            catch (...) {
                std::cout << "Error: Key must be an integer diameter\n";
                return 1;
            }
            encrypted = scytaleEncrypt(text, diameter);
            decrypted = scytaleDecrypt(encrypted, diameter);
            std::cout << "Scytale Cipher:\n";
            break;
        }
        case 8: { // Hill
            std::vector<std::vector<int>> hillKey(3, std::vector<int>(3));
            std::stringstream ss(key);
            std::string num;
            int i = 0, j = 0;
            while (std::getline(ss, num, ',')) {
                try {
                    hillKey[i][j] = std::stoi(num);
                    if (++j == 3) { j = 0; ++i; }
                }
                catch (...) {
                    std::cout << "Error: Key must be 9 comma-separated integers (3x3 matrix)\n";
                    return 1;
                }
            }
            if (i != 3 || j != 0) {
                std::cout << "Error: Key must be 9 comma-separated integers\n";
                return 1;
            }
            encrypted = hillEncrypt(text, hillKey);
            decrypted = hillDecrypt(encrypted, hillKey);
            std::cout << "Hill Cipher:\n";
            break;
        }
        case 9: { // Beaufort
            encrypted = beaufortEncrypt(text, key);
            decrypted = beaufortDecrypt(encrypted, key);
            std::cout << "Beaufort Cipher:\n";
            break;
        }
        case 10: { // ADFGVX
            std::string square = "PH0QGI6NU4A1Y7L5V3R2Z8WXSTB9CDFEKMJB";
            encrypted = adfgvxEncrypt(text, key, square);
            decrypted = adfgvxDecrypt(encrypted, key, square);
            std::cout << "ADFGVX Cipher:\n";
            break;
        }
        case 11: { // Polybius Square
            std::string square = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
            encrypted = polybiusEncrypt(text, square);
            decrypted = polybiusDecrypt(encrypted, square);
            std::cout << "Polybius Square Cipher:\n";
            break;
        }
        case 12: { // Grille
            std::vector<std::vector<int>> grille(4, std::vector<int>(4));
            std::stringstream ss(key);
            std::string row;
            int i = 0;
            while (std::getline(ss, row, ';')) {
                std::stringstream row_ss(row);
                std::string val;
                int j = 0;
                while (std::getline(row_ss, val, ',')) {
                    try {
                        grille[i][j] = std::stoi(val);
                        ++j;
                    }
                    catch (...) {
                        std::cout << "Error: Key must be 4x4 grille (e.g., 1,0,0,0;0,1,0,0;0,0,1,0;0,0,0,1)\n";
                        return 1;
                    }
                }
                if (j != 4) {
                    std::cout << "Error: Each grille row must have 4 values\n";
                    return 1;
                }
                ++i;
            }
            if (i != 4) {
                std::cout << "Error: Grille must have 4 rows\n";
                return 1;
            }
            encrypted = grilleEncrypt(text, grille, 4);
            decrypted = grilleDecrypt(encrypted, grille, 4);
            std::cout << "Grille Cipher:\n";
            break;
        }
        case 13: { // One-Time Pad
            encrypted = oneTimePadEncrypt(text, key);
            decrypted = oneTimePadDecrypt(encrypted, key);
            std::cout << "One-Time Pad:\n";
            break;
        }
        case 14: { // Autokey
            encrypted = autokeyEncrypt(text, key);
            decrypted = autokeyDecrypt(encrypted, key);
            std::cout << "Autokey Cipher:\n";
            break;
        }
        case 15: { // Four-Square
            std::stringstream ss(key);
            std::string key1, key2;
            std::getline(ss, key1, ',');
            std::getline(ss, key2);
            if (key2.empty()) {
                std::cout << "Error: Key must be two keys (e.g., KEYWORD,CIPHER)\n";
                return 1;
            }
            encrypted = fourSquareEncrypt(text, key1, key2);
            decrypted = fourSquareDecrypt(encrypted, key1, key2);
            std::cout << "Four-Square Cipher:\n";
            break;
        }
        case 16: { // Bazeries
            std::stringstream ss(key);
            std::string k;
            size_t number;
            std::getline(ss, k, ',');
            try {
                number = std::stoi(ss.str().substr(ss.tellg()));
            }
            catch (...) {
                std::cout << "Error: Key must be key,number (e.g., CIPHER,3)\n";
                return 1;
            }
            encrypted = bazeriesEncrypt(text, k, number);
            decrypted = bazeriesDecrypt(encrypted, k, number);
            std::cout << "Bazeries Cipher:\n";
            break;
        }
        case 17: { // Columnar Transposition
            encrypted = columnarTranspositionEncrypt(text, key);
            decrypted = columnarTranspositionDecrypt(encrypted, key);
            std::cout << "Columnar Transposition:\n";
            break;
        }
        case 18: { // Bacon
            encrypted = baconEncrypt(text);
            decrypted = baconDecrypt(encrypted);
            std::cout << "Bacon Cipher:\n";
            break;
        }
        case 19: { // Porta
            encrypted = portaEncrypt(text, key);
            decrypted = portaDecrypt(encrypted, key);
            std::cout << "Porta Cipher:\n";
            break;
        }
        case 20: { // Chaocipher
            std::stringstream ss(key);
            std::string leftKey, rightKey;
            std::getline(ss, leftKey, ',');
            std::getline(ss, rightKey);
            if (rightKey.empty()) {
                std::cout << "Error: Key must be two alphabets (e.g., HXUCZVAMDSLKPEFJRIGTWOBNYQ,PTLNBQDEOYSFAVZKGJRIHWXUMC)\n";
                return 1;
            }
            encrypted = chaocipherEncrypt(text, leftKey, rightKey);
            decrypted = chaocipherDecrypt(encrypted, leftKey, rightKey);
            std::cout << "Chaocipher:\n";
            break;
        }
        case 21: { // Alberti
            std::stringstream ss(key);
            std::string k;
            int shift;
            std::getline(ss, k, ',');
            try {
                shift = std::stoi(ss.str().substr(ss.tellg()));
            }
            catch (...) {
                std::cout << "Error: Key must be key,shift (e.g., CIPHER,4)\n";
                return 1;
            }
            encrypted = albertiEncrypt(text, k, shift);
            decrypted = albertiDecrypt(encrypted, k, shift);
            std::cout << "Alberti Cipher:\n";
            break;
        }
        case 22: { // Two-Square
            std::stringstream ss(key);
            std::string key1, key2;
            std::getline(ss, key1, ',');
            std::getline(ss, key2);
            if (key2.empty()) {
                std::cout << "Error: Key must be two keys (e.g., EXAMPLE,KEYWORD)\n";
                return 1;
            }
            encrypted = twoSquareEncrypt(text, key1, key2);
            decrypted = twoSquareDecrypt(encrypted, key1, key2);
            std::cout << "Two-Square Cipher:\n";
            break;
        }
        case 23: { // Bifid
            encrypted = bifidEncrypt(text, key);
            decrypted = bifidDecrypt(encrypted, key);
            std::cout << "Bifid Cipher:\n";
            break;
        }
        case 24: { // Trifid
            std::stringstream ss(key);
            std::string k;
            int period;
            std::getline(ss, k, ',');
            try {
                period = std::stoi(ss.str().substr(ss.tellg()));
            }
            catch (...) {
                std::cout << "Error: Key must be key,period (e.g., KEYWORD,5)\n";
                return 1;
            }
            encrypted = trifidEncrypt(text, k, period);
            decrypted = trifidDecrypt(encrypted, k, period);
            std::cout << "Trifid Cipher:\n";
            break;
        }
        case 25: { // Nihilist
            std::stringstream ss(key);
            std::string k, square;
            std::getline(ss, k, ',');
            std::getline(ss, square);
            if (square.empty()) {
                std::cout << "Error: Key must be key,square (e.g., CIPHER,ABCDEFGHIKLMNOPQRSTUVWXYZ)\n";
                return 1;
            }
            encrypted = nihilistEncrypt(text, k, square);
            decrypted = nihilistDecrypt(encrypted, k, square);
            std::cout << "Nihilist Cipher:\n";
            break;
        }
        case 26: { // Homophonic Substitution
            std::vector<std::vector<std::string>> substitutes(26);
            substitutes['H' - 'A'] = { "23", "45" };
            substitutes['E' - 'A'] = { "12", "34", "56" };
            substitutes['L' - 'A'] = { "78", "90" };
            substitutes['O' - 'A'] = { "11", "22" };
            encrypted = homophonicEncrypt(text, substitutes);
            decrypted = homophonicDecrypt(encrypted, substitutes);
            std::cout << "Homophonic Substitution:\n";
            break;
        }
        case 27: { // Checkerboard
            std::stringstream ss(key);
            std::string k, digits;
            std::getline(ss, k, ',');
            std::getline(ss, digits);
            if (digits.empty()) {
                std::cout << "Error: Key must be key,digits (e.g., CIPHER,1234567890)\n";
                return 1;
            }
            encrypted = checkerboardEncrypt(text, k, digits);
            decrypted = checkerboardDecrypt(encrypted, k, digits);
            std::cout << "Checkerboard Cipher:\n";
            break;
        }
        case 28: { // Fractionated Morse
            encrypted = fractionatedMorseEncrypt(text, key);
            decrypted = fractionatedMorseDecrypt(encrypted, key);
            std::cout << "Fractionated Morse:\n";
            break;
        }
        case 29: { // Kama-Sutra
            encrypted = kamaSutraEncrypt(text);
            decrypted = kamaSutraDecrypt(encrypted);
            std::cout << "Kama-Sutra Cipher:\n";
            break;
        }
        case 30: { // Pollux
            encrypted = polluxEncrypt(text, key);
            decrypted = polluxDecrypt(encrypted, key);
            std::cout << "Pollux Cipher:\n";
            break;
        }


               if (command == "e" || command == "d") {
                   if (argc < 5) {
                       std::cout << "Usage: " << argv[0] << " " << command << " <number> <key> <text>\n";
                       return 1;
                   }

                   int cipherNum;
                   try {
                       cipherNum = std::stoi(argv[2]);
                   }
                   catch (...) {
                       std::cout << "Error: Cipher number must be an integer (1-30)\n";
                       return 1;
                   }

                   if (cipherNum < 1 || cipherNum > 30) {
                       std::cout << "Error: Cipher number must be between 1 and 30\n";
                       return 1;
                   }

                   std::string key = argv[3];
                   std::string text = argv[4];
                   std::string result;

                   if (command == "e") {
                       result = encryptByCipher(cipherNum, key, text);
                       std::cout << "Encrypted: " << result << "\n";
                   }
                   else {  // command == "d"
                       result = decryptByCipher(cipherNum, key, text);
                       std::cout << "Decrypted: " << result << "\n";
                   }

                   // Write result to file
                   std::ofstream outFile("r.txt");
                   if (outFile) {
                       outFile << result;
                       outFile.close();
                       std::cout << "Result written to r.txt\n";
                   }
                   else {
                       std::cerr << "Error writing to file!\n";
                   }

                   return 0;
               }


        }



        std::cout << "Original: " << text << "\n";
        std::cout << "Encrypted: " << encrypted << "\n";
        std::cout << "Decrypted: " << decrypted << "\n";
        return 0;
    }

    std::cout << "Unknown command: " << command << "\n";
    std::cout << "Commands: help, show, test, select <number> <key> <text>\n";
    return 1;
}




/////////////////////////////////////////////////////////

std::string encryptByCipher(int cipherNum, const std::string& key, const std::string& text) {
    switch (cipherNum) {
        // Case 1: Caesar Cipher
    case 1: {
        int shift;
        try { shift = std::stoi(key); }
        catch (...) {
            std::cout << "Error: Key must be an integer shift\n";
            exit(1);
        }
        return caesarEncrypt(text, shift);
    }
          // Case 2: Vigenère Cipher
    case 2: return vigenereEncrypt(text, key);
        // Case 3: Playfair Cipher
    case 3: return playfairEncrypt(text, key);
        // Case 4: Rail Fence Cipher
    case 4: {
        int rails;
        try { rails = std::stoi(key); }
        catch (...) {
            std::cout << "Error: Key must be an integer number of rails\n";
            exit(1);
        }
        return railFenceEncrypt(text, rails);
    }
          // Case 5: Substitution Cipher
    case 5: {
        if (key.length() != 26) {
            std::cout << "Error: Key must be 26 unique letters\n";
            exit(1);
        }
        return substitutionEncrypt(text, key);
    }
          // Case 6: Atbash Cipher
    case 6: return atbashEncrypt(text);
        // Case 7: Scytale Cipher
    case 7: {
        size_t diameter;
        try { diameter = std::stoi(key); }
        catch (...) {
            std::cout << "Error: Key must be an integer diameter\n";
            exit(1);
        }
        return scytaleEncrypt(text, diameter);
    }
          // Case 8: Hill Cipher
    case 8: {
        std::vector<std::vector<int>> hillKey(3, std::vector<int>(3));
        std::stringstream ss(key);
        std::string num;
        int i = 0, j = 0;
        while (std::getline(ss, num, ',')) {
            try { hillKey[i][j] = std::stoi(num); }
            catch (...) {
                std::cout << "Error: Key must be 9 comma-separated integers\n";
                exit(1);
            }
            if (++j == 3) { j = 0; ++i; }
        }
        if (i != 3 || j != 0) {
            std::cout << "Error: Key must be 9 comma-separated integers\n";
            exit(1);
        }
        return hillEncrypt(text, hillKey);
    }
          // Case 9: Beaufort Cipher
    case 9: return beaufortEncrypt(text, key);
        // Case 10: ADFGVX Cipher
    case 10: {
        std::string square = "PH0QGI6NU4A1Y7L5V3R2Z8WXSTB9CDFEKMJB";
        return adfgvxEncrypt(text, key, square);
    }
           // Case 11: Polybius Square Cipher
    case 11: {
        std::string square = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
        return polybiusEncrypt(text, square);
    }
           // Case 12: Grille Cipher
    case 12: {
        std::vector<std::vector<int>> grille(4, std::vector<int>(4));
        std::stringstream ss(key);
        std::string row;
        int i = 0;
        while (std::getline(ss, row, ';')) {
            std::stringstream row_ss(row);
            std::string val;
            int j = 0;
            while (std::getline(row_ss, val, ',')) {
                try { grille[i][j] = std::stoi(val); }
                catch (...) {
                    std::cout << "Error: Invalid grille format\n";
                    exit(1);
                }
                ++j;
            }
            if (j != 4) {
                std::cout << "Error: Each grille row must have 4 values\n";
                exit(1);
            }
            ++i;
        }
        if (i != 4) {
            std::cout << "Error: Grille must have 4 rows\n";
            exit(1);
        }
        return grilleEncrypt(text, grille, 4);
    }
           // Case 13: One-Time Pad
    case 13: return oneTimePadEncrypt(text, key);
        // Case 14: Autokey Cipher
    case 14: return autokeyEncrypt(text, key);
        // Case 15: Four-Square Cipher
    case 15: {
        std::stringstream ss(key);
        std::string key1, key2;
        std::getline(ss, key1, ',');
        std::getline(ss, key2);
        if (key2.empty()) {
            std::cout << "Error: Key must be two comma-separated keys\n";
            exit(1);
        }
        return fourSquareEncrypt(text, key1, key2);
    }
           // Case 16: Bazeries Cipher
    case 16: {
        std::stringstream ss(key);
        std::string k;
        size_t number;
        std::getline(ss, k, ',');
        try { number = std::stoi(ss.str().substr(ss.tellg())); }
        catch (...) {
            std::cout << "Error: Key must be key,number\n";
            exit(1);
        }
        return bazeriesEncrypt(text, k, number);
    }
           // Case 17: Columnar Transposition
    case 17: return columnarTranspositionEncrypt(text, key);
        // Case 18: Bacon Cipher
    case 18: return baconEncrypt(text);
        // Case 19: Porta Cipher
    case 19: return portaEncrypt(text, key);
        // Case 20: Chaocipher
    case 20: {
        std::stringstream ss(key);
        std::string leftKey, rightKey;
        std::getline(ss, leftKey, ',');
        std::getline(ss, rightKey);
        if (rightKey.empty()) {
            std::cout << "Error: Key must be two comma-separated alphabets\n";
            exit(1);
        }
        return chaocipherEncrypt(text, leftKey, rightKey);
    }
           // Case 21: Alberti Cipher
    case 21: {
        std::stringstream ss(key);
        std::string k;
        int shift;
        std::getline(ss, k, ',');
        try { shift = std::stoi(ss.str().substr(ss.tellg())); }
        catch (...) {
            std::cout << "Error: Key must be key,shift\n";
            exit(1);
        }
        return albertiEncrypt(text, k, shift);
    }
           // Case 22: Two-Square Cipher
    case 22: {
        std::stringstream ss(key);
        std::string key1, key2;
        std::getline(ss, key1, ',');
        std::getline(ss, key2);
        if (key2.empty()) {
            std::cout << "Error: Key must be two comma-separated keys\n";
            exit(1);
        }
        return twoSquareEncrypt(text, key1, key2);
    }
           // Case 23: Bifid Cipher
    case 23: return bifidEncrypt(text, key);
        // Case 24: Trifid Cipher
    case 24: {
        std::stringstream ss(key);
        std::string k;
        int period;
        std::getline(ss, k, ',');
        try { period = std::stoi(ss.str().substr(ss.tellg())); }
        catch (...) {
            std::cout << "Error: Key must be key,period\n";
            exit(1);
        }
        return trifidEncrypt(text, k, period);
    }
           // Case 25: Nihilist Cipher
    case 25: {
        std::stringstream ss(key);
        std::string k, square;
        std::getline(ss, k, ',');
        std::getline(ss, square);
        if (square.empty()) square = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
        return nihilistEncrypt(text, k, square);
    }
           // Case 26: Homophonic Substitution
    case 26: {
        std::vector<std::vector<std::string>> substitutes(26);
        substitutes['H' - 'A'] = { "23", "45" };
        substitutes['E' - 'A'] = { "12", "34", "56" };
        substitutes['L' - 'A'] = { "78", "90" };
        substitutes['O' - 'A'] = { "11", "22" };
        return homophonicEncrypt(text, substitutes);
    }
           // Case 27: Checkerboard Cipher
    case 27: {
        std::stringstream ss(key);
        std::string k, digits;
        std::getline(ss, k, ',');
        std::getline(ss, digits);
        if (digits.empty()) digits = "1234567890";
        return checkerboardEncrypt(text, k, digits);
    }
           // Case 28: Fractionated Morse
    case 28: return fractionatedMorseEncrypt(text, key);
        // Case 29: Kama-Sutra Cipher
    case 29: return kamaSutraEncrypt(text);
        // Case 30: Pollux Cipher
    case 30: {
        std::string digits = key.empty() ? "123456789" : key;
        return polluxEncrypt(text, digits);
    }
    default:
        std::cout << "Error: Invalid cipher number\n";
        exit(1);
    }
}

std::string decryptByCipher(int cipherNum, const std::string& key, const std::string& cipherText) {
    switch (cipherNum) {
        // Case 1: Caesar Cipher
    case 1: {
        int shift;
        try { shift = std::stoi(key); }
        catch (...) {
            std::cout << "Error: Key must be an integer shift\n";
            exit(1);
        }
        return caesarDecrypt(cipherText, shift);
    }
          // Case 2: Vigenère Cipher
    case 2: return vigenereDecrypt(cipherText, key);
        // Case 3: Playfair Cipher
    case 3: return playfairDecrypt(cipherText, key);
        // Case 4: Rail Fence Cipher
    case 4: {
        int rails;
        try { rails = std::stoi(key); }
        catch (...) {
            std::cout << "Error: Key must be an integer number of rails\n";
            exit(1);
        }
        return railFenceDecrypt(cipherText, rails);
    }
          // Case 5: Substitution Cipher
    case 5: {
        if (key.length() != 26) {
            std::cout << "Error: Key must be 26 unique letters\n";
            exit(1);
        }
        return substitutionDecrypt(cipherText, key);
    }
          // Case 6: Atbash Cipher
    case 6: return atbashDecrypt(cipherText);
        // Case 7: Scytale Cipher
    case 7: {
        size_t diameter;
        try { diameter = std::stoi(key); }
        catch (...) {
            std::cout << "Error: Key must be an integer diameter\n";
            exit(1);
        }
        return scytaleDecrypt(cipherText, diameter);
    }
          // Case 8: Hill Cipher
    case 8: {
        std::vector<std::vector<int>> hillKey(3, std::vector<int>(3));
        std::stringstream ss(key);
        std::string num;
        int i = 0, j = 0;
        while (std::getline(ss, num, ',')) {
            try { hillKey[i][j] = std::stoi(num); }
            catch (...) {
                std::cout << "Error: Key must be 9 comma-separated integers\n";
                exit(1);
            }
            if (++j == 3) { j = 0; ++i; }
        }
        if (i != 3 || j != 0) {
            std::cout << "Error: Key must be 9 comma-separated integers\n";
            exit(1);
        }
        return hillDecrypt(cipherText, hillKey);
    }
          // Case 9: Beaufort Cipher
    case 9: return beaufortDecrypt(cipherText, key);
        // Case 10: ADFGVX Cipher
    case 10: {
        std::string square = "PH0QGI6NU4A1Y7L5V3R2Z8WXSTB9CDFEKMJB";
        return adfgvxDecrypt(cipherText, key, square);
    }
           // Case 11: Polybius Square Cipher
    case 11: {
        std::string square = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
        return polybiusDecrypt(cipherText, square);
    }
           // Case 12: Grille Cipher
    case 12: {
        std::vector<std::vector<int>> grille(4, std::vector<int>(4));
        std::stringstream ss(key);
        std::string row;
        int i = 0;
        while (std::getline(ss, row, ';')) {
            std::stringstream row_ss(row);
            std::string val;
            int j = 0;
            while (std::getline(row_ss, val, ',')) {
                try { grille[i][j] = std::stoi(val); }
                catch (...) {
                    std::cout << "Error: Invalid grille format\n";
                    exit(1);
                }
                ++j;
            }
            if (j != 4) {
                std::cout << "Error: Each grille row must have 4 values\n";
                exit(1);
            }
            ++i;
        }
        if (i != 4) {
            std::cout << "Error: Grille must have 4 rows\n";
            exit(1);
        }
        return grilleDecrypt(cipherText, grille, 4);
    }
           // Case 13: One-Time Pad
    case 13: return oneTimePadDecrypt(cipherText, key);
        // Case 14: Autokey Cipher
    case 14: return autokeyDecrypt(cipherText, key);
        // Case 15: Four-Square Cipher
    case 15: {
        std::stringstream ss(key);
        std::string key1, key2;
        std::getline(ss, key1, ',');
        std::getline(ss, key2);
        if (key2.empty()) {
            std::cout << "Error: Key must be two comma-separated keys\n";
            exit(1);
        }
        return fourSquareDecrypt(cipherText, key1, key2);
    }
           // Case 16: Bazeries Cipher
    case 16: {
        std::stringstream ss(key);
        std::string k;
        size_t number;
        std::getline(ss, k, ',');
        try { number = std::stoi(ss.str().substr(ss.tellg())); }
        catch (...) {
            std::cout << "Error: Key must be key,number\n";
            exit(1);
        }
        return bazeriesDecrypt(cipherText, k, number);
    }
           // Case 17: Columnar Transposition
    case 17: return columnarTranspositionDecrypt(cipherText, key);
        // Case 18: Bacon Cipher
    case 18: return baconDecrypt(cipherText);
        // Case 19: Porta Cipher
    case 19: return portaDecrypt(cipherText, key);
        // Case 20: Chaocipher
    case 20: {
        std::stringstream ss(key);
        std::string leftKey, rightKey;
        std::getline(ss, leftKey, ',');
        std::getline(ss, rightKey);
        if (rightKey.empty()) {
            std::cout << "Error: Key must be two comma-separated alphabets\n";
            exit(1);
        }
        return chaocipherDecrypt(cipherText, leftKey, rightKey);
    }
           // Case 21: Alberti Cipher
    case 21: {
        std::stringstream ss(key);
        std::string k;
        int shift;
        std::getline(ss, k, ',');
        try { shift = std::stoi(ss.str().substr(ss.tellg())); }
        catch (...) {
            std::cout << "Error: Key must be key,shift\n";
            exit(1);
        }
        return albertiDecrypt(cipherText, k, shift);
    }
           // Case 22: Two-Square Cipher
    case 22: {
        std::stringstream ss(key);
        std::string key1, key2;
        std::getline(ss, key1, ',');
        std::getline(ss, key2);
        if (key2.empty()) {
            std::cout << "Error: Key must be two comma-separated keys\n";
            exit(1);
        }
        return twoSquareDecrypt(cipherText, key1, key2);
    }
           // Case 23: Bifid Cipher
    case 23: return bifidDecrypt(cipherText, key);
        // Case 24: Trifid Cipher
    case 24: {
        std::stringstream ss(key);
        std::string k;
        int period;
        std::getline(ss, k, ',');
        try { period = std::stoi(ss.str().substr(ss.tellg())); }
        catch (...) {
            std::cout << "Error: Key must be key,period\n";
            exit(1);
        }
        return trifidDecrypt(cipherText, k, period);
    }
           // Case 25: Nihilist Cipher
    case 25: {
        std::stringstream ss(key);
        std::string k, square;
        std::getline(ss, k, ',');
        std::getline(ss, square);
        if (square.empty()) square = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
        return nihilistDecrypt(cipherText, k, square);
    }
           // Case 26: Homophonic Substitution
    case 26: {
        std::vector<std::vector<std::string>> substitutes(26);
        substitutes['H' - 'A'] = { "23", "45" };
        substitutes['E' - 'A'] = { "12", "34", "56" };
        substitutes['L' - 'A'] = { "78", "90" };
        substitutes['O' - 'A'] = { "11", "22" };
        return homophonicDecrypt(cipherText, substitutes);
    }
           // Case 27: Checkerboard Cipher
    case 27: {
        std::stringstream ss(key);
        std::string k, digits;
        std::getline(ss, k, ',');
        std::getline(ss, digits);
        if (digits.empty()) digits = "1234567890";
        return checkerboardDecrypt(cipherText, k, digits);
    }
           // Case 28: Fractionated Morse
    case 28: return fractionatedMorseDecrypt(cipherText, key);
        // Case 29: Kama-Sutra Cipher
    case 29: return kamaSutraDecrypt(cipherText);
        // Case 30: Pollux Cipher
    case 30: {
        std::string digits = key.empty() ? "123456789" : key;
        return polluxDecrypt(cipherText, digits);
    }
    default:
        std::cout << "Error: Invalid cipher number\n";
        exit(1);
    }
}