#include "secret.h"
#include <cctype>
#include <algorithm>
#include <vector>
#include <cmath>
#include <sstream>   
 
 


// Helper function to clean text
std::string cleanText(const std::string& text, bool preserveCase) {
    std::string result;
    for (char c : text) {
        if (std::isalpha(c)) {
            result += preserveCase ? c : std::toupper(c);
        }
    }
    return result;
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; // No inverse exists
}



// Helper function to generate a 5x5 grid (I/J combined)
std::vector<std::vector<char>> generate5x5Grid(const std::string& key) {
    std::string keyClean = cleanText(key);
    std::string gridStr = keyClean;
    std::string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // I/J combined
    for (char c : alphabet) {
        if (gridStr.find(c) == std::string::npos) {
            gridStr += c;
        }
    }
    std::vector<std::vector<char>> grid(5, std::vector<char>(5));
    for (size_t i = 0; i < 25; ++i) {
        grid[i / 5][i % 5] = gridStr[i];
    }
    return grid;
}


std::vector<std::vector<char>> generatePolybiusSquare(const std::string& key) {
    std::string keyClean = cleanText(key);
    std::string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // I and J share position
    std::string squareStr;

    // Add key letters first
    for (char c : keyClean) {
        if (squareStr.find(c) == std::string::npos) {
            squareStr += c;
        }
    }

    // Add remaining alphabet letters
    for (char c : alphabet) {
        if (squareStr.find(c) == std::string::npos) {
            squareStr += c;
        }
    }

    // Create 5x5 grid
    std::vector<std::vector<char>> square(5, std::vector<char>(5));
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            square[i][j] = squareStr[i * 5 + j];
        }
    }
    return square;
}


 

// Caesar Cipher: Encrypts text by shifting letters
std::string caesarEncrypt(const std::string& text, int shift) {
    if (shift <= 0) return "Error: Shift must be positive";
    std::string result = text;
    shift = shift % 26;
    for (char& c : result) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            c = static_cast<char>(base + (c - base + shift) % 26);
        }
    }
    return result;
}

// Caesar Cipher: Decrypts text by reversing the shift
std::string caesarDecrypt(const std::string& text, int shift) {
    if (shift <= 0) return "Error: Shift must be positive";
    return caesarEncrypt(text, 26 - (shift % 26));
}

// Vigenère Cipher: Encrypts using a keyword
std::string vigenereEncrypt(const std::string& text, const std::string& key) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string result = text;
    std::string keyUpper = cleanText(key);
    if (keyUpper.empty()) return "Error: Key must contain letters";
    size_t keyIndex = 0;
    for (char& c : result) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            int shift = keyUpper[keyIndex % keyUpper.length()] - 'A';
            c = static_cast<char>(base + (c - base + shift) % 26);
            keyIndex++;
        }
    }
    return result;
}

// Vigenère Cipher: Decrypts using a keyword
std::string vigenereDecrypt(const std::string& text, const std::string& key) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string result = text;
    std::string keyUpper = cleanText(key);
    if (keyUpper.empty()) return "Error: Key must contain letters";
    size_t keyIndex = 0;
    for (char& c : result) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            int shift = keyUpper[keyIndex % keyUpper.length()] - 'A';
            c = static_cast<char>(base + (c - base - shift + 26) % 26);
            keyIndex++;
        }
    }
    return result;
}

// Substitution Cipher: Encrypts using a custom alphabet
std::string substitutionEncrypt(const std::string& text, const std::string& keyAlphabet) {
    if (keyAlphabet.length() != 26) return "Error: Key alphabet must be 26 letters";
    std::string result = text;
    std::string standardAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (char& c : result) {
        if (std::isalpha(c)) {
            bool isUpper = std::isupper(c);
            c = std::toupper(c);
            size_t pos = standardAlphabet.find(c);
            if (pos != std::string::npos) {
                c = keyAlphabet[pos];
                if (!isUpper) {
                    c = std::tolower(c);
                }
            }
        }
    }
    return result;
}

// Substitution Cipher: Decrypts using a custom alphabet
std::string substitutionDecrypt(const std::string& text, const std::string& keyAlphabet) {
    if (keyAlphabet.length() != 26) return "Error: Key alphabet must be 26 letters";
    std::string result = text;
    std::string standardAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (char& c : result) {
        if (std::isalpha(c)) {
            bool isUpper = std::isupper(c);
            c = std::toupper(c);
            size_t pos = keyAlphabet.find(c);
            if (pos != std::string::npos) {
                c = standardAlphabet[pos];
                if (!isUpper) {
                    c = std::tolower(c);
                }
            }
        }
    }
    return result;
}

// Scytale Cipher: Encrypts by wrapping text around a cylinder
std::string scytaleEncrypt(const std::string& text, size_t diameter) {
    if (diameter == 0) return "Error: Diameter must be positive";
    std::string cleaned = cleanText(text, true);
    size_t len = cleaned.length();
    if (len == 0) return "";
    size_t rows = (len + diameter - 1) / diameter;
    std::vector<std::vector<char>> grid(rows, std::vector<char>(diameter, ' '));
    size_t k = 0;
    for (size_t i = 0; i < rows && k < len; ++i) {
        for (size_t j = 0; j < diameter && k < len; ++j) {
            grid[i][j] = cleaned[k++];
        }
    }
    std::string result;
    for (size_t j = 0; j < diameter; ++j) {
        for (size_t i = 0; i < rows; ++i) {
            if (grid[i][j] != ' ') {
                result += grid[i][j];
            }
        }
    }
    return result;
}

// Scytale Cipher: Decrypts by reversing the wrapping
std::string scytaleDecrypt(const std::string& text, size_t diameter) {
    if (diameter == 0) return "Error: Diameter must be positive";
    std::string cleaned = cleanText(text, true);
    size_t len = cleaned.length();
    if (len == 0) return "";
    size_t rows = (len + diameter - 1) / diameter;
    size_t cols = diameter;
    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols, ' '));
    size_t k = 0;
    for (size_t j = 0; j < cols; ++j) {
        for (size_t i = 0; i < rows && k < len; ++i) {
            grid[i][j] = cleaned[k++]; // Fill columns
        }
    }
    std::string result;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols && grid[i][j] != ' '; ++j) {
            result += grid[i][j]; // Read rows
        }
    }
    return result;
}

// Playfair Cipher: Encrypts using a 5x5 grid
std::string playfairEncrypt(const std::string& text, const std::string& key) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    std::vector<std::vector<char>> grid = generate5x5Grid(keyClean);
    std::string pairs;
    for (size_t i = 0; i < cleaned.length(); i += 2) {
        char a = cleaned[i];
        char b = (i + 1 < cleaned.length()) ? cleaned[i + 1] : 'X';
        if (a == b) {
            b = 'X';
            i--;
        }
        pairs += a;
        pairs += b;
    }
    std::string result;
    for (size_t i = 0; i < pairs.length(); i += 2) {
        char a = pairs[i], b = pairs[i + 1];
        size_t row1, col1, row2, col2;
        for (size_t r = 0; r < 5; ++r) {
            for (size_t c = 0; c < 5; ++c) {
                if (grid[r][c] == a) { row1 = r; col1 = c; }
                if (grid[r][c] == b) { row2 = r; col2 = c; }
            }
        }
        if (row1 == row2) {
            result += grid[row1][(col1 + 1) % 5];
            result += grid[row2][(col2 + 1) % 5];
        }
        else if (col1 == col2) {
            result += grid[(row1 + 1) % 5][col1];
            result += grid[(row2 + 1) % 5][col2];
        }
        else {
            result += grid[row1][col2];
            result += grid[row2][col1];
        }
    }
    return result;
}

// Playfair Cipher: Decrypts using a 5x5 grid
std::string playfairDecrypt(const std::string& text, const std::string& key) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    std::vector<std::vector<char>> grid = generate5x5Grid(keyClean);
    std::string decrypted;
    for (size_t i = 0; i < cleaned.length(); i += 2) {
        char a = cleaned[i], b = cleaned[i + 1];
        size_t row1, col1, row2, col2;
        for (size_t r = 0; r < 5; ++r) {
            for (size_t c = 0; c < 5; ++c) {
                if (grid[r][c] == a) { row1 = r; col1 = c; }
                if (grid[r][c] == b) { row2 = r; col2 = c; }
            }
        }
        if (row1 == row2) {
            decrypted += grid[row1][(col1 + 4) % 5];
            decrypted += grid[row2][(col2 + 4) % 5];
        }
        else if (col1 == col2) {
            decrypted += grid[(row1 + 4) % 5][col1];
            decrypted += grid[(row2 + 4) % 5][col2];
        }
        else {
            decrypted += grid[row1][col2];
            decrypted += grid[row2][col1];
        }
    }
    // Remove trailing 'X' if present (likely padding)
    if (!decrypted.empty() && decrypted.back() == 'X') {
        decrypted.pop_back();
    }
    return decrypted;
}

// ADFGX Cipher: Encrypts using a 5x5 Polybius square and transposition
std::string adfgxEncrypt(const std::string& text, const std::string& key, const std::string& polybiusSquare) {
    if (key.empty() || polybiusSquare.length() != 25) return "Error: Invalid key or Polybius square";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string adfgx = "ADFGX";
    std::string result;
    for (char c : cleaned) {
        size_t pos = polybiusSquare.find(c);
        if (pos != std::string::npos) {
            size_t row = pos / 5, col = pos % 5;
            result += adfgx[row];
            result += adfgx[col];
        }
    }
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    size_t cols = keyClean.length();
    size_t rows = (result.length() + cols - 1) / cols;
    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols, ' '));
    size_t k = 0;
    for (size_t i = 0; i < rows && k < result.length(); ++i) {
        for (size_t j = 0; j < cols && k < result.length(); ++j) {
            grid[i][j] = result[k++];
        }
    }
    std::vector<std::pair<char, size_t>> keyOrder;
    for (size_t i = 0; i < cols; ++i) {
        keyOrder.emplace_back(keyClean[i], i);
    }
    std::sort(keyOrder.begin(), keyOrder.end());
    std::string final;
    for (const auto& pair : keyOrder) {
        size_t col = pair.second;
        for (size_t i = 0; i < rows; ++i) {
            if (grid[i][col] != ' ') {
                final += grid[i][col];
            }
        }
    }
    return final;
}

