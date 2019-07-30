from utilities import data_loader
from classifiers import KNearestNeighbor
import matplotlib.pyplot as plt
import numpy as np
from utilities.timer import time_function
import time
from sample_programms.Step05_kNearestNeighbor import step05_run

if __name__ == "__main__":
    data_dir = 'Images'
    # X_train, y_train, X_test, y_test = data_loader.load_data(data_dir)
    # np.savez("1d_data.npz", X_train, y_train, X_test, y_test)
    tic = time.time()
    data_set = np.load("1d_data.npz")
    X_train = data_set['arr_0']
    y_train = data_set['arr_1']
    X_test = data_set['arr_2']
    y_test = data_set['arr_3']
    toc = time.time()
    print("New data loading took %f seconds" % (toc - tic))
    classifier = KNearestNeighbor()
    classifier.train(X_train, y_train)

    dists = classifier.compute_distances_no_loops(X_test)
    print("The shape of the distance matrix is:")
    print(dists.shape)
    plt.imshow(dists, interpolation='none')
    plt.show()

    tic = time.time()
    num_test = 10000
    k_choices = [1, 3, 5, 8, 10, 12, 15, 20, 50, 100]
    i = 0
    k_to_accuracies = np.zeros(10)
    '''
    for k_value in k_choices:
        y_test_pred = classifier.predict_labels(dists, k=k_value)
        num_correct = np.sum(y_test_pred == y_test)
        k_to_accuracies[i] = float(num_correct) / num_test
        print('Got %d / %d correct => accuracy: %f @ k=%d' % (num_correct, num_test, k_to_accuracies[i], k_value))
        i += 1
    # plot the raw observations
    '''
    y_test_pred = classifier.predict_labels(dists, k=1)
    num_correct = np.sum(y_test_pred == y_test)
    k_to_accuracies[i] = float(num_correct) / num_test
    print('Got %d / %d correct => accuracy: %f @ k=%d' % (num_correct, num_test, k_to_accuracies[i], 1))
    plt.plot(k_choices, k_to_accuracies)
    toc = time.time()
    print("Classification took %f seconds" % (toc - tic))
    step05_run()
