#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

using namespace std;

template <typename V> 
class TableEntry {
    public:
        // miembros públicos

        /** Atributos **/
        std::string key;    // El elemento clave del par. 
        V value;            // El elemento valor del par.


        /** Métodos **/

        // Método constructor con el par clave->valor.
        TableEntry(std::string key, V value){   
            this->key = key;
            this->value = value;
        }


        // Crea una entrada solo con clave (sin valor).
        TableEntry(std::string key){     
            this->key = key;
        }


        // Crea una entrada con la clave "" (cadena vacía) y sin valor.
        TableEntry(){       
            this->key = "";
        }


        // Sobrecarga global del operador == para determinar que dos instancias de TableEntry son iguales solo si comparten la misma clave (con independencia del valor).
        friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){  

            if(te1.key == te2.key){
                return true;
            } else {
                return false;
            } 
        }


        // Sobrecarga global del operador != para determinar que dos instancias de TableEntry son diferentes solo si sus claves son distintas (con independencia del valor).
        friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){  

            if(te1.key != te2.key){
                return true;
            } else {
                return false;
            } 
        }


        // Sobrecarga global del operador << para imprimir el contenido de la entrada (par clave->valor) por pantalla. Recuerda incluir la cabecera <ostream> en el .h.  
        friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te){ 

            out << "('" << te.key << "' => " << te.value << ")"; 

            return out;
        }


        // Sobrecarga global del operador < para comparar el orden de los objetos de dicha clase y buscar las posiciones en el ABB de dichos elementos.  
        friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2){ 

            if(te1.key < te2.key){
                return true;
            } else {
                return false;
            } 
        }


        // Sobrecarga global del operador > para comparar el orden de los objetos de dicha clase y buscar las posiciones en el ABB de dichos elementos.  
        friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2){ 

            if(te1.key > te2.key){
                return true;
            } else {
                return false;
            } 
        }
};

#endif