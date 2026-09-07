#include <iostream>
#include <string.h>
#include <locale>

using namespace std;

void direct_search(wstring text, wstring x) {
    int count = 0;
    wcout << L"==================Метод прямого поиска==================" << endl;
    wcout << L"Исходный текст: " << text << endl << L"Искомое слово: " << x << endl;
    for (size_t i = 0; i <= text.length() - x.length(); i++) {
        bool found = true;
        for (size_t j = 0; j < x.length(); j++) {
            count++;
            if (text[i+j] != x[j]) {
                found = false;
                break;
            }
        }
        if (found){
            wcout << L"Найдено на позиции: " << i << endl;
            wcout << L"Количество посимвольных сравнений: "<< count << endl;
        }
    }
}

size_t hash_func(wstring word) {
    size_t hash = 0;
    size_t q = 7;
    size_t basis = 256;
    for(wchar_t c : word) {
        hash = (hash * basis) / q;
    }
    return hash;
}

void rabin_carp_search(wstring text, wstring x) {
    wcout << L"===================Метод Рабина-Карпа===================" << endl;
    wcout << L"Исходный текст: " << text << endl << L"Искомое слово: " << x << endl;
    size_t hash_x = hash_func(x);
    size_t basis = 7;
    
    if (text.length() < x.length()) {
        return;
    }
    
    wstring fragment = text.substr(0, x.length());
    size_t hash_word_in_text = hash_func(fragment);

    size_t step = 1;

    for (size_t i = 0; i < x.length() - 1; i++) {
        step *= basis;
    }

    int count_hash = 0;
    int count_char = 0;
    bool found = false;

    for (size_t i = 0; i <= text.length() - x.length(); i++) {
        count_hash++;
        if (hash_word_in_text == hash_x) {
            bool match = true;
            for (size_t j =0; j < x.length(); j++) {
                count_char++;
                if (text[i + j] != x[j]) {
                    match = false;
                    break;// коллизия
                }

            }
            if (match) {
                found = true;
                wcout << L"Найдено на позиции: " << i << endl;
                wcout << L"Количество посимвольных сравнений: " << count_char << endl << L"Количество сравнений хешей: " << count_hash << endl;
            }
        }
        if (i < text.length() - x.length()) {
            hash_word_in_text = (hash_word_in_text - text[i] * step) * basis + text[i + x.length()];
        }
    }
    if (!found) {
        wcout << L"Слово не найдено" << endl;
    }

}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wstring text = L"Горячий кофе согревал руки. Нет ничего лучше горячего кофе в холодные весенние вечера.";
    wstring x = L"руки";
    direct_search(text, x);
    rabin_carp_search(text, x);
}
