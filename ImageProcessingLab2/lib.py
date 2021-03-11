import cv2
import numpy as np
from copy import copy

def constant_noise(image):
    res_image = copy(image)
    width, height, channel = image.shape
    noise = (np.random.random(size=(width, height))) * 64
    for c in range(channel):
        res_image[:, :, c] = res_image[:, :, c] + noise
    return res_image

def add_gaussian_noise(image, mu, sigma):
    res_image = copy(image)
    width, height, channel = image.shape
    noise = np.random.normal(mu, sigma, size=(width, height))
    for c in range(channel):
        res_image[:, :, c] = res_image[:, :, c] + noise
    return res_image


def median_filter(image, kernel_radius=1):
    result_image = copy(image)
    width, height = image.shape[:2]
    med_index = (2 * kernel_radius + 1) ** 2 // 2
    for x in range(kernel_radius, width - kernel_radius):
        for y in range(kernel_radius, height - kernel_radius):
            submatrix = image[x - kernel_radius: x + kernel_radius +
                              1, y - kernel_radius: y + kernel_radius + 1, :]
            submatrix = submatrix.reshape(-1, 3)
            submatrix = submatrix.tolist()
            submatrix.sort(key=lambda v: v[0]*0.3 + v[1]*0.59 + v[2]*0.11)
            result_image[x, y] = submatrix[med_index]
    return result_image


def averaging_filter(image, radius: int = 1):
    filtered_image = np.ndarray(image.shape, dtype=np.uint8)
    for x in range(radius, image.shape[0] - radius):
        for y in range(radius, image.shape[1] - radius):
            for z in range(image.shape[2]):
                filtered_image[x, y, z] = np.average(
                    image[x-radius:x+(radius+1), y-radius:y+(radius+1), z])
    return filtered_image


def immse(img1, img2):
    img_width, img_height, img_channel = img1.shape
    sm = np.int64()
    mse = np.int64()
    for x in range(img_width):
        for y in range(img_height):
            avg1 = (np.int64(img1.item(x, y, 0)) +
                    np.int64(img1.item(x, y, 1)) +
                    np.int64(img1.item(x, y, 2))) // 3

            avg2 = (np.int64(img2.item(x, y, 0)) +
                    np.int64(img2.item(x, y, 1)) +
                    np.int64(img2.item(x, y, 2))) // 3
            sm += (avg1 - avg2) ** 2
    mse = sm / (img_width * img_height)
    percent = int((255 ** 2 - mse) / (255 ** 2) * 100)
    return mse, percent
