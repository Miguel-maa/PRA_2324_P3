#ifndef DICT_H
#define DICT_H
#include <string>

template <typename V> 
class Dict {
    public:
        // ... aquí los métodos virtuales puros

        virtual void insert(std::string key, V value) = 0;	// Inserta el par key->value en el diccionario.
        virtual V search(std::string key) = 0;	// Busca el valor correspondiente a key. Devuelve el valor value asociado si key está en el diccionario.
        virtual V remove(std::string key) = 0;	// Elimina el par key->value si se encuentra en el diccionario.
        virtual int entries() = 0;	            // Devuelve el número de elementos que tiene el Diccionario.
};

#endif