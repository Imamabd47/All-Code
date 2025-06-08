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

//Utility Umum
void printBanner(const char *text, char border, int totalWidth) {
    printf("\n");
    int textLen = strlen(text);
    int side = (totalWidth - textLen - 2) / 2; // -2 for spaces around text
    for (int i = 0; i < side; i++) printf("%c", border);
    printf(" %s ", text);
    for (int i = 0; i < side; i++) printf("%c", border);
    printf("\n");
}

//Utility Umum
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

//Penentu hari
void preferensi_hari(char *arr,char *dest){
    int T[3]={0};
    //Cek pagi
    if (strstr(arr,"pagi")!=NULL||strstr(arr,"Pagi")!=NULL)
        T[0] = 1;
    //Cek Siang
    if (strstr(arr,"siang")!=NULL||strstr(arr,"Siang")!=NULL)
        T[1] = 1;
    //Cek malam
    if (strstr(arr,"malam")!=NULL||strstr(arr,"Malam")!=NULL)
        T[2] = 1;
    //Cek bebas
    if (strstr(arr,"bebas")!=NULL||strstr(arr,"Bebas")!=NULL){
         T[0]=1;T[1]=1;T[2]=1;
    }    
    /*printf("T[0]:%d |T[1]:%d |T[2]%d\n",T[0],T[1],T[2]);*/
    if (T[2]==1&&T[1]==1&&T[0]==1)
        strcpy(dest,"Pagi Siang dan Malam") ; //0 Bebas
    else if (T[2]==1&&T[1]==1)
        strcpy(dest,"Siang dan Malam");  //6 siang dan malam
    else if (T[0]==1&&T[2]==1)
        strcpy(dest,"Pagi dan Malam");  //5 pagi dan malam
    else if (T[0]==1&&T[1]==1)
        strcpy(dest,"Pagi dan Siang");  //4 pagi dan Siang
    else if (T[2]==1)
        strcpy(dest,"Malam");  //3 malam
    else if (T[1]==1)
        strcpy(dest,"Siang");  //2 siang
    else 
        strcpy(dest,"Pagi");  //1 pagi
}

//Mengubah File Menjadi Linked List
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

