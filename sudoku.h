/****************************************************************/
/* Auteur : S. Gueye						                    */
/* TP : Sudoku bactracking algorithm				            */
/* Date dernière maj : 24/11/2020				                */
/****************************************************************/

/****************************************************************/
/* Objectif : Classe représentant une cellule de la grille 
/****************************************************************/
class cellule
{
	public :
	friend class sudoku;
	int val;			        // Valeur de la cellule
	int l; 			        // Numéro de ligne
	int c; 			        // Numéro de colonne
	int b; 			        // Numéro du bloc où se situe la cellule (l,c)
	int n;			        // Nombre de chiffres qu'il est possible initialement d'utiliser sur la cellule
	cellule();
	cellule(int i, int j, int nbr);  // Construit la cellule de numéro de ligne i et colonne j
};


/****************************************************************/
/* Objectif : Classe permettant de lire une grille sudoku et de la résoudre
/****************************************************************/
class sudoku{
	cellule* grille[9][9];			    // La grille de cellule
	bool ligne[9][9];			        // ligne[i][k] = 1 si le chiffre k est déjà présent sur la ligne i
	bool colonne[9][9];			        // colonne[i][k] = 1 si le chiffre k est déjà présent sur la colonne i
	bool bloc[9][9];			        // bloc[i][k] = 1 si le chiffre k est déjà présent sur le bloc i
    cellule* C[81]; 					// Tableau des cellules à traiter (de taille maximum)
	int r;					        // Nombre de cellules à traiter
public : 
	sudoku(char filename[]);		// Lecture de la grille sudoku se trouvant dans le fichier filename
	void affichage();               // Affichage de la grille
	bool solution();                // Calcul de solution
	bool solutionBacktracking(cellule* C[],int k);           // Calcul de solution à partir de la k-ième cellule a trouve
};



