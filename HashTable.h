#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Dict.h"
#include "TableEntry.h"



template <typename V>
class ListLinked {     
private:
    std::vector<TableEntry<V>> data;
    
    
public:
    void insert(std::string key, V value) override {
    int idx = h(key);
    V aux;

    if (table[idx].find(key, aux)) {
        throw std::runtime_error("Clave duplicada: " + key);
    }

    table[idx].insert(TableEntry<V>(key, value));
    n++;
}


    bool find(const std::string& key, V& out) const {
        for (auto &e : data)
            if (e.key == key) { out = e.value; return true; }
        return false;
    }

    bool remove(const std::string& key, V& out) {
        for (auto it = data.begin(); it != data.end(); it++) {
            if (it->key == key) {
                out = it->value;
                data.erase(it);
                return true;
            }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, const ListLinked<V>& list) {
        for (auto &e : list.data) out << e << " ";
        return out;
    }


};


template <typename V>
class HashTable : public Dict<V> {

private:
    int n;
    int max;
    ListLinked<V>* table;

    int h(const std::string& key) const {
        int sum = 0;
        for (char c : key) sum += int(c);
        return sum % max;
    }

public:

    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<V>[size];
    }

    ~HashTable() {
        delete[] table;
    }

    int capacity() const {
        return max;
    }

    

    void insert(std::string key, V value) override {
        int idx = h(key);
        table[idx].insert(TableEntry<V>(key, value));
        n++;
    }

    V search(std::string key) override {
        int idx = h(key);
        V value;
        if (!table[idx].find(key, value))
            throw std::runtime_error("Clave no encontrada: " + key);
        return value;
    }

    V remove(std::string key) override {
        int idx = h(key);
        V value;
        if (!table[idx].remove(key, value))
            throw std::runtime_error("Clave no encontrada: " + key);
        n--;
        return value;
    }

    int entries() override {
        return n;
    }

    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
        for (int i = 0; i < th.max; i++) {
            out << i << ": " << th.table[i] << "\n";
        }
        return out;
    }


    V operator[](std::string key) {

    int idx = h(key);
    V value;
    if (!table[idx].find(key, value))
        throw std::runtime_error("Clave no encontrada: " + key);
    return value;

    }

};

#endif