//Fungsi utama Ambil data dari file csv
void load_data(char *nama_file){
    FILE *csv1;
    char data[256];

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

//Fungsi Utama Menampilkan linked list
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

//Fungsi Menambah data
void tambah(){
    struct pegawai *temp = malloc(sizeof(struct pegawai));
    char response[100];
    if (Data_Pegawai == NULL){
        temp-> before = NULL;
    }
    else{
        temp -> before = Data_Pegawai;
        Data_Pegawai -> next = temp;
    }
    temp->next = NULL;
    //Memasukkan nama dari pegawai
    printf("\nMasukkan Nama dari Pegawai Baru< ");
    fgets(temp->nama,50,stdin);input_string(temp->nama);
    //Memasukkan jumlah maksimal shift yang diminta pegawai
    printf("Masukkan jumlah maksimal shift yang disanggupi pegawai< ");
    scanf("%d",&(temp->maks_shift));getchar();
    //Memasukkan Preferensi Hari dari pegawai
    printf("Masukkan preferensi bagian shift dari pegawai< ");
    input_string(response);
    preferensi_hari(response,temp->preferensi_shift);
    Data_Pegawai = temp;
    printf("Data pegawai atas nama %s berhasil ditambahkan",temp->nama);
}

//Fungsi Menghapus Data
void hapus(){
    struct pegawai *temp = first;
    struct pegawai *temp_r;
    struct pegawai *temp_l;
    int i = 1;
    char nama_pegawai[100];
    printf("\nNama Pegawai yang ada dalam data:\n");
    while (temp != NULL){
        printf("[%d]%s\n",i,temp->nama);
        temp = temp->next;
        i++;
    }
    temp = first;
    printf("\nMasukkan nama pegawai yang ingin dihapus dari data< ");
    fgets(nama_pegawai,100,stdin);input_string(nama_pegawai);
    while (temp!=NULL){
        if (strcmp(nama_pegawai,temp->nama)==0){
            if (temp==first){
                temp_r = temp->next;
                temp_r -> before = NULL;
                temp -> next = NULL;
                first = temp_r;
            }
            else if (temp == Data_Pegawai){
                Data_Pegawai = temp->before;
                Data_Pegawai -> next = NULL;
                temp -> before = NULL;
            }
            else{
                temp_l = temp->before;
                temp_r = temp->next;
                temp->next = NULL;
                temp->before =NULL;
                temp_l -> next = temp_r;
                temp_r -> before = temp_l;
            }
            printf("Data pegawai atas nama %s berhasil dihapus",temp->nama);
            free(temp);
            break;
        }
        temp = temp->next;
    }  
}

//Fungsi Utama dari Edit
void edit(){
    int choice;
    printf("\nPilih Opsi Pengeditan Data dibawah ini!!!\n[1]Tambah Data\n[2]Hapus Data\n[0]Kembali Ke Menu Utama Database\n\nPerintah< ");
    scanf("%d",&choice);
    switch (choice){
    case 2:
        hapus();
        printf("\n\n");
        break;
    case 1:
        tambah();
        printf("\n\n");
        break;
    case 0:
        break;  
    default:
        printf("Perintah yang anda Masukkan Salah!!!Tolong Input dengan BenarT_T");
        break;
    }
}

void list2file(char *nama_file){
    struct pegawai *temp = first;
    FILE *a;
    a = fopen(nama_file,"w");
    fprintf(a,"\"Nama\",\"shift_maks\",\"Preferensi_shift\"\n");
    while (temp!= NULL){
        fprintf(a,"%s,%d,%s\n",temp->nama,temp->maks_shift,temp->preferensi_shift);
        temp = temp->next;
    }
    fclose(a);
    printf("Data telah tersimpan dalam file %s!!\n\n",nama_file);
}

//Fungsi Utama Simpan
void save(char *nama_file_def){
    int choice;
    printf("\nPilih Opsi Berikut: \n[1]Simpan dalam file baru\n[2]Update File lama\n[0]Kembali ke Menu Utama Database\n\nPerintah< ");
    scanf("%d",&choice);getchar();
    char nama_file[50];
    switch (choice){
    case 1:
        printf("\nMasukkan nama file< ");
        input_string(nama_file);
        list2file(nama_file);
        break;
    case 2:
        list2file(nama_file_def);
        break;
    default:
        break;
    } 
}

void reset(){
    struct pegawai *temp = first;
    if (temp != NULL){
        struct pegawai *temp_r = temp -> next;
        struct pegawai *last = Data_Pegawai;
        Data_Pegawai = NULL;
        first = NULL;
        while (temp_r != last){
            free(temp);
            temp_r = temp_r -> next;
            temp = temp_r -> before;
        }
        free(temp);
        free(last); 
        last = NULL;
    }
}

//Program Utama
int main(){
    int input ;
    char nama_file[100]="belum ada file yang dibaca!!";
    
    printBanner("SELAMAT DATANG",'*',100);
    printf("Perintah yang bisa anda Masukkan!!!\n");
    printf("[1]Muat File\n[2]Tampilkan Data\n[3]Edit Data\n[4]Simpan Data\n[5]Muat Ulang File\n[0]Keluar Database\n\nPerintah< ");
    scanf("%d",&input);
    while(input!=0){
        switch (input){
        case 1:
            //Memasukkan nama file
            reset();
            printf("Masukkan nama file pegawai< ");fgets(nama_file,100,stdin);
            input_string(nama_file);
            load_data(nama_file);
            break;
        case 2:
            Tampil();
            break;
        case 3:
            edit();
            break;
        case 4:
            save(nama_file);
            break;
        case 5:
            break;
        case 0:
            break;
        default:
            printf("Perintah yang anda Masukkan Salah!!!Tolong Input dengan BenarT_T\n");
            break;
        }
        printf("Perintah yang bisa anda Masukkan!!!\n");
        printf("[1]Muat File\n[2]Tampilkan Data\n[3]Edit Data\n[4]Simpan Data\n[5]Muat Ulang File\n[0]Keluar Database\n\nPerintah< ");
        scanf("%d",&input);
    }
}
