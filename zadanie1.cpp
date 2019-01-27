/*
- najpierw losujemy pośpiesznośc y i pT
- na podstawie y i pT obliczamy pZ ze wzoru 46.37
- na podstawie pZ i pT obliczamy kąt theta
- na podstawie theta liczymy pseydpośpieszność eta
- robimy wykresy eta i y
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main() {

  srand(time(NULL));

  int size = 1000;

  double * rapidity = new double[size];
  double * transverseMomentum = new double[size];
  double * zMomentum = new double[size];
  double * theta = new double[size];
  double * eta = new double[size];
  double mass = 1.8; //GeV

  fstream file;

  file.open("results.txt", ios::out);
	file.seekg(0, ios::beg);
	if (file.good()) {
		cout << "Opened file!" << endl << endl;
	} else {
		cout << "Access to file denied!" << endl << endl;
	}

  file << "n\ty\tpT\tpZ\ttheta\teta" << endl;

  for (int i = 0; i < size; i++) {
    rapidity[i] = fRand(-5, 5);
    transverseMomentum[i] = fRand(-10, 10);
    zMomentum[i] = sqrt(pow(mass, 2) + pow(transverseMomentum[i], 2)) * sinh(rapidity[i]);
    theta[i] = atan(transverseMomentum[i] / zMomentum[i]);
    eta[i] = -log(tan(theta[i] / 2));
    file << i + 1 << "\t" << rapidity[i] << "\t" << transverseMomentum[i] << "\t" << zMomentum[i] << "\t" << theta[i] << "\t" << eta[i] << endl;
  }

  file.close();

  cout << "Saving succeeded!" << endl;

  return 0;
}
