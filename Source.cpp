#include "Header.h"

static void printCat() {
    std::cout << " /\\_/\\\n";
    std::cout << "( o.o )\n";
    std::cout << " > ^ <\n";
}

// ЗАДАЧА 1: КОД ХЭММИНГА 
void Hamming15() {
    using namespace std;
    cout << "\nЗАДАЧА 1: КОД ХЭММИНГА\n";
    string data = "1010010111";
    cout << "Сообщение по варианту: " << data << endl;

    int m = data.length();
    int r = 0;
    while ((1 << r) < m + r + 1) r++;

    int n = m + r;
    vector<int> hamming(n + 1, 0);

    cout << "\n ПОСТРОЕНИЕ КОДА ХЭММИНГА \n";
    cout << "Информационных битов (m) = " << m << endl;
    cout << "Контрольных битов (r) = " << r << endl;
    cout << "Общая длина кода (n) = " << n << endl;
    cout << "\nПозиции контрольных битов (степени двойки): ";
    for (int i = 0; i < r; i++) {
        cout << (1 << i) << " ";
    }
    cout << endl;

    // Заполняем информационные биты
    int dataIdx = 0;
    for (int i = 1; i <= n; i++) {
        bool isPowerOfTwo = (i & (i - 1)) == 0;
        if (!isPowerOfTwo) {
            hamming[i] = data[dataIdx++] - '0';
        }
    }
    for (int i = 1; i <= n; i++) {
        bool isPowerOfTwo = (i & (i - 1)) == 0;
    }

    // Вычисляем контрольные биты
    cout << "\n ВЫЧИСЛЕНИЕ КОНТРОЛЬНЫХ БИТОВ \n";
    for (int i = 0; i < r; i++) {
        int pos = 1 << i;
        int sum = 0;
        cout << "\nКонтрольный бит p" << pos << ":\n";
        cout << "  Проверяемые позиции: ";
        for (int j = pos+1; j <= n; j++) {
            if (j & pos) {
                cout << j << " ";
            }
        }
        cout << endl;

        for (int j = pos; j <= n; j++) {
            if (j & pos) {
                if (j != pos) {
                    cout << "  позиция " << j << " = " << hamming[j] << endl;
                    sum ^= hamming[j];
                }
            }
        }
        hamming[pos] = sum;
        cout << "  XOR сумма = " << sum << " -> p" << pos << " = " << sum << endl;
    }

    cout << "\n Код Хэмминга: \n";
    for (int i = 1; i <= n; i++) {
        cout << hamming[i];
    }
    cout << endl;

    // Имитация ошибки
    int errorBit;
    cout << "\n ИМИТАЦИЯ ОШИБКИ \n";
    cout << "Введите номер бита для имитации ошибки (1-" << n << ", 0 - без ошибки): ";
    cin >> errorBit;

    if (errorBit >= 1 && errorBit <= n) {
        cout << "Инвертируем:\n";
        cout << "  Было: " << hamming[errorBit] << endl;
        hamming[errorBit] ^= 1;
        cout << "  Стало: " << hamming[errorBit] << endl;

        cout << "\nКод с ошибкой: ";
        for (int i = 1; i <= n; i++) {
            cout << hamming[i];
        }
        cout << endl;

        // Вычисление синдрома
        cout << "\n ВЫЧИСЛЕНИЕ ОШИБКИ \n";
        int syndrome = 0;
        for (int i = 0; i < r; i++) {
            int pos = 1 << i;
            int sum = 0;
            cout << "\nПроверка p" << pos << ":\n";
            cout << "  Проверяемые позиции: ";
            for (int j = pos; j <= n; j++) {
                if (j & pos) {
                    cout << j << " ";
                }
            }
            cout << endl;

            for (int j = pos; j <= n; j++) {
                if (j & pos) {
                    cout << "  позиция " << j << " = " << hamming[j] << endl;
                    sum ^= hamming[j];
                }
            }
            cout << "  XOR сумма = " << sum << endl;

            if (sum) {
                cout << "  -> НЕСООТВЕТСТВИЕ! Ошибка (XOR должна быть 0)\n";
                syndrome += pos;
            }
            else {
                cout << "  -> OK\n";
            }
        }

        cout << "\n РЕЗУЛЬТАТ \n";
        cout << "Синдром (номер ошибочного бита, складывается из индексов XOR = 1): " << syndrome << endl;

        if (syndrome != 0 && syndrome <= n) {
            cout << "Инвертируем бит на позиции \n";
            cout << "  Было: " << hamming[syndrome] << endl;
            hamming[syndrome] ^= 1;
            cout << "  Стало: " << hamming[syndrome] << endl;

            cout << "\nИсправленный код: ";
            for (int i = 1; i <= n; i++) {
                cout << hamming[i];
            }
            cout << endl;

            // Извлечение исправленного сообщения
            string recovered;
            for (int i = 1; i <= n; i++) {
                bool isPowerOfTwo = (i & (i - 1)) == 0;
                if (!isPowerOfTwo) {
                    recovered += to_string(hamming[i]);
                }
            }
            cout << "Исправленное сообщение: " << recovered << endl;

            if (recovered == data) {
                cout << "Сообщение успешно восстановлено!\n";
            }
            else {
                cout << "Сообщение восстановлено с ошибкой!\n";
            }
        }
        else if (syndrome != 0) {
            cout << "Синдром = " << syndrome << ", но это значение выходит за пределы кода (1.." << n << ")\n";
            cout << "Ошибка не может быть исправлена (возможно, ошибка в контрольном бите или множественная ошибка)\n";
        }
        else {
            cout << "Синдром = 0 -> ошибок не обнаружено\n";
        }
    }
    else if (errorBit == 0) {
        cout << "Ошибка не имитировалась\n";
    }
    else {
        cout << "Неверный номер бита\n";
    }
    printCat();
}

