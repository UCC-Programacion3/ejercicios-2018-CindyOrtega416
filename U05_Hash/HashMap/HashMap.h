#ifndef HASHMAP_H
#define HASHMAP_H

template<class K, class T>
class HashMap {
private:
    unsigned int hashFunc(K clave);

    static unsigned int hashFuncDefault(K clave) { return 0; };

    unsigned int (*hashFuncP)(K clave);

    T **datos;

    unsigned int tam;

public:
    HashMap(unsigned int k);

    HashMap(unsigned int k, unsigned int (*hashFuncP)(K clave));

    T get(K clave);

    void put(K clave, T valor);

    void remove(K clave);

    ~HashMap();

    bool esVacio();

};

template<class K, class T>
HashMap<K, T>::HashMap(unsigned int k) {
    datos = new T *[k];
    tam = k;
    hashFuncP = this->hashFuncDefault;
    for (int i = 0; i < k; i++)
        datos[i] = nullptr;
}

template<class K, class T>
HashMap<K, T>::HashMap(unsigned int k, unsigned int (*fp)(K)) {
    datos = new T *[k];
    tam = k;
    hashFuncP = fp;
    for (int i = 0; i < k; i++)
        datos[i] = nullptr;
}

template<class K, class T>
HashMap<K, T>::~HashMap() {
    for (int i = 0; i < tam; i++)
        if (datos[i] != nullptr)
            delete datos[i];

}

template<class K, class T>
T HashMap<K, T>::get(K clave) {
    unsigned int idx = hashFunc(clave);

    if (datos[idx] == nullptr)
        throw 404;

    return *datos[idx];
}

template<class K, class T>
void HashMap<K, T>::put(K clave, T valor) {

    unsigned int idx = hashFunc(clave);

    if (datos[idx] != nullptr)
        throw 1;

    datos[idx] = new T;
    *datos[idx] = valor;
}

template<class K, class T>
void HashMap<K, T>::remove(K clave) {
    unsigned int idx = hashFunc(clave);
    if (datos[idx] == nullptr)
        throw 404;

    delete datos[idx];

}

template<class K, class T>
bool HashMap<K, T>::esVacio() {
    return false;
}

template<class K, class T>
unsigned int HashMap<K, T>::hashFunc(K clave) {
    return hashFuncP(clave) % tam;
}


#endif //HASHMAP_H