from lib import *


def main():
	menu()


def menu():
	print(
		"""
		0. Exit.
		1. Task 1. Constant noise
		2. Task 1. Gaussian noise
		3. Task 2. Median filter
		4. Task 2. Average filter
		5. Task 3. All comparison
		6. Task 3. Show cv2 filters
		"""
	)

	while True:
		input_symbol = int(input('Task >>> '))
		if input_symbol == 0:
			break
		elif input_symbol == 1:
			task1_const()
		elif input_symbol == 2:
			task1_noise()
		elif input_symbol == 3:
			task2_median_filter()
		elif input_symbol == 4:
			task2_averaging_filter()
		elif input_symbol == 5:
			task_3_comparison()
		elif input_symbol == 6:
			task_3_cv2()

def task1_const():
	img = cv2.imread('images/oka.jpg')
	cv2.imshow('Original', img)
	cv2.waitKey(0)
	cv2.imshow('With constant noise', constant_noise(image=img))
	cv2.waitKey(0)
	cv2.destroyAllWindows()


def task1_noise():
	img = cv2.imread('images/oka.jpg')
	cv2.imshow('Original', img)
	cv2.waitKey(0)
	cv2.imshow('With gaussian noise', add_gaussian_noise(image=img, mu=20, sigma=15))
	cv2.waitKey(0)
	cv2.destroyAllWindows()


def task2_median_filter():
	img = cv2.imread('images/okaNoise.jpg')
	cv2.imshow('Original', img)
	cv2.waitKey(0)
	e1 = cv2.getTickCount()
	result = median_filter(image = img, kernel_radius=1)
	e2 = cv2.getTickCount()
	time = (e2 - e1) / cv2.getTickFrequency()
	print(time, "sec")
	cv2.imshow('ImageFil', result)
	cv2.waitKey(0)
	cv2.imwrite('images/ImageMedianFilter.png', result)
	cv2.destroyAllWindows()


def task2_averaging_filter():
	img = cv2.imread('images/okaNoise.jpg')
	cv2.imshow('Original', img)
	cv2.waitKey(0)
	e1 = cv2.getTickCount()
	average_filter_img = averaging_filter(img, radius=1)
	e2 = cv2.getTickCount()
	time = (e2 - e1) / cv2.getTickFrequency()
	print(time, "sec")
	cv2.imshow('Average Filter', average_filter_img)
	cv2.waitKey(0)
	cv2.imwrite('images/AverageFilter.png', average_filter_img)
	cv2.destroyAllWindows()


def task_3_comparison():
	img = cv2.imread('images/okaNoise.jpg')

	e1 = cv2.getTickCount()
	result_med_our = median_filter(image=img)
	e2 = cv2.getTickCount()
	time1 = (e2 - e1) / cv2.getTickFrequency()

	e1 = cv2.getTickCount()
	result_med_cv2 = cv2.medianBlur(img, 3)
	e2 = cv2.getTickCount()
	time2 = (e2 - e1) / cv2.getTickFrequency()

	print(f"[OPENCV] cv2.medianBlur() - [OUR FILTER] median_filter() = {str(time2-time1)} sec.")
	mse, perc = immse(result_med_our, result_med_cv2)
	print(f"MSE median cv2 & our = {mse} ({perc} %)")

	e1 = cv2.getTickCount()
	average_our_img = averaging_filter(img, radius=1)
	e2 = cv2.getTickCount()
	time1 = (e2 - e1) / cv2.getTickFrequency()

	e1 = cv2.getTickCount()
	average_cv2_img = cv2.blur(img, (3, 3))
	e2 = cv2.getTickCount()
	time2 = (e2 - e1) / cv2.getTickFrequency()

	print(f"[OPENCV] cv2.blur() - [OUR FILTER] averaging_filter = {str(time2-time1)} sec.")
	mse, perc = immse(average_our_img, average_cv2_img)
	print(f"MSE average cv2 & our = {mse} ({perc} %)")

	mse, perc = immse(average_our_img, result_med_our)
	print(f"MSE our average & median = {mse} ({perc} %)")

def task_3_cv2():
	img = cv2.imread('images/okaNoise.jpg')
	med_cv2 = cv2.medianBlur(img, 3)
	average_cv2 = cv2.blur(img, (3, 3))
	cv2.imshow('Noise src', img)
	cv2.imshow('Median cv2', med_cv2)
	cv2.imshow('Average cv2', average_cv2)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

if __name__ == '__main__':
	main()
