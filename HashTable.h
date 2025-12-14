#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Dict.h"
#include "TableEntry.h"

//
// LISTA ENLAZADA (BUCKET)
// Guarda colisiones dentro de una posición de la tabla
//
template <typename V>
class ListLinked {
private:
    std::vector<TableEntry<V>> data;

public:
    // Inserta una entrada en el bucket
    void insert(const TableEntry<V>& e) {
        // Comprobar clave duplicada
        for (auto &x : data) {
            if (x.key == e.key) {
                throw std::runtime_error("Clave duplicada: " + e.key);
            }
        }
        data.push_back(e);
    }

    // Busca una clave en el bucket
    bool find(const std::string& key, V& out) const {
        for (auto &e : data) {
            if (e.key == key) {
                out = e.value;
                return true;
            }
        }
        return false;
    }

    // Elimina una clave del bucket
    bool remove(const std::string& key, V& out) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it->key == key) {
                out = it->value;
                data.erase(it);
                return true;
            }
        }
        return false;
    }

    // Mostrar contenido del bucket
    friend std::ostream& operator<<(std::ostream& out, const ListLinked<V>& list) {
        for (auto &e : list.data) {
            out << e << " ";
        }
        return out;
    }
};


//
// TABLA HASH
//
template <typename V>
class HashTable : public Dict<V> {

private:
    int n;                  // número de entradas
    int max;                // tamaño de la tabla
    ListLinked<V>* table;   // array de buckets

    // Función hash
    int h(const std::string& key) const {
        int sum = 0;
        for (char c : key) sum += int(c);
        return sum % max;
    }

public:
    // Constructor
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<V>[size];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    int capacity() const {
        return max;
    }

    // Insertar par (key, value)
    void insert(std::string key, V value) override {
        int idx = h(key);
        table[idx].insert(TableEntry<V>(key, value));
        n++;
    }

    // Buscar valor por clave
    V search(std::string key) override {
        int idx = h(key);
        V value;
        if (!table[idx].find(key, value)) {
            throw std::runtime_error("Clave no encontrada: " + key);
        }
        return value;
    }

    // Eliminar clave
    V remove(std::string key) override {
        int idx = h(key);
        V value;
        if (!table[idx].remove(key, value)) {
            throw std::runtime_error("Clave no encontrada: " + key);
        }
        n--;
        return value;
    }

    // Número de entradas
    int entries() override {
        return n;
    }

    // Operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Mostrar tabla completa
    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
        for (int i = 0; i < th.max; i++) {
            out << i << ": " << th.table[i] << "\n";
        }
        return out;
    }
};

#endif


