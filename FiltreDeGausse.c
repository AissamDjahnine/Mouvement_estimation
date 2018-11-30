#include "FiltreDeGausse.h"

/** Methode de calcul des coifficients du filtre de GAUSS
*/
float FiltreGausse(int x,int y)
{
    float result=((x*x)+(y*y))/(-2.*sigma*sigma);
    result=exp(result)*(1./(2.*pi*sigma*sigma));
    return result;
}

/** Methode de creation de matrice de GAUSS
  */
float ** MatriceDeGausse()
{
    int i,j;
    float somme=0;

    float ** mat=CreateTable(filter_gauss_dim,filter_gauss_dim);
    for(i=0;i<filter_gauss_dim;i++)
    {
        for(j=0;j < filter_gauss_dim; j++)
        {
            mat[i][j]=FiltreGausse(i-1,j-1);
            somme+=mat[i][j];
        }
    }

    //normalisation de la matrice de gauss
    for(i=0;i<filter_gauss_dim;i++)
         for(j=0;j < filter_gauss_dim; j++)
            mat[i][j]/=somme;

    return mat;
}


/** Methode de produit de convolution
*/
float** produitDeConv(float** I, int dimX,int dimY,float** K)
{
    float** result=CreateTable(dimX,dimY);
    int x,y;
    for(x=1;x<dimX-1;x++)
    {
        for(y=1;y<dimY-1;y++)
        {
            result[x][y] =  I[x+1][y+1]*K[0][0] + I[x][y+1]*K[1][0] + I[x-1][y+1]*K[2][0]+
                            I[x+1][y]*K[0][1]   + I[x][y]*K[1][1]   + I[x-1][y]*K[2][1]+
                            I[x+1][y-1]*K[0][2] + I[x][y-1]*K[1][2] + I[x-1][y-1]*K[2][2];
        }
    }
    return result;
}

/** Methode de Produit des matrices terme par terme
*/
float** ProduitMatTermeParTerme(float** terme1,float** terme2,int dimX,int dimY )
{
    int i,j;
    float**result=CreateTable(dimX,dimY);
    for(i=0;i<dimX;i++)
        for(j=0;j<dimY;j++)
            result[i][j]=terme1[i][j]*terme2[i][j];

    return result;
}

/** Methode de calcul U et V
*/
void CalcU_V_avecConv(float**U,float**V,float** ubar ,float ** vbar, float** W , float** Ix , float** Iy,float** It,int lignes,int cols)
{
    //recadrement de l'image
    if(lignes%2!=0)
        lignes--;
    if(cols%2!=0)
        cols--;

    float** IyIt=ProduitMatTermeParTerme(Iy,It,lignes,cols);
    float** IxIt=ProduitMatTermeParTerme(Ix,It,lignes,cols);
    float** IxIy=ProduitMatTermeParTerme(Ix,Iy,lignes,cols);
    float** IxIx=ProduitMatTermeParTerme(Ix,Ix,lignes,cols);
    float** IyIy=ProduitMatTermeParTerme(Iy,Iy,lignes,cols);

    float** temp=produitDeConv(IyIt,lignes,cols,W); // temp = Covolution [ (Iy*It) , W ]
    float** temp1=produitDeConv(IxIt,lignes,cols,W);     // temp1 = Covolution [ (Ix*It) , W ]
    float** temp2=produitDeConv(IxIy,lignes,cols,W);     // temp2 = Covolution [ (Ix*Iy) , W ]
    float** temp3=produitDeConv(IxIx,lignes,cols,W);        // temp3 = Covolution [ (Ix*Ix) , W ]
    float** temp4=produitDeConv(IyIy,lignes,cols,W);      // temp4 = Covolution [ (Iy*Iy) , W ]

    int i,j;
    for(i=0;i<lignes;i++)
    {
        for(j=0;j<cols;j++)
        {
            //denomunateur
            //temp5 = alpha+Convolution [ (Ix*Ix) , W]+ Convolution [ (Iy*Iy) , W]
            float temp5=alpha_u+temp3[i][j]+temp4[i][j];
            //relation avec u
            //temp6= Covolution [ (Ix*It) , W ]+ ( Covolution [ (Ix*Iy) , W ] * vbar)+ (Covolution [ (Ix*Ix) , W ] * ubar)
            float temp6=temp1[i][j]+(temp2[i][j]*vbar[i][j])+(temp3[i][j]*ubar[i][j]);
            //relation avec v
            //temp7= Covolution [ (Iy*It) , W ]+ ( Covolution [ (Iy*Iy) , W ] * vbar)+ (Covolution [ (Ix*Iy) , W ] * ubar)
            float temp7=temp[i][j]+(temp4[i][j]*vbar[i][j])+(temp2[i][j]*ubar[i][j]);
            // formule de U
            U[i][j]=ubar[i][j]-(temp6/temp5);
            // formule de V
            V[i][j]=vbar[i][j]-(temp7/temp5);
        }
    }
}

/** Methode de reduction des dimensions
*/
float **reduire_res(float** entree,int lignes,int cols)
{
    float** sortie=CreateTable(lignes/2,cols/2);
    int i,j;
    for(i=0;i<lignes-2; i=i+2)
         for(j=0;j<cols-2; j=j+2)
            sortie[i/2][j/2]=entree[i][j];

    return sortie;
}

/** Methode de agrandissement des dimensions
*/
float** augment_res(float** entree,int lignes,int cols) // matrice sortie
{
    float** sortie=CreateTable(lignes*2,cols*2);
    int i,j;
    for(i=0;i<lignes-2;i=i+2)
        for(j=0;j<cols-2;j=j+2)
            sortie[i*2][j*2]=entree[i][j];

    return sortie;
}





