import cv2
import numpy as np
from lib import *
import time

def task_1_immse():
    print('[TAKS 1: IMMSE] <Starting testing>')
    img1 = cv2.imread('images/etg.jpg')
    img2 = cv2.imread('images/etgNoise.jpg')
    mse = immse(img1, img2)
    print('\tmse = ' + str(mse))
    try:
        coincidence = (255 ** 2 - mse) / (255 ** 2) * 100
    except ZeroDivisionError:
        coincidence = 0
    print('\tCoincidence = ' + str(coincidence) + ' %')
    print('[TASK 1] <Successfully has ended>')

def task_2_average_of_rgb():
    print('[TAKS 2: AVERAGE OF RGB] <Starting testing>')
    img1 = cv2.imread('images/etg.jpg')
    img2 = cv2.imread('images/etg.jpg')
    print('[Opening images...]')
    start_time = time.time()
    cv2.imshow('my ', average_of_rgb(img1))
    print(f'\tmy time = {(time.time() - start_time)} seconds')
    start_time = time.time()
    cv2.imshow('opencv ', cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY))
    print(f'\topencv time = {(time.time() - start_time)} seconds')
    mse = immse(img1, img2)
    coincidence = (255 ** 2 - mse) / (255 ** 2) * 100
    print(f'\tmse = {mse}')
    print(f'\tcoincidence = {int(coincidence)} %')
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print('[TASK 2] <Successfully has ended>')

def task_3_bgr_to_hsv():
    print('[TAKS 3: BGR TO HSV] <Starting testing>')
    img1 = cv2.imread('images/img.jpg')
    img2 = cv2.imread('images/img.jpg')
    print('[Opening images...]')
    start_time = time.time()
    cv2.imshow('my ', bgr_to_hsv(img1))
    print(f'\tmy time = {(time.time() - start_time)} seconds')
    start_time = time.time()
    cv2.imshow('openCV ', cv2.cvtColor(img2, cv2.COLOR_BGR2HSV))
    print(f'\topencv time = {(time.time() - start_time)} seconds')
    mse = immse(img1, img2)
    coincidence = (255 ** 2 - mse) / (255 ** 2) * 100
    print(f'\tmse = {mse}')
    print(f'\tcoincidence = {int(coincidence)} %')
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print('[TASK 3] <Successfully has ended>')

def task_3_hsv_to_bgr():
    print('[TAKS 3: HSV TO BGR] <Starting testing>')
    img1 = cv2.imread('images/img.jpg')
    img2 = cv2.imread('images/img.jpg')
    img1_hsv = bgr_to_hsv(img1)
    print('[Opening images...]')
    img2_hsv = cv2.cvtColor(img2, cv2.COLOR_BGR2HSV)
    start_time = time.time()
    cv2.imshow('my ', hsv_to_bgr(img1_hsv))
    print(f'\tmy time = {(time.time() - start_time)} seconds')
    start_time = time.time()
    cv2.imshow('openCV ', cv2.cvtColor(img2_hsv, cv2.COLOR_HSV2BGR))
    print(f'\topencv time = {(time.time() - start_time)} seconds')
    mse = immse(img1_hsv, img2_hsv)
    coincidence = (255 ** 2 - mse) / (255 ** 2) * 100
    print(f'\tmse = {mse}')
    print(f'\tcoincidence = {int(coincidence)} %')
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print('[TASK 3] <Successfully has ended>')

def task_3_brightness_bgr():
    print('[TAKS 3: BRIGHTNESS BGR] <Starting testing>')
    img = cv2.imread('images/etg.jpg')
    print('[Opening image...]')
    start_time = time.time()
    cv2.imshow('my ', brightness_inc_bgr(img, 150))
    print(f'\tmy time = {(time.time() - start_time)} seconds')
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print('[TASK 3] <Successfully has ended>')
    
def task_3_brightness_hsv():
    print('[TAKS 3: BRIGHTNESS HSV] <Starting testing>')
    img = cv2.imread('images/etg.jpg')
    print('[Opening image...]')
    img = bgr_to_hsv(img)
    start_time = time.time()
    br_img = brightness_inc_hsv(img, 50)
    print(f'\tmy time = {(time.time() - start_time)} seconds')
    cv2.imshow('my ', hsv_to_bgr(br_img))
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    print('[TASK 3] <Successfully has ended>')

def task_3_immse_comp_in_time():
    print('[TASK 3: IMMSE COMP IN TIME] <Starting testing>')
    img = cv2.imread('images/etg.jpg')
    img_bgr = img
    img = cv2.imread('images/etg.jpg')
    img_hsv = img
    time1, time2, img_bgr, img_hsv = immse_comp_in_time(img_bgr, 100, img_hsv, 100)
    print('\ttime BGR img filtering = ' + str(time1) + ' seconds')
    print('\ttime HSV img filtering = ' + str(time2)+ ' seconds')
    print('[TASK 3] <Successfully has ended>')


def main():
    menu()


def menu():
    print(
        """
        0. Exit.
        1. Task 1. MMSE
        2. Task 2. Average of RGB
        3. Task 3. BGR to HVS
        4. Task 3. HSV to BGR
        5. Task 3. Brightness increment BGR
        6. Task 3. Brightness increment HSV
        7. Task 3. HSV&BGR brightness comparison in time + IMMSE
        """
    )

    while True:
        input_symbol = int(input('Task >>> '))
        if input_symbol == 0:
            break
        if input_symbol == 1:
            task_1_immse()
        elif input_symbol == 2:
            task_2_average_of_rgb()
        elif input_symbol == 3:
            task_3_bgr_to_hsv()
        elif input_symbol == 4:
            task_3_hsv_to_bgr()
        elif input_symbol == 5:
            task_3_brightness_bgr()
        elif input_symbol == 6:
            task_3_brightness_hsv()
        elif input_symbol == 7:
            task_3_immse_comp_in_time()


if __name__ == '__main__':
    main()