// ADFGX Cipher: Decrypts using a 5x5 Polybius square and transposition
std::string adfgxDecrypt(const std::string& text, const std::string& key, const std::string& polybiusSquare) {
    if (key.empty() || polybiusSquare.length() != 25) return "Error: Invalid key or Polybius square";
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    size_t cols = keyClean.length();
    if (text.length() % cols != 0) return "Error: Invalid ciphertext length";
    size_t rows = text.length() / cols;
    std::vector<std::pair<char, size_t>> keyOrder;
    for (size_t i = 0; i < cols; ++i) {
        keyOrder.emplace_back(keyClean[i], i);
    }
    std::sort(keyOrder.begin(), keyOrder.end());
    std::vector<size_t> colOrder(cols);
    for (size_t i = 0; i < cols; ++i) {
        colOrder[keyOrder[i].second] = i;
    }
    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols, ' '));
    size_t k = 0;
    for (size_t j : colOrder) {
        for (size_t i = 0; i < rows && k < text.length(); ++i) {
            grid[i][j] = text[k++];
        }
    }
    std::string intermediate;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (grid[i][j] != ' ') {
                intermediate += grid[i][j];
            }
        }
    }
    std::string adfgx = "ADFGX";
    std::string result;
    for (size_t i = 0; i < intermediate.length(); i += 2) {
        size_t row = adfgx.find(intermediate[i]);
        size_t col = adfgx.find(intermediate[i + 1]);
        if (row != std::string::npos && col != std::string::npos) {
            result += polybiusSquare[row * 5 + col];
        }
    }
    return result;
}

// Polybius Square: Encrypts letters to number pairs
std::string polybiusEncrypt(const std::string& text, const std::string& polybiusSquare) {
    if (polybiusSquare.length() != 25) return "Error: Polybius square must be 25 letters";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string result;
    for (char c : cleaned) {
        size_t pos = polybiusSquare.find(c);
        if (pos != std::string::npos) {
            size_t row = pos / 5 + 1, col = pos % 5 + 1;
            result += std::to_string(row) + std::to_string(col);
        }
    }
    return result;
}

// Polybius Square: Decrypts number pairs to letters
std::string polybiusDecrypt(const std::string& text, const std::string& polybiusSquare) {
    if (polybiusSquare.length() != 25) return "Error: Polybius square must be 25 letters";
    if (text.length() % 2 != 0) return "Error: Invalid ciphertext length";
    std::string result;
    for (size_t i = 0; i < text.length(); i += 2) {
        if (std::isdigit(text[i]) && std::isdigit(text[i + 1])) {
            size_t row = text[i] - '0' - 1;
            size_t col = text[i + 1] - '0' - 1;
            if (row < 5 && col < 5) {
                result += polybiusSquare[row * 5 + col];
            }
        }
    }
    return result;
}

// Grille Cipher: Encrypts using a turning grille
std::string grilleEncrypt(const std::string& text, const std::vector<std::vector<int>>& grille, size_t size) {
    if (size == 0 || grille.size() != size || grille[0].size() != size) return "Error: Invalid grille size";
    std::string cleaned = cleanText(text, true); // Uppercase and remove non-letters
    if (cleaned.empty()) return "";
    // Pad to size * size (16 for 4x4)
    while (cleaned.length() < size * size) cleaned += 'X';
    std::vector<std::vector<char>> grid(size, std::vector<char>(size, ' '));
    std::vector<std::vector<int>> currentGrille = grille;
    size_t k = 0;
    // Place letters over 4 rotations
    for (size_t rot = 0; rot < 4; ++rot) {
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                if (currentGrille[i][j] == 1 && k < cleaned.length()) {
                    grid[i][j] = cleaned[k++];
                }
            }
        }
        // Rotate grille 90° clockwise
        std::vector<std::vector<int>> newGrille(size, std::vector<int>(size));
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                newGrille[j][size - 1 - i] = currentGrille[i][j];
            }
        }
        currentGrille = newGrille;
    }
    // Read grid row by row
    std::string result;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result += grid[i][j];
        }
    }
    return result;
}

std::string grilleDecrypt(const std::string& text, const std::vector<std::vector<int>>& grille, size_t size) {
    if (size == 0 || grille.size() != size || grille[0].size() != size) return "Error: Invalid grille size";
    if (text.length() != size * size) return "Error: Ciphertext length must be " + std::to_string(size * size);
    std::vector<std::vector<char>> grid(size, std::vector<char>(size));
    // Fill grid row by row
    size_t k = 0;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            grid[i][j] = text[k++];
        }
    }
    // Extract via grille rotations
    std::string result;
    std::vector<std::vector<int>> currentGrille = grille;
    for (size_t rot = 0; rot < 4; ++rot) {
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                if (currentGrille[i][j] == 1) {
                    result += grid[i][j];
                }
            }
        }
        // Rotate grille 90° clockwise
        std::vector<std::vector<int>> newGrille(size, std::vector<int>(size));
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                newGrille[j][size - 1 - i] = currentGrille[i][j];
            }
        }
        currentGrille = newGrille;
    }
    // Remove padding 'X's
    while (!result.empty() && result.back() == 'X') result.pop_back();
    return result;
}

// Monoalphabetic Substitution with Keyword: Encrypts using a keyword-based alphabet
std::string monoalphabeticKeyEncrypt(const std::string& text, const std::string& keyword) {
    if (keyword.empty()) return "Error: Keyword cannot be empty";
    std::string keyClean = cleanText(keyword);
    if (keyClean.empty()) return "Error: Keyword must contain letters";
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string keyAlphabet = keyClean;
    for (char c : alphabet) {
        if (keyAlphabet.find(c) == std::string::npos) {
            keyAlphabet += c;
        }
    }
    return substitutionEncrypt(text, keyAlphabet);
}

// Monoalphabetic Substitution with Keyword: Decrypts using a keyword-based alphabet
std::string monoalphabeticKeyDecrypt(const std::string& text, const std::string& keyword) {
    if (keyword.empty()) return "Error: Keyword cannot be empty";
    std::string keyClean = cleanText(keyword);
    if (keyClean.empty()) return "Error: Keyword must contain letters";
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string keyAlphabet = keyClean;
    for (char c : alphabet) {
        if (keyAlphabet.find(c) == std::string::npos) {
            keyAlphabet += c;
        }
    }
    return substitutionDecrypt(text, keyAlphabet);
}

// Beaufort Cipher: Encrypts by subtracting plaintext from key
std::string beaufortEncrypt(const std::string& text, const std::string& key) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string result = text;
    std::string keyUpper = cleanText(key);
    if (keyUpper.empty()) return "Error: Key must contain letters";
    size_t keyIndex = 0;
    for (char& c : result) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            int shift = keyUpper[keyIndex % keyUpper.length()] - 'A';
            c = static_cast<char>(base + (shift - (c - base) + 26) % 26);
            keyIndex++;
        }
    }
    return result;
}

// Beaufort Cipher: Decrypts (same as encrypt due to symmetry)
std::string beaufortDecrypt(const std::string& text, const std::string& key) {
    return beaufortEncrypt(text, key);
}

// One-Time Pad: Encrypts using a random key of equal length
std::string oneTimePadEncrypt(const std::string& text, const std::string& key) {
    std::string cleanedText = cleanText(text);
    std::string cleanedKey = cleanText(key);
    if (cleanedKey.length() < cleanedText.length()) {
        return "Error: Key must be at least as long as text";
    }
    if (cleanedText.empty()) return "";
    std::string result;
    for (size_t i = 0; i < cleanedText.length(); ++i) {
        char base = 'A';
        int textVal = cleanedText[i] - base;
        int keyVal = cleanedKey[i] - base;
        result += static_cast<char>(base + (textVal + keyVal) % 26);
    }
    return result;
}

// One-Time Pad: Decrypts using the same key
std::string oneTimePadDecrypt(const std::string& text, const std::string& key) {
    std::string cleanedText = cleanText(text);
    std::string cleanedKey = cleanText(key);
    if (cleanedKey.length() < cleanedText.length()) {
        return "Error: Key must be at least as long as text";
    }
    if (cleanedText.empty()) return "";
    std::string result;
    for (size_t i = 0; i < cleanedText.length(); ++i) {
        char base = 'A';
        int textVal = cleanedText[i] - base;
        int keyVal = cleanedKey[i] - base;
        result += static_cast<char>(base + (textVal - keyVal + 26) % 26);
    }
    return result;
}

// Rail Fence Cipher: Encrypts by writing text in a zigzag pattern
std::string railFenceEncrypt(const std::string& text, int rails) {
    if (rails <= 1) return text;
    std::string cleaned = cleanText(text, true);
    if (cleaned.empty()) return "";
    std::vector<std::vector<char>> grid(rails, std::vector<char>(cleaned.length(), ' '));
    size_t row = 0, col = 0;
    int dir = 1;
    for (char c : cleaned) {
        grid[row][col] = c;
        if (row == 0) dir = 1;
        if (row == static_cast<size_t>(rails) - 1) dir = -1;
        row += dir;
        col++;
    }
    std::string result;
    for (size_t i = 0; i < static_cast<size_t>(rails); ++i) {
        for (size_t j = 0; j < cleaned.length(); ++j) {
            if (grid[i][j] != ' ') {
                result += grid[i][j];
            }
        }
    }
    return result;
}

