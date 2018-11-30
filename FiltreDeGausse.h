# ifndef FiltreDeGausse_h_
# define FiltreDeGausse_h_
#include"Matrix.h"
#include <math.h>
#define pi 3.14159265358979323846
#define N_pyr 100
#define alpha_u 15
#define  filter_gauss_dim 3
#define sigma 0.8

/** Methode de calcul des coifficients du filtre de GAUSS
  * @param x Point 1
  * @param y Point 2
  * @return  coifficient de GAUSS
  */
float FiltreGausse(int x,int y);

/** Methode de creation de matrice de GAUSS
  * @return return une matrice 3x3 de GAUSS
  */
float** MatriceDeGausse();

/** Methode de produit de convolution
  * @param mat matrice pour produit de convolution
  * @param dimX nombre de lignes de matrice mat
  * @param dimY nombre de colonnes de matrice mat
  * @param MatDeGauss Filtre de GAUSS 3*3
  * @return Produit de convolution [ mat '*' Filtre de GAUSS ]
  */
float **produitDeConv(float**mat, int dimX,int dimY,float** MatDeGauss);

/** Methode de Produit des matrices terme par terme
  * @param matrice terme1
  * @param matrice terme2
  * @param dimX nombre de lignes de matrice terme 1( resp terme 2)
  * @param dimY nombre de colonnes de matrice terme 1( resp terme 2)
  * @return Matrice de taille dimX*dimY
  */
float** ProduitMatTermeParTerme(float** terme1,float** terme2,int dimX,int dimY );

/** Methode de calcul U et V
  * @param U comme entree
  * @param V comme entree
  * @param ubar
  * @param vbar
  * @param W matrice de filtre de GAUSS
  * @param le gradient spatial suivant Ix
  * @param le gradient spatial suivant Iy
  * @param le gradient temporel It
  * @param dimX nombre de lignes de matrice U (resp V)
  * @param dimY nombre de colonnes de matrice U (resp V)
  */
void CalcU_V_avecConv(float**U,float**V,float** ubar ,float ** vbar,
                       float** W , float** Ix , float** Iy,float** It,int lignes,int cols);

/** Methode de reduction des dimensions
  * @param entree matrice float taille lignes/cols
  * @param lignes nombre de lignes de matrice d'entrée
  * @param cols nombre de colonnes de matrice d'entrée
  * @return matrice float taille (lignes/2) * (cols/2)
  */
float **reduire_res(float** entree,int lignes,int cols);

/** Methode de agrandissement des dimensions
  * @param entree matrice float taille lignes/cols
  * @param lignes nombre de lignes de matrice d'entrée
  * @param cols nombre de colonnes de matrice d'entrée
  * @return matrice float taille (lignes*2) * (cols*2)
  */
float** augment_res(float** entree,int lignes,int cols);
# endif
