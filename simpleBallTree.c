#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define DIM 5 // dimensionality of data points
#define MAX_POINTS 273 // maximum number of data points (the number of songs bts has on spotify)

typedef struct point_t {
    double x[DIM]; //x[i] contains the i parameter values of a single data point.
} point_t;


//creating the ball tree node structure
typedef struct node_t {
    int id; //index
    point_t *p; // data point associated with node (unique index)
    double radius; // radius of ball (taken by max distance)
    struct node_t *left; // left child
    struct node_t *right; // right child
} node_t;

//calculating the euclidean distance
double distance(point_t *p1, point_t *p2) {
    double dist = 0;
    for (int i = 0; i < DIM; i++) {
        double diff = p1->x[i] - p2->x[i];
        dist += diff * diff;
    }
    return sqrt(dist);
}


// calculating manhattan distance



//given a datapoint, create a node of the ball tree
// the first time we make this, it will be the root node
node_t* create_node(point_t *p) {
    node_t *node = malloc(sizeof(node_t)); //allocating required memory
    node->id = data[2];
    node->p = p; 
    // radius, leftchild and right child are initialized with 0, NULL, NULL to accomodate the leaf nodes
    node->radius = 0; 
    node->left = NULL;
    node->right = NULL;
    return node;
}


// calculating the radius, given a root node and point, if 
// the distance  exceeds the existing radius value, 
// then this distance becomes the new radius
void calculate_radius(node_t *node, point_t *p) {
    double dist = distance(node->p, p);
    if (dist > node->radius) {
        node->radius = dist;
    }
}

// Define a function to recursively build a ball tree from a set of data points
node_t* build_ball_tree(int *indices, int start, int end, double **data) {
    // Base case: leaf node
    if (start == end) {
        node_t *leaf = (node_t*) malloc(sizeof(node_t));
        leaf->id = indices[start];
        leaf->p = data[indices[start]];
        leaf->radius = 0.0;
        leaf->left = NULL;
        leaf->right = NULL;
        return leaf;
    }
    // Recursive case: internal node
    int mid = (start + end) / 2;
    node_t *internal = (node_t*) malloc(sizeof(node_t));
    internal->left = build_ball_tree(indices, start, mid, data);
    internal->right = build_ball_tree(indices, mid+1, end, data);
    double max_dist_left = 0.0, max_dist_right = 0.0;
    for (int i = start; i <= end; i++) {
        double dist_left = euclidean_distance(data[indices[i]], internal->left->p);
        double dist_right = euclidean_distance(data[indices[i]], internal->right->p);
        if (dist_left > max_dist_left) {
            max_dist_left = dist_left;
        }
        if (dist_right > max_dist_right) {
            max_dist_right = dist_right;
        }
    }
    internal->radius = fmax(max_dist_left, max_dist_right);
    return internal;
}







// //starting the tree
// void insert_node(node_t **root, point_t *p) {
//     if (*root == NULL) {
//         *root = create_node(p);
//         return;
//     }
//     node_t *current = *root;
//     while (1) {
//         calculate_radius(current, p);
//         double left_dist = (current->left) ? distance(current->left->p, p) : INFINITY;
//         double right_dist = (current->right) ? distance(current->right->p, p) : INFINITY;
//         if (left_dist < right_dist) {
//             if (current->left == NULL) {
//                 current->left = create_node(p);
//                 return;
//             }
//             current = current->left;
//         } else {
//             if (current->right == NULL) {
//                 current->right = create_node(p);
//                 return;
//             }
//             current = current->right;
//         }
//     }
// }


//
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
    // create a sample dataset
    data[] = {
        {{0.5, 0.2, 0.3, 0.4, 0.1}, 1},
        {{0.2, 0.4, 0.1, 0.5, 0.3}, 2},
        {{0.1, 0.3, 0.4, 0.2, 0.5}, 3},
        {{0.4, 0.5, 0.2, 0.1, 0.3}, 4},
        {{0.3, 0.1, 0.5, 0.2, 0.4}, 5},
        {{0.2, 0.5, 0.4, 0.1, 0.3}, 6},
        {{0.4, 0.1, 0.2, 0.5, 0.3}, 7},
        {{0.3, 0.4, 0.5, 0.2, 0.1}, 8},
        {{0.1, 0.2, 0.3, 0.5, 0.4}, 9},
        {{0.5, 0.3, 0.1, 0.4, 0.2}, 10}
    };

    // build the ball tree from the dataset
    node_t *root = build_ball_tree(data, 10);

    // search for the nearest neighbor for a given query point
    point_t query = {{0.2, 0.3, 0.4, 0.5, 0.1}, -1};
    point_t *nearest_neighbor = search_node(root, *query, 10);

    // print the label of the nearest neighbor
    printf("The label of the nearest neighbor is %d\n", nearest_neighbor->id);

    return 0;
}
