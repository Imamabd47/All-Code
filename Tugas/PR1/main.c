#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Library.h> 

void terakhir_n(char *arr){
    int i=0;
    while (1){
        if (*(arr+i)=='\n'){
            *(arr+i)='\0';
            break;
        }
        i++;
    }
}

int hitung(char *arr){
    int count  = 1;
    int i=0;
    while (*(arr+i)!='\0'){
        if (*(arr+i)==' '){
            count += 1 ;
        }
        i++;
    }
    return count;
}

void str2list(char *arr, int *dest){
    char *token;
    int indeks = 0;
    token = strtok(arr," ");
    while (token!=NULL){
        sscanf(token,"%d",&dest[indeks]);
        token = strtok(NULL," ");
        indeks += 1;
    }
}

void printlist(int *arr,int size){
    int i;
    printf("\nList:{");
    for(i=0;i<size;i++){
        if (i+1!=size){
            printf("%d,",*(arr+i));
            }
        else{
            printf("%d}\n\n",*(arr+i));
        }
    }
}

void bigthree(){
    //Define text,str,fptr
    char text[15];
    char str[35];
    FILE *fptr;

    //Input text dan ganti null
    printf("\nMasukkan Nama File< ");
    fgets(text,15,stdin);fgets(text,15,stdin);terakhir_n(text);
    fptr = fopen(text,"r");
    fgets(str,35,fptr);
    int count = hitung(str);
    int list_i[count];
    str2list(str,list_i);  //ubah  string ke list integer
    printlist(list_i,count);  //Cek isi list(print)

    //Mulai cek cari 3 Integer terbesar
    int x,y,z; //Variabel untuk menampung  3 integer terbesar dari list_i|x>y>z 
    LargestThree(list_i,count,&x,&y,&z);
    printf("Berikut merupakan 3 elemen terbesarnya>\nTerbesar-1: %d\nTerbesar-2: %d\nTerbesar-3: %d\n",x,y,z);
    fclose(fptr);
}

void volume(){
    char text[15];
    char data[10];
    int data1[2];
    char *token;
    FILE *fptr;
    int i=0;

    //Input text dan ganti null
    printf("\nMasukkan Nama File< ");
    fgets(text,15,stdin);fgets(text,15,stdin);terakhir_n(text);
    fptr = fopen(text,"r");
    fgets(data,10,fptr);

    //memuat data tinggi dan jari jari
    token = strtok(data,",");
    while (token!= NULL){
        sscanf(token,"%d",&data1[i]);
        token = strtok(NULL,",");
        i++;
    }
    
    //Menghitung Volume dan Luas Permukaan
    float L,V;
    LuasPermukaanVolumeTabungan(data1[0],data1[1],&V,&L);
    printf("Volume dan Luas Permukaan dari Tabung dengan\nJari-jari %d dan Tinggi %d :\n\n",data1[1],data1[0]);
    printf("Volume: %.2f\nLuas Permukaan: %.2f\n",V,L);
    fclose(fptr);
}

int main(){
    int choice;
    printf("\nWELCCOOOOMEEEEE~~\n");
    while (choice!=0){
        printf("\nMau Ngapain Nich??\n[1]Cari 3 Angka terbesar dalam list\n[2]Cari Volume dan Luas Permukaan Tabung\n[0]Keluar\n");
        printf("\nMasukkan< ");scanf("%d",&choice);
        switch (choice){
            case 1:
                bigthree();
                break;
            case 2:
                volume();
                break;
            default:
                break;
        }
    }
    return 0;
}
