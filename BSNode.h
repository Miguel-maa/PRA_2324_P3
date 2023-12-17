#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
        // miembros públicos

        T elem;      // El elemento de tipo T almacenado en el nodo.
        BSNode<T>* izq;     // Puntero al nodo sucesor izquierdo.
        BSNode<T>* der;    // Puntero al nodo sucesor derecho.


        // Método constructor que crea un BSNode con el elemento elem y los punteros a los nodos sucesores left y  right proporcionados (nulos por defecto). 
        BSNode(T elem, BSNode<T>* izq=nullptr, BSNode<T>* der=nullptr){
            this->elem = elem;
            this->izq = izq;
            this->der = der;
        }

        // Sobrecarga global del operador << para imprimir el nodo por pantalla. Por simplicidad, puedes limitarte a imprimir el atributo elem. Recuerda incluir la cabecera <ostream> en el .h.
        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn){
            
            out << "elem = ('" << bsn.elem << "')"; 

            return out;
        }
};

#endif