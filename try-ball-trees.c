#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM 2 // dimensionality of data points
#define MAX_POINTS 100 // maximum number of data points

typedef struct point_t {
    double x[DIM];
} point_t;

typedef struct node_t {
    point_t *p; // data point associated with node
    double radius; // radius of ball
    struct node_t *left; // left child
    struct node_t *right; // right child
} node_t;

double distance(point_t *p1, point_t *p2) {
    double dist = 0;
    for (int i = 0; i < DIM; i++) {
        double diff = p1->x[i] - p2->x[i];
        dist += diff * diff;
    }
    return sqrt(dist);
}

node_t* create_node(point_t *p) {
    node_t *node = malloc(sizeof(node_t));
    node->p = p;
    node->radius = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void calculate_radius(node_t *node, point_t *p) {
    double dist = distance(node->p, p);
    if (dist > node->radius) {
        node->radius = dist;
    }
}

void insert_node(node_t **root, point_t *p) {
    if (*root == NULL) {
        *root = create_node(p);
        return;
    }
    node_t *current = *root;
    while (1) {
        calculate_radius(current, p);
        double left_dist = (current->left) ? distance(current->left->p, p) : INFINITY;
        double right_dist = (current->right) ? distance(current->right->p, p) : INFINITY;
        if (left_dist < right_dist) {
            if (current->left == NULL) {
                current->left = create_node(p);
                return;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = create_node(p);
                return;
            }
            current = current->right;
        }
    }
}

void search_node(node_t *root, point_t *p, int *count) {
    if (root == NULL) {
        return;
    }
    double dist = distance(root->p, p);
    (*count)++;
    if (dist <= root->radius) {
        search_node(root->left, p, count);
        search_node(root->right, p, count);
    } else {
        double left_dist = (root->left) ? distance(root->left->p, p) : INFINITY;
        double right_dist = (root->right) ? distance(root->right->p, p) : INFINITY;
        if (left_dist < right_dist) {
            search_node(root->left, p, count);
        } else {
            search_node(root->right, p, count);
        }
    }
}

int main() {
    // sample data points
    point_t points[MAX_POINTS];
    points[0].x[0] = 0;
    points[0].x[1] = 0;
    points[1].x[0] = 1;
    points[1].x[1] = 1;
    points[2].x[0] = 2;
    points[2].x[1] = 2;
    points[3].x[0] = 3;
   
