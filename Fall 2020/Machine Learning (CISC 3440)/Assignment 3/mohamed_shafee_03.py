# -*- coding: utf-8 -*-
"""Mohamed.Shafee.03

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1bcHEh0qDPNeSxz97WgiUu8Lv8hawGiyE
"""

# import libraries 
import numpy as np
from sklearn.datasets import fetch_openml
import matplotlib as mlp
import matplotlib.pyplot as plt
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import cross_val_score
from sklearn.metrics import confusion_matrix
from sklearn.metrics import f1_score
from sklearn.metrics import accuracy_score
from sklearn.model_selection import GridSearchCV
from scipy.ndimage.interpolation import shift

# fetch the data set
mnist = fetch_openml('mnist_784', version=1)

# create test and training sets
X, y = mnist["data"], mnist["target"] 
X.shape
X_train, X_test, y_train, y_test = X[:60000], X[60000:], y[:60000], y[60000:]

# grid search to find best hyperparamters. Worked well when I first tested it, but I couldnt get it to run after that. I believe I used up to many recourses during my session on Colab. 
model = KNeighborsClassifier()
modelParamaters = {
    'n_neighbors' : [1,3,5,7,9,11,13,15,17,19,21],
    'weights' : ['uniform', 'distance']
}

gridSearch = GridSearchCV(
    estimator = model,
    param_grid = modelParamaters,
    scoring = 'accuracy'
)
gridSearch.fit(X_train, y_train)
grid_search_clf.best_score_
grid_search_clf.best_params_
bestK = grid_search_clf.best_params_.get('n_neighbors')
bestWeight = grid_search_clf.best_params_.get('weights')
print(bestK)
print(bestWeight)

# Another technique I used to find the optimal hyperparameter values.
"""
accuracies = []
k_vals = []
for k in range (1, 30, 2):
  knc = KNeighborsClassifier(n_neighbors=k, weights='distance', n_jobs=-1)
  knc.fit(X_train, y_train)
  score = knc.score(X_test, y_test)
  accuracies.append(score)
  print ("K: " + str(k) + " | Accuracy = " + str(score * 100) + "%")
bestK = k_vals[accuracies.index(max(accuracies))]

knc = KNeighborsClassifier(n_neighbors= bestK, weights= bestWeight, n_jobs=-1)
knc.fit(X_train, y_train)
score = knc.score(X_test, y_test)
print ("Accuracy: " + str(score * 100))

"""**The following code is for the second part of the homework assignemnt. **"""

# numpy.rolls() shifts the array without padding the ends with zeros. No generic way to shift with padding.. 
def shiftImage(image, direction, shift=1):
  image = image.reshape(28,28)
  if direction == "up":
    image = np.roll(image, -shift, axis=0)
  elif direction == "down":
    image = np.roll(image, shift, axis=0)
  elif direction == "left":
    image = np.roll(image, -shift, axis=1)
  elif direction == "right":
    image = np.roll(image, shift, axis=1)
  image = image.reshape(1,784)
  return image

def shiftImages(images, direction, shift=1):
  for x in range(np.shape(images)[0]):
    images[x] = shiftImage(images[x], direction, shift)
  return images

leftShift = shiftImages(X_train, "left")
rightShift = shiftImages(X_train, "right")
upShift = shiftImages(X_train, "up")
downShift = shiftImages(X_train, "down")

augmentedX = np.concatenate((leftShift,rightShift,upShift,downShift), axis=0)
augmentedY=  np.concatenate((y_train, y_train,y_train,y_train), axis=0)

X_train = np.concatenate((X_train, augmentedX), axis=0)
y_train = np.concatenate((y_train, augmentedY), axis=0)

knc = KNeighborsClassifier(n_neighbors=bestK, weights=bestWeight , n_jobs=-1)
knc.fit(X_train, y_train)
score = knc.score(X_test, y_test)
print ("Accuracy: " + str(score * 100) + " (images shifted using numpy.roll()")