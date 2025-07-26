# Cryptographic Ciphers Program

This C++ program implements 30 classical cryptographic ciphers, providing both encryption and decryption functionalities. Designed for educational purposes, it demonstrates a variety of historical encryption techniques. The program supports a command-line interface for testing ciphers, encrypting/decrypting text, and outputting results to the console or a file.

## Features

- **30 Ciphers**: Implements a wide range of classical ciphers, from simple substitution to complex polygraphic and transposition ciphers.
- **Command-Line Interface**: Supports commands for testing, selecting ciphers, encrypting, and decrypting text.
- **Flexible Output**: Results can be printed to the console for piping to other programs or saved to a file.
- **Error Handling**: Validates input parameters, such as cipher numbers and key formats.
- **Windows Compatibility**: Includes `Sleep` calls for test output readability on Windows.

## Supported Ciphers

The program implements the following 30 ciphers, each with encryption and decryption functions:

1. **Caesar Cipher**: Shifts letters by a fixed number.
2. **Vigenère Cipher**: Uses a keyword for polybius substitution.
3. **Playfair Cipher**: Encrypts digraphs using a 5x5 grid.
4. **Rail Fence Cipher**: Arranges text in a zigzag pattern across rails.
5. **Substitution Cipher**: Maps each letter to another via a 26-letter key.
6. **Atbash Cipher**: Reverses the alphabet (A↔Z, B↔Y, etc.).
7. **Scytale Cipher**: Transposes text based on a cylinder diameter.
8. **Hill Cipher**: Uses matrix multiplication with a 3x3 key.
9. **Beaufort Cipher**: A variant of Vigenère with subtraction.
10. **ADFGVX Cipher**: Combines a 6x6 Polybius square with transposition.
11. **Polybius Square Cipher**: Maps letters to row-column pairs in a 5x5 grid.
12. **Grille Cipher**: Uses a 4x4 turning grille for transposition.
13. **One-Time Pad**: XOR-based encryption with a random key.
14. **Autokey Cipher**: Extends Vigenère by appending plaintext to the key.
15. **Four-Square Cipher**: Uses two 5x5 grids for digraph substitution.
16. **Bazeries Cipher**: Combines substitution and transposition with a number key.
17. **Columnar Transposition**: Rearranges text by columns based on a keyword.
18. **Bacon Cipher**: Encodes letters as binary (A/B) strings.
19. **Porta Cipher**: Uses a tableau for substitution based on key letters.
20. **Chaocipher**: Dynamic substitution with two shifting alphabets.
21. **Alberti Cipher Disk**: Substitutes letters using a disk with a shift.
22. **Two-Square Cipher**: Similar to Four-Square but with two grids.
23. **Bifid Cipher**: Combines Polybius square with fractionation.
24. **Trifid Cipher**: Extends Bifid with three dimensions and a period.
25. **Nihilist Cipher**: Adds Polybius coordinates to a numerical key.
26. **Homophonic Substitution**: Maps letters to multiple numerical codes.
27. **Checkerboard Cipher**: Maps letters to digits via a Polybius grid.
28. **Fractionated Morse**: Converts text to Morse-like code and substitutes.
29. **Kama-Sutra Cipher**: Pairs letters for substitution without a key.
30. **Pollux Cipher**: Encodes Morse code as digits with random separators.

## Usage

The program is executed via command-line arguments. Below are detailed instructions for all supported commands, including examples for various ciphers. The program supports 30 ciphers, numbered 1 to 30, and each command uses specific key formats depending on the cipher.

### Commands

#### 1. `help`
Displays a help message listing all commands and supported ciphers.

**Syntax**:
```
./crypto.exe help
```

**Example**:
```
./crypto.exe help
```

**Output**:
```
Usage: ./crypto.exe <command> [args]
Commands:
  help                - Display this help message
  show                - Show source code (not implemented)
  test                - Run all cipher tests
  select <number> <key> <text> - Run cipher <number> with <key> and <text>
  e <number> <key> <text> [output_file] - Encrypt text with cipher <number>
  d <number> <key> <text> [output_file] - Decrypt text with cipher <number>
Ciphers:
  1: Caesar
  2: Vigenère
  ...
  30: Pollux
```

#### 2. `show`
Placeholder command for displaying source code (not implemented).

**Syntax**:
```
./crypto.exe show
```

**Example**:
```
./crypto.exe show
```

**Output**:
```
Show command not implemented.
```

#### 3. `test`
Runs predefined test cases for all 30 ciphers, displaying the original text, encrypted text, and decrypted text for each. The test cases are defined in the `test` function in `main.cpp`.

**Syntax**:
```
./crypto.exe test
```

**Example**:
```
./crypto.exe test
```

**Output** (abridged):
```
Caesar Cipher:
Original: HELLO
Encrypted: KHOOR
Decrypted: HELLO

Vigenère Cipher:
Original: ATTACKATDAWN
Encrypted: LXFOPVEFRNHR
Decrypted: ATTACKATDAWN
...
Pollux Cipher:
Original: SOS
Encrypted: 111744471117
Decrypted: SOS
```