//  ЗАДАЧА 2: КОД ХАФФМАНА 

// Реализация HuffmanNode
HuffmanNode::HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
HuffmanNode::HuffmanNode(int f, HuffmanNode* l, HuffmanNode* r) : ch(0), freq(f), left(l), right(r) {}
HuffmanNode::~HuffmanNode() {}

bool HuffmanNode::isLeaf() const { return !left && !right; }

std::string HuffmanNode::toString() const {
    if (ch) return std::string(1, ch) + "(" + std::to_string(freq) + ")";
    return "*(" + std::to_string(freq) + ")";
}

// Реализация HuffmanTree
HuffmanTree::HuffmanTree() : root(nullptr) {}

HuffmanTree::HuffmanTree(const HuffmanTree& other) : root(nullptr) {
    if (other.root) root = copyTree(other.root);
}

HuffmanTree::~HuffmanTree() { deleteTree(root); }

HuffmanTree& HuffmanTree::operator=(const HuffmanTree& other) {
    if (this != &other) {
        deleteTree(root);
        root = other.root ? copyTree(other.root) : nullptr;
    }
    return *this;
}

void HuffmanTree::deleteTree(HuffmanNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

HuffmanNode* HuffmanTree::copyTree(HuffmanNode* node) {
    if (!node) return nullptr;
    HuffmanNode* newNode;
    if (node->ch) {
        newNode = new HuffmanNode(node->ch, node->freq);
    }
    else {
        newNode = new HuffmanNode(node->freq, nullptr, nullptr);
    }
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

void HuffmanTree::getFrequencies(const std::string& text, std::map<char, int>& freq) {
    freq.clear();
    for (char c : text) freq[c]++;
}

void HuffmanTree::buildFromText(const std::string& text) {
    deleteTree(root);
    root = nullptr;

    std::map<char, int> freq;
    getFrequencies(text, freq);

    auto cmp = [](HuffmanNode* a, HuffmanNode* b) { return a->freq > b->freq; };
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, decltype(cmp)> pq(cmp);

    for (auto& p : freq) {
        pq.push(new HuffmanNode(p.first, p.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* parent = new HuffmanNode(left->freq + right->freq, left, right);
        pq.push(parent);
    }

    if (!pq.empty()) root = pq.top();
}

void HuffmanTree::buildCodesRecursive(HuffmanNode* node, std::string code, std::map<char, std::string>& codes) {
    if (!node) return;
    if (node->ch) codes[node->ch] = code;
    buildCodesRecursive(node->left, code + "0", codes);
    buildCodesRecursive(node->right, code + "1", codes);
}

void HuffmanTree::getCodes(std::map<char, std::string>& codes) {
    codes.clear();
    buildCodesRecursive(root, "", codes);
}

HuffmanNode* HuffmanTree::getRoot() const { return root; }

void HuffmanTree::printTreeSideRecursiveConsole(HuffmanNode* node, int level) {
    if (!node) return;
    printTreeSideRecursiveConsole(node->right, level + 1);
    for (int i = 0; i < level; i++) std::cout << "      ";
    std::cout << std::right << std::setw(12) << node->toString() << std::endl;
    printTreeSideRecursiveConsole(node->left, level + 1);
}

void HuffmanTree::printTreeSideConsole() {
    std::cout << "\nГрафическое представление дерева Хаффмана:\n";
    std::cout << "(Корень справа, листья слева)\n\n";
    printTreeSideRecursiveConsole(root, 0);
}

void HuffmanTree::printTreeSideRecursive(HuffmanNode* node, int level, std::ofstream& file, int width) {
    if (!node) return;
    printTreeSideRecursive(node->right, level + 1, file, width);
    for (int i = 0; i < level; i++) file << std::string(width, ' ');
    file << std::right << std::setw(width) << node->toString() << std::endl;
    printTreeSideRecursive(node->left, level + 1, file, width);
}

void HuffmanTree::printTreeSideFile(const std::string& filename, int width) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) return;
    file << "\nГрафическое представление дерева Хаффмана:\n";
    file << "(Корень справа, листья слева)\n\n";
    printTreeSideRecursive(root, 0, file, width);
    file.close();
}

std::string HuffmanTree::encode(const std::string& text) {
    std::map<char, std::string> codes;
    getCodes(codes);
    std::string result;
    for (char c : text) {
        if (codes.find(c) != codes.end()) result += codes[c];
    }
    return result;
}

std::string HuffmanTree::decode(const std::string& encoded) {
    if (!root) return "";
    std::string result;
    HuffmanNode* current = root;
    for (char bit : encoded) {
        if (bit == '0') current = current->left;
        else current = current->right;
        if (current->isLeaf()) {
            result += current->ch;
            current = root;
        }
    }
    return result;
}

void HuffmanTree::clear() {
    deleteTree(root);
    root = nullptr;
}

void Huffman1() {
    using namespace std;
    cout << "\n ЗАДАЧА 2: КОД ХАФФМАНА\n";

    string text = "УВИДИМ ВАДИМА И УДИВИМ";
    cout << "Текст по варианту: \"" << text << "\"\n";

    HuffmanTree tree;
    tree.buildFromText(text);

    map<char, int> freq;
    for (char c : text) freq[c]++;

    cout << "\nЧастоты символов:\n";
    for (auto& p : freq) {
        cout << "  '" << p.first << "' : " << p.second << endl;
    }

    map<char, string> codes;
    tree.getCodes(codes);

    cout << "\nКоды символов:\n";
    for (auto& p : codes) {
        cout << "  '" << p.first << "' -> " << p.second << endl;
    }

    tree.printTreeSideConsole();

    string encoded = tree.encode(text);
    int uniformBits = text.length() * 8;
    int huffmanBits = encoded.length();

    cout << "\n РЕЗУЛЬТАТ \n";
    cout << "Исходный текст: " << text << endl;
    cout << "Закодированное сообщение (" << huffmanBits << " бит):\n";
    for (size_t i = 0; i < encoded.length(); i++) {
        cout << encoded[i];
        if ((i + 1) % 8 == 0 && i != encoded.length() - 1);
    }
    cout << endl;

    cout << "\nДлина при равномерном кодировании (8 бит/символ): " << uniformBits << " бит\n";
    cout << "Длина при кодировании Хаффмана: " << huffmanBits << " бит\n";
    cout << "Экономия: " << uniformBits - huffmanBits << " бит\n";

    printCat();
}

// ЗАДАЧА 3: ШИФР МОРЗЕ 

int inputMethod() {
    int method;
    std::cout << "\nСпособ ввода данных:\n";
    std::cout << "1. Ввод с консоли\n";
    std::cout << "2. Случайные данные\n";
    std::cout << "3. Из файла\n";
    std::cout << "Выбор: ";
    std::cin >> method;
    return method;
}

void Morse3() {
    using namespace std;

    cout << "\n ЗАДАЧА 3: ШИФР МОРЗЕ \n";

    int lang;
    cout << "\nВыберите язык:\n";
    cout << "1. Русский\n";
    cout << "2. Английский\n";
    cout << "Выбор: ";
    cin >> lang;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Ошибка ввода!\n";
    }

    map<char, string> morse;
    map<string, char> revMorse;

    if (lang == 1) {
        morse['А'] = ".-";     morse['Б'] = "-...";   morse['В'] = ".--";
        morse['Г'] = "--.";    morse['Д'] = "-..";    morse['Е'] = ".";
        morse['Ж'] = "...-";   morse['З'] = "--..";   morse['И'] = "..";
        morse['Й'] = ".---";   morse['К'] = "-.-";    morse['Л'] = ".-..";
        morse['М'] = "--";     morse['Н'] = "-.";     morse['О'] = "---";
        morse['П'] = ".--.";   morse['Р'] = ".-.";    morse['С'] = "...";
        morse['Т'] = "-";      morse['У'] = "..-";    morse['Ф'] = "..-.";
        morse['Х'] = "....";   morse['Ц'] = "-.-.";   morse['Ч'] = "---.";
        morse['Ш'] = "----";   morse['Щ'] = "--.-";   morse['Ъ'] = "--.--";
        morse['Ы'] = "-.--";   morse['Ь'] = "-..-";   morse['Э'] = "..-..";
        morse['Ю'] = "..--";   morse['Я'] = ".-.-";
        morse[' '] = "/";
        for (auto& p : morse) revMorse[p.second] = p.first;
        cout << "\nВыбран русский язык\n";
    }
    else {
        morse['A'] = ".-";     morse['B'] = "-...";   morse['C'] = "-.-.";
        morse['D'] = "-..";    morse['E'] = ".";      morse['F'] = "..-.";
        morse['G'] = "--.";    morse['H'] = "....";   morse['I'] = "..";
        morse['J'] = ".---";   morse['K'] = "-.-";    morse['L'] = ".-..";
        morse['M'] = "--";     morse['N'] = "-.";     morse['O'] = "---";
        morse['P'] = ".--.";   morse['Q'] = "--.-";   morse['R'] = ".-.";
        morse['S'] = "...";    morse['T'] = "-";      morse['U'] = "..-";
        morse['V'] = "...-";   morse['W'] = ".--";    morse['X'] = "-..-";
        morse['Y'] = "-.--";   morse['Z'] = "--..";
        morse[' '] = "/";
        for (auto& p : morse) revMorse[p.second] = p.first;
        cout << "\nВыбран английский язык\n";
    }

    cout << "\n= ШИФРОВАНИЕ =\n";
    string originalText;
    int methodEncode = inputMethod();

    if (methodEncode == 1) {
        cin.ignore();
        cout << "Введите текст для шифрования: ";
        getline(cin, originalText);
    }
    else if (methodEncode == 2) {
        vector<string> words;
        if (lang == 1) {
            words = { "ПРИВЕТ", "МИР", "МОРЗЕ", "АЗБУКА", "ШИФР" };
        }
        else {
            words = { "HELLO", "WORLD", "MORSE", "ALPHABET", "CIPHER" };
        }
        originalText = "";
        int wordCount = 2 + rand() % 4;
        for (int i = 0; i < wordCount; i++) {
            if (i > 0) originalText += " ";
            originalText += words[rand() % words.size()];
        }
        for (char& c : originalText) c = toupper(c);
        cout << "\nСгенерированный текст: " << originalText << endl;
    }
    else if (methodEncode == 3) {
        string filename;
        cout << "Введите имя файла: ";
        cin >> filename;
        ifstream file(filename);
        if (file) {
            cin.ignore();
            getline(file, originalText);
            file.close();
            for (char& c : originalText) c = toupper(c);
            cout << "\nТекст из файла: " << originalText << endl;
        }
        else {
            cout << "Ошибка открытия файла!\n";
            return;
        }
    }
    else {
        cout << "Неверный выбор!\n";
        return;
    }

    for (char& c : originalText) c = toupper(c);

    string encoded = "";
    for (char c : originalText) {
        if (morse.count(c)) {
            encoded += morse[c] + " ";
        }
        else if (c == ' ') {
            encoded += "/ ";
        }
        else {
            encoded += "? ";
        }
    }

    cout << "\n РЕЗУЛЬТАТ ШИФРОВАНИЯ \n";
    cout << "Исходный текст: " << originalText << endl;
    cout << "Шифр Морзе: " << encoded << endl;

    cout << "\n= ДЕШИФРОВКА =\n";
    string morseInput;
    int methodDecode = inputMethod();

    if (methodDecode == 1) {
        cin.ignore();
        cout << "Введите строку Морзе (символы разделены пробелом, слова — /):\n";
        getline(cin, morseInput);
    }
    else if (methodDecode == 2) {
        vector<string> cods;
        if (lang == 1) {
            cods = { "... --- ...", "-- .. .-.", "-- --- .-. --.. ." };
        }
        else {
            cods = { "... --- ...", ".-- --- .-. .-.. -..", "-- --- .-. ... ." };
        }
        morseInput = "";
        int wordCount = 2 + rand() % 3;
        for (int i = 0; i < wordCount; i++) {
            if (i > 0) morseInput += " / ";
            morseInput += cods[rand() % cods.size()];
        }
        cout << "\nСгенерированный случайный код Морзе:\n";
        cout << morseInput << endl;
    }
    else if (methodDecode == 3) {
        string filename;
        cout << "Введите имя файла с кодом Морзе: ";
        cin >> filename;
        ifstream file(filename);
        if (file) {
            cin.ignore();
            getline(file, morseInput);
            file.close();
            cout << "\nКод Морзе из файла:\n" << morseInput << endl;
        }
        else {
            cout << "Ошибка открытия файла!\n";
            return;
        }
    }
    else {
        cout << "Неверный выбор!\n";
        return;
    }

    string decoded = "";
    string token = "";
    vector<string> unknownTokens;

    for (char c : morseInput) {
        if (c == ' ') {
            if (!token.empty()) {
                if (token == "/") {
                    decoded += ' ';
                }
                else if (revMorse.count(token)) {
                    decoded += revMorse[token];
                }
                else {
                    decoded += '?';
                    unknownTokens.push_back(token);
                }
                token = "";
            }
        }
        else {
            token += c;
        }
    }

    if (!token.empty()) {
        if (token == "/") {
            decoded += ' ';
        }
        else if (revMorse.count(token)) {
            decoded += revMorse[token];
        }
        else {
            decoded += '?';
            unknownTokens.push_back(token);
        }
    }

    cout << "\n РЕЗУЛЬТАТ ДЕШИФРОВКИ \n";

    if (unknownTokens.empty()) {
        cout << "Расшифрованный текст: " << decoded << endl;
        cout << "Декодирование выполнено успешно!\n";
    }
    else {
        cout << "ОШИБКА ДЕШИФРОВКИ!\n";
        cout << "Следующие коды Морзе не найдены в словаре:\n";
        for (const string& t : unknownTokens) {
            cout << "   \"" << t << "\"\n";
        }
    }
    printCat();
}