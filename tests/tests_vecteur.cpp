//
// Created by Pascal Charpentier on 2023-05-11.
//

#include "gtest/gtest.h"
#include "Vecteur.h"

TEST(Vecteur, ajouter_des_elements) {
    Vecteur<int> vt ;
    vt.annexer(20) ;
    vt.annexer(21) ;
    vt.annexer(22) ;
    vt.annexer(23) ;
    vt.annexer(24) ;
    vt.annexer(25) ;
    EXPECT_FALSE(vt.estVide()) ;
    EXPECT_EQ(6, vt.taille()) ;
    EXPECT_EQ(23, vt.lireIndex(3)) ;
}

class VecteurTest : public ::testing::Test {
protected:
    VecteurTest() :  vt() {}

    void SetUp() override {
        vt.annexer(20) ;
        vt.annexer(21) ;
        vt.annexer(22) ;
        vt.annexer(23) ;
        vt.annexer(24) ;
        vt.annexer(25) ;
    }

    Vecteur<int> vt ;
};

TEST_F(VecteurTest, const_iterator_boucle) {
    int valeur = 20 ;
    for (auto it = vt.debutConst(), fin = vt.finConst(); it != fin; ++ it) {
        EXPECT_EQ(valeur, *it) ;
        ++ valeur ;
    }
}

TEST_F(VecteurTest, iterator_boucle) {
    int valeur = 20 ;
    for (auto it = vt.debut(), fin = vt.fin(); it != fin; ++ it) {
        EXPECT_EQ(valeur, *it) ;
        ++ valeur ;
    }
}

TEST_F(VecteurTest, const_iterator_affectation) {
    int valeur = 40 ;
    for (auto it = vt.debut(), fin = vt.fin(); it != fin; ++ it) {
        *it = valeur ;
        EXPECT_EQ(valeur, *it) ;
        ++ valeur ;
    }
}

TEST_F(VecteurTest, inserer_un_element_debut) {
    vt.inserer(33, vt.debut()) ;

}