// Rail Fence Cipher: Decrypts by reconstructing the zigzag pattern
std::string railFenceDecrypt(const std::string& text, int rails) {
    if (rails <= 1) return text;
    std::string cleaned = cleanText(text, true);
    if (cleaned.empty()) return "";
    std::vector<std::vector<char>> grid(rails, std::vector<char>(cleaned.length(), ' '));
    std::vector<size_t> railPos(cleaned.length());
    size_t row = 0, col = 0;
    int dir = 1;
    for (size_t i = 0; i < cleaned.length(); ++i) {
        railPos[i] = row;
        if (row == 0) dir = 1;
        if (row == static_cast<size_t>(rails) - 1) dir = -1;
        row += dir;
        col++;
    }
    size_t k = 0;
    for (size_t i = 0; i < static_cast<size_t>(rails); ++i) {
        for (size_t j = 0; j < cleaned.length(); ++j) {
            if (railPos[j] == i && k < cleaned.length()) {
                grid[i][j] = cleaned[k++];
            }
        }
    }
    std::string result;
    row = 0, col = 0, dir = 1;
    for (size_t i = 0; i < cleaned.length(); ++i) {
        result += grid[row][col];
        if (row == 0) dir = 1;
        if (row == static_cast<size_t>(rails) - 1) dir = -1;
        row += dir;
        col++;
    }
    return result;
}

// Reverse Cipher: Simply reverses the text
std::string reverseCipher(const std::string& text) {
    std::string result = text;
    std::reverse(result.begin(), result.end());
    return result;
}

// Alberti Cipher Disk: Encrypts using two alphabets with a shift
std::string albertiEncrypt(const std::string& text, const std::string& key, int shift) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    std::string innerDisk = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string outerDisk;
    for (char c : keyClean) {
        if (outerDisk.find(c) == std::string::npos) {
            outerDisk += c;
        }
    }
    for (char c : innerDisk) {
        if (outerDisk.find(c) == std::string::npos) {
            outerDisk += c;
        }
    }
    std::string result;
    for (size_t i = 0; i < cleaned.length(); ++i) {
        size_t pos = innerDisk.find(cleaned[i]);
        if (pos != std::string::npos) {
            size_t shiftedPos = (pos + shift) % 26;
            result += outerDisk[shiftedPos];
        }
    }
    return result;
}


// Alberti Cipher Disk: Decrypts using two alphabets with a shift
std::string albertiDecrypt(const std::string& text, const std::string& key, int shift) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    std::string innerDisk = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string outerDisk;
    for (char c : keyClean) {
        if (outerDisk.find(c) == std::string::npos) {
            outerDisk += c;
        }
    }
    for (char c : innerDisk) {
        if (outerDisk.find(c) == std::string::npos) {
            outerDisk += c;
        }
    }
    std::string result;
    for (size_t i = 0; i < cleaned.length(); ++i) {
        size_t pos = outerDisk.find(cleaned[i]);
        if (pos != std::string::npos) {
            size_t shiftedPos = (pos - shift + 26) % 26;
            result += innerDisk[shiftedPos];
        }
    }
    return result;
}


// Bazeries Cipher: Combines substitution and transposition
std::string bazeriesEncrypt(const std::string& text, const std::string& key, size_t number) {
    if (key.empty()) return "Error: Key cannot be empty";
    if (number == 0) return "Error: Number must be positive";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string keyAlphabet = keyClean;
    for (char c : alphabet) {
        if (keyAlphabet.find(c) == std::string::npos) {
            keyAlphabet += c;
        }
    }
    std::string substituted = substitutionEncrypt(cleaned, keyAlphabet);
    std::string result;
    for (size_t i = 0; i < substituted.length(); i += number) {
        std::string group = substituted.substr(i, number);
        std::reverse(group.begin(), group.end());
        result += group;
    }
    return result;
}

// Bazeries Cipher: Decrypts by reversing substitution and transposition
std::string bazeriesDecrypt(const std::string& text, const std::string& key, size_t number) {
    if (key.empty()) return "Error: Key cannot be empty";
    if (number == 0) return "Error: Number must be positive";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string keyAlphabet = keyClean;
    for (char c : alphabet) {
        if (keyAlphabet.find(c) == std::string::npos) {
            keyAlphabet += c;
        }
    }
    std::string reversed;
    for (size_t i = 0; i < cleaned.length(); i += number) {
        std::string group = cleaned.substr(i, number);
        std::reverse(group.begin(), group.end());
        reversed += group;
    }
    return substitutionDecrypt(reversed, keyAlphabet);
}

// Enigma Cipher: Simplified rotor-based substitution
std::string enigmaEncrypt(const std::string& text, const std::string& rotorSettings) {
    if (rotorSettings.length() < 3) return "Error: Rotor settings must be at least 3 letters";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string rotor1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    std::string rotor2 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    std::string rotor3 = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    std::string reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
    std::string result;
    int pos1 = rotorSettings[0] - 'A';
    int pos2 = rotorSettings[1] - 'A';
    int pos3 = rotorSettings[2] - 'A';
    for (char c : cleaned) {
        int val = c - 'A';
        val = (val + pos3) % 26;
        val = rotor3[val] - 'A';
        val = (val - pos3 + 26) % 26;
        val = (val + pos2) % 26;
        val = rotor2[val] - 'A';
        val = (val - pos2 + 26) % 26;
        val = (val + pos1) % 26;
        val = rotor1[val] - 'A';
        val = (val - pos1 + 26) % 26;
        val = reflector[val] - 'A';
        val = (val + pos1) % 26;
        val = rotor1.find('A' + val);
        val = (val - pos1 + 26) % 26;
        val = (val + pos2) % 26;
        val = rotor2.find('A' + val);
        val = (val - pos2 + 26) % 26;
        val = (val + pos3) % 26;
        val = rotor3.find('A' + val);
        val = (val - pos3 + 26) % 26;
        result += static_cast<char>('A' + val);
        pos3 = (pos3 + 1) % 26;
        if (pos3 == 0) pos2 = (pos2 + 1) % 26;
        if (pos2 == 0 && pos3 == 0) pos1 = (pos1 + 1) % 26;
    }
    return result;
}

// Enigma Cipher: Decrypts (same as encrypt due to reflector)
std::string enigmaDecrypt(const std::string& text, const std::string& rotorSettings) {
    return enigmaEncrypt(text, rotorSettings);
}

// Hill Cipher: Encrypts using matrix multiplication
std::string hillEncrypt(const std::string& text, const std::vector<std::vector<int>>& keyMatrix) {
    if (keyMatrix.size() != 3 || keyMatrix[0].size() != 3 || keyMatrix[1].size() != 3 || keyMatrix[2].size() != 3) {
        return "Error: Key matrix must be 3x3";
    }

    // Calculate determinant
    int det = keyMatrix[0][0] * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) -
        keyMatrix[0][1] * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]) +
        keyMatrix[0][2] * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]);
    det = (det % 26 + 26) % 26; // Ensure positive
    if (modInverse(det, 26) == -1) {
        return "Error: Key matrix is not invertible";
    }

    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    while (cleaned.length() % 3 != 0) cleaned += 'X'; // Pad with X to make length divisible by 3

    std::string result;
    for (size_t i = 0; i < cleaned.length(); i += 3) {
        int a = cleaned[i] - 'A';
        int b = cleaned[i + 1] - 'A';
        int c = cleaned[i + 2] - 'A';

        int x = (keyMatrix[0][0] * a + keyMatrix[0][1] * b + keyMatrix[0][2] * c) % 26;
        int y = (keyMatrix[1][0] * a + keyMatrix[1][1] * b + keyMatrix[1][2] * c) % 26;
        int z = (keyMatrix[2][0] * a + keyMatrix[2][1] * b + keyMatrix[2][2] * c) % 26;

        result += static_cast<char>((x + 26) % 26 + 'A');
        result += static_cast<char>((y + 26) % 26 + 'A');
        result += static_cast<char>((z + 26) % 26 + 'A');
    }
    return result;
}

// Hill Cipher: Decrypts using inverse matrix (3x3 matrix)
std::string hillDecrypt(const std::string& text, const std::vector<std::vector<int>>& keyMatrix) {
    if (keyMatrix.size() != 3 || keyMatrix[0].size() != 3 || keyMatrix[1].size() != 3 || keyMatrix[2].size() != 3) {
        return "Error: Key matrix must be 3x3";
    }

    // Calculate determinant
    int det = keyMatrix[0][0] * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) -
        keyMatrix[0][1] * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]) +
        keyMatrix[0][2] * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]);
    det = (det % 26 + 26) % 26; // Ensure positive
    int detInv = modInverse(det, 26);
    if (detInv == -1) {
        return "Error: Key matrix is not invertible";
    }

    // Calculate adjugate matrix
    std::vector<std::vector<int>> adj(3, std::vector<int>(3));
    adj[0][0] = (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) % 26;
    adj[0][1] = (-(keyMatrix[0][1] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][1]) + 26) % 26;
    adj[0][2] = (keyMatrix[0][1] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][1]) % 26;
    adj[1][0] = (-(keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]) + 26) % 26;
    adj[1][1] = (keyMatrix[0][0] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][0]) % 26;
    adj[1][2] = (-(keyMatrix[0][0] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][0]) + 26) % 26;
    adj[2][0] = (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]) % 26;
    adj[2][1] = (-(keyMatrix[0][0] * keyMatrix[2][1] - keyMatrix[0][1] * keyMatrix[2][0]) + 26) % 26;
    adj[2][2] = (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) % 26;

    // Calculate inverse matrix
    std::vector<std::vector<int>> inv(3, std::vector<int>(3));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            inv[i][j] = (adj[i][j] * detInv) % 26;
            if (inv[i][j] < 0) inv[i][j] += 26;
        }
    }

    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    if (cleaned.length() % 3 != 0) return "Error: Ciphertext length must be divisible by 3";

    std::string result;
    for (size_t i = 0; i < cleaned.length(); i += 3) {
        int a = cleaned[i] - 'A';
        int b = cleaned[i + 1] - 'A';
        int c = cleaned[i + 2] - 'A';

        int x = (inv[0][0] * a + inv[0][1] * b + inv[0][2] * c) % 26;
        int y = (inv[1][0] * a + inv[1][1] * b + inv[1][2] * c) % 26;
        int z = (inv[2][0] * a + inv[2][1] * b + inv[2][2] * c) % 26;

        result += static_cast<char>((x + 26) % 26 + 'A');
        result += static_cast<char>((y + 26) % 26 + 'A');
        result += static_cast<char>((z + 26) % 26 + 'A');
    }
    return result;
}

