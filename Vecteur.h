//
// Created by Pascal Charpentier on 2023-05-11.
//

#ifndef VECTEURTD_VECTEUR_H
#define VECTEURTD_VECTEUR_H

template <typename T>
class Vecteur {
private:
    static const size_t DEF_CAPACITE = 2 ;
    constexpr static const double DEF_FACTEUR = 2.0 ;

public:
    class iterator ;

    class const_iterator {
    public:
        explicit const_iterator(T* adr) ;

        virtual const T& operator* () const ;
        const_iterator operator ++ () ;
        const const_iterator operator ++ (int) ;
        const_iterator operator + (size_t) ;

        const_iterator operator -- () ;
        bool operator == (const const_iterator& rhs) const ;
        bool operator != (const const_iterator& rhs) const ;

        explicit operator iterator () const {return iterator(const_iterator::adresse) ; }

    protected:
        T* adresse ;
    };

    class iterator : public const_iterator {
    public:
        explicit  iterator(T* adr) : const_iterator(adr) {}
        T& operator* () const override ;

    };

    Vecteur() ;
    explicit Vecteur(size_t cap) ;

    const_iterator debutConst() const ;
    const_iterator finConst() const ;
    iterator debut() const ;
    iterator fin() const ;

    ~Vecteur() ;

    void annexer(const T& valeur) ;
    iterator inserer(const T& valeur, iterator pos) ;

    size_t taille() const ;
    bool estVide() const ;
    const T& lireIndex(size_t index) const ;

private:
    T* base ;
    size_t cardinal ;
    size_t capacite ;

    void transferer_vers(T* nouvelle) ;
    T* reallouer(size_t n) ;
    void augmenter_capacite(double facteur = DEF_FACTEUR) ;
    void decaler(size_t offset, iterator pos) ;

};

template<typename T>
T &Vecteur<T>::iterator::operator*() const {
    return *const_iterator::adresse ;
}

template<typename T>
Vecteur<T>::const_iterator::const_iterator(T *adr) : adresse(adr) {

}

template<typename T>
const T &Vecteur<T>::const_iterator::operator*() const {
    return *adresse ;
}

template<typename T>
typename Vecteur<T>::const_iterator Vecteur<T>::const_iterator::operator++() {
    ++ adresse ;
    return *this ;
}

template<typename T>
const typename Vecteur<T>::const_iterator Vecteur<T>::const_iterator::operator++(int) {
    auto old = adresse ;
    ++ adresse ;
    return Vecteur::const_iterator(old);
}

template<typename T>
typename Vecteur<T>::const_iterator Vecteur<T>::const_iterator::operator+(size_t decalage) {
    return const_iterator(adresse + decalage) ;
}

template<typename T>
bool Vecteur<T>::const_iterator::operator==(const Vecteur<T>::const_iterator &rhs) const {
    return adresse == rhs.adresse ;
}

template<typename T>
bool Vecteur<T>::const_iterator::operator!=(const Vecteur<T>::const_iterator &rhs) const {
    return !(rhs == *this) ;
}

template<typename T>
typename Vecteur<T>::const_iterator Vecteur<T>::const_iterator::operator--() {
    -- adresse ;
    return *this ;
}


template<typename T>
Vecteur<T>::Vecteur() : base(new T[DEF_CAPACITE]), cardinal(0), capacite(DEF_CAPACITE) {

}


template<typename T>
Vecteur<T>::Vecteur(size_t cap) : base(new T[cap]), cardinal(0), capacite(cap) {

}

template<typename T>
T* Vecteur<T>::reallouer(size_t n) {
    T* nouvelle = new T[n] ;
    return nouvelle ;
}

template<typename T>
void Vecteur<T>::transferer_vers(T* nouvelle) {
  for (size_t i = 0; i < cardinal; ++i) {
      nouvelle[i] = base[i] ;
  }
}

template<typename T>
void Vecteur<T>::augmenter_capacite(double facteur) {
    auto nouvelle_capacite = static_cast<size_t>(facteur * capacite) ;
    auto nouvelle_base = reallouer(nouvelle_capacite) ;
    transferer_vers(nouvelle_base) ;
    capacite = nouvelle_capacite ;
    delete[] base ;
    base = nouvelle_base ;
}

template<typename T>
void Vecteur<T>::annexer(const T &valeur) {
    if (cardinal == capacite) augmenter_capacite() ;
    base[cardinal] = valeur ;
    ++ cardinal ;
}

template<typename T>
size_t Vecteur<T>::taille() const {
    return cardinal ;
}

template<typename T>
bool Vecteur<T>::estVide() const {
    return cardinal == 0 ;
}

template<typename T>
const T &Vecteur<T>::lireIndex(size_t index) const {
    if (index >= cardinal) throw std::invalid_argument("lireIndex: out_of_range") ;
    return *(base + index) ;
}

template<typename T>
Vecteur<T>::~Vecteur() {
    delete base ;
}

template<typename T>
typename Vecteur<T>::const_iterator Vecteur<T>::debutConst() const {
    return Vecteur::const_iterator(base) ;
}

template<typename T>
typename Vecteur<T>::const_iterator Vecteur<T>::finConst() const {
    return Vecteur::const_iterator(base + cardinal) ;
}

template<typename T>
typename Vecteur<T>::iterator Vecteur<T>::debut() const {
    return iterator(base) ;
}

template<typename T>
typename Vecteur<T>::iterator Vecteur<T>::fin() const {
    return iterator(base + cardinal) ;
}

template<typename T>
typename Vecteur<T>::iterator Vecteur<T>::inserer(const T &valeur, iterator pos) {
    if (cardinal == capacite) augmenter_capacite() ;
    decaler(1, pos) ;
    *pos = valeur ;
    ++ cardinal ;
    return pos ;
}

template<typename T>
void Vecteur<T>::decaler(size_t offset, Vecteur::iterator pos) {
    for (auto it = fin(), debut = pos; it != debut; ) {
        -- it ;
        auto result = static_cast<iterator> (it + offset) ;
        result.operator *() = *it ;
    }
}


#endif //VECTEURTD_VECTEUR_H
