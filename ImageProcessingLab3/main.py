from Canny import *
import time
from distance_map import *
from watershed import *


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


def test_canny():
    print('----------TEST CANNY----------')
    img = cv2.imread('images/sp.jpg')
    cv2.imshow('Source Image', img)
    cv2.waitKey(0)
    t0 = cv2.getTickCount()
    imgCanny = Canny(img)
    t1 = cv2.getTickCount()
    time_our = (t1 - t0) / cv2.getTickFrequency()
    cv2.imshow('CannyOur', imgCanny)
    t0 = cv2.getTickCount()
    imgCannyCv2 = cv2.Canny(img, 128, 180)
    t1 = cv2.getTickCount()
    time_cv2 = (t1 - t0) / cv2.getTickFrequency()
    cv2.imshow('CannyCV2', imgCannyCv2)
    print(f'our time: {time_our} sec, cv2 time: {time_cv2} sec')
    mse, percent = immse(imgCanny, cv2.cvtColor(imgCannyCv2, cv2.COLOR_GRAY2BGR))
    print (f'mse: {mse} ~ {percent} %')
    cv2.waitKey(0)
    cv2.destroyAllWindows()


def test_watershed():
    print('--------TEST WATERSHED--------')
    img = cv2.imread('images/tesla.jpg')
    cv2.imshow('Source Image', img)
    cv2.waitKey(0)
    print('Doing ... Wait, please ...')
    distances = distance_map(img)

    time1 = cv2.getTickCount()
    watershed_image = watershed_alg(img, distances)
    time2 = cv2.getTickCount()
    
    time_our = (time2 - time1) / cv2.getTickFrequency()
    print(f'our time: {time_our} sec')

    cv2.imshow('Watershed Image', watershed_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def test_distance_map():
    print('--------TEST DISTANCE--------')
    img = cv2.imread('images/tesla.jpg')
    cv2.imshow('Source Image', img)
    cv2.waitKey(0)
    time1 = cv2.getTickCount()
    final_image = distance_map(img)
    time2 = cv2.getTickCount()
    time = (time2 - time1) / cv2.getTickFrequency()
    print(f'our time: {time} sec')
    cv2.imshow('Distance map', final_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == '__main__':
    test_canny()
    test_distance_map()
    test_watershed()