// Autokey Cipher: Encrypts using plaintext as part of the key
std::string autokeyEncrypt(const std::string& text, const std::string& key) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    std::string fullKey = keyClean + cleaned;
    std::string result;
    for (size_t i = 0; i < cleaned.length(); ++i) {
        char base = 'A';
        int shift = fullKey[i] - base;
        result += static_cast<char>(base + (cleaned[i] - base + shift) % 26);
    }
    return result;
}

// Autokey Cipher: Decrypts using the key and recovered plaintext
std::string autokeyDecrypt(const std::string& text, const std::string& key) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    std::string result;
    std::string fullKey = keyClean;
    for (size_t i = 0; i < cleaned.length(); ++i) {
        char base = 'A';
        int shift = fullKey[i] - base;
        char decrypted = static_cast<char>(base + (cleaned[i] - base - shift + 26) % 26);
        result += decrypted;
        fullKey += decrypted;
    }
    return result;
}

// Four-Square Cipher: Encrypts using four 5x5 grids
std::string fourSquareEncrypt(const std::string& text, const std::string& key1, const std::string& key2) {
    if (key1.empty() || key2.empty()) return "Error: Keys cannot be empty";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string key1Clean = cleanText(key1);
    std::string key2Clean = cleanText(key2);
    if (key1Clean.empty() || key2Clean.empty()) return "Error: Keys must contain letters";
    std::vector<std::vector<char>> grid1 = generate5x5Grid(key1Clean);
    std::vector<std::vector<char>> grid2 = generate5x5Grid(key2Clean);
    std::vector<std::vector<char>> gridStd(5, std::vector<char>(5));
    std::string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < 25; ++i) {
        gridStd[i / 5][i % 5] = alphabet[i];
    }
    std::string pairs;
    for (size_t i = 0; i < cleaned.length(); i += 2) {
        char a = cleaned[i];
        char b = (i + 1 < cleaned.length()) ? cleaned[i + 1] : 'X';
        if (a == b) {
            b = 'X';
            i--;
        }
        pairs += a;
        pairs += b;
    }
    std::string result;
    for (size_t i = 0; i < pairs.length(); i += 2) {
        char a = pairs[i], b = pairs[i + 1];
        size_t row1, col1, row2, col2;
        for (size_t r = 0; r < 5; ++r) {
            for (size_t c = 0; c < 5; ++c) {
                if (gridStd[r][c] == a) { row1 = r; col1 = c; }
                if (gridStd[r][c] == b) { row2 = r; col2 = c; }
            }
        }
        result += grid1[row1][col2];
        result += grid2[row2][col1];
    }
    return result;
}

// Four-Square Cipher: Decrypts using four 5x5 grids
std::string fourSquareDecrypt(const std::string& text, const std::string& key1, const std::string& key2) {
    if (key1.empty() || key2.empty()) return "Error: Keys cannot be empty";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    if (cleaned.length() % 2 != 0) return "Error: Invalid ciphertext length";
    std::string key1Clean = cleanText(key1);
    std::string key2Clean = cleanText(key2);
    if (key1Clean.empty() || key2Clean.empty()) return "Error: Keys must contain letters";
    std::vector<std::vector<char>> grid1 = generate5x5Grid(key1Clean);
    std::vector<std::vector<char>> grid2 = generate5x5Grid(key2Clean);
    std::vector<std::vector<char>> gridStd(5, std::vector<char>(5));
    std::string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < 25; ++i) {
        gridStd[i / 5][i % 5] = alphabet[i];
    }
    std::string result;
    for (size_t i = 0; i < cleaned.length(); i += 2) {
        char a = cleaned[i], b = cleaned[i + 1];
        size_t row1, col1, row2, col2;
        for (size_t r = 0; r < 5; ++r) {
            for (size_t c = 0; c < 5; ++c) {
                if (grid1[r][c] == a) { row1 = r; col1 = c; }
                if (grid2[r][c] == b) { row2 = r; col2 = c; }
            }
        }
        result += gridStd[row1][col2];
        result += gridStd[row2][col1];
    }
    return result;
}

// Two-Square Cipher: Encrypts using two 5x5 grids
std::string twoSquareEncrypt(const std::string& text, const std::string& key1, const std::string& key2) {
    if (key1.empty() || key2.empty()) return "Error: Keys cannot be empty";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string key1Clean = cleanText(key1);
    std::string key2Clean = cleanText(key2);
    if (key1Clean.empty() || key2Clean.empty()) return "Error: Keys must contain letters";
    std::vector<std::vector<char>> grid1 = generate5x5Grid(key1Clean);
    std::vector<std::vector<char>> grid2 = generate5x5Grid(key2Clean);
    std::string pairs;
    for (size_t i = 0; i < cleaned.length(); i += 2) {
        char a = cleaned[i];
        char b = (i + 1 < cleaned.length()) ? cleaned[i + 1] : 'X';
        if (a == b) {
            b = 'X';
            i--;
        }
        pairs += a;
        pairs += b;
    }
    std::string result;
    for (size_t i = 0; i < pairs.length(); i += 2) {
        char a = pairs[i], b = pairs[i + 1];
        size_t row1, col1, row2, col2;
        for (size_t r = 0; r < 5; ++r) {
            for (size_t c = 0; c < 5; ++c) {
                if (grid1[r][c] == a) { row1 = r; col1 = c; }
                if (grid2[r][c] == b) { row2 = r; col2 = c; }
            }
        }
        result += grid1[row1][col2];
        result += grid2[row2][col1];
    }
    return result;
}

// Two-Square Cipher: Decrypts using two 5x5 grids
std::string twoSquareDecrypt(const std::string& text, const std::string& key1, const std::string& key2) {
    if (key1.empty() || key2.empty()) return "Error: Keys cannot be empty";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    if (cleaned.length() % 2 != 0) return "Error: Invalid ciphertext length";
    std::string key1Clean = cleanText(key1);
    std::string key2Clean = cleanText(key2);
    if (key1Clean.empty() || key2Clean.empty()) return "Error: Keys must contain letters";
    std::vector<std::vector<char>> grid1 = generate5x5Grid(key1Clean);
    std::vector<std::vector<char>> grid2 = generate5x5Grid(key2Clean);
    std::string result;
    for (size_t i = 0; i < cleaned.length(); i += 2) {
        char a = cleaned[i], b = cleaned[i + 1];
        size_t row1, col1, row2, col2;
        for (size_t r = 0; r < 5; ++r) {
            for (size_t c = 0; c < 5; ++c) {
                if (grid1[r][c] == a) { row1 = r; col1 = c; }
                if (grid2[r][c] == b) { row2 = r; col2 = c; }
            }
        }
        result += grid1[row1][col2];
        result += grid2[row2][col1];
    }
    return result;
}

// Bifid Cipher: Encrypts using a 5x5 grid and fractionation
std::string bifidEncrypt(const std::string& text, const std::string& key) {
    auto square = generatePolybiusSquare(key);
    std::string cleanText = ::cleanText(text);

    if (cleanText.empty()) return "";

    std::vector<int> rows, cols;

    // Get all row and column numbers first
    for (char c : cleanText) {
        bool found = false;
        for (int i = 0; i < 5 && !found; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (square[i][j] == c) {
                    rows.push_back(i);
                    cols.push_back(j);
                    found = true;
                    break;
                }
            }
        }
        if (!found) return "Error: Invalid character in text";
    }

    // Combine row and column numbers
    std::vector<int> combined;
    combined.insert(combined.end(), rows.begin(), rows.end());
    combined.insert(combined.end(), cols.begin(), cols.end());

    // Convert back to letters
    std::string result;
    for (size_t i = 0; i < combined.size(); i += 2) {
        if (i + 1 >= combined.size()) break;
        int row = combined[i];
        int col = combined[i + 1];
        result += square[row][col];
    }

    return result;
}

std::string bifidDecrypt(const std::string& text, const std::string& key) {
    auto square = generatePolybiusSquare(key);
    std::string cleanText = ::cleanText(text);

    if (cleanText.empty()) return "";

    // Get all row and column numbers
    std::vector<int> numbers;
    for (char c : cleanText) {
        bool found = false;
        for (int i = 0; i < 5 && !found; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (square[i][j] == c) {
                    numbers.push_back(i);
                    numbers.push_back(j);
                    found = true;
                    break;
                }
            }
        }
        if (!found) return "Error: Invalid character in ciphertext";
    }

    // Split into rows and columns
    size_t half = numbers.size() / 2;
    std::vector<int> rows(numbers.begin(), numbers.begin() + half);
    std::vector<int> cols(numbers.begin() + half, numbers.end());

    // Reconstruct original coordinates
    std::string result;
    for (size_t i = 0; i < rows.size(); ++i) {
        if (i < cols.size()) {
            int row = rows[i];
            int col = cols[i];
            result += square[row][col];
        }
    }

    return result;
}

