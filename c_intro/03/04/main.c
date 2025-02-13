/*
Следующая программа выводит таблицу Пифагора для чисел от 1 до 5.
*/

#include <stdio.h> 
int main(void){

  for (int i=1; i<=5; i++){
    for (int j=1; j<=5; j++)
      printf("%-5d",i*j);
    printf("\n");
  }

  return(0);
}