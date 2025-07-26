Cryptographic Ciphers Program
This C++ program implements 30 different cryptographic ciphers, providing both encryption and decryption functionalities. It is designed for educational purposes, demonstrating classical and historical encryption techniques. The program supports command-line operations for testing ciphers, encrypting/decrypting text, and outputting results to the console or a file.
Features

30 Ciphers: Implements a wide range of classical ciphers, from simple substitution ciphers to complex polygraphic and transposition ciphers.
Command-Line Interface: Supports commands for testing, selecting ciphers, encrypting, and decrypting text.
Flexible Output: Results can be printed to the console or saved to a file for use by other programs.
Error Handling: Validates input parameters, such as cipher numbers and key formats.
Windows Compatibility: Includes Sleep calls for test output readability on Windows.

Supported Ciphers
The program implements the following 30 ciphers, each with encryption and decryption functions:

Caesar Cipher: Shifts letters by a fixed number.
Vigenère Cipher: Uses a keyword for polybius substitution.
Playfair Cipher: Encrypts digraphs using a 5x5 grid.
Rail Fence Cipher: Arranges text in a zigzag pattern across rails.
Substitution Cipher: Maps each letter to another via a 26-letter key.
Atbash Cipher: Reverses the alphabet (A↔Z, B↔Y, etc.).
Scytale Cipher: Transposes text based on a cylinder diameter.
Hill Cipher: Uses matrix multiplication with a 3x3 key.
Beaufort Cipher: A variant of Vigenère with subtraction.
ADFGVX Cipher: Combines a 6x6 Polybius square with transposition.
Polybius Square Cipher: Maps letters to row-column pairs in a 5x5 grid.
Grille Cipher: Uses a 4x4 turning grille for transposition.
One-Time Pad: XOR-based encryption with a random key.
Autokey Cipher: Extends Vigenère by appending plaintext to the key.
Four-Square Cipher: Uses two 5x5 grids for digraph substitution.
Bazeries Cipher: Combines substitution and transposition with a number key.
Columnar Transposition: Rearranges text by columns based on a keyword.
Bacon Cipher: Encodes letters as binary (A/B) strings.
Porta Cipher: Uses a tableau for substitution based on key letters.
Chaocipher: Dynamic substitution with two shifting alphabets.
Alberti Cipher Disk: Substitutes letters using a disk with a shift.
Two-Square Cipher: Similar to Four-Square but with two grids.
Bifid Cipher: Combines Polybius square with fractionation.
Trifid Cipher: Extends Bifid with three dimensions and a period.
Nihilist Cipher: Adds Polybius coordinates to a numerical key.
Homophonic Substitution: Maps letters to multiple numerical codes.
Checkerboard Cipher: Maps letters to digits via a Polybius grid.
Fractionated Morse: Converts text to MIDI-like code and substitutes.
Kama-Sutra Cipher: Pairs letters for substitution without a key.
Pollux Cipher: Encodes Morse code as digits with random separators.

Usage
The program is executed via command-line arguments. Below are the supported commands and their formats:
Commands

help: Displays the help message with usage instructions.
./crypto.exe help


show: Placeholder for showing source code (not implemented).
./crypto.exe show


test: Runs tests for all 30 ciphers, displaying original, encrypted, and decrypted text for predefined examples.
./crypto.exe test


select <number> <key> <text>: Applies the specified cipher (1-30) to encrypt and decrypt the text, displaying both results.
./crypto.exe select 1 3 "Hello"


e <number> <key> <text> [output_file]: Encrypts the text using the specified cipher and key. Outputs to stdout or a file.
./crypto.exe e 1 3 "Hello" output.txt


d <number> <key> <text> [output_file]: Decrypts the text using the specified cipher and key. Outputs to stdout or a file.
./crypto.exe d 1 3 "KHOOR" output.txt



Key Formats
Each cipher requires a specific key format:

