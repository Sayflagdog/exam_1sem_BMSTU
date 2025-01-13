using namespace std;
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <vector>

using namespace std;

class Block {
public:
    int index;
    string data;
    string previousHash;
    string hash;
    time_t timestamp;
    int nonce;
    int difficulty;

    Block(int idx, const string& d, const string& prevHash, int diff)
        : index(idx), data(d), previousHash(prevHash), timestamp(time(nullptr)), nonce(0), difficulty(diff) {
        hash = calculateHash();
        mineBlock();
    }

    string calculateHash() const {
        stringstream ss;
        ss << index << data << previousHash << timestamp << nonce;
        return sha256(ss.str());
    }

    void mineBlock() {
        string target(difficulty, '0');
        while (hash.substr(0, difficulty) != target) {
            nonce++;
            hash = calculateHash();
        }
    }

private:
    string sha256(const string& input) const {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, input.c_str(), input.size());
        SHA256_Final(hash, &sha256);
        stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        return ss.str();
    }
};



class Blockchain {
private:
    vector<Block> chain;
    int difficulty;

    Block createGenesisBlock() {
        return Block(0, "Генезис Блок", "0", difficulty);
    }

public:
    Blockchain(int diff) : difficulty(diff) {
        chain.push_back(createGenesisBlock());
    }

    void addBlock(const string& data) {
        const Block& lastBlock = chain.back();
        chain.emplace_back(chain.size(), data, lastBlock.hash, difficulty);
    }

    bool isChainValid() const {
        for (size_t i = 1; i < chain.size(); ++i) {
            const Block& current = chain[i];
            const Block& previous = chain[i - 1];
            if (current.hash != current.calculateHash() || current.previousHash != previous.hash) {
                return false;
            }
        }
        return true;
    }


    void printChain() const {
        for (const auto& block : chain) {
            cout << "Блок " << block.index << ":\n";
            cout << "Метка времени: " << block.timestamp << "\n";
            cout << "Данные: " << block.data << "\n";
            cout << "Хэш: " << block.hash << "\n";
            cout << "Предыдущий Хэш: " << block.previousHash << "\n";
            cout << "Нонсенс: " << block.nonce << "\n\n";
        }
    }
};

void printMenu() {
    cout << "1. Добавить блок\n";
    cout << "2. Проверить цепочку\n";
    cout << "3. Вывести цепочку\n";
    cout << "4. Выйти\n";
}

int main() {
    Blockchain blockchain(4);
    int choice;
    string data;

    while (true) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите данные транзакции: ";
                cin.ignore();
                getline(cin, data);
                blockchain.addBlock(data);
                cout << "Блок добавлен!\n";
                break;
            case 2:
                if (blockchain.isChainValid()) {
                    cout << "Цепочка блоков валидна.\n";
                } else {
                    cout << "Цепочка блоков не валидна.\n";
                }
                break;
            case 3:
                blockchain.printChain();
                break;
            case 4:
                return 0;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}
