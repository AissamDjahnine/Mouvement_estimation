 #include"Matrix.h"

 // Constructeur et Destructeur des matrices
 // Constructeur et Destructeur des matrices
/** Methode de creation d'une matrice des flottans
  * @param rows nombre de lignes de la matrice
  * @param cols nombre de colonnes de la matrice
  * @return une matrice de taille rows*cols prete a l'emploi
  */

 float** CreateTable(int rows,int cols)
{
    float ** matReel ;
    matReel = malloc ( rows * sizeof ( float* ) );
    int i;
    for ( i = 0; i < rows ; i++ )
    {
        matReel [i] = calloc ( cols , sizeof ( float ) );
    }
    return matReel;
}
// Methode de lecture / ecriture

/** Methode de lecture d'une matrice a partir d'un fichier Txt
  * @param path nom du fichier -chemin d'accés-
  * @return une matrice float de dimension : height*width
  */

float** LireTable(char* path)
{
    FILE * fTxt = fopen ( path , "r" );
    if( fTxt != NULL )
    {
        int i = 0,j = 0;
        int height,width;
        fscanf(fTxt,"%d %d",&height,&width);
        float** tabTxt=CreateTable(height,width);
        for(i=0;i<height;i++)
        {
            for(j=0;j<width;j++)
            {
                fscanf( fTxt , "%f", &( tabTxt [i][j]));
            }
        }
            return tabTxt;

    }
    fclose ( fTxt );
    }

/** Methode d'ecriture d'une matrice
  * @param MatToBeWritten la matrice à écrire dans un fichier Txt
  * @param height nombre de lignes de la matrice à écrire
  * @param width nombre de colonnes de la matrice à écrire
  * @param path nom du fichier -chemin d'accés-
  */
void WriteTable(float** MatToBeWritten,int height, int width,char* path)
{

    if(height%2!=0)
        height--;
    if(width%2!=0)
        width--;

    FILE * fTxt = fopen ( path , "w" );

    if( fTxt != NULL )
    {
        int i = 0,j = 0;
        for(i=height-1;i>=0;i--)
        {
            for(j=0;j<width;j++)
            {
                fprintf( fTxt , "%f ",MatToBeWritten [i][j]);
            }
            fprintf( fTxt , "\n");
        }



        fclose ( fTxt );
    }

    }

    /** Methode de destruction d'une image
  * @param tab matrice à detruire / desallouer
  * @param rows nombre des lignes de la matrice a desallouer

  */

void FreeTable(float** tab, int rows)
{
    int i=0;
    for ( i = 0; i < rows ; i++ )
    {
        free ( tab [i] );
    }
    free ( tab );
    tab = NULL ;
}

/** Methode de destruction des matrices
  * @param matrices
  * @param leurs dimensions
  */
    void freeAll (float**mat1,float**mat2,float**mat3,float**mat4,float**mat5,float**mat6,float**mat7,int DIM)
    {
        FreeTable(mat1,DIM);
        FreeTable(mat2,DIM);
        FreeTable(mat3,DIM);
        FreeTable(mat4,DIM);
        FreeTable(mat5,DIM);
        FreeTable(mat6,DIM);
        FreeTable(mat7,DIM);
    }
