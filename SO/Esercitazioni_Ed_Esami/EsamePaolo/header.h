#include <fstream>


void recuperoValori(std::ifstream& file, int **matrice, int r, int c); 
void vedoMatrice(int **matrice, int r, int c);
void verificaContenuto(int **matrice, int r, int c);
int conversioneBinarioDec(int **matrice, int r, int c);
int potenzaDue(int exp);
void sommaTotale(int **matrix, int r, int c, int *vettore);