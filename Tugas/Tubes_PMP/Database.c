#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct

struct pegawai{
    char nama[50];
    int maks_shift;
    char preferensi_shift[25];
    struct pegawai *next;
    struct pegawai *before;
} ;

struct pegawai *Data_Pegawai = NULL; //Data Pegawai 
struct pegawai *first = NULL;//Menyimpan node awal dari Data_Pegawai

void printBanner(const char *text, char border, int totalWidth) {
    printf("\n");
    int textLen = strlen(text);
    int side = (totalWidth - textLen - 2) / 2; // -2 for spaces around text
    for (int i = 0; i < side; i++) printf("%c", border);
    printf(" %s ", text);
    for (int i = 0; i < side; i++) printf("%c", border);
    printf("\n");
}

void preferensi_hari(char *arr,char *dest){
    int T[3]={0};
    //Cek pagi
    if (strstr(arr,"pagi")!=NULL)
        T[0] = 1;
    //Cek Siang
    if (strstr(arr,"siang")!=NULL)
        T[1] = 1;
    //Cek malam
    if (strstr(arr,"malam")!=NULL)
        T[2] = 1;
    //Cek bebas
    if (strstr(arr,"bebas")!=NULL){
         T[0]=1;T[1]=1;T[2]=1;
    }    
    /*printf("T[0]:%d |T[1]:%d |T[2]%d\n",T[0],T[1],T[2]);*/
    if (T[2]==1&&T[1]==1&&T[0]==1)
        strcpy(dest,"Pagi,Siang,Malam") ; //0 Bebas
    else if (T[2]==1&&T[1]==1)
        strcpy(dest,"Siang,Malam");  //6 siang dan malam
    else if (T[0]==1&&T[2]==1)
        strcpy(dest,"Pagi,Malam");  //5 pagi dan malam
    else if (T[0]==1&&T[1]==1)
        strcpy(dest,"Pagi,Siang");  //4 pagi dan Siang
    else if (T[2]==1)
        strcpy(dest,"Malam");  //3 malam
    else if (T[1]==1)
        strcpy(dest,"Siang");  //2 siang
    else 
        strcpy(dest,"Pagi");  //1 pagi
}

void file2list(char *data){
    struct pegawai *temp = malloc(sizeof(struct pegawai));
    //Beri node next
    temp->next = NULL;
    //Beri node before 
    if (Data_Pegawai == NULL){
       temp -> before = NULL;
       first = temp;
    }
    else{
        temp -> before = Data_Pegawai;
        Data_Pegawai -> next = temp;
    }
    //Ambil nama
    char *token ;
    token = strtok(data,",");
    strcpy(temp->nama,token);
    //Ambil Maks Shift
    token = strtok(NULL,",");
    sscanf(token,"%d",&(temp->maks_shift));
    //Ambil Preferensi Shift
    token = strtok(NULL,",");
    preferensi_hari(token,temp->preferensi_shift);
    Data_Pegawai  = temp;
}

void input_string(char *arr){
    fgets(arr,100,stdin);
    int i=0;
    while (1){
        if (*(arr+i)=='\n'){
            *(arr+i)='\0';
            break;
        }
        i++;
    }  
}

void Tampil(){
    struct pegawai *temp = first;
    printBanner("DATA PEGAWAI",'=',100);
    printf("%-36s%-39s%-25s\n","Nama Pegawai","Maksimal Shift(Per Minggu)","Preferensi Shift");
    while (temp != NULL){
        printf("%-36s%11s%d%27s%-25s\n",temp->nama," ",temp->maks_shift," ",temp->preferensi_shift);
        temp = temp -> next;
    }
    printf("\n");
}

void load_data(){
    FILE *csv1;
    char data[256];
    char nama_file[100];
    
    //Memasukkan nama file
    printf("Masukkan nama file pegawai< ");fgets(data,100,stdin);
    input_string(nama_file);
    csv1 = fopen(nama_file,"r");
    if (csv1 == NULL){
        printf("Data belum ada, Tidak Berhasil Memuat File!!");
    }
    else{
        fgets(data,256,csv1);
        while (fgets(data,256,csv1)!=NULL){
            file2list(data);
        }
        printf("Data Berhasi Dimuat!!\n\n");
        fclose(csv1);
    }
}

//Program Utama
int main(){
    int input ;
    printBanner("SELAMAT DATANG",'*',100);
    printf("Perintah yang bisa anda Masukkan!!!\n");
    printf("[1]Muat File\n[2]Tampilkan Data\n[3]Edit Data\n[4]Simpan Data\n[5]Muat Ulang File\n[0]Keluar Database\n\nPerintah< ");
    scanf("%d",&input);
    while(input!=0){
        switch (input){
        case 1:
            load_data();
            break;
        case 2:
            Tampil();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 0:
            break;
        default:
            printf("Perintah yang anda Masukkan Salah!!!Tolong Input dengan BenarT_T\n");
            break;
        }
        printf("Perintah yang bisa anda Masukkan!!!\n\n");
        printf("[1]Muat File\n[2]Tampilkan Data\n[3]Edit Data\n[4]Simpan Data\n[5]Muat Ulang File\n[0]Keluar Database\n\nPerintah< ");
        scanf("%d",&input);
    }
}