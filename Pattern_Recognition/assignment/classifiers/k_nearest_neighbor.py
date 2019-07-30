import numpy as np


class KNearestNeighbor(object):
    def __init__(self):
        pass

    def train(self, X, y):
        self.X_train = X
        self.y_train = y

    def predict(self, X, k=1, num_loops=0):
        if num_loops == 0:
            dists = self.compute_distances_no_loops(X)
        return self.predict_labels(dists, k=k)

    def compute_distances_no_loops(self, X):
        num_test = X.shape[0]
        num_train = self.X_train.shape[0]
        dists = np.zeros((num_test, num_train))
        dists = np.sqrt(
            np.sum(X ** 2, axis=1).reshape(num_test, 1) + np.sum(self.X_train ** 2, axis=1) - 2 * X.dot(self.X_train.T))
        return dists

    def predict_labels(self, dists, k=1):
        num_test = dists.shape[0]
        y_pred = np.zeros(num_test)
        for i in range(num_test):
            closest_y = []
            sorted_indices = np.argsort(dists[i])
            for j in range(k):
                closest_y.append(self.y_train[sorted_indices[j]])
            closest_y.sort()
            if (k == 1):
                y_pred[i] = closest_y.pop()
            else:
                y_pred[i] = max(set(closest_y), key=closest_y.count)
        return y_pred
