import numpy as np
import matplotlib.pyplot as plt
from network import Network
import random

# with np.load('mnist.npz') as data:
#     training_images = data['training_images']
#     training_labels = data['training_labels']
#     test_images = data['test_images']
#     test_labels = data['test_labels']
#     validation_images = data['validation_images']
#     validation_labels = data['validation_labels']

# # Reformat arrays to work with matrix system in network
# training_images = np.array(np.reshape(training_images, (len(training_images), 784)))
# training_labels = np.array(np.reshape(training_labels, (len(training_labels), 10)))
# test_images = np.array(np.reshape(test_images, (len(test_images), 784)))
# test_labels = np.array(np.reshape(test_labels, (len(test_labels), 10)))
# validation_labels = np.array(np.reshape(validation_labels, (len(test_labels), 10)))
# validation_images = np.array(np.reshape(validation_images, (len(validation_images), 784)))

# def optimize(eta):
#     net = Network([784, 512, 512, 10], training_images[:10000], training_labels[:10000], test_images[:1000], test_labels[:1000], validation_images[:1000], validation_labels[:1000])
#     return net.SGD(20, eta, 128)

# from hyperopt import hp
# space = hp.uniform('eta', 0.0, 0.4)
# from hyperopt import fmin, tpe
# best = fmin(fn=optimize,
#     space=space,
#     algo=tpe.suggest,
#     max_evals=100)
# print(best)

# # Train network

# 25*25 scaled images with RGB values
# Total inputs = 150 * 150 * 3 = 1875
# Aim for 50 training images? Use rotatation and skew to generate further variation

net = Network([1875, 512, 512, 10], training_images, training_labels, test_images, test_labels, validation_images, validation_labels)
net.SGD(35, 0.2, 128, monitor_text=True, optimizing=False)
# Best eta so far: 0.2
# Hyper-opt says: 0.38384960552488084

# Make 5 predictions using trained network for demonstration
# images = np.zeros((5, 784))
# guesses = []
# confidences = []
# for _ in range(5):
#     i = random.randint(0, len(validation_images) - 1)
#     images[_] = validation_images[i]
#     output = net.feedforward(validation_images[i])
#     guess = np.argmax(output)
#     confidence = round((output[0][guess] / np.sum(output)) * 100.0, 2)
#     guesses.append(guess)
#     confidences.append(confidence)

# plt.imshow(images.reshape(140, 28), cmap='gray')

# for i in range(5):
#     plt.annotate(str(guesses[i]), xy=(0, 0), xytext=(35, 17 + 28 * i), fontsize=20, color='k')
#     plt.annotate(str(confidences[i]) + "%", xy=(0, 0), xytext=(50, 17 + 28 * i), fontsize=20)

# plt.xticks([])
# plt.yticks([])
# plt.show()