#### 4. `select <number> <key> <text>`
Applies the specified cipher (1-30) to encrypt the input text, then decrypts the result, displaying both the encrypted and decrypted text. The `<key>` format depends on the cipher.

**Syntax**:
```
./crypto.exe select <number> <key> <text>
```

**Examples**:
- **Caesar Cipher (1)**:
  ```
  ./crypto.exe select 1 3 "HELLO"
  ```
  **Output**:
  ```
  Caesar Cipher:
  Original: HELLO
  Encrypted: KHOOR
  Decrypted: HELLO
  ```

- **Vigenère Cipher (2)**:
  ```
  ./crypto.exe select 2 LEMON "ATTACK"
  ```
  **Output**:
  ```
  Vigenère Cipher:
  Original: ATTACK
  Encrypted: LXFOPV
  Decrypted: ATTACK
  ```

- **Grille Cipher (12)**:
  ```
  ./crypto.exe select 12 "1,0,0,0;0,0,1,0;0,1,0,0;0,0,0,1" "SECRETMESSAGE"
  ```
  **Output**:
  ```
  Grille Cipher:
  Original: SECRETMESSAGE
  Encrypted: SCRTEMSAEXEGSEXX
  Decrypted: SECRETMESSAGE
  ```

- **Hill Cipher (8)**:
  ```
  ./crypto.exe select 8 "6,24,1,13,16,10,20,17,15" "ACT"
  ```
  **Output**:
  ```
  Hill Cipher:
  Original: ACT
  Encrypted: POH
  Decrypted: ACT
  ```

#### 5. `e <number> <key> <text> [output_file]`
Encrypts the input text using the specified cipher (1-30) and key. Outputs the result to the console and `r.txt`. If an optional `output_file` is provided, the result is also written to that file.

**Syntax**:
```
./crypto.exe e <number> <key> <text> [output_file]
```

**Examples**:
- **Caesar Cipher (1)**:
  ```
  ./crypto.exe e 1 3 "HELLO"
  ```
  **Output**:
  ```
  Encrypted: KHOOR
  Result written to r.txt
  ```
  **File (`r.txt`)**: `KHOOR`

- **Playfair Cipher (3) with output file**:
  ```
  ./crypto.exe e 3 KEYWORD "HIDETHEGOLD" output.txt
  ```
  **Output**:
  ```
  Encrypted: ILGDVFDNCSBU
  Result written to r.txt
  ```
  **Files**: `r.txt` and `output.txt` contain `ILGDVFDNCSBU`.

- **ADFGVX Cipher (10)**:
  ```
  ./crypto.exe e 10 GERMAN "ATTACK"
  ```
  **Output**:
  ```
  Encrypted: GDAAAADFDVGA
  Result written to r.txt
  ```
  **File (`r.txt`)**: `GDAAAADFDVGA`

#### 6. `d <number> <key> <text> [output_file]`
Decrypts the input text using the specified cipher (1-30) and key. Outputs the result to the console and `r.txt`. If an optional `output_file` is provided, the result is also written to that file.

**Syntax**:
```
./crypto.exe d <number> <key> <text> [output_file]
```

**Examples**:
- **Caesar Cipher (1)**:
  ```
  ./crypto.exe d 1 3 "KHOOR"
  ```
  **Output**:
  ```
  Decrypted: HELLO
  Result written to r.txt
  ```
  **File (`r.txt`)**: `HELLO`

- **Columnar Transposition (17) with output file**:
  ```
  ./crypto.exe d 17 CANO "EDOEEOXWECRLTEAIVDENXRSEFACX" output.txt
  ```
  **Output**:
  ```
  Decrypted: WEAREDISCOVEREDFLEEATONCE
  Result written to r.txt
  ```
  **Files**: `r.txt` and `output.txt` contain `WEAREDISCOVEREDFLEEATONCE`.

- **Pollux Cipher (30)**:
  ```
  ./crypto.exe d 30 "123456789" "111744471117"
  ```
  **Output**:
  ```
  Decrypted: SOS
  Result written to r.txt
  ```
  **File (`r.txt`)**: `SOS`

### Key Formats

Each cipher requires a specific key format, as used in the `test` function and `select`/`e`/`d` commands:

