import sys
import cv2
from matplotlib import pyplot as plt
import numpy as np

img = cv2.imread(sys.argv[1], 0)

cv2.imshow("Original Image", img)

hist = cv2.calcHist([img], [0], None, [256], [0, 256])

p1 = plt.figure(1)
plt.plot(hist)

cv2.add(img, 40, img)
np.clip(img, 0, 255, out=img)
cv2.imshow("New Image", img)

hist = cv2.calcHist([img], [0], None, [256], [0, 256])

p2 = plt.figure(2)
plt.plot(hist)

p1.show()
p2.show()

cv2.waitKey(0)
print('Done')
