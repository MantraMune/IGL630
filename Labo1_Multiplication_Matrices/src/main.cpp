#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <functional>
#include <algorithm>
#include <thread>
#include <format> 
#include <iomanip>


using matrice_t = std::vector<std::vector<int>>;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 99);


struct matrice{
  matrice_t operator()(size_t ligne, size_t col, bool initialiser) {
    matrice_t m(ligne, std::vector<int>(col));
    for (size_t i = 0; i < ligne; ++i)
      for (size_t j = 0; j < col; ++j)
        m[i][j] =  initialiser ? dis(gen) : 0;
    return m;
  }
};

std::ostream& operator<<(std::ostream& os, const matrice_t& m) {
  for (const auto& row : m) {
    for (const auto& elem : row)
      os << std::setw(2) << elem << " ";
    os << "\n";
  }
  return os;
}

void calculBloc(const matrice_t& A, const matrice_t& B, matrice_t& resultat, int debut, int fin) {
  int m = A[0].size(); // Nombre de colonnes de A
  int p = B[0].size(); // Nombre de colonnes de B

  for (int i = debut; i < fin; ++i) 
  {
    for (int j = 0; j < p; ++j)
    {
      resultat[i][j] = 0; // On initialise la matrice C
      for (int k = 0; k < m; ++k)
      {
        resultat[i][j] += A[i][k] * B[k][j]; // On fait le produit de A et B
      }
    }
  } 
}

int main() {
  enum { N = 3, M = 4, P = 3, NB_FILS = N }; // Nombre de lignes de A (n), colonnes de A (m) et B (p), et nombre de fils
  matrice_t A = matrice()(N, M, true);
  matrice_t B = matrice()(M, P, true);
  matrice_t C = matrice()(N, P, false);

  size_t taille_segment = N / NB_FILS; // Taille de chaque segment à traiter par un thread
  std::vector<std::thread> threads; // Vecteur pour stocker les threads
  

  for (size_t i = 1; i < NB_FILS + 1; ++i) 
  {
    int debut = (i - 1) * taille_segment;
    int fin = std::min(i * taille_segment, static_cast<size_t>(N));
    threads.emplace_back(calculBloc, std::ref(A), std::ref(B), std::ref(C), debut, fin); // emplace_back insère chaque thread à la fin du vecteur 
  }

  for (auto& th : threads) 
  {
    th.join(); // On attend que tous les threads aient terminé
  }

  // Affichage des matrices
  std::cout << "A :\n" << A;
  std::cout << "B :\n" << B;
  std::cout << "C :\n" << C;
  
  return 0;  
}