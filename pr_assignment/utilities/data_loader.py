import numpy as np
import os
from imageio import imread
import glob
import time


def load_data_batch(file_path, name):
    xs = np.ones((1, 784))
    counter = len(glob.glob1(file_path, "*.png"))
    ys = np.zeros(counter)
    i = 0
    print("Loading %s now" % name)
    for file in os.listdir(file_path):
        filename = os.path.join(file_path, file)
        if file.endswith(".png"):
            ys[i] = (file.split("-")[0])
            i += 1
            image = imread(filename)
            X = image.reshape(1, 784)
            xs = np.concatenate((xs, X))
    xs = np.delete(xs, 0, 0)
    print('The shape of data is: ', end='')
    print(xs.shape)
    print('The shape of label is: ', end='')
    print(ys.shape)
    return xs, ys


def load_data(ROOT):
    print("Data directory:" + ROOT)
    tic = time.time()
    path = os.path.join(ROOT, 'TrainingSamples')
    Xtr, Ytr = load_data_batch(path, 'TrainingSamples')

    path = os.path.join(ROOT, 'TestSamples')
    Xte, Yte = load_data_batch(path, 'TestSamples')
    toc = time.time()
    print('Data loading took %f seconds' % (toc - tic))

    return Xtr, Ytr, Xte, Yte

# load_data("../Images")
