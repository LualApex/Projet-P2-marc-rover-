#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "queue.h"



// Fonction pour créer un nœud de l'arbre
Node* createNode(t_location position, int direction, int cost) {
    Node* noeud = malloc(sizeof(Node*));
    if (noeud == NULL) {
        exit(EXIT_FAILURE);
    }
    noeud->position = position;
    noeud->direction = direction;
    noeud->cost = cost;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        noeud->children[i] = NULL;
    }
    return noeud;
}




void buildTree(Node* racine, int niveau) {
    if (niveau == MAX_CHILDREN) {
        return; // Si le niveau maximal est atteint, arrêter la construction
    }

    // Pour chaque enfant potentiel, créer un nouveau nœud
    for (int i = 0; i < 4; i++) {

        t_location newPosition = racine->position;
        // Déplacer en fonction de la direction
        switch (i) {
            case 0: newPosition.y--; break; // Nord
            case 1: newPosition.x++; break; // Est
            case 2: newPosition.y++; break; // Sud
            case 3: newPosition.x--; break; // Ouest
        }

        // Créer un nouvel enfant si la position est valide
        if (newPosition.x >= 0 && newPosition.y >= 0) {
            Node* child = createNode(newPosition, i, racine->cost + 1); // Ajouter le coût
            racine->children[i] = child;
            buildTree(child, niveau + 1);
        }
    }
}


int isSheet(Node* noeud) {
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (noeud->children[i] != NULL) {
            return 0; // Ce n'est pas une feuille
        }
    }
    return 1; // C'est une feuille
}



Node* minimSheet(Node* racine) {
    if (racine == NULL) {
        return NULL;
    }

    if (isSheet(racine)) {
        return racine;
    }

    Node* minSheet = NULL;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (racine->children[i] != NULL) {
            Node* tempMinSheet = minimSheet(racine->children[i]);
            if (tempMinSheet && (!minSheet || tempMinSheet->cost < minSheet->cost)) {
                minSheet = tempMinSheet;
            }
        }
    }
    return minSheet;
}




void freeTree(Node* racine) {
    if (racine == NULL) {
        return;
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (racine->children[i] != NULL) {
            freeTree(racine->children[i]);
        }
    }

    free(racine);
}
/*//Fonction pour trouver le chemin jusqu'à la feuille minimale
void findPath(Node* sheet, t_queue* path) {
    Node* cur = sheet;
    while (cur != NULL) {
        t_position pos;
        pos.x = cur->x;
        pos.y = cur->y;
        enqueue(path, pos);
        cur = cur->parent;
    }
}

// Fonction pour afficher le chemin
void afficher_chemin(PathQueue* chemin) {
    printf("Chemin vers la feuille minimale :\n");
    for (int i = chemin->rear - 1; i >= 0; i--) {
        printf("Position : (%d, %d), Coût : %d\n", chemin->nodes[i]->x, chemin->nodes[i]->y, chemin->nodes[i]->cost);
    }
}*/