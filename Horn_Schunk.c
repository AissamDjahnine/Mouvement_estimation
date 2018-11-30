#include"Horn_Schunk.h"
/** Methode de calcul de Ubar( resp Vbar )
*/
void compute_bar(float **ubar,float** U,int width, int height)
{
	int i,j;
	for (i = 1; i < height-1; i++)
	for (j = 1; j < width-1; j++)
		ubar[i][j] = (1.0/8) * (U[i-1][j-1]+U[i-1][j]+U[i-1][j+1]
                          +U[i][j-1]+U[i][j+1]
                          +U[i+1][j-1]+U[i+1][j]+U[i+1][j+1]);
}
/** Methode de calcul des gradients ( spatials , temporel)  Ix,Iy,It
*/
void gradient(float** image1,float** image2,float** Ix,float**Iy,float** It,int h,int w)
{
    int i,j;
    for(i = 0; i < h-1; i++)
        {
            for(j = 0; j < w-1; j++)
            {
                if(j==0) Ix[i][j]=image1[i][1]-image1[i][0];
                else if(j==w-1) Ix[i][j]=image1[i][w-1]-image1[i][w-2];
                else Ix[i][j]=0.5*(image1[i][j+1]-image1[i][j-1]);

                if(i==0) Iy[i][j]=image1[1][j]-image1[0][j];
                else if(j==w-1) Iy[i][j]=image1[h-1][j]-image1[h-2][j];
                else Iy[i][j]=0.5*(image1[i+1][j]-image1[i-1][j]);

                It[i][j]=image2[i][j]-image1[i][j];
            }
        }
}

/** Methode de calcul d'une seule iteration de U ( resp V )
*/
void compute_one_iteration(float** Ix,float** Iy,float** It,float** U,float** V,float **ubar,float** vbar,int width,int height)
{

    compute_bar(ubar,U,width,height);
    compute_bar(vbar,V,width,height);

    int i,j;
	for (i = 0; i < height-1; i++)
	for (j = 0; j < width-1; j++)
    {
        float temp=-1.*(Ix[i][j]*ubar[i][j]+Iy[i][j]*vbar[i][j]+It[i][j]);
        temp /= (alpha+ Ix[i][j]*Ix[i][j]+Iy[i][j]*Iy[i][j]);
        U[i][j]=U[i][j]+Ix[i][j]*temp;
        V[i][j]=V[i][j]+Iy[i][j]*temp;

    }

}

/** Methode de Recadrement de l'image ( la matrice )
*/
float R(float** x,int h,int w,int i, int j){  // Reencadrement de l'image  w= largeur h=hauteur

	if (i < 0) i = 0;
	if (j < 0) j = 0;
	if (i >= w) i = w - 1;
	if (j >= h) j = h - 1;
	return x[i][j];
}


/** Methode de calcul LES MATRICES : U , V
*/
void calcul_u_v(float** u,float** v,float** Ix,float** Iy,float** It,float** ubar,float** vbar,int h,int w,int n){  // procedure qui calcule u bar et v bar par la methode de horn & schrunk

   if(w%2!=0)w--;
   if(h%2!=0)h--;

    float fu,fv;
    int i=0,j=0;


n=0;
    while (n<=Nmax ) {

          //  compute_one_iteration(Ix,Iy,It,u,v,ubar,vbar,w,h);
        for (i = 0; i < h-1; i++){
            for (j = 0; j < w-1; j++){
            ubar[i][j] = (1.0/8) * ( R(u,h,w,i-1,j-1)+ R(u,h,w,i-1,j)+ R(u,h,w,i-1,j-1)+
                                     R(u,h,w,i-1,j+1)+ R(u,h,w,i,j-1)+ R(u,h,w,i,j+1)+
                                    R(u,h,w,i+1,j-1)+ R(u,h,w,i+1,j+1));

            vbar[i][j] = (1.0/8) * ( R(v,h,w,i-1,j-1)+ R(v,h,w,i-1,j)+ R(v,h,w,i-1,j-1)+
                                     R(v,h,w,i-1,j+1)+ R(v,h,w,i,j-1)+ R(v,h,w,i,j+1)+
                                    R(v,h,w,i+1,j-1)+ R(v,h,w,i+1,j+1));


            fu= (Ix[i][j]*ubar[i][j]+Iy[i][j]*vbar[i][j]+It[i][j])/(alpha+Ix[i][j]*Ix[i][j]+Iy[i][j]*Iy[i][j]);
            fv= (Ix[i][j]*ubar[i][j]+Iy[i][j]*vbar[i][j]+It[i][j])/(alpha+Ix[i][j]*Ix[i][j]+Iy[i][j]*Iy[i][j]);
            u[i][j]=ubar[i][j]-Ix[i][j]*fu;
            v[i][j]=vbar[i][j]-Iy[i][j]*fv;

            }
        }
        n++;
    }
}
