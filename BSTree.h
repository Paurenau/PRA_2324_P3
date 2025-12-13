#ifndef BSTREE_H
#define BSTREE_H

#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
	private:
		BSNode<T> *root;
		int nelem;

	public:
		// Constructor del arbol
		BSTree() {
			root = nullptr;
			nelem = 0;
		}

		// Devuelve el tamaño del ABB
		int size() const {
			return nelem;
		}

/* ===================== BÚSQUEDA DE ELEMENTOS ============================= */

	private:
		// Método recursivo de búsqueda de un elemento
		BSNode<T> *search(BSNode <T> *n, T e) const {
			// Si el puntero apunta a null, lanzo una excepcion
			if(n == nullptr) {
				throw std::runtime_error("No se ha encontrado el elemento");
			}
			// Los elementos más pequeños que el anterior están colocados a la izquierda
			else if(e < n->elem){
				return search(n->left, e);
			}
			// Los elementos más grandes que el anterior están colocados a la derecha
			else if(e > n->elem) {
				return search(n->right, e);
			}
			// Si encontró el elemento devuelvo el nodo
			else {
				return n;
			}
		}

	public:	

		// Devuelve el elemento del nodo devuelto por la funcion privada y recursiva
		T search(T e) const {
			return search(root, e)->elem;
		}


		T operator[](T e) const {
			return search(e);	
		}

/* ==================== INSERCIÓN DE ELEMENTOS ======================== */

	private:
		// Método recursivo que inserta el elemento en el arbol ordenado
		// Devuelve la cabeza del nodo (el anterior)
		BSNode<T> *insert(BSNode<T> *n, T e) {
			// Si no apunta a ninguno
			if(n == nullptr) {
                                return new BSNode<T>(e);
                        }
			// Si ya se encuentra en el árbol
			else if(e == n->elem) {
				throw std::runtime_error("El elemento ya se encuentra en el árbol");
			} 
			// Los menores al anterior se encuentran a la izquierda
			else if(e < n->elem) {
				n->left =  insert(n->left, e);
			}
			// Los mayores al anterior se encuentran a la derecha
			else if(e > n->elem) {
				n->right = insert(n->right, e);
			}	
			// Devuelvo n
			return n;
		}

	public:
		// Método lanzadera
		void insert(T e) {
			root = insert(root, e);
			nelem++;
		}

/* =================== RECORRIDO E IMPRESIÓN DEL ÁRBOL =============== */

	private:
		//  Recorrido inorden (Imprime los elementos de menor a mayor)
		void print_inorder(std::ostream &out, BSNode<T> *n) const {
			// Primero imprime los de la izquierda ya que son los más pequeños
			// Luego imprime los de la derecha
			if(n != nullptr) {
				print_inorder(out, n->left);
				out << n->elem << " ";
				print_inorder(out, n->right);
			}
			// El padre hace recorrer el camino de la izquierda, se imprime y luego hace el 
			// camino de la derecha
		}

	public:
		// Método lanzadera
		friend std::ostream &operator<<(std::ostream &out, const BSTree<T> &bst) {
			bst.print_inorder(out, bst.root);
			return out;
		}

/* ==================== ELIMINACIÓN DE OBJETOS ========================= */
		
	private: 
		// Método recursivo que devuelve el máximo de un árbol
		T max(BSNode<T> *n) const {
			if(n == nullptr) {
				throw std::runtime_error("No hay raíz por la que empezar a buscar");
			} else if (n->right != nullptr){
				// El elemento máximo se encuentra a la derecha del todo
				// Si no hemos llegado ahí seguimos recorriendo el árbol
				return max(n->right);
			} else {
				// Si ha lleago al final devuelvo el elemento
				return n->elem;
			}
		}

		BSNode<T> *remove_max(BSNode<T> *n) {
			if(n == nullptr) {
				throw std::runtime_error("No se puede eliminar el máximo sin árbol");
			}
			// Recorro el arbol hasta llegar al elemento más a la derecha (el mayor)
			// Si tiene elementos a la izquierda se reemplazan
			else if(n->right == nullptr) {
				return n->left;
			} else {
				n->right = remove_max(n->right);
				return n;
			}
		}

		BSNode<T> *remove(BSNode<T> *n, T e) {
			if(n == nullptr) {
				throw std::runtime_error("No existe el elemento a eliminar");
			}
			// Búsqueda del elemento
			else if(e < n->elem) {
				n->left = remove(n->left, e);
			} else if(e > n->elem) {
				n->right = remove(n->right, e);
			} 
			// Se encuentra el elemento
			else {
				// Si tiene nodos a la derecha y a la izquierda 
				// elimino el nodo y lo sustituyo por el maximo del arbol izquierdo
				if(n->left != nullptr && n->right != nullptr) {
					n->elem = max(n->left);
					n->left = remove_max(n->left);
				} 
				// En el caso de que haya 1 ó 0 descendientes
				else {
					// Si n->left no es nullptr, se sustituye por el
					// Si n->left es nullptr, se sustituye por el de la derecha
					// Si n->left es nullptr y n->right es nullptr, n va a pasar a valer nullpr
					// (Se elimina)
					n = (n->left != nullptr) ? n->left : n->right;
				}
			}
			// Devuelvo el nodo modificado
			return n;
		}

	public:
		// Método lanzadera
		void remove(T e) {
			root = remove(root, e);
			nelem--;
		}

/* ==================== DESTRUCCIÓN ===================== */

	private:
		// Método recursivo para liberación de memoria dinámica
		void delete_cascada(BSNode<T> *n) {
			if(n != nullptr) {
				delete_cascada(n->left);
				delete_cascada(n->right);
				delete n;
			}
		}

	public:
		// Método lanzadera
		~BSTree() {
			delete_cascada(root);
		}
		
};
	
#endif