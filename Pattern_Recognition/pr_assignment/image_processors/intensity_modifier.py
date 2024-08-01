import numpy as np


def intensity_attenuator(img_array, strength):
    return img_array * ((100 - strength) / 100)


def binarizer(image_array, threshold):
    return np.where(image_array > threshold, 255, 0)