// Trifid Cipher: Encrypts using a 3x3x3 cube and fractionation
std::string trifidEncrypt(const std::string& text, const std::string& key, int period) {
    if (key.empty()) return "Error: Key cannot be empty";
    if (period <= 0) return "Error: Period must be positive";

    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";

    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";

    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.";
    std::string keyAlphabet = keyClean;
    for (char c : alphabet) {
        if (keyAlphabet.find(c) == std::string::npos) {
            keyAlphabet += c;
        }
    }
    keyAlphabet = keyAlphabet.substr(0, 27);

    // Build the cube
    std::vector<std::vector<std::vector<char>>> cube(3, std::vector<std::vector<char>>(3, std::vector<char>(3)));
    size_t idx = 0;
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            for (size_t k = 0; k < 3; ++k)
                cube[i][j][k] = keyAlphabet[idx++];

    std::vector<size_t> coords;
    for (char c : cleaned) {
        for (size_t i = 0; i < 3; ++i)
            for (size_t j = 0; j < 3; ++j)
                for (size_t k = 0; k < 3; ++k)
                    if (cube[i][j][k] == c) {
                        coords.push_back(i);
                        coords.push_back(j);
                        coords.push_back(k);
                    }
    }

    std::string result;
    for (size_t i = 0; i < coords.size(); i += period * 3) {
        std::vector<size_t> group(coords.begin() + i, coords.begin() + std::min(i + period * 3, coords.size()));

        std::vector<size_t> mixed;
        for (size_t dim = 0; dim < 3; ++dim) {
            for (size_t j = dim; j < group.size(); j += 3)
                mixed.push_back(group[j]);
        }

        for (size_t j = 0; j + 2 < mixed.size(); j += 3)
            result += cube[mixed[j]][mixed[j + 1]][mixed[j + 2]];
    }

    return result;
}

// Trifid Cipher: Decrypts using a 3x3x3 cube and fractionation
std::string trifidDecrypt(const std::string& text, const std::string& key, int period) {
    if (key.empty()) return "Error: Key cannot be empty";
    if (period <= 0) return "Error: Period must be positive";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.";
    std::string keyAlphabet = keyClean;
    for (char c : alphabet) {
        if (keyAlphabet.find(c) == std::string::npos) {
            keyAlphabet += c;
        }
    }
    keyAlphabet = keyAlphabet.substr(0, 27);
    std::vector<std::vector<std::vector<char>>> cube(3, std::vector<std::vector<char>>(3, std::vector<char>(3)));
    size_t idx = 0;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            for (size_t k = 0; k < 3; ++k) {
                if (idx < keyAlphabet.length()) {
                    cube[i][j][k] = keyAlphabet[idx++];
                }
            }
        }
    }
    std::vector<size_t> coords;
    for (char c : cleaned) {
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                for (size_t k = 0; k < 3; ++k) {
                    if (cube[i][j][k] == c) {
                        coords.push_back(i);
                        coords.push_back(j);
                        coords.push_back(k);
                    }
                }
            }
        }
    }
    std::vector<size_t> dim1, dim2, dim3;
    for (size_t i = 0; i < coords.size(); i += period * 3) {
        std::vector<size_t> group(coords.begin() + i, coords.begin() + std::min(i + period * 3, coords.size()));
        for (size_t j = 0; j < group.size() / 3; ++j) {
            dim1.push_back(group[j]);
            dim2.push_back(group[j + group.size() / 3]);
            dim3.push_back(group[j + 2 * group.size() / 3]);
        }
    }
    std::string result;
    for (size_t i = 0; i < dim1.size(); ++i) {
        result += cube[dim1[i]][dim2[i]][dim3[i]];
    }
    return result;
}


// ADFGVX Cipher (unchanged from previous)
std::string adfgvxEncrypt(const std::string& text, const std::string& key, const std::string& square) {
    if (square.length() != 36) return "Error: Polybius square must be 36 characters (6x6)";
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    const std::string adfgvx = "ADFGVX";
    std::string intermediate;
    for (char c : cleaned) {
        size_t pos = square.find(c);
        if (pos == std::string::npos) return "Error: Character '" + std::string(1, c) + "' not in square";
        intermediate += adfgvx[pos / 6];
        intermediate += adfgvx[pos % 6];
    }
    std::string cleanKey = cleanText(key);
    if (cleanKey.empty()) return "Error: Empty key";
    size_t cols = cleanKey.length();
    size_t rows = (intermediate.length() + cols - 1) / cols;
    std::vector<std::pair<char, size_t>> keyOrder;
    for (size_t i = 0; i < cols; ++i) {
        keyOrder.emplace_back(cleanKey[i], i);
    }
    std::sort(keyOrder.begin(), keyOrder.end());
    std::string result;
    for (const auto& pair : keyOrder) {
        size_t col = pair.second;
        for (size_t row = 0; row < rows; ++row) {
            size_t idx = row * cols + col;
            if (idx < intermediate.length()) {
                result += intermediate[idx];
            }
        }
    }
    return result;
}

// Updated ADFGVX Decrypt
std::string adfgvxDecrypt(const std::string& text, const std::string& key, const std::string& square) {
    if (square.length() != 36) return "Error: Polybius square must be 36 characters (6x6)";
    std::string cleanKey = cleanText(key);
    if (cleanKey.empty()) return "Error: Empty key";
    size_t cols = cleanKey.length();
    if (text.length() % cols != 0) return "Error: Ciphertext length must be multiple of key length";
    size_t rows = text.length() / cols;
    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols));
    std::vector<std::pair<char, size_t>> keyOrder;
    for (size_t i = 0; i < cols; ++i) {
        keyOrder.emplace_back(cleanKey[i], i);
    }
    std::sort(keyOrder.begin(), keyOrder.end());
    std::vector<size_t> fillOrder;
    for (const auto& pair : keyOrder) {
        fillOrder.push_back(pair.second);
    }
    size_t idx = 0;
    for (size_t col : fillOrder) {
        for (size_t j = 0; j < rows; ++j) {
            if (idx < text.length()) {
                grid[j][col] = text[idx++];
            }
        }
    }
    std::string intermediate;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            intermediate += grid[i][j];
        }
    }
    const std::string adfgvx = "ADFGVX";
    std::string result;
    for (size_t i = 0; i < intermediate.length(); i += 2) {
        if (i + 1 >= intermediate.length()) break;
        size_t row = adfgvx.find(intermediate[i]);
        size_t col = adfgvx.find(intermediate[i + 1]);
        if (row == std::string::npos || col == std::string::npos) {
            return "Error: Invalid ADFGVX pair";
        }
        size_t pos = row * 6 + col;
        if (pos >= square.length()) return "Error: Invalid position in square";
        result += square[pos];
    }
    return result;
}


// Atbash Cipher: Reverses the alphabet (A->Z, B->Y, etc.)
std::string atbashEncrypt(const std::string& text) {
    std::string result = text;
    for (char& c : result) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            c = static_cast<char>(base + ('Z' - std::toupper(c)));
        }
    }
    return result;
}

// Atbash Cipher: Decrypts (same as encrypt due to symmetry)
std::string atbashDecrypt(const std::string& text) {
    return atbashEncrypt(text);
}

// Bacon Cipher: Encodes letters as 5-bit binary (A=aaaaa, B=aaaab, etc.) using 'A' and 'B'
std::string baconEncrypt(const std::string& text) {
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    const std::string baconCodes[26] = {
        "AAAAA", "AAAAB", "AAABA", "AAABB", "AABAA", // A-E
        "AABAB", "AABBA", "AABBB", "ABAAA", "ABAAB", // F-J
        "ABABA", "ABABB", "ABBAA", "ABBAB", "ABBBA", // K-O
        "ABBBB", "BAAAA", "BAAAB", "BAABA", "BAABB", // P-T
        "BABAA", "BABAB", "BABBA", "BABBB", "BBAAA", // U-Y
        "BBAAB"  // Z
    };
    std::string result;
    for (char c : cleaned) {
        size_t idx = c - 'A';
        if (idx < 26) {
            result += baconCodes[idx];
        }
    }
    return result;
}

// Bacon Cipher: Decodes 'A' and 'B' sequences into letters
std::string baconDecrypt(const std::string& text) {
    std::string cleaned = text;
    std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::toupper);
    cleaned.erase(std::remove_if(cleaned.begin(), cleaned.end(), [](char c) { return c != 'A' && c != 'B'; }), cleaned.end());
    if (cleaned.length() % 5 != 0) return "Error: Invalid ciphertext length";
    const std::string baconCodes[26] = {
        "AAAAA", "AAAAB", "AAABA", "AAABB", "AABAA", // A-E
        "AABAB", "AABBA", "AABBB", "ABAAA", "ABAAB", // F-J
        "ABABA", "ABABB", "ABBAA", "ABBAB", "ABBBA", // K-O
        "ABBBB", "BAAAA", "BAAAB", "BAABA", "BAABB", // P-T
        "BABAA", "BABAB", "BABBA", "BABBB", "BBAAA", // U-Y
        "BBAAB"  // Z
    };
    std::string result;
    for (size_t i = 0; i < cleaned.length(); i += 5) {
        std::string code = cleaned.substr(i, 5);
        for (size_t j = 0; j < 26; ++j) {
            if (code == baconCodes[j]) {
                result += static_cast<char>('A' + j);
                break;
            }
        }
    }
    return result;
}

