```markdown
# Secret Ciphers

This C++ program implements 30 classical cryptographic ciphers, providing a command-line interface to encrypt and decrypt text using various techniques. The program includes a test suite to demonstrate each cipher and allows users to select specific ciphers with custom keys and text.

## Table of Contents
- [Features](#features)
- [Usage](#usage)
- [Ciphers](#ciphers)
- [Compilation with Visual Studio 2022](#compilation-with-visual-studio-2022)
- [Dependencies](#dependencies)
- [Known Issues](#known-issues)
- [License](#license)

## Features
- Implements 30 classical ciphers (e.g., Caesar, Vigenère, ADFGVX, etc.).
- Command-line interpreter with commands: `help`, `show`, `test`, `select`.
- Supports custom keys and text for encryption/decryption.
- Includes error handling for invalid inputs.
- Test suite to demonstrate all ciphers with predefined inputs.

## Usage
The program is run from the command line with the following commands:

### Commands
- **`help`**: Displays available commands and cipher list.
  ```bash
  secret.exe help
  ```
- **`show`**: Prints the source code of the `test()` function, which demonstrates all ciphers.
  ```bash
  secret.exe show
  ```
- **`test`**: Runs all 30 ciphers with predefined inputs, displaying original, encrypted, and decrypted text.
  ```bash
  secret.exe test
  ```
- **`select <number> <key> <text>`**: Runs a specific cipher (1–30) with the provided key and text.
  ```bash
  secret.exe select 1 3 HELLO
  secret.exe select 10 GERMAN SECRET
  secret.exe select 8 6,24,1,13,16,10,20,17,15 ACT
  ```

### Example Outputs
- **Caesar Cipher (select 1 3 HELLO)**:
  ```
  Caesar Cipher:
  Original: HELLO
  Encrypted: KHOOR
  Decrypted: HELLO
  ```
- **ADFGVX Cipher (select 10 GERMAN ATTACK)**:
  ```
  ADFGVX Cipher:
  Original: ATTACK
  Encrypted: DFVVVDDVVVXF
  Decrypted: ATTACK
  ```

## Ciphers
The program implements the following 30 ciphers. Each cipher has specific key requirements, and some have known decryption issues (see [Known Issues](#known-issues)).

| #  | Cipher                  | Description                                                                 | Key Format                                      | Notes                                                                 |
|----|-------------------------|-----------------------------------------------------------------------------|------------------------------------------------|----------------------------------------------------------------------|
| 1  | Caesar                  | Shifts letters by a fixed number.                                           | Integer shift (e.g., `3`)                       | Simple substitution cipher.                                          |
| 2  | Vigenère                | Uses a keyword to shift letters.                                            | String key (e.g., `LEMON`)                     | Polybius substitution.                                              |
| 3  | Playfair                | Digraph substitution using a 5x5 grid.                                      | String key (e.g., `KEYWORD`)                   | Handles I/J as one letter.                                           |
| 4  | Rail Fence              | Writes text in a zigzag pattern across rails.                               | Integer rails (e.g., `3`)                      | Transposition cipher.                                               |
| 5  | Substitution            | Replaces letters with a permuted alphabet.                                  | 26-letter alphabet (e.g., `ZYXWVUTSRQPONMLKJIHGFEDCBA`) | Monoalphabetic substitution.                                        |
| 6  | Atbash                  | Reverses the alphabet (A↔Z, B↔Y, etc.).                                     | None                                           | Involutive (encrypt = decrypt).                                     |
| 7  | Scytale                 | Wraps text around a cylinder, read by columns.                              | Integer diameter (e.g., `2`)                   | Ancient transposition cipher.                                       |
| 8  | Hill                    | Matrix multiplication modulo 26.                                            | 9 comma-separated integers for 3x3 matrix (e.g., `6,24,1,13,16,10,20,17,15`) | Requires invertible matrix.                                         |
| 9  | Beaufort                | Vigenère variant with key subtraction.                                      | String key (e.g., `KEY`)                       | Involutive.                                                         |
| 10 | ADFGVX                  | Uses a 6x6 Polybius square and columnar transposition.                       | String key (e.g., `GERMAN`)                    | Uses fixed square `PH0QGI6NU4A1Y7L5V3R2Z8WXSTB9CDFEKMJB`.           |
| 11 | Polybius Square         | Maps letters to row-column numbers in a 5x5 grid.                           | None (uses `ABCDEFGHIKLMNOPQRSTUVWXYZ`)        | Outputs numbers (e.g., `23153131345234423114`).                     |
| 12 | Grille                  | Places text through holes in a grid.                                        | 4x4 grid (e.g., `1,0,0,0;0,1,0,0;0,0,1,0;0,0,0,1`) | **Decryption issue**: Outputs incorrect text (e.g., `SESTMAEG`).    |
| 13 | One-Time Pad            | XOR with a random key of equal length.                                      | String key (e.g., `XMCKLB`)                    | Perfect secrecy if key is truly random.                             |
| 14 | Autokey                 | Vigenère with plaintext/ciphertext as key extension.                        | String key (e.g., `QUEENLY`)                   | Key extends with text.                                              |
| 15 | Four-Square             | Uses four 5x5 grids for digraph substitution.                               | Two keys (e.g., `EXAMPLE,KEYWORD`)             | Complex Playfair variant.                                           |
| 16 | Bazeries                | Combines substitution and transposition.                                    | Key and number (e.g., `CIPHER,3`)              | Uses number for block size.                                         |
| 17 | Columnar Transposition  | Rearranges text by columns ordered by key.                                  | String key (e.g., `CANO`)                      | **Decryption issue**: Adds padding (e.g., `XXX`).                   |
| 18 | Bacon                   | Encodes letters as 5-bit A/B sequences.                                     | None                                           | Outputs `AABBBAABAAABABBABABBABBBA`.                               |
| 19 | Porta                   | Uses a tableau with key-driven shifts.                                      | String key (e.g., `KEY`)                       | **Decryption issue**: Outputs incorrect text (e.g., `EUDBXIRN`).    |
| 20 | Chaocipher              | Dynamic alphabet substitution with two disks.                               | Two alphabets (e.g., `HXUCZVAMDSLKPEFJRIGTWOBNYQ,PTLNBQDEOYSFAVZKGJRIHWXUMC`) | Complex mechanical cipher.                                          |
| 21 | Alberti                 | Rotates alphabet based on key and shift.                                    | Key and shift (e.g., `CIPHER,4`)               | **Decryption issue**: Outputs incorrect text (e.g., `BYZZWWWZZX`).  |
| 22 | Two-Square              | Uses two 5x5 grids for digraph substitution.                                | Two keys (e.g., `EXAMPLE,KEYWORD`)             | Simplified Four-Square.                                             |
| 23 | Bifid                   | Fractionates Polybius coordinates, then recombines.                         | String key (e.g., `PLAYFAIREXAMPLE`)           | Combines substitution and transposition.                            |
| 24 | Trifid                  | Uses a 3D cube for fractionation.                                           | Key and period (e.g., `KEYWORD,5`)             | **Decryption issue**: Outputs incorrect text (e.g., `JHDEO`).       |
| 25 | Nihilist                | Polybius square with key-based number addition.                             | Key and square (e.g., `CIPHER,ABCDEFGHIKLMNOPQRSTUVWXYZ`) | Outputs numbers (e.g., `24 68 79 34 28 67`).                        |
| 26 | Homophonic Substitution | Maps letters to multiple substitutes.                                       | None (uses fixed substitutes)                  | Outputs numbers (e.g., `23 12 78 78 11`).                           |
| 27 | Checkerboard            | Polybius variant with custom digits.                                        | Key and digits (e.g., `CIPHER,1234567890`)     | Outputs digits (e.g., `1910383846`).                                |
| 28 | Fractionated Morse      | Converts text to Morse, fractionates, then substitutes.                     | String key (e.g., `CIPHER`)                    | Complex Morse-based cipher.                                         |
| 29 | Kama-Sutra              | Swaps letter pairs based on a fixed pattern.                                | None                                           | Simple substitution.                                                |
| 30 | Pollux                  | Encodes Morse as digits with random separators.                             | Digits (e.g., `123456789`)                     | Outputs digits (e.g., `111744471117`).                              |

## Compilation with Visual Studio 2022
Follow these steps to compile `secret.cpp` using Visual Studio 2022 on Windows:

1. **Prerequisites**:
   - Install Visual Studio 2022 Community, Professional, or Enterprise.
   - Ensure the **Desktop development with C++** workload is installed (includes MSVC compiler and Windows SDK).

2. **Setup Project**:
   - Open Visual Studio 2022.
   - Click **File > New > Project**.
   - Select **Empty Project (C++)**, name it (e.g., `SecretCiphers`), and choose a location.
   - Click **Create**.

3. **Add Source File**:
   - In **Solution Explorer**, right-click **Source Files** > **Add > New Item**.
   - Select **C++ File (.cpp)**, name it `secret.cpp`, and click **Add**.
   - Copy and paste the `secret.cpp` content from this repository into the file.

4. **Add Header File**:
   - Right-click **Header Files** > **Add > New Item**.
   - Select **Header File (.h)**, name it `secret.h`, and click **Add**.
   - Add the necessary function declarations (see `secret.h` in this repository or implement cipher functions directly in `secret.cpp`).

5. **Configure Project**:
   - Right-click the project in **Solution Explorer** > **Properties**.
   - Set **Configuration** to `Release` and **Platform** to `x64` (or `Win32` for 32-bit).
   - Ensure **C/C++ > Language > C++ Language Standard** is set to `ISO C++17 Standard` or later.
   - Under **Linker > Input**, ensure `Additional Dependencies` includes `user32.lib` (for `Sleep`).

6. **Build and Run**:
   - Press **F5** to build and run in Debug mode, or **Ctrl+F5** to run without debugging.
   - Alternatively, open a **Developer Command Prompt for VS 2022** and run:
     ```bash
     cl secret.cpp /EHsc /Fe:secret.exe
     secret.exe test
     ```
   - The executable (`secret.exe`) will be in the project’s `x64/Release` or `x64/Debug` folder.

7. **Test**:
   - Run commands like `secret.exe help`, `secret.exe test`, or `secret.exe select 1 3 HELLO` from the command prompt.

## Dependencies
- **C++ Standard Library**: Uses `<iostream>`, `<string>`, `<vector>`, `<sstream>`, `<algorithm>`, `<cctype>`.
- **Windows API**: Uses `<windows.h>` for `Sleep` function.
- **No External Libraries**: All ciphers are implemented using standard C++.

## Known Issues
Some ciphers have decryption issues, producing incorrect outputs:
- **Grille (12)**: Decrypts to `SESTMAEG` instead of `SECRETMESSAGE`. Likely a flaw in `grilleDecrypt`.
- **Columnar Transposition (17)**: Decrypts with extra padding (e.g., `XXX`). Check `columnarTranspositionDecrypt` for padding handling.
- **Porta (19)**: Decrypts to `EUDBXIRN` instead of `ATTACKATDAWN`. Verify `portaDecrypt` logic.
- **Alberti (21)**: Decrypts to `BYZZWWWZZX` instead of `HELLOWORLD`. Check shift/key application in `albertiDecrypt`.
- **Trifid (24)**: Decrypts to `JHDEO` instead of `HELLO`. Verify `trifidDecrypt` period/key handling.

To debug, use the `select` command with custom inputs or provide the specific cipher function implementations for further analysis.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---
*Last updated: July 25, 2025*
```

