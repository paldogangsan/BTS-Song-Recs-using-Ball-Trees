#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM 5 // number of dimensions

typedef struct {
    double point[DIM];
    int label;
} DataPoint;

typedef struct node {
    int is_leaf;
    DataPoint *point;
    double radius;
    struct node *left_child;
    struct node *right_child;
} BallTreeNode;

// function to calculate the distance between two data points
double distance(DataPoint *p1, DataPoint *p2) {
    double sum = 0;
    for (int i = 0; i < DIM; i++) {
        sum += (p1->point[i] - p2->point[i]) * (p1->point[i] - p2->point[i]);
    }
    return sqrt(sum);
}

// function to search for the nearest neighbor
DataPoint *search(BallTreeNode *root, DataPoint *query) {
    DataPoint *best_point = NULL;
    double best_distance = INFINITY;

    if (root == NULL) {
        return best_point;
    }

    if (root->is_leaf) {
        double d = distance(root->point, query);
        if (d < best_distance) {
            best_point = root->point;
            best_distance = d;
        }
        return best_point;
    }

    double d = distance(root->point, query);
    if (d < best_distance) {
        best_point = root->point;
        best_distance = d;
    }

    if (d < root->radius + best_distance) {
        DataPoint *left_best = search(root->left_child, query);
        if (left_best != NULL) {
            double left_distance = distance(left_best, query);
            if (left_distance < best_distance) {
                best_point = left_best;
                best_distance = left_distance;
            }
        }

        DataPoint *right_best = search(root->right_child, query);
        if (right_best != NULL) {
            double right_distance = distance(right_best, query);
            if (right_distance < best_distance) {
                best_point = right_best;
                best_distance = right_distance;
            }
        }
    }
    else {
        DataPoint *far_best = search(root->right_child, query);
        if (far_best != NULL) {
            double far_distance = distance(far_best, query);
            if (far_distance < best_distance) {
                best_point = far_best;
                best_distance = far_distance;
            }
        }

        DataPoint *near_best = search(root->left_child, query);
        if (near_best != NULL) {
            double near_distance = distance(near_best, query);
            if (near_distance < best_distance) {
                best_point = near_best;
                best_distance = near_distance;
            }
        }
    }
    return best_point;
}


int main() {
    // create a sample dataset
    DataPoint data[] = {
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
    BallTreeNode *root = build_ball_tree(data, 10);

    // search for the nearest neighbor for a given query point
    DataPoint query = {{0.2, 0.3, 0.4, 0.5, 0.1}, -1};
    DataPoint *nearest_neighbor = search(root, &query);

    // print the label of the nearest neighbor
    printf("The label of the nearest neighbor is %d\n", nearest_neighbor->label);

    return 0;
}
