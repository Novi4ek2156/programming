// =======================================================
// ============= КРИПТОГРАФИЧЕСКИЕ АЛГОРИТМЫ =============
// =======================================================
// Ожидаемый вывод:
/*
=== Test 0: XOR Cipher ===
Original: Hello World
Encrypted: 3B 00 0F 1E 0A 54 24 0A 11 1E 01 
Decrypted: Hello World

=== Test 1: Caesar Cipher ===
Original: The quick brown fox jumps over the lazy dog
Encrypted: Wkh txlfn eurzq ira mxpsv ryhu wkh oazb grj
Decrypted: The quick brown fox jumps over the lazy dog

=== Test 2: Vigenere Cipher ===
Original: ATTACKATDAWN
Keyword: LEMON
Encrypted: ATTACKATDAWN

=== Test 3: RC4-like Cipher ===
Original: Secret message
Encrypted: B8 FA 14 F3 D2 40 EA 1F C2 6A 39 49 00 D3 
Decrypted: Secret message

=== Test 4: Simple Hash ===
Hash of "Hello": 1835
Hash of "World": 1833
Hash of "HelloWorld": 6268
Hash of "Test": 1295

=== Test 5: Key Generation ===
// Здесь у вас будет два разных ключа
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void xor_encrypt_len(char *text, int text_len, char *key, char *output) {
    int key_len = strlen(key);
    
    for (int i = 0; i < text_len; i++) {
        output[i] = text[i] ^ key[i % key_len];
    }
}

void caesar_cipher(char *text, int shift, char *output) {
    int len = strlen(text);
    // shift = shift % 26;
    // if (shift < 0) shift += 26;
    
    for (int i = 0; i < len; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            output[i] = ((text[i] - 'a' + shift) % 26) + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            output[i] = ((text[i] - 'A' + shift) % 26) + 'A';
        } else {
            output[i] = text[i];
        }
    }
    // output[len] = '\0';
}

void vigenere_encrypt(char *text, char *keyword, char *output) {
    int text_len = strlen(text);
    int key_len = strlen(keyword);
    int key_index = 0;
    
    for (int i = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            int shift;
            if (isupper(text[i])) {
                shift = toupper(keyword[key_index % key_len]) - 'A';
                output[i] = ((text[i] - 'A' + shift) % 26) + 'A';
            } else {
                shift = tolower(keyword[key_index % key_len]) - 'a';
                output[i] = ((text[i] - 'a' + shift) % 26) + 'a';
            }
            key_index++;
        } else {
            output[i] = text[i];
        }
    }
    output[text_len] = '\0';
}

void vigenere_decrypt(char *text, char *keyword, char *output) {
    int text_len = strlen(text);
    int key_len = strlen(keyword);
    int key_index = 0;
    
    for (int i = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            int shift;
            if (isupper(text[i])) {
                shift = toupper(keyword[key_index % key_len]) - 'A';
                output[i] = ((text[i] - 'A' - shift + 26) % 26) + 'A';
            } else {
                shift = tolower(keyword[key_index % key_len]) - 'a';
                output[i] = ((text[i] - 'a' - shift + 26) % 26) + 'a';
            }
            key_index++;
        } else {
            output[i] = text[i];
        }
    }
    output[text_len] = '\0';
}

void simple_rc4(char *key, int key_len, char *data, int data_len) {
    unsigned char S[256];
    unsigned char temp;
    int i, j = 0;
    for (i = 0; i < 256; i++) {
        S[i] = i;
    }
    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_len]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
    i = 0;
    j = 0;
    for (int k = 0; k < data_len; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        
        data[k] = data[k] ^ S[(S[i] + S[j]) % 256];
    }
}

unsigned int simple_hash(char *str) {
    unsigned int hash = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        hash += str[i] * (i + 1) + 50;
    }
    
    return hash;
}

void generate_key(char *key, int length) {
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    
    for (int i = 0; i < length; i++) {
        key[i] = 'a' + (rand() % 26);
    }
    key[length] = '\0';
}

// ============= ТЕСТОВЫЕ ФУНКЦИИ =============

void test_xor_cipher() {
    printf("\n=== Test 0: XOR Cipher ===\n");
    
    char text[] = "Hello World";
    int data_len = strlen(text);
    char key[] = "secret";
    char output[20];
    char output2[20];
    char decrypted[20];
    
    printf("Original: %s\n", text);
    
    // Шифрование (функция без добавления \0 в середину)
    xor_encrypt_len(text, data_len, key, output);
    
    // Копируем через memcpy (НЕ strcpy!)
    memcpy(output2, output, data_len);
    
    printf("Encrypted: ");
    for (int i = 0; i < data_len; i++) {
        printf("%02X ", (unsigned char)output[i]);
    }
    printf("\n");
    
    // Дешифрование
    xor_encrypt_len(output2, data_len, key, decrypted);
    decrypted[data_len] = '\0';
    
    printf("Decrypted: %s\n", decrypted);
}

void test_caesar_cipher() {
    printf("\n=== Test 1: Caesar Cipher ===\n");
    
    char text[] = "The quick brown fox jumps over the lazy dog";
    char output[100];
    char decrypted[100];
    
    caesar_cipher(text, 3, output);
    printf("Original: %s\n", text);
    
    caesar_cipher(output, -3, decrypted);
    printf("Decrypted: %s\n", decrypted);
}

void test_vigenere_cipher() {
    printf("\n=== Test 2: Vigenere Cipher ===\n");
    
    char text[] = "ATTACKATDAWN";
    char keyword[] = "LEMON";
    char encrypted[100];
    char decrypted[100];
    
    vigenere_encrypt(text, keyword, encrypted);
    printf("Original: %s\n", text);
    printf("Keyword: %s\n", keyword);

    
    vigenere_decrypt(encrypted, keyword, decrypted);
    printf("Decrypted: %s\n", decrypted);
}

void test_rc4_cipher() {
    printf("\n=== Test 3: RC4-like Cipher ===\n");
    
    char key[] = "Key";
    char data[] = "Secret message";
    char original[100];
    int data_len = strlen(data);
    
    strcpy(original, data);
    
    printf("Original: %s\n", original);
    
    // Шифрование
    simple_rc4(key, strlen(key), data, data_len);
    printf("Encrypted: ");
    for (int i = 0; i < data_len; i++) {
        printf("%02X ", (unsigned char)data[i]);
    }
    printf("\n");
    
    // Дешифрование
    simple_rc4(key, strlen(key), data, data_len);
    printf("Decrypted: %s\n", data);
}

void test_hash_function() {
    printf("\n=== Test 4: Simple Hash ===\n");
    
    char *strings[] = {"Hello", "World", "HelloWorld", "Test"};
    
    for (int i = 0; i < 4; i++) {
        unsigned int hash = simple_hash(strings[i]);
        printf("Hash of \"%s\": %u\n", strings[i], hash);
    }
}

void test_key_generation() {
    printf("\n=== Test 5: Key Generation ===\n");
    
    char key1[11];
    char key2[11];
    
    generate_key(key1, 10);
    printf("Generated key: %s\n", key1);
    
    generate_key(key2, 10);
    printf("Another key: %s\n", key2);
}

// ============= MAIN =============

int main() {
    printf("========================================\n");
    printf("CRYPTOGRAPHY DEBUGGING PRACTICE\n");
    printf("Find and fix all bugs!\n");
    printf("========================================\n");
    
    test_xor_cipher();
    test_caesar_cipher();
    test_vigenere_cipher();
    test_rc4_cipher();
    test_hash_function(); 
    test_key_generation();
    
    return 0;
}