#include"myBmpGris.h"
#include"Matrix.h"
#include"Horn_Schunk.h"
#include "FiltreDeGausse.h"

int main()
{
    printf("/*\tP6 ESTIMATION DU MOUVEMENT\t*/ \n ");
    printf("\nObjectif du projet :\n Estimer le mouvement apparant des pixels entre 2 images successives\n en utilisant des methodes differentielles basees sur le flux optique\n\n");
    printf("1- METHODE 1 : \t Horn & Schunck\n");
    int i,j;

    BmpImg image_1;
    FILE* fichier1=fopen("image1.txt","w");
    if (fichier1!=NULL)
    {
        image_1=readBmpImage("image1.bmp");
        fprintf(fichier1,"%d %d\n",image_1.dimX,image_1.dimY);
        for(i=0;i<image_1.dimX;i++)
            for(j=0;j<image_1.dimY;j++)
                fprintf(fichier1,"%d ",image_1.img[i][j]);
    }
    printf("lecture de la 1 er image\n");



    BmpImg image_2;
    FILE* fichier2=fopen("image2.txt","w");
    if (fichier2!=NULL)
    {
        image_2=readBmpImage("image2.bmp");
        fprintf(fichier2,"%d %d\n",image_2.dimX,image_1.dimY);
        for(i=0;i<image_2.dimX;i++)
            for(j=0;j<image_2.dimY;j++)
                fprintf(fichier2,"%d ",image_2.img[i][j]);
    }
    printf("lecture de la 2 eme image\n");





    float** A=LireTable("image1.txt");
    float** B=LireTable("image2.txt");
    float**Ix=CreateTable(image_1.dimX,image_1.dimY);
    float**Iy=CreateTable(image_1.dimX,image_1.dimY);
    float**It=CreateTable(image_1.dimX,image_1.dimY);
    gradient(A,B,Ix,Iy,It,image_1.dimX,image_1.dimY);
    WriteTable(Ix,image_1.dimX,image_1.dimY,"Ix.txt");
    printf("Ecriture de la matrice Ix dans un fchier : Ix.txt\n");
    WriteTable(Iy,image_1.dimX,image_1.dimY,"Iy.txt");
    printf("Ecriture de la matrice Iy dans un fchier : Iy.txt\n");
    WriteTable(It,image_1.dimX,image_1.dimY,"It.txt");
    printf("Ecriture de la matrice It dans un fchier : It.txt\n");

    //creation des iamges BMP des gradients Ix,Iy,It :
    //Ix:
    BmpImg image_3=createBmpImg("Ix.bmp",image_1.dimX,image_1.dimY);
    for(i = 0 ; i <image_1.dimX; i++ )
      for( j = 0 ; j <image_1.dimY; j++)
        image_3.img[i][j]=Ix[i][j];

    writeBmpImage("Ix.bmp",&image_3);
    printf("Creation de l'image du gradient Ix - Ix.Bmp -\n");

    //Iy:
    BmpImg image_4=createBmpImg("Iy.bmp",image_1.dimX,image_1.dimY);
    for(i = 0 ; i < image_1.dimX; i++ )
      for( j = 0 ; j < image_1.dimY; j++)
        image_4.img[i][j]=Iy[i][j];

    writeBmpImage("Iy.bmp",&image_4);
    printf("Creation de l'image du gradient Iy - Iy.Bmp -\n");

    //It:
    BmpImg image_5=createBmpImg("It.bmp",image_1.dimX,image_1.dimY);
    for(i = 0 ; i <image_1.dimX; i++ )
      for( j = 0 ; j <image_1.dimY; j++)
        image_5.img[i][j]=It[i][j];

    writeBmpImage("It.bmp",&image_5);
    printf("Creation de l'image du gradient It - It.Bmp -\n");




    float** U=CreateTable(image_1.dimX,image_1.dimY);
    float** ubar=CreateTable(image_1.dimX,image_1.dimY);
    float** V=CreateTable(image_1.dimX,image_1.dimY);
    float** vbar=CreateTable(image_1.dimX,image_1.dimY);

    calcul_u_v(U,V,Ix,Iy,It,ubar,vbar,image_1.dimX,image_1.dimY,Nmax);
    printf("calcul des matrices : ubar,vbar,U,V \t Nombre d'iterations : %d\n",Nmax);

    //ecriture des fichiers U,V,Ubar,Vbar :
    WriteTable(ubar,image_1.dimX,image_1.dimY,"ubar.txt");
    printf("Ecriture de la matrice ubar dans un fchier : ubar.txt\n");
    WriteTable(vbar,image_1.dimX,image_1.dimY,"vbar.txt");
    printf("Ecriture de la matrice vbar dans un fchier : vbar.txt\n");
    WriteTable(U,image_1.dimX,image_1.dimY,"U.txt");
    printf("Ecriture de la matrice U dans un fchier : U.txt\n");
    WriteTable(V,image_1.dimX,image_1.dimY,"V.txt");
    printf("Ecriture de la matrice V dans un fchier : V.txt\n\n");



    printf("2- METHODE 2 : \t Methode de multi-resolution\n\n"); // METHODE DE MULTI-RESOLUTION :
    float** Gauss_W=MatriceDeGausse(); // FILTRE_GAUSSIEN_SIGMA_0.8

    float** image_1_lisse=A;
    image_1_lisse=produitDeConv(A,image_1.dimX,image_1.dimY,Gauss_W);
    printf("creation d'une Image 1 -SMOOTH - avec un filtre de GAUSS dim 3 - taille : %d x %d\n",image_1.dimX,image_1.dimY);

    float** image_2_lisse=B;
    image_2_lisse=produitDeConv(B,image_2.dimX,image_2.dimY,Gauss_W);
    printf("creation d'une Image 2 -SMOOTH - avec un filtre de GAUSS dim 3 - taille : %d x %d\n",image_2.dimX,image_2.dimY);

    // REDUIRE LA RESOLUTION  SCALE 2 :

    float** image_1_lisse_scale2=reduire_res(image_1_lisse,image_1.dimX, image_1.dimY);
    float** image_2_lisse_scale2=reduire_res(image_2_lisse, image_2.dimX , image_2.dimY);

    // ecrtiure de l'image REDIMENSIONNE : voir fichier "image1_scale2.bmp"
    BmpImg image1_scale2=createBmpImg("image1_scale2.Bmp",image_1.dimX/2,image_1.dimY/2);
    for(i=0;i<image_1.dimX/2;i++)
        for(j=0;j<image_1.dimY/2;j++)
            image1_scale2.img[i][j]=(int)image_1_lisse_scale2[i][j];

    writeBmpImage("image1_scale2.Bmp",&image1_scale2);
    printf("creation d'une Image 1 - scale 2 - -SMOOTH -  avec un filtre de GAUSS dim 3 - taille : %d x %d\n",image_1.dimX/2,image_1.dimY/2);

    // ecrtiure de l'image REDIMENSIONNE : voir fichier "image2_scale2.bmp"
    BmpImg image2_scale2=createBmpImg("image2_scale2.Bmp",image_1.dimX/2,image_1.dimY/2);
    for(i=0;i<image_2.dimX/2;i++)
        for(j=0;j<image_2.dimY/2;j++)
            image2_scale2.img[i][j]=(int)image_2_lisse_scale2[i][j];

    writeBmpImage("image2_scale2.Bmp",&image2_scale2);
    printf("creation d'une Image 2 - scale 2 - -SMOOTH - avec un filtre de GAUSS dim 3 - taille : %d x %d\n",image_2.dimX/2,image_2.dimY/2);


    float** image_1_lisse_scale2_a_lisser=produitDeConv(image_1_lisse_scale2,image_1.dimX/2,image_1.dimY/2,Gauss_W);
    float** image_2_lisse_scale2_a_lisser=produitDeConv(image_2_lisse_scale2,image_2.dimX/2,image_2.dimY/2,Gauss_W);

    // REDUIRE LA RESOLUTION  SCALE 4 :
    float** image_1_lisse_scale4=reduire_res(image_1_lisse_scale2_a_lisser, image_1.dimX/2 ,image_1.dimY/2);
    float** image_2_lisse_scale4=reduire_res(image_2_lisse_scale2_a_lisser , image_2.dimX/2 , image_2.dimY/2);

    // ecrtiure de l'image REDIMENSIONNE : voir fichier "image1_scale2.bmp"
    BmpImg image1_scale4=createBmpImg("image1_scale4.Bmp",image_1.dimX/4,image_1.dimY/4);
    for(i=0;i<image_1.dimX/4;i++)
        for(j=0;j<image_1.dimY/4;j++)
            image1_scale4.img[i][j]=(int)image_1_lisse_scale4[i][j];

    writeBmpImage("image1_scale4.Bmp",&image1_scale4);
    printf("creation d'une image 1 - scale 4 - -SMOOTH -  avec filtre de GAUSS dim 3 - taille : %d x %d\n", image_1.dimX/4 ,image_1.dimY/4 );
    // ecrtiure de l'image REDIMENSIONNE : voir fichier "image2_scale2.bmp"
    BmpImg image2_scale4=createBmpImg("image2_scale4.Bmp",image_1.dimX/4,image_1.dimY/4);
    for(i=0;i<image_2.dimX/4;i++)
        for(j=0;j<image_2.dimY/4;j++)
            image2_scale4.img[i][j]=(int)image_2_lisse_scale4[i][j];

    writeBmpImage("image2_scale4.Bmp",&image2_scale4);
    printf("creation d'une image 2 - scale 4 - -SMOOTH -  avec filtre de GAUSS dim 3 - taille : %d x %d\n", image_2.dimX/4 ,image_2.dimY/4);


    // debut de calcul :
    float** u_4=CreateTable(image_1.dimX/4,image_1.dimY/4);
    float** ubar_4=CreateTable(image_1.dimX/4,image_1.dimY/4);
    float** v_4=CreateTable(image_1.dimX/4,image_1.dimY/4);
    float** vbar_4=CreateTable(image_1.dimX/4,image_1.dimY/4);
    float** Ix_4=CreateTable(image_1.dimX/4,image_1.dimY/4);
    float** Iy_4=CreateTable(image_1.dimX/4,image_1.dimY/4);
    float** It_4=CreateTable(image_1.dimX/4,image_1.dimY/4);

    gradient(image_1_lisse_scale4,image_2_lisse_scale4,Ix_4,Iy_4,It_4, image_1.dimX/4 ,image_1.dimY/4 );

    CalcU_V_avecConv(u_4,v_4,ubar_4,vbar_4,Gauss_W,Ix_4,Iy_4,It_4,image_1.dimX/4,image_1.dimY/4);


    // interpolation vers U2 :
    float** u_2=augment_res(u_4,image_1.dimX/4,image_1.dimY/4);
    float** ubar_2=augment_res(ubar_4,image_1.dimX/4,image_1.dimY/4);
    float** v_2=augment_res(v_4,image_1.dimX/4,image_1.dimY/4);
    float** vbar_2=augment_res(vbar_4,image_1.dimX/4,image_1.dimY/4);
    float** Ix_2=augment_res(Ix_4,image_1.dimX/4,image_1.dimY/4);
    float** Iy_2=augment_res(Iy_4,image_1.dimX/4,image_1.dimY/4);
    float** It_2=augment_res(It_4,image_1.dimX/4,image_1.dimY/4);

    gradient(image_1_lisse_scale2,image_2_lisse_scale2, Ix_2 , Iy_2 , It_2 , image_1.dimX/2 , image_1.dimY/2);

    for(i=0;i<N_pyr;i++)
        CalcU_V_avecConv( u_2, v_2, ubar_2, vbar_2, Gauss_W, Ix_2, Iy_2, It_2, image_1.dimX/2 , image_1.dimY/2);

    float** u_pyr=augment_res(u_2,image_1.dimX/2,image_1.dimY/2);
    float** ubar_pyr=augment_res(ubar_2,image_1.dimX/2,image_1.dimY/2);
    float** v_pyr=augment_res(v_2,image_1.dimX/2,image_1.dimY/2);
    float** vbar_pyr=augment_res(vbar_2,image_1.dimX/2,image_1.dimY/2);
    float** Ix_pyr=augment_res(Ix_2,image_1.dimX/2,image_1.dimY/2);
    float** Iy_pyr=augment_res(Iy_2,image_1.dimX/2,image_1.dimY/2);
    float** It_pyr=augment_res(It_2,image_1.dimX/2,image_1.dimY/2);

    gradient(image_1_lisse,image_2_lisse,Ix_pyr,Iy_pyr,It_pyr,image_1.dimX,image_1.dimY);

    for(i=0;i<N_pyr;i++)
        CalcU_V_avecConv(u_pyr,v_pyr,ubar_pyr,vbar_pyr,Gauss_W,Ix_pyr,Iy_pyr,It_pyr,image_1.dimX,image_1.dimY);


    WriteTable(u_pyr,image_1.dimX,image_1.dimY,"U_pyr.txt");
    printf("Ecriture de la matrice U dans un fchier : U_pyr.txt\n");
    WriteTable(v_pyr,image_1.dimX,image_1.dimY,"V_pyr.txt");
    printf("Ecriture de la matrice V dans un fchier : V_pyr.txt\n");



    FreeTable(A,image_1.dimX);
    FreeTable(B,image_1.dimX);
    freeAll(Ix,Iy,It,U,V,ubar,vbar,image_1.dimX);
    freeAll(Ix_4,Iy_4,It_4,u_4,v_4,ubar_4,vbar_4,image_1.dimX/4);
    freeAll(Ix_2,Iy_2,It_2,u_2,v_2,ubar_2,vbar_2,image_1.dimX/2);
    freeAll(Ix_pyr,Iy_pyr,It_pyr,u_pyr,ubar_pyr,v_pyr,vbar_pyr,image_1.dimX);

    printf("\n\n*/  \t FIN \t  */");

return 0;

}

