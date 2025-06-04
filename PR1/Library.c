#include "Library.h"
#include <stdio.h>

void LargestThree(int *arr,int size, int *a, int *b, int *c) {
    *a = *b = *c = 0; // Initialize the largest three numbers to zero
    int i;int j;int x;int k;
    int *hasil[3]; hasil[0]=a; hasil[1]=b; hasil[2]=c;
    int used[size];
        for (i = 0; i < size; i++){
            used[i]=0;
        }   

    switch (size){
    //Kalau Size 2
    case 2:
        if (*(arr)>*(arr+1)){
            *a = *(arr);
            *b = *(arr+1);
            *c = *b;
        }
        else{
            *a = *(arr+1);
            *b = *(arr);
            *c = *b;
        }
    
        break;

    //Kalau Size 1
    case 1:{
        *a = *(arr);
        *b = *a;
        *c = *a;
        break;
    }
    //Kalau Size lebih dari 3
    default:{
        for (k = 0; k < 3; k++){
                for(i=0;i<size;i++){
                    if (i == 0){
                        for ( j = 0; j < size; j++){
                            if (used[j]!=1){
                                **(hasil+k) = *(arr+i);
                                x = i;
                                break;
                            }
                        }
                    }
                    else{
                        if ((**(hasil+k) < *(arr+i))&&(*(used+i)!=1)){
                            **(hasil+k) = *(arr+i);
                            x = i;
                        }
                    }
                }
                *(used+x)= 1;
            }
        break;
        }
    }
}

void LuasPermukaanVolumeTabungan(int h, int r, float *V, float *L){
    float phi = 3.14159;
    *V = phi * r * r * h;
    *L = 2 * phi * r * (r+h);
}

