import numpy as np
import cv2

def trim(x):
    if x > 255:
        return 255
    else:
        return x

def border(matr):
    val = 254
    matr[0, :] = val
    matr[:, 0] = val
    matr[matr.shape[0]-1, :] = val
    matr[:, matr.shape[1]-1] = val
    return matr

def toGray1ch(img):
    (img_width, img_height, c) = img.shape
    res = np.zeros((img_width, img_height))
    for x in range(img_width):
        for y in range(img_height):
            b = int(img.item(x, y, 0))
            g = int(img.item(x, y, 1))
            r = int(img.item(x, y, 2))
            avg = (b + g + r) // 3
            res.itemset((x, y), avg)
    return res

def distance_map(image):
    image = toGray1ch(image)
    retv, image = cv2.threshold(image, 100, 255, cv2.THRESH_BINARY)
    img_height, img_width = image.shape
    distMatrix = border(np.zeros((img_height + 2, img_width + 2), dtype=np.uint8))
    for y in range(img_height):
        for x in range(img_width):
            if (image[y, x] != 0):
                tmp = min(distMatrix[y, x+1], distMatrix[y+1, x]) + 1
                trim(tmp)
                distMatrix[y+1, x+1] = tmp
    resultMatrix = np.zeros((img_height, img_width), dtype=np.uint8)
    for y in reversed(range(img_height)):
        for x in reversed(range(img_width)):
            if (image[y, x] != 0):
                tmp = min(min(distMatrix[y+1 + 1, x+1], distMatrix[y+1, x+1 + 1]) + 1, distMatrix[y+1, x+1])
                trim(tmp)
                distMatrix[y+1, x+1] = tmp
                resultMatrix[y, x] = tmp
    return resultMatrix
