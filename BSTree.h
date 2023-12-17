#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        /**** Miembros privados *****/


        int nelem;  // Número de elementos almacenados en el ABB. 
        BSNode<T>* root;  //  Nodo raíz del ABB.


        /*** Búsqueda de elementos ***/

        // Método recursivo para la búsqueda elementos en el ABB. Busca y devuelve el elemento e de tipo T si se encuentra en el (sub-)árbol cuya raíz es n, de lo contrario lanza una std::runtime_error. 
        BSNode<T>* search(BSNode<T>* n, T e) const{  

            if (n == nullptr){  // Elemento no encontrado
                throw std::runtime_error("¡Elemento no encontrado!");   // Si no se encuentra, lanza una excepción
            } else if (n->elem < e){    // Valor del elemento superior al del elemento del nodo
                return search(n->der, e);
            } else if (n->elem > e){    // Valor del elemento inferior al del elemento del nodo
                return search(n->izq, e);
            } else {        // Elemento encontrado
                return n;
            } 
        }



        /*** Inserción de elementos ***/

        // Método recursivo para la inserción ordenada de elementos. Inserta el elemento e de tipo T de manera ordenada en el (sub-)árbol cuya raíz es n. Devuelve el nodo que encabeza dicho (sub-)árbol modificado. Si el elemento e ya existe, lanza un std::runtime_error. 
        BSNode<T>* insert(BSNode<T>* n, T e){
            
            if (n == nullptr){  // Si llegamos al final del arbol insertamos elemento 
                nelem ++;   // Incrementamos el número de elementos almacenados en el ABB. 
                return new BSNode<T>(e);    
            } else if (n->elem == e){   // Si el elemnto ya a sido insertado, lanzamos una excepción
                throw std::runtime_error("¡Elemento duplicado!");
            } else if (n->elem < e){    // Valor del elemento superior al del elemento del nodo
                n->der = insert(n->der, e);
            } else {        // Valor del elemento inferior al del elemento del nodo
                n->izq = insert(n->izq, e);
            }

            return n;
        }



        /*** Recorrido e impresión del árbol ***/

        // Recorrido inorden o simétrico del (sub-)árbol cuya raíz es n para mostrar a través de out los elementos ordenados de menor a mayor. 
        void print_inorder(std::ostream &out, BSNode<T>* n) const{
            
            if (n != nullptr) {     // Si no hemos llegado al final del arbol (nodos)
                print_inorder(out, n->izq); // Recorre el hijo izquierdo
                out << n->elem << " ";      // Procesa el nodo actual
                print_inorder(out, n->der); // Recorre el hijo derecho
            }
        }


        /*** Eliminación de elementos ***/
        
        // Método recursivo para la eliminación de elementos. Elimina el elemento e del (sub-)árbol cuya raíz es n. Devuelve el nodo que encabeza dicho (sub-)árbol modificado. En caso de eliminar un nodo con dos sucesores (izquierdo y derecho), aplicará la politica de reemplazo por el elemento máximo del subárbol izquierdo. Para ello, se apoyará en los métodos privados auxiliares max() y remove_max(). Si el elemento e no existe, lanza un std::runtime_error.
        BSNode<T>* remove(BSNode<T>* n, T e){
            
            if (n == nullptr){  // Elemento no encontrado
                throw std::runtime_error("¡Elemento no encontrado!");   // Si no se encuentra, lanza una excepción
            } else if (n->elem < e){    // Valor del elemento superior al del elemento del nodo
                n->der = remove(n->der, e);
            } else if (n->elem > e){    // Valor del elemento inferior al del elemento del nodo
                n->izq = remove(n->izq, e); 
            } else {        // Elemento encontrado
                nelem --;   // Decrementamos el número de elementos almacenados en el ABB.
                if (n->izq != nullptr && n->der != nullptr){    // 2 desc.
                    n->elem = max(n->izq);       // Devolvemos el elemento de máximo valor del sub-árbol izquierdo
                    n->izq = remove_max(n->izq); 
                } else {  // 1 ó 0 descendientes
                    n = (n->izq != nullptr)? n->izq: n->der;
                } 
            } 

            return n;   // Devuelve el nodo que encabeza dicho (sub-)árbol modificado. 
        }


        // Método recursivo que devuelve el elemento de máximo valor contenido en el (sub-)árbol cuya raíz es n. 
        T max(BSNode<T>* n) const{
            
            if (n == nullptr){  // Llegada al final del arbor (nodos) y no hemos ncontardo el elemento de máximo valor
                throw std::runtime_error("¡No quedan elementos!");   // Si no quedan elementos, lanza una excepción
            } else if (n->der != nullptr){  // Si no hemos encontardo el elemento de máximo valor, volvemos a llamar a la función
                return max(n->der);
            } else {    // Devolvemos el elemento de máximo valor del sub-árbol izquierdo
                return n->elem;
            } 
        }


        // Método recursivo que elimina el elemento de máximo valor contenido en el (sub-)árbol cuya raíz es n. 
        BSNode<T>* remove_max(BSNode<T>* n){
            if (n->der == nullptr){ 
                return n->izq;
            } else {        
                n->der = remove_max(n->der);
                return n;
            } 
        }



        /*** Destrucción ***/
        
        // Método recursivo para liberación de la memoria dinámica ocupada por los objetos de tipo BSNode<T> que conforman el (sub-)árbol cuya raíz es n.
        void delete_cascade(BSNode<T>* n){
            if(n != nullptr){   // Si no hemos llegado al final del arbol (nodos)
                delete_cascade(n->der); // Recorremos los nodos derechos
                delete_cascade(n->izq); // Recorremos los nodos izquierdos
                delete n;   // Eliminamos los nodos
            }
        }




    public:
        /**** Miembros públicos *****/


        /*** Creación y tamaño ***/

        // Método constructor. Crea un ABB vacío.
        BSTree(){
            this->nelem = 0;
            this->root = nullptr;
        }


        // Devuelve el número de elementos nelem del ABB.
        int size() const{
            return nelem;
        }



        /*** Búsqueda de elementos ***/

        // Busca y devuelve el elemento e de tipo T en el ABB.  Actúa como método lanzadera del método privado recursivo search(BSNode<T>* n, T e). 
        T search(T e) const{    // función lanzadera
            return search(root, e)->elem; // r -> nodo raíz
        }


        // Sobrecarga del operador[]. Actúa como interfaz al método search(T e).
        T operator[](T e) const{    
            return search(root, e)->elem;;
        }



        /*** Inserción de elementos ***/

        // Inserta el elemento e de tipo T de manera ordenada en el  ABB. Actúa como método lanzadera del método privado recursivo insert(BSNode<T>* n, T e).
        void insert(T e){   // función lanzadera 
            root = insert(root, e); // r -> nodo raíz
        }


        
        /*** Recorrido e impresión del árbol ***/

        // Sobrecarga del operador << para mostrar a través de out los contenidos del ABB bst, realizando un recorrido inorden o simétrico del árbol para mostrar los elementos ordenados de menor a mayor. Delega en el método privado recursivo print_inorder(). 
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            
            bst.print_inorder(out, bst.root);   // función lanzadera

            return out;
        }



        /*** Eliminación de elementos ***/
        
        // Elimina el elemento e de tipo T del ABB. Actúa como método lanzadera del método privado recursivo remove(BSNode<T>* n, T e).
        void remove(T e){
            root = remove(root, e);   // función lanzadera;
        }



        /*** Destrucción ***/
        
        // Método destructor. Delega en el método privado recursivo delete_cascade().
        ~BSTree(){
            delete_cascade(root);   // función lanzadera
        }

};

#endif