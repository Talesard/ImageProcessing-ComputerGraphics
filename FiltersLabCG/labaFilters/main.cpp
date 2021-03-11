#include <QtCore/QCoreApplication>
#include <qimage.h>
#include <string>
#include "Filters.h"
#include <iostream>
#include <Windows.h>
#include "MultiThreadFunctions.h"
using namespace std;

void main(int argc, char *argv[]){
	setlocale(LC_ALL, "Russian");
	cout << "1. ћеню выбора фильтров" << endl;
	cout << "2. «апустить все в многопотоке с рекомендуемыми картинками" << endl;
	int startmenu = 0;
	cout << "> ";
	cin >> startmenu;

	if (startmenu == 1) {//меню
		string s;
		QImage photo;
		for (int i = 0; i < argc; i++) {
			if (!strcmp(argv[i], "-p") && (i + 1 < argc)) {
				s = argv[i + 1];
			}
		}
		cout << s << endl << endl;
		int fname = -1;
		do {
			cout << "-1. Exit" << endl;
			cout << " 0. Original" << endl;
			cout << " 1. Invert" << endl;
			cout << " 2. Blur" << endl;
			cout << " 3. Gauss Blur" << endl;
			cout << " 4. Gray Scale" << endl;
			cout << " 5. Sepia" << endl;
			cout << " 6. Brightness" << endl;
			cout << " 7. Sobel" << endl;
			cout << " 8. Sharpness #1" << endl;
			cout << "-----lab-----" << endl;
			cout << " 9. Embossing" << endl;
			cout << "10. Rotation" << endl;
			cout << "11. Waves" << endl;
			cout << "12. Sharpness #2" << endl;
			cout << "13. Dilation\t\t\t(wolf.png recommended for test)" << endl;
			cout << "14. Erosion\t\t\t(cat.png recommended for test)" << endl;
			cout << "15. Opening\t\t\t(cat.png recommended for test)" << endl;
			cout << "16. Closing\t\t\t(wolf.png recommended for test)" << endl;
			cout << "17. Grad\t\t\t(grlec.png recommended for test)" << endl;
			cout << "18. Median" << endl;
			cout << "19. Gray World" << endl;
			cout << "20. Linear Stretch\t\t(lslec2.png recommended for test)" << endl;
			cout << "21. Open Folder" << endl;
			cout << "Filter number->";
			cin >> fname;
			photo.load(QString(s.c_str()));
			photo.save("Starting.PNG");
			switch (fname) {
			case -1: {return; break; }
			case 0: {system("Starting.PNG"); break; }
			case 1: {
				Invert_Filter* invert = new Invert_Filter();
				QImage invertImage = invert->calculateNewImagePixMap(photo, 0);
				invertImage.save("Invert.PNG");
				cout << "done\n";
				system("Invert.PNG");
				break;
			}
			case 2: {
				Blur_Filter* blur = new Blur_Filter();
				QImage blurImage = blur->calculateNewImagePixMap(photo, 1);
				blurImage.save("Blur.PNG");
				cout << "done\n";
				system("Blur.PNG");
				break;
			}
			case 3: {
				Gaussian_Blur_Filter* gblur = new Gaussian_Blur_Filter();
				QImage gblurImage = gblur->calculateNewImagePixMap(photo, 3);
				gblurImage.save("GaussBlur.PNG");
				cout << "done\n";
				system("GaussBlur.PNG");
				break;
			}
			case 4: {
				Gray_Scale_Filter* grayscale = new Gray_Scale_Filter();
				QImage grayscaleImage = grayscale->calculateNewImagePixMap(photo, 0);
				grayscaleImage.save("GrayScale.PNG");
				cout << "done\n";
				system("GrayScale.PNG");
				break;
			}
			case 5: {
				Sepia_Filter* sepia = new Sepia_Filter();
				QImage sepiaImage = sepia->calculateNewImagePixMap(photo, 25);
				sepiaImage.save("Sepia.PNG");
				cout << "done\n";
				system("Sepia.PNG");
				break;
			}
			case 6: {
				Brihtness_Filter* bright = new Brihtness_Filter();
				QImage brightImage = bright->calculateNewImagePixMap(photo, 100);
				brightImage.save("Brightness.PNG");
				cout << "done\n";
				system("Brightness.PNG");
				break;
			}
			case 7: {
				Sobel_Filter* sobel = new Sobel_Filter();
				QImage sobelImage = sobel->calculateNewImagePixMap(photo, 1);
				sobelImage.save("Sobel.PNG");
				cout << "done\n";
				system("Sobel.PNG");
				break;
			}
			case 8: {
				Sharpness_Filter* sharp = new Sharpness_Filter();
				QImage sharpImage = sharp->calculateNewImagePixMap(photo, 1);
				sharpImage.save("Sharpness1.PNG");
				cout << "done\n";
				system("Sharpness1.PNG");
				break;
			}
			case 9: {
				Embossing_Filter* emb = new Embossing_Filter();
				QImage embImage = emb->calculateNewImagePixMap(photo, 1);
				embImage.save("Embossing.PNG");
				cout << "done";
				system("Embossing.PNG");
				break;
			}
			case 10: {
				Rotation_Filter* rot = new Rotation_Filter();
				QImage rotImage = rot->calculateNewImagePixMap(photo, 0);
				rotImage.save("Rotation.PNG");
				cout << "done\n";
				system("Rotation.PNG");
				break;
			}
			case 11: {
				Waves_Filter* wav = new Waves_Filter();
				QImage wavImage = wav->calculateNewImagePixMap(photo, 0);
				wavImage.save("Waves.PNG");
				cout << "done\n";
				system("Waves.PNG");
				break;
			}
			case 12: {
				Sharpness2_Filter* sharp = new Sharpness2_Filter();
				QImage sharpImage = sharp->calculateNewImagePixMap(photo, 1);
				sharpImage.save("Sharpness2.PNG");
				cout << "done\n";
				system("Sharpness2.PNG");
				break;
			}
			case 13: {
				int* strElem;
				strElem = new int[9];
				strElem[0] = 1; strElem[3] = 1; strElem[6] = 1;
				strElem[1] = 1; strElem[4] = 1; strElem[7] = 1;
				strElem[2] = 1; strElem[5] = 1; strElem[8] = 1;
				Dilation* dil = new Dilation();
				QImage dilImage = dil->calculateNewImagePixMap(photo, 1, strElem);
				dilImage.save("Dilation.PNG");
				cout << "done\n";
				system("Dilation.PNG");
				break;
			}
			case 14: {
				int* strElem;
				strElem = new int[9];
				strElem[0] = 1; strElem[3] = 1; strElem[6] = 1;
				strElem[1] = 1; strElem[4] = 1; strElem[7] = 1;
				strElem[2] = 1; strElem[5] = 1; strElem[8] = 1;
				Erosion* eros = new Erosion();
				QImage erosImage = eros->calculateNewImagePixMap(photo, 1, strElem);
				erosImage.save("Erosion.PNG");
				cout << "done\n";
				system("Erosion.PNG");
				break;
			}
			case 15: {
				int* strElem;
				strElem = new int[9];
				strElem[0] = 1; strElem[3] = 1; strElem[6] = 1;
				strElem[1] = 1; strElem[4] = 1; strElem[7] = 1;
				strElem[2] = 1; strElem[5] = 1; strElem[8] = 1;
				Opening* op = new Opening();
				QImage opImage = op->calculateNewImagePixMap(photo, 1, strElem);
				opImage.save("Opening.PNG");
				cout << "done\n";
				system("Opening.PNG");
				break;
			}
			case 16: {
				int* strElem;
				strElem = new int[9];
				strElem[0] = 1; strElem[3] = 1; strElem[6] = 1;
				strElem[1] = 1; strElem[4] = 1; strElem[7] = 1;
				strElem[2] = 1; strElem[5] = 1; strElem[8] = 1;
				Closing* cl = new Closing();
				QImage clImage = cl->calculateNewImagePixMap(photo, 1, strElem);
				clImage.save("Closing.PNG");
				cout << "done\n";
				system("Closing.PNG");
				break;
			}
			case 17: {
				int* strElem;
				strElem = new int[9];
				strElem[0] = 0; strElem[3] = 1; strElem[6] = 0;
				strElem[1] = 1; strElem[4] = 1; strElem[7] = 1;
				strElem[2] = 0; strElem[5] = 1; strElem[8] = 0;
				Grad* gr = new Grad();
				QImage grImage = gr->calculateNewImagePixMap(photo, 1, strElem);
				grImage.save("Grad.PNG");
				cout << "done\n";
				system("Grad.PNG");
				break;
			}
			case 18: {
				Median_Filter* med = new Median_Filter();
				QImage medImage = med->calculateNewImagePixMap(photo, 2);
				medImage.save("Mediane.PNG");
				cout << "done\n";
				system("Mediane.PNG");
				break;
			}
			case 19: {
				Gray_World* gw = new Gray_World();
				QImage gwImage = gw->calculateNewImagePixMap(photo);
				gwImage.save("GrayWorld.PNG");
				cout << "done\n";
				system("GrayWorld.PNG");
				break;
			}
			case 20: {
				Linear_Stretch* ls = new Linear_Stretch();
				QImage lsImage = ls->calculateNewImagePixMap(photo);
				lsImage.save("LinearStretch.PNG");
				cout << "done\n";
				system("LinearStretch.PNG");
				break;
			}
			case 21: {
				system("explorer.exe .");
				break;
			}
			default: {
				cout << "Invalid input!" << endl;
			}
			}
			system("cls");
		} while (fname != -1);
	}

	if (startmenu == 2) {//все через многопоток
		std::cout << std::endl;
		loadimages();
		HANDLE handles[20];
		handles[0] = CreateThread(NULL, 0, &InversionTP, NULL, 0, NULL);
		handles[1] = CreateThread(NULL, 0, &BlurTP, NULL, 0, NULL);
		handles[2] = CreateThread(NULL, 0, &GaussianTP, NULL, 0, NULL);
		handles[3] = CreateThread(NULL, 0, &GrayScaleTP, NULL, 0, NULL);
		handles[4] = CreateThread(NULL, 0, &SepiaTP, NULL, 0, NULL);
		handles[5] = CreateThread(NULL, 0, &BrithnessTP, NULL, 0, NULL);
		handles[6] = CreateThread(NULL, 0, &SobelTP, NULL, 0, NULL);
		handles[7] = CreateThread(NULL, 0, &EmbossingTP, NULL, 0, NULL);
		handles[8] = CreateThread(NULL, 0, &RotationTP, NULL, 0, NULL);
		handles[9] = CreateThread(NULL, 0, &WavesTP, NULL, 0, NULL);
		handles[10] = CreateThread(NULL, 0, &Sharpness1TP, NULL, 0, NULL);
		handles[11] = CreateThread(NULL, 0, &Sharpness2TP, NULL, 0, NULL);
		handles[12] = CreateThread(NULL, 0, &DilationTP, NULL, 0, NULL);
		handles[13] = CreateThread(NULL, 0, &ErosionTP, NULL, 0, NULL);
		handles[14] = CreateThread(NULL, 0, &ClosingTP, NULL, 0, NULL);
		handles[15] = CreateThread(NULL, 0, &OpeningTP, NULL, 0, NULL);
		handles[16] = CreateThread(NULL, 0, &GradTP, NULL, 0, NULL);
		handles[17] = CreateThread(NULL, 0, &MedianTP, NULL, 0, NULL);
		handles[18] = CreateThread(NULL, 0, &GrayWorldTP, NULL, 0, NULL);
		handles[19] = CreateThread(NULL, 0, &LinearStretchTP, NULL, 0, NULL);
		WaitForMultipleObjects(20, handles, true, INFINITE);
	}
}
