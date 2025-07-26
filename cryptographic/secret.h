#ifndef SECRET_H
#define SECRET_H

#include <string>
#include <vector>

std::string cleanText(const std::string& text, bool preserveCase = false);
std::vector<std::vector<char>> generate5x5Grid(const std::string& key);
int modInverse(int a, int m);
std::string caesarEncrypt(const std::string& text, int shift);
std::string caesarDecrypt(const std::string& text, int shift);
std::string vigenereEncrypt(const std::string& text, const std::string& key);
std::string vigenereDecrypt(const std::string& text, const std::string& key);
std::string substitutionEncrypt(const std::string& text, const std::string& keyAlphabet);
std::string substitutionDecrypt(const std::string& text, const std::string& keyAlphabet);
std::string scytaleEncrypt(const std::string& text, size_t diameter);
std::string scytaleDecrypt(const std::string& text, size_t diameter);
std::string playfairEncrypt(const std::string& text, const std::string& key);
std::string playfairDecrypt(const std::string& text, const std::string& key);
std::string adfgxEncrypt(const std::string& text, const std::string& key, const std::string& polybiusSquare);
std::string adfgxDecrypt(const std::string& text, const std::string& key, const std::string& polybiusSquare);
std::string polybiusEncrypt(const std::string& text, const std::string& polybiusSquare);
std::string polybiusDecrypt(const std::string& text, const std::string& polybiusSquare);
std::string grilleEncrypt(const std::string& text, const std::vector<std::vector<int>>& grille, size_t size);
std::string grilleDecrypt(const std::string& text, const std::vector<std::vector<int>>& grille, size_t size);
std::string monoalphabeticKeyEncrypt(const std::string& text, const std::string& keyword);
std::string monoalphabeticKeyDecrypt(const std::string& text, const std::string& keyword);
std::string beaufortEncrypt(const std::string& text, const std::string& key);
std::string beaufortDecrypt(const std::string& text, const std::string& key);
std::string oneTimePadEncrypt(const std::string& text, const std::string& key);
std::string oneTimePadDecrypt(const std::string& text, const std::string& key);
std::string railFenceEncrypt(const std::string& text, int rails);
std::string railFenceDecrypt(const std::string& text, int rails);
std::string reverseCipher(const std::string& text);
std::string albertiEncrypt(const std::string& text, const std::string& key, int shift);
std::string albertiDecrypt(const std::string& text, const std::string& key, int shift);
std::string bazeriesEncrypt(const std::string& text, const std::string& key, size_t number);
std::string bazeriesDecrypt(const std::string& text, const std::string& key, size_t number);
std::string enigmaEncrypt(const std::string& text, const std::string& rotorSettings);
std::string enigmaDecrypt(const std::string& text, const std::string& rotorSettings);
std::string hillEncrypt(const std::string& text, const std::vector<std::vector<int>>& keyMatrix);
std::string hillDecrypt(const std::string& text, const std::vector<std::vector<int>>& keyMatrix);
std::string autokeyEncrypt(const std::string& text, const std::string& key);
std::string autokeyDecrypt(const std::string& text, const std::string& key);
std::string fourSquareEncrypt(const std::string& text, const std::string& key1, const std::string& key2);
std::string fourSquareDecrypt(const std::string& text, const std::string& key1, const std::string& key2);
std::string twoSquareEncrypt(const std::string& text, const std::string& key1, const std::string& key2);
std::string twoSquareDecrypt(const std::string& text, const std::string& key1, const std::string& key2);
std::string bifidEncrypt(const std::string& text, const std::string& key);
std::string bifidDecrypt(const std::string& text, const std::string& key);
std::string trifidEncrypt(const std::string& text, const std::string& key, int period);
std::string trifidDecrypt(const std::string& text, const std::string& key, int period);
std::string adfgvxEncrypt(const std::string& text, const std::string& key, const std::string& polybiusSquare);
std::string adfgvxDecrypt(const std::string& text, const std::string& key, const std::string& polybiusSquare);

std::string atbashEncrypt(const std::string& text);
std::string atbashDecrypt(const std::string& text);
std::string baconEncrypt(const std::string& text);
std::string baconDecrypt(const std::string& text);
std::string runningKeyEncrypt(const std::string& text, const std::string& key);
std::string runningKeyDecrypt(const std::string& text, const std::string& key);

std::string gronsfeldEncrypt(const std::string& text, const std::string& key);
std::string gronsfeldDecrypt(const std::string& text, const std::string& key);
std::string pigpenEncrypt(const std::string& text);
std::string pigpenDecrypt(const std::string& text);


std::string portaEncrypt(const std::string& text, const std::string& key);
std::string portaDecrypt(const std::string& text, const std::string& key);
std::string nihilistEncrypt(const std::string& text, const std::string& key, const std::string& polybiusSquare);
std::string nihilistDecrypt(const std::string& text, const std::string& key, const std::string& polybiusSquare);
std::string homophonicEncrypt(const std::string& text, const std::vector<std::vector<std::string>>& substitutes);
std::string homophonicDecrypt(const std::string& text, const std::vector<std::vector<std::string>>& substitutes);
std::string checkerboardEncrypt(const std::string& text, const std::string& key, const std::string& digits);
std::string checkerboardDecrypt(const std::string& text, const std::string& key, const std::string& digits);
std::string fractionatedMorseEncrypt(const std::string& text, const std::string& key);
std::string fractionatedMorseDecrypt(const std::string& text, const std::string& key);

std::string columnarTranspositionEncrypt(const std::string& text, const std::string& key);
std::string columnarTranspositionDecrypt(const std::string& text, const std::string& key);
std::string bealeEncrypt(const std::string& text, const std::string& bookText);
std::string bealeDecrypt(const std::string& text, const std::string& bookText);
std::string chaocipherEncrypt(const std::string& text, const std::string& leftKey, const std::string& rightKey);
std::string chaocipherDecrypt(const std::string& text, const std::string& leftKey, const std::string& rightKey);
std::string kamaSutraEncrypt(const std::string& text);
std::string kamaSutraDecrypt(const std::string& text);
std::string polluxEncrypt(const std::string& text, const std::string& digitMap);
std::string polluxDecrypt(const std::string& text, const std::string& digitMap);

#endif // SECRET_H