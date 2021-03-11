import cv2
import numpy as np


def toGray1ch(img):
    (width, height, c) = img.shape
    res = np.zeros((width, height))
    for x in range(width):
        for y in range(height):
            b = int(img.item(x, y, 0))
            g = int(img.item(x, y, 1))
            r = int(img.item(x, y, 2))
            avg = (b + g + r) // 3
            res.itemset((x, y), avg)
    return res


def toGrayForWaterShed(input_image):
    (height, width, channel) = input_image.shape
    res = np.zeros(shape=(height, width), dtype='uint8')
    for x in range(width):
        for y in range(height):
            b = input_image[y, x, 0]
            g = input_image[y, x, 1]
            r = input_image[y, x, 2]
            sum = 0.2952 * r + 0.5547 * g + 0.148 * b
            res[y, x] = sum
    return res


def add_borders(img, mark, r):
	for i in range(r, mark.shape[0]-r):
		for j in range(r, mark.shape[1]-r):
			if mark[i][j] == -1:
				for x in range(i-r, i+r+1):
					for y in range(j-r, j+r+1):
						img[x][y] = (0,255,0)
	return img

def watershed_alg(input_image, distances):
    copy_image = np.copy(input_image)
    gray_image = toGrayForWaterShed(copy_image)
    rets, binare_image = cv2.threshold(gray_image,100, 255,
                                       cv2.THRESH_BINARY)
    back = cv2.dilate(binare_image,
                      cv2.getStructuringElement(cv2.MORPH_RECT,
                                                (3, 3)), iterations=3)
    ret, markers = cv2.connectedComponents(back)
    rets, fore = cv2.threshold(distances, distances.max() * 0.6, 255,
                               cv2.THRESH_BINARY)
    markers +=  1
    a = cv2.subtract(back, np.uint8(fore))
    markers[a == 255] = 0
    markers = cv2.watershed(copy_image, markers=markers)
    return add_borders(copy_image, markers, 2)
  