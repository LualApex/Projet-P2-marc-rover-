#ifndef UNTITLED1_ARBRE_H
#define UNTITLED1_ARBRE_H
#define MAX_CHILDREN 9

typedef struct {
    int x; // Coordonnée x
    int y; // Coordonnée y
} t_location;


//Structure du nœud de l'arbre de sélection des déplacements
typedef struct Node {
    t_location position; // Position actuelle du rover
    int direction; // Direction du rover (0: Nord, 1: Est, 2: Sud, 3: Ouest)
    int cost; // Coût cumulé jusqu'à ce nœud
    struct Node* children[MAX_CHILDREN]; // Pointeurs vers les nœuds enfants
}Node;


// Fonctions associées à l'arbre (prototypes)
Node* createNode(t_location position, int direction, int cost);
void buildTree(Node* racine, int niveau);
Node* minimSheet(Node* racine);
int isSheet(Node* noeud);
void freeTree(Node* racine);

#endif // ARBRE_H