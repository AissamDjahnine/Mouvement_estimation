#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include<stdlib.h>
#include<stdio.h>

// Constructeur et Destructeur des matrices
/** Methode de creation d'une matrice des flottans
  * @param rows nombre de lignes de la matrice
  * @param cols nombre de colonnes de la matrice
  * @return une matrice de taille rows*cols prete a l'emploi
  */
float** CreateTable(int rows,int cols);

// Methode de lecture / ecriture
/** Methode de lecture d'une matrice a partir d'un fichier Txt
  * @param path nom du fichier -chemin d'accés-
  * @return une matrice float de dimension : height*width
  */

float** LireTable(char* path);


/** Methode d'ecriture d'une matrice
  * @param MatToBeWritten la matrice à écrire dans un fichier Txt
  * @param height nombre de lignes de la matrice à écrire
  * @param width nombre de colonnes de la matrice à écrire
  * @param path nom du fichier -chemin d'accés-
  */
void WriteTable(float** MatToBeWritten,int height,int width,char* path);

/** Methode de destruction d'une image
  * @param tab matrice à detruire / desallouer
  * @param rows nombre des lignes de la matrice a desallouer

  */
void FreeTable(float** tab, int rows);

/** Methode de destruction des matrices
  * @param matrices
  * @param leurs dimensions

  */
    void freeAll (float**mat1,float**mat2,float**mat3,float**mat4,float**mat5,float**mat6,float**mat7,int DIM);



#endif // MATRIX_H_INCLUDED