Caesar (1): Integer shift (e.g., 3).
Vigenère (2), Beaufort (9), Porta (19), etc.: String of letters (e.g., KEYWORD).
Playfair (3), Four-Square (15), Two-Square (22): Keyword(s) or two keys (e.g., KEYWORD,CIPHER).
Rail Fence (4): Number of rails (e.g., 3).
Substitution (5): 26 unique letters (e.g., ZYXWVUTSRQPONMLKJIHGFEDCBA).
Scytale (7): Integer diameter (e.g., 2).
Hill (8): 9 comma-separated integers for a 3x3 matrix (e.g., 6,24,1,13,16,10,20,17,15).
ADFGVX (10): Keyword (e.g., GERMAN); uses a fixed 6x6 square.
Grille (12): 4x4 grille as semicolon-separated rows (e.g., 1,0,0,0;0,0,1,0;0,1,0,0;0,0,0,1).
Bazeries (16): Key and number (e.g., CIPHER,3).
Chaocipher (20): Two 26-letter alphabets (e.g., HXUCZ...,PTLNB...).
Alberti (21): Key and shift (e.g., CIPHER,3).
Trifid (24): Key and period (e.g., CIPHER,5).
Nihilist (25): Key and optional square (e.g., CIPHER,ABCDEFGHIKLMNOPQRSTUVWXYZ).
Checkerboard (27): Key and digits (e.g., CIPHER,1234567890).
Pollux (30): Digit string (e.g., 123456789).
Others: Specific keys as shown in the test function or no key (e.g., Atbash, Kama-Sutra).

Output

For e and d commands, the result is written to r.txt by default and printed to the console.
If an optional [output_file] is provided, the result is written to that file instead.
For select, both encrypted and decrypted texts are displayed.

Example Usage

Test all ciphers:
./crypto.exe test

Output: Displays test cases for all 30 ciphers.

Encrypt "Hello" with Caesar Cipher (shift 3):
./crypto.exe e 1 3 "Hello" output.txt

Output: KHOOR written to output.txt and r.txt, printed to console.

Decrypt "KHOOR" with Caesar Cipher (shift 3):
./crypto.exe d 1 3 "KHOOR"

Output: HELLO printed to console and written to r.txt.

Select Vigenère Cipher with key "LEMON":
./crypto.exe select 2 LEMON "ATTACK"

Output:
Vigenère Cipher:
Original: ATTACK
Encrypted: LXFOPV
Decrypted: ATTACK



Compilation
Prerequisites

C++ Compiler: Supports C++11 or later (e.g., g++, MSVC).
Operating System: Windows (due to <windows.h> and Sleep usage). For other platforms, replace Sleep with std::this_thread::sleep_for and include <thread> and <chrono>.
Dependencies: Standard C++ libraries only (<iostream>, <string>, <vector>, <sstream>, <fstream>, <cctype>, <algorithm>, <cmath>).

Steps

Clone the repository:
git clone https://github.com/yourusername/crypto-ciphers.git
cd crypto-ciphers


Compile the program:

Windows (MSVC):cl /EHsc main.cpp secret.cpp /Fe:crypto.exe

Ensure main.cpp and secret.cpp (containing cipher implementations) are in the same directory.
Linux/Mac (g++):Modify main.cpp to replace <windows.h> and Sleep(100) with:#include <thread>
#include <chrono>
std::this_thread::sleep_for(std::chrono::milliseconds(100));

Then compile:g++ -std=c++11 main.cpp secret.cpp -o crypto




Run the executable:
./crypto.exe test



Project Structure

main.cpp: Contains the command-line interface, test function, and cipher selection logic.
secret.h: Header file declaring cipher functions.
secret.cpp: Implements the encryption and decryption functions for all ciphers (not provided here but assumed to exist).

Dependencies

Standard C++ Libraries: No external libraries required.
Windows-Specific: <windows.h> for Sleep. For cross-platform compatibility, use <thread> and <chrono> as described above.

Notes

Error Handling: The program validates inputs (e.g., cipher number 1-30, key format) and outputs error messages for invalid parameters.
Output File: The e and d commands always write to r.txt. If an optional output file is specified, it writes there instead.
Cross-Platform: Primarily designed for Windows. For Linux/Mac, modify the sleep function as noted.
Extensibility: Add new ciphers by extending the encryptByCipher and decryptByCipher functions with new case statements.

Contributing
Contributions are welcome! To contribute:

Fork the repository.
Create a feature branch (git checkout -b feature/new-cipher).
Commit changes (git commit -m "Add new cipher").
Push to the branch (git push origin feature/new-cipher).
Open a pull request.

Please ensure:

Code follows C++11 standards.
New ciphers include test cases in the test function.
Key formats are documented in the README.

License
This project is licensed under the MIT License. See the LICENSE file for details.
Contact
For issues or questions, open an issue on GitHub or contact the maintainer at [your.email@example.com].

This project is for educational purposes and should not be used for secure communication, as many classical ciphers are easily broken with modern cryptanalysis.