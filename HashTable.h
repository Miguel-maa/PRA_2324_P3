#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../Practica 1/PRA_2324_P1/ListLinked.h"  // La tabla hash se implementará como un array de punteros a listas de tipo ListLinked<T> (Práctica 1). 

template <typename V>
class HashTable: public Dict<V> {

    private:
        // Miembros privados

        int n;      // Número de elementos almacenados actualmente en la tabla hash.
        int max;    // Tamaño de la tabla hash (número total de cubetas).
        ListLinked<TableEntry<V>>* table;   // Tabla de cubetas, representada por un array de punteros a listas enlazadas (tipo ListLinked<T>) que almacenan pares clave→valor (tipo TableEntry<V>).


    public:
        // Miembros públicos, incluidos los heredados de Dict<T>
        
        int h(std::string key){ // Función hash que devuelve la posición (cubeta) en la tabla hash de key.
        // Se calculará como el resto de la divisón entre la suma de los valores ASCII numéricos de los caracteres de la clave y el tamaño de la tabla hash (ver nota más abajo).

            int valor = -(int)'0'* key.length();

            for (char c : key){     // 0btenemos el valor ASCII numérico del la clave (Key).
                valor += (int)c;    
            } 

            return valor % max;     // Escalamos el valor obtenido al tamaño de la tabla hash (número total de cubetas).
        }


        HashTable(int size){    // Método constructor. 
        // Reservará memoria dinámica para crear una tabla table de tamaño size, e inicializará los atributos n y max de la clase.

            n = 0;
            max = size;
            table = new ListLinked<TableEntry<V>>[size];
        }


        ~HashTable(){           // Método destructor.
            delete[] table;
        }

        int capacity(){         // Devuelve el número total de cubetas de la tabla.
            return max;
        }


        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){ // Sobrecarga global del operador << para imprimir el contenido de la tabla hash por pantalla. Recuerda incluir la cabecera <ostream> en el .h.

            out << "===================================" << endl;
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << endl;
            out << "===================================" << endl << endl;


            for(int i = 0; i < th.max; i++){
                out << "== Cubeta " << i << " ==" << endl;  // Imprimimos la cubeta indicada
                out << th.table[i] << endl << endl;         // Llamamos a la sobrecarga global del operador << para imprimir una instancia de ListLinked<T> por pantalla.
            }
            
            return out;
        }


        V operator[](std::string key){  // Sobrecarga del operador []. Devuelve el valor correspondiente a key. Si no existe, lanza la excepción std::runtime_error.

            int valor_Key = h(key);     // Obtenemos la posición (cubeta) en la tabla hash en función de la key.

            TableEntry<V> valor(key);   // Creamos una variable de tipo TableEntry<V>, donde almacenamos la clave sin valor.

            if (table[valor_Key].search(valor) == -1){  // Comprobamos si la clave (key) está en el diccionario. Si no existe devuelve un -1.
                throw std::runtime_error("¡Clave (Key) '" + key + "' no encontrada!");   // Si no se encuentra, lanza una excepción
            } 

            int Pos_Key = table[valor_Key].search(valor);           // Guardamos la posición donde se guarda el valor de la clave (Key).
            TableEntry<V> result = table[valor_Key].get(Pos_Key);   // Buscamos el valor que se guarda en la posición de la clave (Key).
            return result.value;    // Retornamos el resultado
        }





        // Métodos heredados de la interfaz Dict<T>

        void insert(std::string key, V value) override{ 	// Inserta el par key->value en el diccionario.

            int valor_Key = h(key);     // Obtenemos la posición (cubeta) en la tabla hash en función de la key.

            TableEntry<V> valor(key, value);  // Creamos una variable de tipo TableEntry<V>, donde almacenamos los pares clave→valor

            if (table[valor_Key].search(valor) != -1){  // Comprobamos si la clave (key) ya existe en el diccionario. Si no existe devuelve un -1.
                throw std::runtime_error("¡La clave (Key) '" + key + "' ya existe!");   // Si ya existe lanzamos una excepción.
            } 

            table[valor_Key].prepend(valor);    // Insertamos la variable de tipo TableEntry<V> al principio de la lista.

            n++;    // Incrementamos el número de elementos almacenados actualmente en la tabla hash.
        } 
        

        V search(std::string key) override{	    // Busca el valor correspondiente a key. Devuelve el valor value asociado si key está en el diccionario.
            
            int valor_Key = h(key);     // Obtenemos la posición (cubeta) en la tabla hash en función de la key.

            TableEntry<V> valor(key);   // Creamos una variable de tipo TableEntry<V>, donde almacenamos la clave sin valor.

            if (table[valor_Key].search(valor) == -1){  // Comprobamos si la clave (key) está en el diccionario. Si no existe devuelve un -1.
                throw std::runtime_error("¡Clave (Key) '" + key + "' no encontrada!");   // Si no se encuentra, lanza una excepción
            } 

            int Pos_Key = table[valor_Key].search(valor);           // Guardamos la posición donde se guarda el valor de la clave (Key).
            TableEntry<V> result = table[valor_Key].get(Pos_Key);   // Buscamos el valor que se guarda en la posición de la clave (Key).
            return result.value;    // Retornamos el resultado
        }


        V remove(std::string key) override{ 	// Elimina el par key->value si se encuentra en el diccionario.
            
            int valor_Key = h(key);     // Obtenemos la posición (cubeta) en la tabla hash en función de la key.

            TableEntry<V> valor(key);   // Creamos una variable de tipo TableEntry<V>, donde almacenamos la clave sin valor.

            if (table[valor_Key].search(valor) == -1){  // Comprobamos si la clave (key) está en el diccionario. Si no existe devuelve un -1.
                throw std::runtime_error("¡Clave (Key) '" + key + "' no encontrada!");   // Si no se encuentra, lanza una excepción
            } 

            n--;    // Decrementamos el número de elementos almacenados actualmente en la tabla hash.

            int Pos_Key = table[valor_Key].search(valor);           // Guardamos la posición donde se guarda el valor de la clave (Key).
            TableEntry<V> result = table[valor_Key].remove(Pos_Key);// Eliminamos el valor que se guarda en la posición de la clave (Key).
            return result.value;    // Retornamos el resultado
        } 
        

        int entries() override{	            // Devuelve el número de elementos que tiene el Diccionario.
            return n;
        } 

};

#endif