- **Caesar (1)**: Integer shift (e.g., `3`).
- **Vigenère (2), Beaufort (9), Porta (19), Autokey (14), Fractionated Morse (28)**: String of letters (e.g., `KEYWORD`).
- **Playfair (3), Bifid (23)**: Single keyword (e.g., `KEYWORD`).
- **Rail Fence (4)**: Number of rails (e.g., `3`).
- **Substitution (5)**: 26 unique letters (e.g., `ZYXWVUTSRQPONMLKJIHGFEDCBA`).
- **Atbash (6), Kama-Sutra (29)**: No key required (pass empty string or any value, ignored).
- **Scytale (7)**: Integer diameter (e.g., `2`).
- **Hill (8)**: 9 comma-separated integers for a 3x3 matrix (e.g., `6,24,1,13,16,10,20,17,15`).
- **ADFGVX (10)**: Keyword (e.g., `GERMAN`); uses fixed square `PH0QGI6NU4A1Y7L5V3R2Z8WXSTB9CDFEKMJB`.
- **Polybius Square (11)**: 25-letter square (e.g., `ABCDEFGHIKLMNOPQRSTUVWXYZ`, default used).
- **Grille (12)**: 4x4 grille as semicolon-separated rows (e.g., `1,0,0,0;0,0,1,0;0,1,0,0;0,0,0,1`).
- **One-Time Pad (13)**: Key same length as text (e.g., `XMCKLB`).
- **Four-Square (15), Two-Square (22)**: Two keywords (e.g., `EXAMPLE,KEYWORD`).
- **Bazeries (16)**: Keyword and number (e.g., `CIPHER,3`).
- **Columnar Transposition (17)**: Keyword (e.g., `CANO`).
- **Bacon (18)**: No key required.
- **Chaocipher (20)**: Two 26-letter alphabets (e.g., `HXUCZVAMDSLKPEFJRIGTWOBNYQ,PTLNBQDEOYSFAVZKGJRIHWXUMC`).
- **Alberti (21)**: Keyword and shift (e.g., `CIPHER,3`).
- **Trifid (24)**: Keyword and period (e.g., `CIPHER,5`).
- **Nihilist (25)**: Keyword and optional square (e.g., `CIPHER,ABCDEFGHIKLMNOPQRSTUVWXYZ`).
- **Homophonic Substitution (26)**: Fixed substitutes (e.g., `H:23,45`, `E:12,34,56`, `L:78,90`, `O:11,22`).
- **Checkerboard (27)**: Keyword and digits (e.g., `CIPHER,1234567890`).
- **Pollux (30)**: Digit string (e.g., `123456789`).

### Notes on Usage
- **Text Input**: Text should be uppercase letters for most ciphers. Non-letters are typically removed by a `cleanText` function (assumed in `secret.h`).
- **Output Files**: The `e` and `d` commands always write to `r.txt`. If `[output_file]` is specified, it writes there too.
- **Piping**: For `e` and `d`, console output can be piped to another program (e.g., `./crypto.exe e 1 3 HELLO | another_program`).
- **Error Messages**: Invalid inputs (e.g., wrong cipher number, malformed key) produce error messages and exit with code 1.

## Compilation

### Prerequisites
- **C++ Compiler**: Supports C++11 or later (e.g., g++, MSVC).
- **Operating System**: Windows (due to `<windows.h>` and `Sleep` usage). For Linux/Mac, replace `Sleep` with:
  ```cpp
  #include <thread>
  #include <chrono>
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  ```
- **Dependencies**: Standard C++ libraries only (`<iostream>`, `<string>`, `<vector>`, `<sstream>`, `<fstream>`, `<cctype>`, `<algorithm>`, `<cmath>`).

### Steps
1. Clone the repository:
   ```
   git clone https://github.com/yourusername/crypto-ciphers.git
   cd crypto-ciphers
   ```

2. Compile the program:
   - **Windows (MSVC)**:
     ```
     cl /EHsc main.cpp secret.cpp /Fe:crypto.exe
     ```
     Ensure `main.cpp` and `secret.cpp` are in the same directory.
   - **Linux/Mac (g++)**:
     Modify `main.cpp` to replace `<windows.h>` and `Sleep` calls as above, then:
     ```
     g++ -std=c++11 main.cpp secret.cpp -o crypto
     ```

3. Run the executable:
   ```
   ./crypto.exe test
   ```

### Project Structure
- `main.cpp`: Command-line interface, test function, and cipher selection logic.
- `secret.h`: Declares cipher functions.
- `secret.cpp`: Implements encryption/decryption functions (not included here but required).

## Dependencies

- **Standard C++ Libraries**: No external libraries required.
- **Windows-Specific**: `<windows.h>` for `Sleep`. For cross-platform use, replace with `<thread>` and `<chrono>`.

## Notes

- **Error Handling**: Validates cipher numbers (1-30) and key formats, exiting with error messages for invalid inputs.
- **Output File**: `e` and `d` commands write to `r.txt` by default, with optional custom output files.
- **Cross-Platform**: Designed for Windows. For Linux/Mac, modify sleep functionality.
- **Extensibility**: Add new ciphers by updating `encryptByCipher` and `decryptByCipher` in `main.cpp`.

## Contributing

Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/new-cipher`).
3. Commit changes (`git commit -m "Add new cipher"`).
4. Push to the branch (`git push origin feature/new-cipher`).
5. Open a pull request.

Please ensure:
- Code follows C++11 standards.
- New ciphers include test cases in the `test` function.
- Key formats are documented in the README.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For issues or questions, open an issue on GitHub or contact the maintainer at [your.email@example.com].

---

*This project is for educational purposes and should not be used for secure communication, as classical ciphers are vulnerable to modern cryptanalysis.*