// Running Key Cipher: Encrypts using a key as long as the text
std::string runningKeyEncrypt(const std::string& text, const std::string& key) {
    std::string cleanedText = cleanText(text);
    std::string cleanedKey = cleanText(key);
    if (cleanedKey.length() < cleanedText.length()) return "Error: Key must be at least as long as text";
    if (cleanedText.empty()) return "";
    std::string result;
    for (size_t i = 0; i < cleanedText.length(); ++i) {
        char base = 'A';
        int shift = cleanedKey[i] - base;
        result += static_cast<char>(base + (cleanedText[i] - base + shift) % 26);
    }
    return result;
}

// Running Key Cipher: Decrypts using the same key
std::string runningKeyDecrypt(const std::string& text, const std::string& key) {
    std::string cleanedText = cleanText(text);
    std::string cleanedKey = cleanText(key);
    if (cleanedKey.length() < cleanedText.length()) return "Error: Key must be at least as long as text";
    if (cleanedText.empty()) return "";
    std::string result;
    for (size_t i = 0; i < cleanedText.length(); ++i) {
        char base = 'A';
        int shift = cleanedKey[i] - base;
        result += static_cast<char>(base + (cleanedText[i] - base - shift + 26) % 26);
    }
    return result;
}



// Gronsfeld Cipher: Encrypts using a numerical key like Vigenère
std::string gronsfeldEncrypt(const std::string& text, const std::string& key) {
    std::string cleanedText = cleanText(text);
    if (cleanedText.empty()) return "";
    std::string cleanedKey = key;
    cleanedKey.erase(std::remove_if(cleanedKey.begin(), cleanedKey.end(), [](char c) { return !std::isdigit(c); }), cleanedKey.end());
    if (cleanedKey.empty()) return "Error: Key must contain digits";
    std::vector<int> keyDigits;
    for (char c : cleanedKey) {
        keyDigits.push_back(c - '0');
    }
    std::string result;
    for (size_t i = 0; i < cleanedText.length(); ++i) {
        char base = 'A';
        int shift = keyDigits[i % keyDigits.size()];
        result += static_cast<char>(base + (cleanedText[i] - base + shift) % 26);
    }
    return result;
}

// Gronsfeld Cipher: Decrypts using a numerical key
std::string gronsfeldDecrypt(const std::string& text, const std::string& key) {
    std::string cleanedText = cleanText(text);
    if (cleanedText.empty()) return "";
    std::string cleanedKey = key;
    cleanedKey.erase(std::remove_if(cleanedKey.begin(), cleanedKey.end(), [](char c) { return !std::isdigit(c); }), cleanedKey.end());
    if (cleanedKey.empty()) return "Error: Key must contain digits";
    std::vector<int> keyDigits;
    for (char c : cleanedKey) {
        keyDigits.push_back(c - '0');
    }
    std::string result;
    for (size_t i = 0; i < cleanedText.length(); ++i) {
        char base = 'A';
        int shift = keyDigits[i % keyDigits.size()];
        result += static_cast<char>(base + (cleanedText[i] - base - shift + 26) % 26);
    }
    return result;
}

// Pigpen Cipher: Encrypts using a geometric substitution (standard tic-tac-toe and X grids)
std::string pigpenEncrypt(const std::string& text) {
    std::string cleaned = cleanText(text);
    if (cleaned.empty()) return "";
    const std::string pigpenCodes[26] = {
        "A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3", // Tic-tac-toe grid (A-I)
        "D1", "D2", "D3", "E1", "E2", "E3", "F1", "F2", "F3", // Tic-tac-toe with dot (J-R)
        "G1", "G2", "G3", "G4",                          // X grid (S-V)
        "H1", "H2", "H3", "H4"                           // X grid with dot (W-Z)
    };
    std::string result;
    for (char c : cleaned) {
        size_t idx = c - 'A';
        if (idx < 26) {
            result += pigpenCodes[idx];
            if (c != cleaned.back()) result += " ";
        }
    }
    return result;
}

// Pigpen Cipher: Decrypts geometric substitution codes
std::string pigpenDecrypt(const std::string& text) {
    std::string cleaned = text;
    cleaned.erase(std::remove_if(cleaned.begin(), cleaned.end(), [](char c) { return !std::isalnum(c); }), cleaned.end());
    if (cleaned.empty()) return "";
    const std::string pigpenCodes[26] = {
        "A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3", // Tic-tac-toe grid (A-I)
        "D1", "D2", "D3", "E1", "E2", "E3", "F1", "F2", "F3", // Tic-tac-toe with dot (J-R)
        "G1", "G2", "G3", "G4",                          // X grid (S-V)
        "H1", "H2", "H3", "H4"                           // X grid with dot (W-Z)
    };
    std::string result;
    for (size_t i = 0; i < cleaned.length(); i += 2) {
        if (i + 1 >= cleaned.length()) return "Error: Invalid ciphertext length";
        std::string code = cleaned.substr(i, 2);
        for (size_t j = 0; j < 26; ++j) {
            if (code == pigpenCodes[j]) {
                result += static_cast<char>('A' + j);
                break;
            }
        }
    }
    return result;
}




// Porta Cipher: Encrypts using a tableau with a keyword
std::string portaEncrypt(const std::string& text, const std::string& key) {
    std::string cleanedText = cleanText(text);
    if (cleanedText.empty()) return "";
    std::string cleanedKey = cleanText(key);
    if (cleanedKey.empty()) return "Error: Key must contain letters";
    std::string result;
    const std::string tableau[13] = {
        "NOPQRSTUVWXYZABCDEFGHIJKLM", // A-B
        "OPQRSTUVWXYZNMABCDEFGHIJKL", // C-D
        "PQRSTUVWXYZONMABCDEFGHIJKL", // E-F
        "QRSTUVWXYZPONMABCDEFGHIJKL", // G-H
        "RSTUVWXYZQPONMABCDEFGHIJKL", // I-J
        "STUVWXYZRQPONMABCDEFGHIJKL", // K-L
        "TUVWXYZSRQPONMABCDEFGHIJKL", // M-N
        "UVWXYZTSRQPONMABCDEFGHIJKL", // O-P
        "VWXYZUTSRQPONMABCDEFGHIJKL", // Q-R
        "WXYZVUTSRQPONMABCDEFGHIJKL", // S-T
        "XYZWVUTSRQPONMABCDEFGHIJKL", // U-V
        "YZXWVUTSRQPONMABCDEFGHIJKL", // W-X
        "ZYXWVUTSRQPONMABCDEFGHIJKL"  // Y-Z

   
    };
    for (size_t i = 0; i < cleanedText.length(); ++i) {
        char keyChar = cleanedKey[i % cleanedKey.length()];
        size_t tableIdx = (keyChar - 'A') / 2;
        size_t pos = cleanedText[i] - 'A';
        result += tableau[tableIdx][pos];
    }
    return result;
}

std::string portaDecrypt(const std::string& text, const std::string& key) {

    const std::string tableau[13] = {
    "NOPQRSTUVWXYZABCDEFGHIJKLM", // A-B
    "OPQRSTUVWXYZNMABCDEFGHIJKL", // C-D
    "PQRSTUVWXYZONMABCDEFGHIJKL", // E-F
    "QRSTUVWXYZPONMABCDEFGHIJKL", // G-H
    "RSTUVWXYZQPONMABCDEFGHIJKL", // I-J
    "STUVWXYZRQPONMABCDEFGHIJKL", // K-L
    "TUVWXYZSRQPONMABCDEFGHIJKL", // M-N
    "UVWXYZTSRQPONMABCDEFGHIJKL", // O-P
    "VWXYZUTSRQPONMABCDEFGHIJKL", // Q-R
    "WXYZVUTSRQPONMABCDEFGHIJKL", // S-T
    "XYZWVUTSRQPONMABCDEFGHIJKL", // U-V
    "YZXWVUTSRQPONMABCDEFGHIJKL", // W-X
    "ZYXWVUTSRQPONMABCDEFGHIJKL"  // Y-Z
    };

    std::string cleanedText = cleanText(text);
    std::string cleanedKey = cleanText(key);
    if (cleanedKey.empty()) return "Error: Key must contain letters";
    std::string result;
    for (size_t i = 0; i < cleanedText.length(); ++i) {
        char y = cleanedText[i];
        char keyChar = cleanedKey[i % cleanedKey.length()];
        size_t tableIdx = (keyChar - 'A') / 2;
        // Find x where tableau[tableIdx][x - 'A'] == y
        for (size_t pos = 0; pos < 26; ++pos) {
            if (tableau[tableIdx][pos] == y) {
                result += 'A' + pos;
                break;
            }
        }
    }
    return result;
}


std::string nihilistEncrypt(const std::string& text, const std::string& key,
    const std::string& squareKey = "") {
    auto square = generatePolybiusSquare(squareKey.empty() ? key : squareKey);
    std::string cleanKey = cleanText(key);
    std::string cleanText = ::cleanText(text);

    if (cleanKey.empty() || cleanText.empty()) return "";

    // Convert key to numbers
    std::vector<int> keyNumbers;
    for (char c : cleanKey) {
        bool found = false;
        for (int i = 0; i < 5 && !found; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (square[i][j] == c) {
                    keyNumbers.push_back((i + 1) * 10 + (j + 1));
                    found = true;
                    break;
                }
            }
        }
    }

    // Encrypt each character
    std::string result;
    for (size_t i = 0; i < cleanText.size(); ++i) {
        char c = cleanText[i];
        bool found = false;
        for (int row = 0; row < 5 && !found; ++row) {
            for (int col = 0; col < 5; ++col) {
                if (square[row][col] == c) {
                    int textNum = (row + 1) * 10 + (col + 1);
                    int keyNum = keyNumbers[i % keyNumbers.size()];
                    result += std::to_string(textNum + keyNum) + " ";
                    found = true;
                    break;
                }
            }
        }
        if (!found) return "Error: Invalid character in text";
    }

    if (!result.empty()) result.pop_back(); // Remove trailing space
    return result;
}

