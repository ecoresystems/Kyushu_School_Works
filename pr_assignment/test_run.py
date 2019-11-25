from utilities import data_loader
from classifiers import KNearestNeighbor
import matplotlib.pyplot as plt
import numpy as np
from utilities.timer import time_function
import time, scipy, imageio, os
from sample_programms.Step05_kNearestNeighbor import step05_run
from sample_programms.Step02_ImageProcessing import step02_run
from image_processors import intensity_modifier


def knn_native_driver(X_train, y_train, X_test, y_test):
    classifier = KNearestNeighbor()
    classifier.train(X_train, y_train)

    two_loop_time = time_function(classifier.compute_distances_two_loops, X_test)
    print('Original loop version took %f seconds' % two_loop_time)

    no_loop_time = time_function(classifier.compute_distances_no_loops, X_test)
    print('Linear algebra version took %f seconds' % no_loop_time)

    tic = time.time()
    dists = classifier.compute_distances_no_loops(X_test)
    dists1 = classifier.compute_distances_two_loops(X_test)
    print("The shape of the distance matrix is:", end='')
    print(dists.shape)
    print("The difference between 2 versions is: %f" % np.sum(dists1 - dists))
    plt.imshow(dists, interpolation='none')
    plt.show()

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
    pass


def intensity_attenuator_driver(img_array, strength, output_path):
    modified_array = intensity_modifier.intensity_attenuator(img_array, strength)
    for i in range(modified_array.shape[0]):
        path = os.path.join(output_path, 'OutSamples', str(i) + '.png')
        imageio.imwrite(path, modified_array[i].reshape(28, 28).astype(np.uint8))


def binarizer_driver(img_array, threshold, output_path):
    modified_array = intensity_modifier.binarizer(img_array, threshold)
    for i in range(modified_array.shape[0]):
        path = os.path.join(output_path, 'OutSamples', str(i) + '.png')
        imageio.imwrite(path, modified_array[i].reshape(28, 28).astype(np.uint8))


if __name__ == "__main__":
    tic = time.time()
    data_dir = 'Images'
    X_train, y_train, X_test, y_test = data_loader.load_data(data_dir)
    intensity_attenuator_driver(X_train, 50, data_dir)
    intensity_attenuator_driver(X_test, 50, data_dir)
    toc = time.time()
    print("The execution time of np array is: %f s" % (toc - tic))
    tic = time.time()
    step02_run()
    toc = time.time()
    print("The execution time of original version is: %f s" % (toc - tic))
    # binarizer_driver(X_train, 150, data_dir)
    # knn_native_driver(X_train, y_train, X_test, y_test)
    # step05_run()
