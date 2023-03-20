
////////////////
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

////////