std::string nihilistDecrypt(const std::string& text, const std::string& key,
    const std::string& squareKey = "") {
    auto square = generatePolybiusSquare(squareKey.empty() ? key : squareKey);
    std::string cleanKey = cleanText(key);

    if (cleanKey.empty()) return "";

    // Convert key to numbers
    std::vector<int> keyNumbers;
    for (char c : cleanKey) {
        bool found = false;
        for (int i = 0; i < 5 && !found; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (square[i][j] == c) {
                    keyNumbers.push_back((i + 1) * 10 + (j + 1));
                    found = true;
                    break;
                }
            }
        }
    }

    // Process ciphertext numbers
    std::string result;
    std::istringstream iss(text);
    std::string numStr;
    size_t keyIndex = 0;

    while (iss >> numStr) {
        try {
            int cipherNum = std::stoi(numStr);
            if (keyIndex >= keyNumbers.size()) keyIndex = 0;
            int keyNum = keyNumbers[keyIndex++];
            int textNum = cipherNum - keyNum;

            if (textNum < 11 || textNum > 55) return "Error: Invalid ciphertext number";

            int row = (textNum / 10) - 1;
            int col = (textNum % 10) - 1;

            if (row < 0 || row >= 5 || col < 0 || col >= 5) {
                return "Error: Invalid ciphertext number";
            }

            result += square[row][col];
        }
        catch (...) {
            return "Error: Invalid ciphertext format";
        }
    }

    return result;
}
// Homophonic Substitution Cipher Implementation

std::string homophonicEncrypt(const std::string& text,
    const std::vector<std::vector<std::string>>& substitutes) {
    if (substitutes.size() != 26) return "Error: Substitutes must provide 26 letter mappings";

    std::string cleaned;
    for (char c : text) {
        if (isalpha(c)) cleaned += toupper(c);
    }
    if (cleaned.empty()) return "";

    std::string result;
    for (size_t i = 0; i < cleaned.size(); ++i) {
        char c = cleaned[i];
        size_t idx = c - 'A';

        if (idx >= 26 || substitutes[idx].empty()) {
            return "Error: No substitution for " + std::string(1, c);
        }

        // Select first substitute for simplicity
        result += substitutes[idx][0];
        if (i != cleaned.size() - 1) result += " ";
    }
    return result;
}

std::string homophonicDecrypt(const std::string& text,
    const std::vector<std::vector<std::string>>& substitutes) {
    if (substitutes.size() != 26) return "Error: Substitutes must provide 26 letter mappings";

    std::istringstream iss(text);
    std::string token;
    std::string result;

    while (iss >> token) {
        bool found = false;
        for (size_t i = 0; i < 26; ++i) {
            for (const auto& sub : substitutes[i]) {
                if (sub == token) {
                    result += 'A' + i;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) return "Error: Invalid ciphertext token: " + token;
    }
    return result;
}


// Checkerboard Cipher: Encrypts using a 5x5 grid with numerical coordinates
std::string checkerboardEncrypt(const std::string& text, const std::string& key, const std::string& digits) {
    if (digits.length() != 10) return "Error: Need exactly 10 unique digits";
    if (key.empty()) return "Error: Key cannot be empty";
    
    std::string cleanedText = cleanText(text);
    if (cleanedText.empty()) return "";
    
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    
    auto grid = generate5x5Grid(keyClean);
    std::string result;
    
    for (char c : cleanedText) {
        bool found = false;
        // Replace J with I for the grid
        char searchChar = (c == 'J') ? 'I' : c;
        
        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 5; ++col) {
                if (grid[row][col] == searchChar) {
                    result += digits[row];
                    result += digits[col + 5];
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) return "Error: Letter not found in grid";
    }
    return result;
}

std::string checkerboardDecrypt(const std::string& text, const std::string& key, const std::string& digits) {
    if (digits.length() != 10) return "Error: Need exactly 10 unique digits";
    if (key.empty()) return "Error: Key cannot be empty";
    
    std::string cleanedText;
    for (char c : text) {
        if (digits.find(c) != std::string::npos) {
            cleanedText += c;
        }
    }
    if (cleanedText.length() % 2 != 0) return "Error: Odd number of digits";
    
    std::string keyClean = cleanText(key);
    if (keyClean.empty()) return "Error: Key must contain letters";
    
    auto grid = generate5x5Grid(keyClean);
    std::string result;
    
    for (size_t i = 0; i < cleanedText.length(); i += 2) {
        size_t rowPos = digits.find(cleanedText[i]);
        size_t colPos = digits.find(cleanedText[i+1]) - 5;
        
        if (rowPos >= 5 || colPos >= 5) {
            return "Error: Invalid digit pair";
        }
        result += grid[rowPos][colPos];
    }
    return result;
}

// Fractionated Morse Cipher: Encrypts by converting to Morse code and fractionating
std::string fractionatedMorseEncrypt(const std::string& text, const std::string& key) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string cleanedText = cleanText(text);
    if (cleanedText.empty()) return "";
    std::string cleanedKey = cleanText(key);
    if (cleanedKey.empty()) return "Error: Key must contain letters";
    const std::string morseCodes[26] = {
        ".-", "-...", "-.-.", "-..", ".", // A-E
        "..-.", "--.", "....", "..", ".---", // F-J
        "-.-", ".-..", "--", "-.", "---", // K-O
        ".--.", "--.-", ".-.", "...", "-", // P-T
        "..-", "...-", ".--", "-..-", "-.--", // U-Y
        "--.." // Z
    };
    std::string morse;
    for (char c : cleanedText) {
        morse += morseCodes[c - 'A'] + "X";
    }
    if (!morse.empty()) morse.pop_back(); // Remove final X
    while (morse.length() % 3 != 0) morse += "X";
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string keyAlphabet = cleanedKey;
    for (char c : alphabet) {
        if (keyAlphabet.find(c) == std::string::npos) {
            keyAlphabet += c;
        }
    }
    std::string morseTriplets[27] = {
        "...", "..-", "..X", ".-.", ".-.", ".-X", ".X.", ".X-", ".XX", // 0-8
        "-..", "-.-", "-.X", "--.", "--.", "--X", "-X.", "-X-", "-XX", // 9-17
        "X..", "X.-", "X.X", "XX.", "XX-", "XXX", "X--", "X-." // 18-25
    };
    std::string result;
    for (size_t i = 0; i < morse.length(); i += 3) {
        std::string triplet = morse.substr(i, 3);
        for (size_t j = 0; j < 26; ++j) {
            if (triplet == morseTriplets[j]) {
                result += keyAlphabet[j];
                break;
            }
        }
    }
    return result;
}

// Fractionated Morse Cipher: Decrypts by reversing fractionation and Morse conversion
std::string fractionatedMorseDecrypt(const std::string& text, const std::string& key) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string cleanedText = cleanText(text);
    if (cleanedText.empty()) return "";
    std::string cleanedKey = cleanText(key);
    if (cleanedKey.empty()) return "Error: Key must contain letters";
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string keyAlphabet = cleanedKey;
    for (char c : alphabet) {
        if (keyAlphabet.find(c) == std::string::npos) {
            keyAlphabet += c;
        }
    }
    std::string morseTriplets[27] = {
        "...", "..-", "..X", ".-.", ".-.", ".-X", ".X.", ".X-", ".XX", // 0-8
        "-..", "-.-", "-.X", "--.", "--.", "--X", "-X.", "-X-", "-XX", // 9-17
        "X..", "X.-", "X.X", "XX.", "XX-", "XXX", "X--", "X-." // 18-25
    };
    std::string morse;
    for (char c : cleanedText) {
        size_t pos = keyAlphabet.find(c);
        if (pos != std::string::npos && pos < 26) {
            morse += morseTriplets[pos];
        }
    }
    const std::string morseCodes[26] = {
        ".-", "-...", "-.-.", "-..", ".", // A-E
        "..-.", "--.", "....", "..", ".---", // F-J
        "-.-", ".-..", "--", "-.", "---", // K-O
        ".--.", "--.-", ".-.", "...", "-", // P-T
        "..-", "...-", ".--", "-..-", "-.--", // U-Y
        "--.." // Z
    };
    std::string result;
    std::string current;
    for (char c : morse + "X") {
        if (c == 'X' && !current.empty()) {
            for (size_t i = 0; i < 26; ++i) {
                if (current == morseCodes[i]) {
                    result += static_cast<char>('A' + i);
                    break;
                }
            }
            current.clear();
        }
        else if (c != 'X') {
            current += c;
        }
    }
    return result;
}



// Columnar Transposition Cipher: Encrypts by rearranging letters in a grid by key order
std::string columnarTranspositionEncrypt(const std::string& text, const std::string& key) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string cleanedText = cleanText(text, true);
    if (cleanedText.empty()) return "";
    std::string cleanedKey = cleanText(key);
    if (cleanedKey.empty()) return "Error: Key must contain letters";
    size_t cols = cleanedKey.length();
    size_t rows = (cleanedText.length() + cols - 1) / cols;
    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols, 'X'));
    size_t k = 0;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols && k < cleanedText.length(); ++j) {
            grid[i][j] = cleanedText[k++];
        }
    }
    std::vector<std::pair<char, size_t>> keyOrder;
    for (size_t i = 0; i < cols; ++i) {
        keyOrder.emplace_back(cleanedKey[i], i);
    }
    std::sort(keyOrder.begin(), keyOrder.end());
    std::string result;
    for (const auto& pair : keyOrder) {
        size_t col = pair.second;
        for (size_t i = 0; i < rows; ++i) {
            result += grid[i][col];
        }
    }
    return result;
}