### Additional Notes
- **GitHub Setup**:
  - Create a new repository on GitHub (e.g., `SecretCiphers`).
  - Add `secret.cpp`, `secret.h`, and `README.md` to the repository.
  - Optionally, include a `LICENSE` file (e.g., MIT License).
  - Push the files to GitHub:
    ```bash
    git init
    git add secret.cpp secret.h README.md LICENSE
    git commit -m "Initial commit with cipher program and README"
    git remote add origin https://github.com/yourusername/SecretCiphers.git
    git push -u origin main
    ```
- **Secret.h**: The README assumes `secret.h` contains declarations for all cipher functions. If cipher functions are implemented in `secret.cpp`, mention this in the README under **Compilation** (e.g., “No separate `secret.h` needed if all functions are in `secret.cpp`”).
- **VS2022 Compilation**:
  - The instructions are tailored for Windows users with VS2022.
  - The program uses `Sleep` from `<windows.h>`, making it Windows-specific. For cross-platform compatibility, replace `Sleep` with `std::this_thread::sleep_for` from `<thread>` and `<chrono>`.
- **Cipher Issues**: The known decryption issues for Grille, Columnar Transposition, Porta, Alberti, and Trifid are highlighted. Users are directed to use `select` for testing or provide function implementations for fixes.
- **ADFGVX**: The README notes the fixed 36-character square, resolving the previous error.

### Creating the Repository
1. Save the above README content as `README.md`.
2. Create `secret.h` with function declarations (or embed all functions in `secret.cpp`).
3. Initialize a Git repository, add files, and push to GitHub.
4. Update the README with the repository URL if needed (e.g., for badges or links).

This README provides comprehensive guidance for users to understand, compile, and use the cipher program, addressing all requirements and known issues. If you need `secret.h` content or further assistance with GitHub setup, let me know!