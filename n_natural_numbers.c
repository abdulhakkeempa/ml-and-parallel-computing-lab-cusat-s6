#include <stdio.h>
#include <omp.h>

int main(){
  int N;
  printf("Enter the natural number: ");
  scanf("%d", &N);
#pragma omp parallel for
  for(int i=0;i<N;i++){
    printf("%i from thread number %i  \n",i, omp_get_thread_num());
  }
  return 0;
}