// Columnar Transposition Cipher: Decrypts by reversing the grid arrangement
std::string columnarTranspositionDecrypt(const std::string& text, const std::string& key) {
    if (key.empty()) return "Error: Key cannot be empty";
    std::string cleanedText = cleanText(text, true);
    if (cleanedText.empty()) return "";
    std::string cleanedKey = cleanText(key);
    if (cleanedKey.empty()) return "Error: Key must contain letters";
    size_t cols = cleanedKey.length();
    if (cleanedText.length() % cols != 0) return "Error: Invalid ciphertext length";
    size_t rows = cleanedText.length() / cols;
    std::vector<std::pair<char, size_t>> keyOrder;
    for (size_t i = 0; i < cols; ++i) {
        keyOrder.emplace_back(cleanedKey[i], i);
    }
    std::sort(keyOrder.begin(), keyOrder.end());
    std::vector<size_t> colOrder(cols);
    for (size_t i = 0; i < cols; ++i) {
        colOrder[keyOrder[i].second] = i;
    }
    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols));
    size_t k = 0;
    for (size_t j : colOrder) {
        for (size_t i = 0; i < rows; ++i) {
            grid[i][j] = cleanedText[k++];
        }
    }
    std::string decrypted;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            decrypted += grid[i][j];
        }
    }
    // Remove trailing 'X's (padding)
    while (!decrypted.empty() && decrypted.back() == 'X') {
        decrypted.pop_back();
    }
    return decrypted;
}

// Beale Cipher (simplified): Encrypts using a reference text for numbered substitution
std::string bealeEncrypt(const std::string& text, const std::string& bookText) {
    std::string cleanedText = cleanText(text);
    if (cleanedText.empty()) return "";
    std::string cleanedBook = bookText;
    std::vector<size_t> letterPositions[26];
    size_t pos = 0;
    for (char c : cleanedBook) {
        if (std::isalpha(c)) {
            size_t idx = std::toupper(c) - 'A';
            if (idx < 26) {
                letterPositions[idx].push_back(pos);
            }
        }
        ++pos;
    }
    std::string result;
    for (char c : cleanedText) {
        size_t idx = c - 'A';
        if (letterPositions[idx].empty()) return "Error: Book text lacks letter " + std::string(1, c);
        // Use first available position for simplicity
        result += std::to_string(letterPositions[idx][0]) + " ";
    }
    return result;
}

// Beale Cipher (simplified): Decrypts by mapping numbers to book text letters
std::string bealeDecrypt(const std::string& text, const std::string& bookText) {
    std::string cleanedBook = bookText;
    std::vector<char> letters;
    for (char c : cleanedBook) {
        if (std::isalpha(c)) {
            letters.push_back(std::toupper(c));
        }
    }
    std::string cleanedText = text;
    cleanedText.erase(std::remove_if(cleanedText.begin(), cleanedText.end(),
        [](char c) { return !std::isdigit(c) && c != ' '; }), cleanedText.end());
    std::vector<size_t> numbers;
    std::string num;
    for (char c : cleanedText + " ") {
        if (c == ' ' && !num.empty()) {
            numbers.push_back(std::stoul(num));
            num.clear();
        }
        else if (std::isdigit(c)) {
            num += c;
        }
    }
    if (numbers.empty()) return "Error: Invalid ciphertext";
    std::string result;
    for (size_t n : numbers) {
        if (n >= letters.size()) return "Error: Invalid position in ciphertext";
        result += letters[n];
    }
    return result;
}

// Chaocipher: Encrypts using dynamic shifting alphabets
std::string chaocipherEncrypt(const std::string& text, const std::string& leftKey, const std::string& rightKey) {
    if (leftKey.length() != 26 || rightKey.length() != 26) return "Error: Keys must be 26 letters";
    std::string cleanedText = cleanText(text);
    if (cleanedText.empty()) return "";
    std::string left = cleanText(leftKey);
    std::string right = cleanText(rightKey);
    if (left.length() != 26 || right.length() != 26) return "Error: Keys must contain 26 letters";
    std::string result;
    for (char c : cleanedText) {
        size_t pos = right.find(c);
        if (pos == std::string::npos) continue;
        result += left[pos];
        // Permute left alphabet
        char temp = left[pos];
        left.erase(pos, 1);
        left.insert(pos == 25 ? 0 : pos + 1, 1, temp);
        std::rotate(left.begin() + 2, left.begin() + 3, left.end());
        // Permute right alphabet
        temp = right[pos];
        right.erase(pos, 1);
        right.insert(pos == 25 ? 0 : pos + 1, 1, temp);
        std::rotate(right.begin() + 1, right.begin() + 2, right.end());
    }
    return result;
}

// Chaocipher: Decrypts using dynamic shifting alphabets
std::string chaocipherDecrypt(const std::string& text, const std::string& leftKey, const std::string& rightKey) {
    if (leftKey.length() != 26 || rightKey.length() != 26) return "Error: Keys must be 26 letters";
    std::string cleanedText = cleanText(text);
    if (cleanedText.empty()) return "";
    std::string left = cleanText(leftKey);
    std::string right = cleanText(rightKey);
    if (left.length() != 26 || right.length() != 26) return "Error: Keys must contain 26 letters";
    std::string result;
    for (char c : cleanedText) {
        size_t pos = left.find(c);
        if (pos == std::string::npos) continue;
        result += right[pos];
        // Permute left alphabet
        char temp = left[pos];
        left.erase(pos, 1);
        left.insert(pos == 25 ? 0 : pos + 1, 1, temp);
        std::rotate(left.begin() + 2, left.begin() + 3, left.end());
        // Permute right alphabet
        temp = right[pos];
        right.erase(pos, 1);
        right.insert(pos == 25 ? 0 : pos + 1, 1, temp);
        std::rotate(right.begin() + 1, right.begin() + 2, right.end());
    }
    return result;
}

// Kama-Sutra Cipher: Encrypts by swapping letters based on predefined pairs
std::string kamaSutraEncrypt(const std::string& text) {
    std::string cleanedText = cleanText(text);
    if (cleanedText.empty()) return "";
    const char pairs[26] = {
        'N', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', // A-J -> N,B,C,D,E,F,G,H,I,J
        'K', 'L', 'M', 'A', 'O', 'P', 'Q', 'R', 'S', 'T', // K-T -> K,L,M,A,O,P,Q,R,S,T
        'U', 'V', 'W', 'X', 'Y', 'Z'  // U-Z -> U,V,W,X,Y,Z
    };
    std::string result;
    for (char c : cleanedText) {
        size_t idx = c - 'A';
        result += pairs[idx];
    }
    return result;
}

// Kama-Sutra Cipher: Decrypts by swapping letters (involutive)
std::string kamaSutraDecrypt(const std::string& text) {
    return kamaSutraEncrypt(text);
}

// Pollux Cipher: Encrypts Morse code into random digits
std::string polluxDecrypt(const std::string& text, const std::string& digitMap) {
    if (digitMap.length() != 9) return "Error: Digit map must contain 9 digits";

    // Clean the input text to only contain digits from the digitMap
    std::string cleanedText;
    for (char c : text) {
        if (digitMap.find(c) != std::string::npos) {
            cleanedText += c;
        }
    }
    if (cleanedText.empty()) return "";

    // Convert digits to Morse components
    std::string morse;
    for (char c : cleanedText) {
        size_t pos = digitMap.find(c);
        if (pos < 3) morse += '.';      // First 3 digits -> dot
        else if (pos < 6) morse += '-'; // Next 3 digits -> dash
        else morse += ' ';              // Last 3 digits -> space
    }

    // Morse code to letters mapping
    const std::vector<std::pair<std::string, char>> morseMap = {
        {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'},
        {"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'},
        {"-.-", 'K'}, {".-..", 'L'}, {"--", 'M'}, {"-.", 'N'}, {"---", 'O'},
        {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'},
        {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'}, {"-.--", 'Y'},
        {"--..", 'Z'}
    };

    // Split morse string into letters and convert
    std::string result;
    std::string currentSymbol;
    for (char c : morse) {
        if (c == ' ') {
            // Find matching Morse code
            for (const auto& pair : morseMap) {
                if (pair.first == currentSymbol) {
                    result += pair.second;
                    break;
                }
            }
            currentSymbol.clear();
        }
        else {
            currentSymbol += c;
        }
    }

    // Process the last symbol
    if (!currentSymbol.empty()) {
        for (const auto& pair : morseMap) {
            if (pair.first == currentSymbol) {
                result += pair.second;
                break;
            }
        }
    }

    return result;
}

std::string polluxEncrypt(const std::string& text, const std::string& digitMap) {
    if (digitMap.length() != 9) return "Error: Digit map must contain 9 digits";

    const std::vector<std::pair<char, std::string>> morseMap = {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
        {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
        {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
        {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
        {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
        {'Z', "--.."}
    };

    std::string upperText;
    for (char c : text) {
        upperText += toupper(c);
    }

    std::string morse;
    for (char c : upperText) {
        if (c == ' ') {
            morse += " ";
            continue;
        }
        for (const auto& pair : morseMap) {
            if (pair.first == c) {
                morse += pair.second + " ";
                break;
            }
        }
    }

    std::string result;
    for (char c : morse) {
        if (c == '.') {
            result += digitMap[0]; // First digit for dot
        }
        else if (c == '-') {
            result += digitMap[3]; // Fourth digit for dash
        }
        else if (c == ' ') {
            result += digitMap[6]; // Seventh digit for space
        }
    }

    return result;
}
