#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	float *tableauPile;
	size_t taillePile;
}pile;

pile *creationPile()
{
	pile *nouvellePile = malloc(sizeof(pile));
	nouvellePile->tableauPile = NULL;
	nouvellePile->taillePile = 0;
	return nouvellePile;
}

void liberationPile(pile *pile)
{
	free(pile->tableauPile);
	free(pile);
}

void pushPile(pile *pile, float valeur) {
    float *nouveauTableau = realloc(pile->tableauPile, (pile->taillePile + 1) * sizeof(float));
    if (nouveauTableau == NULL) {
        printf("Allocation de la memoire ratée push");
        exit(1);
    }
    pile->tableauPile = nouveauTableau;
    pile->tableauPile[pile->taillePile] = valeur;
    pile->taillePile++;
}

float popPile(pile *pile) {
    if (pile->taillePile == 0) {
        printf("La pile est vide");
        return -1;
    } else {
        float valeur = pile->tableauPile[pile->taillePile-1];
        float *nouveauTableau = realloc(pile->tableauPile, (pile->taillePile + 1) * sizeof(float));
        if(nouveauTableau == NULL) {
            printf("Allocation de la memoire ratée pop");
            exit(1);
        }
        pile->tableauPile = nouveauTableau;
        pile->taillePile--;
        return valeur;
	}
}

void affichagePile(pile *pile)
{
	printf("pile :");
	for (int i = 0; i < pile->taillePile; i++) {
		printf("%f ", pile->tableauPile[i]);
	}
}

char** divisionChaineDeCaracteresDelimiterParEspace(char* string) {
    char* copieChaine = strdup(string);
    int compteur = 0;
    char *token;
    char** tableauFinal;
    const char s[2] = " ";
    token = strtok(copieChaine, s);

    while (token != NULL) {
        compteur++;
        token = strtok(NULL, s);
    }
    tableauFinal = malloc((compteur+1) * sizeof(char*));
    if (tableauFinal == NULL) {
        printf("Allocation de la memoire ratée divide_string");
        exit(1);
    }

    token = strtok(string, s);
    for (int i = 0; i < compteur; i++) {
        tableauFinal[i] = malloc(strlen(token) + 1);
        strcpy(tableauFinal[i], token);
        token = strtok(NULL, s);
    }
    tableauFinal[compteur] = NULL;
    free(copieChaine);
    return tableauFinal;
}

char** saisieUtilisateur(){
    char* saisieBrut = malloc(100*sizeof(char));
    printf("Saisir une chaine de caractere : ");
    fgets(saisieBrut, 100, stdin);
	char** saisieFinal = divisionChaineDeCaracteresDelimiterParEspace(saisieBrut);
	free(saisieBrut);
    return saisieFinal;
}

float addition(float a, float b) {
    return a + b;
}

float multiplication(float a, float b) {
    return a * b;
}

float soustraction(float a, float b) {
    return a - b;
}

float division(float a, float b) {
	return a / b;
}

float calculUneOperation(pile *pile, char operation) {
    float premierOperande, deuxiemeOperande, resultatCalcul;
    deuxiemeOperande = popPile(pile);
    premierOperande = popPile(pile);
    switch (operation) {
        case '+':
            resultatCalcul = addition(premierOperande, deuxiemeOperande);
            break;
        case '*':
            resultatCalcul = multiplication(premierOperande, deuxiemeOperande);
            break;
        case '-':
            resultatCalcul = soustraction(premierOperande, deuxiemeOperande);
            break;
		case '/':
			if (deuxiemeOperande == 0) {
				printf("Division par 0 impossible");
				return -1;
			}
			resultatCalcul = division(premierOperande, deuxiemeOperande);
        default:
            printf("operation impossible: %c\n", operation);
            return -1;
    }
    pushPile(pile, resultatCalcul);
    return resultatCalcul;
}

int tailleTableauChar(char** tableau) {
	int compteur = 0;
	while (tableau[compteur] != NULL) {
		compteur++;
	}
	return compteur;
}

void calcul(pile *pile,char** tableau) {
	int comptage = tailleTableauChar(tableau);
	for (int i = 0; i < comptage; i++) {
		printf("%s", tableau[i]);
		if (strcmp(tableau[i], "+") == 0) {
			printf("addition\n");
			calculUneOperation(pile, '+');
		}
		else if (strcmp(tableau[i], "*") == 0) {
			printf("multiplication\n");
			calculUneOperation(pile, '*');
		}
		else if (strcmp(tableau[i], "-") == 0) {
			printf("soustraction\n");
			calculUneOperation(pile, '-');
		}
		else if (strcmp(tableau[i], "/") == 0) {
			printf("division\n");
			calculUneOperation(pile, '/');
		}
		else if (strcmp((tableau[i]), "\n") == 0) {
			printf("fin de la chaine\n");
		}

		else {
			printf("push\n");
			pushPile(pile, atoi(tableau[i]));
		}
	}
}

void liberationTableauChar(char** tableau) {
    int i = 0;
    while (tableau[i] != NULL) {
        free(tableau[i]);
        i++;
    }
    free(tableau);
}

int main (int argc, char *argv[])
{
	char** chaineEntreeUtilisateur = saisieUtilisateur();

	pile *pile = creationPile();

	calcul(pile, chaineEntreeUtilisateur);

	affichagePile(pile);

	liberationTableauChar(chaineEntreeUtilisateur);

	liberationPile(pile);
}
