#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <iostream>
#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        /**** Miembros privados *****/

        BSTree<TableEntry<V>>* tree;    // ABB con elementos de tipo TableEntry<V> para gestionar los elementos de un diccionario.



    public:
        /**** Miembros públicos *****/

        // Constructor. Crea un ABB vacío con memoria dinámica
        BSTreeDict(){
            tree = new BSTree<TableEntry<V>>;
        }


        // Método destructor. Se encargará de liberar la memoria dinámica ocupada por el ABB tree.
        ~BSTreeDict(){
            delete tree;
        }


        // Sobrecarga global del operador << para imprimir el contenido del Diccionario por pantalla. 
        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
            
            out << *(bs.tree);  // Llamamos a la sobrecarga global del operador << para imprimir una instancia de ListLinked<T> por pantalla.
            
            return out;
        }


        // Sobrecarga del operador[]. Actúa como interfaz al método de interfaz heredado search(std::string key).
        V operator[](std::string key){

            TableEntry<V> valor(key);   // Creamos una variable de tipo TableEntry<V>, donde almacenamos la clave sin valor.
            
            TableEntry<V> result = tree->search(valor);   // Buscamos el valor que se guarda en la posición de la clave (Key).
            
            return result.value;    // Retornamos el resultado
        }





        // Métodos heredados de la interfaz Dict<T>

        // Inserta el par key->value en el diccionario.
        void insert(std::string key, V value) override{ 	

            TableEntry<V> valor(key, value);  // Creamos una variable de tipo TableEntry<V>, donde almacenamos los pares clave→valor

            tree->insert(valor);    // Insertamos la variable de tipo TableEntry<V> en el arbol.
        } 
        

        // Busca el valor correspondiente a key. Devuelve el valor value asociado si key está en el diccionario.
        V search(std::string key) override{	    
            
            TableEntry<V> valor(key);   // Creamos una variable de tipo TableEntry<V>, donde almacenamos la clave sin valor.

            TableEntry<V> result = tree->search(valor);   // Buscamos el valor que se guarda en la posición de la clave (Key).

            return result.value;
        }


        // Elimina el par key->value si se encuentra en el diccionario.
        V remove(std::string key) override{ 	
            
            TableEntry<V> valor(key);   // Creamos una variable de tipo TableEntry<V>, donde almacenamos la clave sin valor.

            TableEntry<V> result = tree->search(valor);   // Buscamos el valor que se guarda en la posición de la clave (Key).
            
            tree->remove(valor);   // Eliminamos el valor que se guarda en la posición de la clave (Key).

            return result.value;    // Retornamos el resultado
        } 
        

        // Devuelve el número de elementos que tiene el Diccionario.
        int entries() override{	            
            return tree->size();
        } 
        
};

#endif