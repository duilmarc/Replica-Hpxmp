#include <iostream>
#include <time.h>
#include <blaze/Math.h>
#include <omp.h>

#define endl '\n'

using blaze::StaticVector;
using blaze::DynamicVector;
using blaze::CompressedMatrix;
using blaze::columnMajor;

using std::cout;

int main(int argc, char* argv[])
{
   int thread_count = strtol(argv[1], NULL, 10);
   omp_set_num_threads( thread_count );
   const size_t threads = blaze::getNumThreads();
   cout << "Numero de threads: " << threads << endl;
   cout << "=======================================\n";
   float start, finish;
   clock_t start_c, finish_c; 
   constexpr unsigned long  sz = 2*100*100*1UL;
   start_c = clock(); 
      blaze::DynamicMatrix<float,blaze::rowMajor> A( sz, sz, rand()%10);
      blaze::DynamicMatrix<float,blaze::rowMajor> B( sz, sz, rand()%10);
      blaze::DynamicMatrix<float,blaze::rowMajor> C( sz, sz, rand()%10);
   finish_c = clock(); 
   printf("Instanciacion de matrices mediante blaze en  %f segundos.\n", int(threads), float((finish_c - start_c) / double(CLOCKS_PER_SEC)));   
   int j, i;
   start = omp_get_wtime();
   for (int i = 0; i < sz; ++i)
   {
      #pragma omp parallel for num_threads(1) private(j)
      for (j = 0; j < sz; ++j)
      {
         A.at(i,j) = rand()%10;
         B.at(i,j) = rand()%10;
      }
   }
   finish = omp_get_wtime();
   printf("Asignacion de matrices en %f segundos.\n", float(finish-start));   
   start = omp_get_wtime();
   #pragma omp sections
   {
      #pragma omp section
      C=A+B;
   }
   finish = omp_get_wtime(); 
    printf("Suma de Matrices %d threads en %f seconds.\n", int(threads), float(finish-start));
}
