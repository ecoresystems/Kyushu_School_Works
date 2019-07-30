import keras
from keras.datasets import mnist
from keras.models import Sequential, model_from_json
from keras.layers import Dense, Dropout, Flatten, Conv2D, MaxPooling2D
from pathlib import Path
import tensorflow as tf
import numpy as np


def nn_training():
    sess = tf.Session(config=tf.ConfigProto(log_device_placement=True))

    (x_train, y_train), (x_test, y_test) = mnist.load_data()
    x_train = x_train.reshape(x_train.shape[0], 28, 28, 1)
    x_test = x_test.reshape(x_test.shape[0], 28, 28, 1)

    # Normalize data set to 0-to-1 range
    x_train = x_train.astype('float32')
    x_test = x_test.astype('float32')
    x_train /= 255
    x_test /= 255

    # Convert class vectors to binary class matrices
    y_train = keras.utils.to_categorical(y_train, 10)
    y_test = keras.utils.to_categorical(y_test, 10)

    # Create a model and add layers
    model = Sequential()

    model.add(Conv2D(28, (3, 3), padding='same', input_shape=(28, 28, 1), activation="relu"))
    model.add(Conv2D(28, (3, 3), activation="relu"))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Dropout(0.25))

    model.add(Conv2D(56, (3, 3), padding='same', activation="relu"))
    model.add(Conv2D(56, (3, 3), activation="relu"))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Dropout(0.25))

    model.add(Flatten())
    model.add(Dense(448, activation="relu"))
    model.add(Dropout(0.5))
    model.add(Dense(10, activation="softmax"))

    # Compile the model
    model.compile(
        loss='categorical_crossentropy',
        optimizer='adam',
        metrics=['accuracy']
    )

    # Train the model
    model.fit(
        x_train,
        y_train,
        batch_size=1250,
        epochs=60,
        validation_data=(x_test, y_test),
        shuffle=True
    )

    # Save neural network structure
    model_structure = model.to_json()
    f = Path("model_structure.json")
    f.write_text(model_structure)

    # Save neural network's trained weights
    model.save_weights("model_weights.h5")


def nn_predict():
    # Load the json file that contains the model's structure
    f = Path("model_structure.json")
    model_structure = f.read_text()

    # Recreate the Keras model object from the json data
    model = model_from_json(model_structure)

    # Re-load the model's trained weights
    model.load_weights("model_weights.h5")
    model.summary()

    npz_file = np.load("dataset.npz")
    x_tr = npz_file['arr_0']
    y_tr = npz_file['arr_1']
    x_te = npz_file['arr_2']
    y_te = npz_file['arr_3']

    (x_train, y_train), (x_test, y_test) = mnist.load_data()


    # Make a prediction using the model
    x_te = x_te.reshape(x_te.shape[0], 28, 28, 1)
    results = model.predict(x_te)
    result_1d = np.zeros(y_te.shape)
    for i in range(results.shape[0]):
        for j in range(results.shape[1]):
            if results[i][j] == 1:
                result_1d[i] = j
    num_correct = int(np.sum(result_1d == y_te))
    accuracy = float(num_correct) / (y_te.shape[0])
    print("Got %d correct, accuracy = %f%%" % (num_correct, accuracy*100))

    x_test = x_test.reshape(x_te.shape[0], 28, 28, 1)
    results = model.predict(x_test)
    result_1d = np.zeros(y_test.shape)
    for i in range(results.shape[0]):
        for j in range(results.shape[1]):
            if results[i][j] == 1:
                result_1d[i] = j
    num_correct = int(np.sum(result_1d == y_test))
    accuracy = float(num_correct) / (y_test.shape[0])
    print("Got %d correct, accuracy = %f%% on mnist data" % (num_correct, accuracy*100))


if __name__ == "__main__":
    # nn_training()
    nn_predict()
