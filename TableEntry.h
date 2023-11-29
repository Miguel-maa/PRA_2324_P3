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
        TableEntry(std::string key, V value){   // Método constructor con el par clave->valor.
            this->key = key;
            this->value = value;
        }

        TableEntry(std::string key){    // Crea una entrada solo con clave (sin valor). 
            this->key = key;
        }

        TableEntry(){       // Crea una entrada con la clave "" (cadena vacía) y sin valor.
            this->key = "";
        }

        friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){  // Sobrecarga global del operador == para determinar que dos instancias de TableEntry son iguales solo si comparten la misma clave (con independencia del valor).

            if(te1.key == te2.key){
                return true;
            } else {
                return false;
            } 
        }

        friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){  // Sobrecarga global del operador != para determinar que dos instancias de TableEntry son diferentes solo si sus claves son distintas (con independencia del valor).

            if(te1.key != te2.key){
                return true;
            } else {
                return false;
            } 
        }

        friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te){ // Sobrecarga global del operador << para imprimir el contenido de la entrada (par clave->valor) por pantalla. Recuerda incluir la cabecera <ostream> en el .h.  

            out << "('" << te.key << "' => " << te.value << ")"; 

            return out;
        }
};

#endif