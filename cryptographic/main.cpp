#include "secret.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream> 

std::string encryptByCipher(int cipherNum, const std::string& key, const std::string& text);
std::string decryptByCipher(int cipherNum, const std::string& key, const std::string& cipherText);




std::string prepText(const std::string& base) {
    std::string s;
    for (char c : base) {
        if (std::isalpha(c)) {
            char u = std::toupper(c);
            if (u == 'J') u = 'I';
            s += u;
        }
    }
    std::string noDups;
    for (char c : s) {
        if (!noDups.empty() && noDups.back() == c) {
            noDups += (c == 'X' ? 'Q' : 'X');
        }
        noDups += c;
    }
    
    // LCM of 2, 3, 5, 36 is 180.
    while (noDups.length() % 180 != 0) {
        char pad = "ABCDEFGHIKLMNOPQRSTUVWYZ"[(noDups.length()) % 24]; // Avoid X, J
        if (noDups.back() == pad) pad = (pad == 'Z' ? 'A' : pad + 1);
        if (pad == 'J') pad = 'K';
        if (pad == 'X') pad = 'Y';
        noDups += pad;
    }
    return noDups;
}

void test()
{
    std::string rawDate = std::string(__DATE__) + std::string(__TIME__);
    std::string text = prepText("COMPLEXCRYPTOGRAPHYBINDSTHESAVAGEMENREALDATE" + rawDate);
    
    std::vector<std::vector<std::string>> subs(26);
    for(int i = 0; i < 26; i++) subs[i] = { std::to_string(i + 100) };

    int fails = 0;
    std::string enc, dec;

    {
        std::string adjText = text;
        enc = caesarEncrypt(adjText, 3);
        dec = caesarDecrypt(enc, 3);
        if (dec != adjText) {
            std::cerr << "ERROR: caesar failed!\n";
            fails++;
        } else {
            std::cout << "caesar Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = vigenereEncrypt(adjText, "SECRETKEY");
        dec = vigenereDecrypt(enc, "SECRETKEY");
        if (dec != adjText) {
            std::cerr << "ERROR: vigenere failed!\n";
            fails++;
        } else {
            std::cout << "vigenere Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = substitutionEncrypt(adjText, "ZYXWVUTSRQPONMLKJIHGFEDCBA");
        dec = substitutionDecrypt(enc, "ZYXWVUTSRQPONMLKJIHGFEDCBA");
        if (dec != adjText) {
            std::cerr << "ERROR: substitution failed!\n";
            fails++;
        } else {
            std::cout << "substitution Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = scytaleEncrypt(adjText, 4);
        dec = scytaleDecrypt(enc, 4);
        if (dec != adjText) {
            std::cerr << "ERROR: scytale failed!\n";
            fails++;
        } else {
            std::cout << "scytale Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = playfairEncrypt(adjText, "PLAYFAIREXAMPLE");
        dec = playfairDecrypt(enc, "PLAYFAIREXAMPLE");
        if (dec != adjText) {
            std::cerr << "ERROR: playfair failed!\n";
            fails++;
        } else {
            std::cout << "playfair Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = adfgxEncrypt(adjText, "SECRET", "ABCDEFGHIKLMNOPQRSTUVWXYZ");
        dec = adfgxDecrypt(enc, "SECRET", "ABCDEFGHIKLMNOPQRSTUVWXYZ");
        if (dec != adjText) {
            std::cerr << "ERROR: adfgx failed!\n";
            fails++;
        } else {
            std::cout << "adfgx Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = polybiusEncrypt(adjText, "ABCDEFGHIKLMNOPQRSTUVWXYZ");
        dec = polybiusDecrypt(enc, "ABCDEFGHIKLMNOPQRSTUVWXYZ");
        if (dec != adjText) {
            std::cerr << "ERROR: polybius failed!\n";
            fails++;
        } else {
            std::cout << "polybius Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        
        std::string adjText = text.substr(0, 16);
        
        enc = grilleEncrypt(adjText, {{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}}, 4);
        dec = grilleDecrypt(enc, {{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}}, 4);
        if (dec != adjText) {
            std::cerr << "ERROR: grille failed!\n";
            fails++;
        } else {
            std::cout << "grille Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = monoalphabeticKeyEncrypt(adjText, "KEYWORD");
        dec = monoalphabeticKeyDecrypt(enc, "KEYWORD");
        if (dec != adjText) {
            std::cerr << "ERROR: monoalphabeticKey failed!\n";
            fails++;
        } else {
            std::cout << "monoalphabeticKey Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = beaufortEncrypt(adjText, "SECRETKEY");
        dec = beaufortDecrypt(enc, "SECRETKEY");
        if (dec != adjText) {
            std::cerr << "ERROR: beaufort failed!\n";
            fails++;
        } else {
            std::cout << "beaufort Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = oneTimePadEncrypt(adjText, "SUPERSECRETKEYTHATISVERYLONGANDCANCOVERTHEWHOLETEXTXYZABCDEF");
        dec = oneTimePadDecrypt(enc, "SUPERSECRETKEYTHATISVERYLONGANDCANCOVERTHEWHOLETEXTXYZABCDEF");
        if (dec != adjText) {
            std::cerr << "ERROR: oneTimePad failed!\n";
            fails++;
        } else {
            std::cout << "oneTimePad Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = railFenceEncrypt(adjText, 3);
        dec = railFenceDecrypt(enc, 3);
        if (dec != adjText) {
            std::cerr << "ERROR: railFence failed!\n";
            fails++;
        } else {
            std::cout << "railFence Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = albertiEncrypt(adjText, "CIPHER", 3);
        dec = albertiDecrypt(enc, "CIPHER", 3);
        if (dec != adjText) {
            std::cerr << "ERROR: alberti failed!\n";
            fails++;
        } else {
            std::cout << "alberti Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = bazeriesEncrypt(adjText, "CIPHER", 3);
        dec = bazeriesDecrypt(enc, "CIPHER", 3);
        if (dec != adjText) {
            std::cerr << "ERROR: bazeries failed!\n";
            fails++;
        } else {
            std::cout << "bazeries Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = enigmaEncrypt(adjText, "ABC");
        dec = enigmaDecrypt(enc, "ABC");
        if (dec != adjText) {
            std::cerr << "ERROR: enigma failed!\n";
            fails++;
        } else {
            std::cout << "enigma Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = hillEncrypt(adjText, {{6,24,1},{13,16,10},{20,17,15}});
        dec = hillDecrypt(enc, {{6,24,1},{13,16,10},{20,17,15}});
        if (dec != adjText) {
            std::cerr << "ERROR: hill failed!\n";
            fails++;
        } else {
            std::cout << "hill Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = autokeyEncrypt(adjText, "QUEENLY");
        dec = autokeyDecrypt(enc, "QUEENLY");
        if (dec != adjText) {
            std::cerr << "ERROR: autokey failed!\n";
            fails++;
        } else {
            std::cout << "autokey Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = fourSquareEncrypt(adjText, "EXAMPLE", "KEYWORD");
        dec = fourSquareDecrypt(enc, "EXAMPLE", "KEYWORD");
        if (dec != adjText) {
            std::cerr << "ERROR: fourSquare failed!\n";
            fails++;
        } else {
            std::cout << "fourSquare Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = twoSquareEncrypt(adjText, "EXAMPLE", "KEYWORD");
        dec = twoSquareDecrypt(enc, "EXAMPLE", "KEYWORD");
        if (dec != adjText) {
            std::cerr << "ERROR: twoSquare failed!\n";
            fails++;
        } else {
            std::cout << "twoSquare Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = bifidEncrypt(adjText, "PLAYFAIREXAMPLE");
        dec = bifidDecrypt(enc, "PLAYFAIREXAMPLE");
        if (dec != adjText) {
            std::cerr << "ERROR: bifid failed!\n";
            fails++;
        } else {
            std::cout << "bifid Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = trifidEncrypt(adjText, "CIPHER", 5);
        dec = trifidDecrypt(enc, "CIPHER", 5);
        if (dec != adjText) {
            std::cerr << "ERROR: trifid failed!\n";
            fails++;
        } else {
            std::cout << "trifid Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = adfgvxEncrypt(adjText, "GERMAN", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
        dec = adfgvxDecrypt(enc, "GERMAN", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
        if (dec != adjText) {
            std::cerr << "ERROR: adfgvx failed!\n";
            fails++;
        } else {
            std::cout << "adfgvx Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = atbashEncrypt(adjText);
        dec = atbashDecrypt(enc);
        if (dec != adjText) {
            std::cerr << "ERROR: atbash failed!\n";
            fails++;
        } else {
            std::cout << "atbash Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = baconEncrypt(adjText);
        dec = baconDecrypt(enc);
        if (dec != adjText) {
            std::cerr << "ERROR: bacon failed!\n";
            fails++;
        } else {
            std::cout << "bacon Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = runningKeyEncrypt(adjText, "SUPERSECRETKEYTHATISVERYLONGANDCANCOVERTHEWHOLETEXTXYZABCDEF");
        dec = runningKeyDecrypt(enc, "SUPERSECRETKEYTHATISVERYLONGANDCANCOVERTHEWHOLETEXTXYZABCDEF");
        if (dec != adjText) {
            std::cerr << "ERROR: runningKey failed!\n";
            fails++;
        } else {
            std::cout << "runningKey Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = gronsfeldEncrypt(adjText, "1234");
        dec = gronsfeldDecrypt(enc, "1234");
        if (dec != adjText) {
            std::cerr << "ERROR: gronsfeld failed!\n";
            fails++;
        } else {
            std::cout << "gronsfeld Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = pigpenEncrypt(adjText);
        dec = pigpenDecrypt(enc);
        if (dec != adjText) {
            std::cerr << "ERROR: pigpen failed!\n";
            fails++;
        } else {
            std::cout << "pigpen Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = portaEncrypt(adjText, "KEY");
        dec = portaDecrypt(enc, "KEY");
        if (dec != adjText) {
            std::cerr << "ERROR: porta failed!\n";
            fails++;
        } else {
            std::cout << "porta Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = nihilistEncrypt(adjText, "CIPHER", "ABCDEFGHIKLMNOPQRSTUVWXYZ");
        dec = nihilistDecrypt(enc, "CIPHER", "ABCDEFGHIKLMNOPQRSTUVWXYZ");
        if (dec != adjText) {
            std::cerr << "ERROR: nihilist failed!\n";
            fails++;
        } else {
            std::cout << "nihilist Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = homophonicEncrypt(adjText, subs);
        dec = homophonicDecrypt(enc, subs);
        if (dec != adjText) {
            std::cerr << "ERROR: homophonic failed!\n";
            fails++;
        } else {
            std::cout << "homophonic Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = checkerboardEncrypt(adjText, "CIPHER", "1234567890");
        dec = checkerboardDecrypt(enc, "CIPHER", "1234567890");
        if (dec != adjText) {
            std::cerr << "ERROR: checkerboard failed!\n";
            fails++;
        } else {
            std::cout << "checkerboard Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = fractionatedMorseEncrypt(adjText, "CIPHER");
        dec = fractionatedMorseDecrypt(enc, "CIPHER");
        if (dec != adjText) {
            std::cerr << "ERROR: fractionatedMorse failed!\n";
            fails++;
        } else {
            std::cout << "fractionatedMorse Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = columnarTranspositionEncrypt(adjText, "CANO");
        dec = columnarTranspositionDecrypt(enc, "CANO");
        if (dec != adjText) {
            std::cerr << "ERROR: columnarTransposition failed!\n";
            fails++;
        } else {
            std::cout << "columnarTransposition Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = bealeEncrypt(adjText, "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG DEFEND THE EAST WALL OF THE CASTLE AT MIDNIGHT COMPLEX CRYPTOGRAPHY BINDS THE SAVAGE MEN REAL DATE TIME ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        dec = bealeDecrypt(enc, "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG DEFEND THE EAST WALL OF THE CASTLE AT MIDNIGHT COMPLEX CRYPTOGRAPHY BINDS THE SAVAGE MEN REAL DATE TIME ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        if (dec != adjText) {
            std::cerr << "ERROR: beale failed!\n";
            fails++;
        } else {
            std::cout << "beale Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = chaocipherEncrypt(adjText, "HXUCZVAMDSLKPEFJRIGTWOBNYQ", "PTLNBQDEOYSFAVZKGJRIHWXUMC");
        dec = chaocipherDecrypt(enc, "HXUCZVAMDSLKPEFJRIGTWOBNYQ", "PTLNBQDEOYSFAVZKGJRIHWXUMC");
        if (dec != adjText) {
            std::cerr << "ERROR: chaocipher failed!\n";
            fails++;
        } else {
            std::cout << "chaocipher Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = kamaSutraEncrypt(adjText);
        dec = kamaSutraDecrypt(enc);
        if (dec != adjText) {
            std::cerr << "ERROR: kamaSutra failed!\n";
            fails++;
        } else {
            std::cout << "kamaSutra Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    {
        std::string adjText = text;
        enc = polluxEncrypt(adjText, "123456789");
        dec = polluxDecrypt(enc, "123456789");
        if (dec != adjText) {
            std::cerr << "ERROR: pollux failed!\n";
            fails++;
        } else {
            std::cout << "pollux Cipher:\nOriginal: " << adjText.substr(0, 30) << "...\nEncrypted: " << enc.substr(0, 30) << "...\nDecrypted: " << dec.substr(0, 30) << "...\n\n";
        }
    }

    if (fails > 0) {
        std::cerr << fails << " tests failed.\n";
        exit(1);
    } else {
        std::cout << "All tests passed successfully.\n";
    }
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