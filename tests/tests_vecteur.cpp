//
// Created by Pascal Charpentier on 2023-05-11.
//

#include "gtest/gtest.h"
#include "Vecteur.h"

TEST(Vecteur, constructeur_defaut_no_throw) {
    EXPECT_NO_THROW(Vecteur<int> v) ;
}
