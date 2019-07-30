import numpy as np
import os
from imageio import imread
import glob
import time


def load_data_batch(file_path):
    # print(file_path)
    xs = np.ones((1, 784))
    counter = len(glob.glob1(file_path, "*.png"))
    ys = np.zeros(counter)
    i = 0
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
    tic = time.time()
    print(ROOT)
    path = os.path.join(ROOT, 'TrainingSamples')
    print(path)
    Xtr, Ytr = load_data_batch(path)

    path = os.path.join(ROOT, 'TestSamples')
    Xte, Yte = load_data_batch(path)
    toc = time.time()

    print('Data loading took %f seconds' % (toc - tic))

    return Xtr, Ytr, Xte, Yte


def load_data_batch3d(file_path):
    # print(file_path)
    xs = np.ones((1, 28, 28))
    counter = len(glob.glob1(file_path, "*.png"))
    ys = np.zeros(counter)
    i = 0
    for file in os.listdir(file_path):
        filename = os.path.join(file_path, file)
        if file.endswith(".png"):
            ys[i] = (file.split("-")[0])
            i += 1
            image = imread(filename).reshape(1, 28, 28)
            xs = np.concatenate((xs, image))
    xs = np.delete(xs, 0, 0)
    print(xs)
    print('The shape of data is: ', end='')
    print(xs.shape)
    print('The shape of label is: ', end='')
    print(ys.shape)
    return xs, ys


def load_data_3d(ROOT):
    tic = time.time()
    print(ROOT)
    path = os.path.join(ROOT, 'TrainingSamples')
    print(path)
    Xtr, Ytr = load_data_batch3d(path)

    path = os.path.join(ROOT, 'TestSamples')
    Xte, Yte = load_data_batch3d(path)
    toc = time.time()

    print('Data loading took %f seconds' % (toc - tic))

    return Xtr, Ytr, Xte, Yte
