#include <iostream>
#include <iomanip>
#include <fstream> 
#include <sstream>
#include <string>

using namespace std;

#include "sudoku.h"


/****************************************/
/* Objectif : Construction d'une cellule
/****************************************/
cellule::cellule(int i, int j, int nbr)
{
	l = i;
	c = j;
	// Détermination du numéro du bloc
	if (i < 3){
		if (j < 3) b = 0;
		else if (j < 6) b = 1;
		else b = 2;
	} else if (i < 6){
		if (j < 3) b = 3;
		else if (j < 6) b = 4;
		else b = 5;
	} else {
		if (j < 3) b = 6;
		else if (j < 6) b = 7;
		else b = 8;
	}
	n = 9;
	val = nbr;
}

cellule::cellule()
{
	l = 0;
	c = 0;
	b = 0;
	n = 9;
	val = 0;
}


/****************************************/
/* Objectif : Construteur avec argument 
permettant la création d'une grille à partir d'un 
fichier.
/****************************************/
sudoku::sudoku(char filename[])
{
	ifstream file;
	file.open(filename);
	if(!file.is_open()){
		cout << "Erreur lors de l'ouverture du fichier" << endl;
		exit(1);
	} else {
		string ligne; // ligne du fichier
		int current; // valeur courante
		int k = 0; // indice du tableau C contenant les cellules à traiter
		for(int i = 0; i < 9; i++){
			getline(file, ligne);
			istringstream flux(ligne);
			for(int j = 0; j < 9; j++){
				if(flux >> current) {
					this->grille[i][j] = new cellule (i, j, current);
					if (current != 0){
						this->ligne[i][current] = true;
						this->colonne[j][current] = true;
						this->bloc[this->grille[i][j]->b][current] = true;
					} else {
						this->ligne[i][current] = false;
						this->colonne[j][current] = false;
						this->bloc[this->grille[i][j]->b][current] = false;
						this->C[k] = grille[i][j];
						k++;
					}
				}
			}
		}
		this->r = k; // Nombre de cellules à traiter
	}
}


/****************************************/
/* Objectif : Affichage de la grille sudoku
/****************************************/
void sudoku::affichage()
{
	cout << setw(3) << "-" << "------------------------------------" << endl;
	for(int i = 0; i < 9; i++){
		if((i == 3) || (i == 6))
			cout << setw(3) << "-" << "------------------------------------" << endl;
		cout << setw(3) << "|";		
		for(int j = 0; j < 8; j++){
			if((j == 3) || (j == 6))
				cout << setw(3) << "|" << setw(3) << grille[i][j]->val;
			else
				cout << setw(3) << grille[i][j]->val;
		}
		cout << setw(3) << grille[i][8]->val << setw(3)<<  "|" << endl;
	}
	cout << setw(3) << "-" << "------------------------------------" << endl;
}


/****************************************/
/* Objectif : Détermination d'une solution de la grilleées.
La méthode renvoie vrai si une solution a été trouvée, 0 sinon
/****************************************/
bool sudoku::solution()
{
	return solutionBacktracking(this->C, 0);
}

bool sudoku::solutionBacktracking(cellule* C[], int k)
{
    if (k == r){
		return true;
	} else {
		for (int j = 1; j <= 9; j++){
			if (ligne[C[k]->l][j] != 1 && colonne[C[k]->c][j] != 1 && bloc[C[k]->b][j]!=1){
				ligne[C[k]->l][j] = 1;
				colonne[C[k]->c][j] = 1;
				bloc[C[k]->b][j] = 1;
				if (solutionBacktracking(C, k+1)){
					C[k]->val = j;				
					return true;
				}
				ligne[C[k]->l][j] = 0;
				colonne[C[k]->c][j] = 0;
				bloc[C[k]->b][j] = 0;
			}
		}
	}
	return false;
}
