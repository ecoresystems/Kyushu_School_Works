import numpy


def generate(num_range, size):
    a = numpy.arange(num_range)
    numpy.random.shuffle(a)
    return a[:size]
