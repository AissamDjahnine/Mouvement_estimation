#ifndef _Horn_Schunk_h_
#define _Horn_Schunk_h_
#define alpha 15
#define Nmax 50 //NOMBRE DES ITERATIONS

/** Methode de calcul de Ubar( resp Vbar )
  * @param ubar ( resp vbar ) a calculer
  * @param U MATRICE DE TAILLE height*width
  * @param height nombre de lignes de l'image
  * @param width nombre de colonnes de l'image
  */
void compute_bar(float **ubar,float** U,int width, int height);

/** Methode de calcul des gradients ( spatials , temporel)  Ix,Iy,It

  * @param image1 MATRICE float de la 1 er image
  * @param image2 MATRICE float de la 2 eme image
  * @param Ix Gradient Spatial suivant X a calculer
  * @param IY Gradient Spatial suivant Y a calculer
  * @param It Gradient TEMPOREL a calculer
  * @param height nombre de lignes de l'image
  * @param width nombre de colonnes de l'image
  */

void gradient(float** image1,float** image2,float** Ix,float**Iy,float** It,int h,int w);

/** Methode de calcul d'une seule iteration de U ( resp V )
  * @param Ix Gradient Spatial suivant X
  * @param Iy Gradient Spatial suivant Y
  * @param It Gradient temporel
  * @param U MATRICE DE TAILLE height*width a remplir
  * @param V MATRICE DE TAILLE height*width a remplir
  * @param ubar MATRICE DE TAILLE height*width a remplir
  * @param vbar MATRICE DE TAILLE height*width a remplir
  * @param height nombre de lignes de l'image
  * @param width nombre de colonnes de l'image
 */

void compute_one_iteration(float** Ix,float** Iy,float** It,float** U,float** V,float **ubar,float** vbar,int width,int height);

/** Methode de Recadrement de l'image ( la matrice )
  * @param h nombre de lignes de l'image
  * @param w nombre de colonnes de l'image
  * @param i position suivant X
  * @param j position suivant Y
  * @return x un float du la valeur de matrice recadrée
  */

float R(float** x,int h,int w,int i, int j);
/** Methode de calcul LES MATRICES : U , V
  * @param U MATRICE DE TAILLE height*width a remplir
  * @param V MATRICE DE TAILLE height*width a remplir
  * @param Ix Gradient Spatial suivant X
  * @param Iy Gradient Spatial suivant Y
  * @param It Gradient temporel
  * @param ubar MATRICE DE TAILLE height*width
  * @param vbar MATRICE DE TAILLE height*width
  * @param h nombre de lignes de l'image
  * @param w nombre de colonnes de l'image
  * @param n nombre max d'iterations
  * @param eps condition d'arret
  */

void calcul_u_v(float** u,float** v,float** Ix,float** Iy,float** It,float** ubar,float** vbar,int h,int w,int n);



#endif

