#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define columnMax 40
#define rowMax 40

void buatProyekBaru(char layout[40][40][10], char routing[40][40],int *n, int *m, char namaProyek[20]);
void editPCB(char layout[40][40][10], char routing[40][40],int n, int m, char namaProyek[20]);
int isSizeValid(int m, int n);
void printLayout (char arr[40][40][10], int n, int m);
void printRouting(char arr[40][40],int n, int m);
void drc();
int isPlaceCmpValid(int i,int j,int N, int M, char layout [40][40][10]);
int isJarakValid(int i1, int j1, int i2, int j2, int jrkMin);
void layoutManual(int N, int M, char layout[40][40][10]);
int IsNode (char sym, int Node_x , int Node_y, int Baris, int Kolom, char Route[40][40]);
int IsInputKoordinat (char pilih[]);
int IsSimbolValid (char p);
int IsKeluar (char pilih[]);
void routingManual(char Arr[40][40], int n,int m);
void saveLayout(char matrix[40][40][10], int Ncol, int Nrow, char fname[20], FILE *fp);
void loadLayout(char matrix[40][40][10], int Ncol, int Nrow, char fname[20], FILE *fp);
void saveRouting(char matrix[40][40], int Ncol, int Nrow, char fname[20], FILE *fp);
void loadRouting(char matrix[40][40], int Ncol, int Nrow, char fname[20], FILE *fp);
void layoutOtomatis();
void routingOtomatis();

void buatProyekBaru(char layout[40][40][10], char routing[40][40],int *n, int *m, char namaProyek[20]){
    int i,j;
    printf("====== Membuat Proyek Baru ====== \nMasukkan nama proyek:");
    scanf("%s", namaProyek);
    printf("\n");
    printf("Masukkan ukuran PCB NxM (N,M<40) dengan format input N M: ");
    scanf(" %d %d",n,m);
    printf("\n");

    while(!isSizeValid(*m,*n)){
        printf("Ukuran PCB tidak valid\n");
        printf("Masukkan ukuran PCB NxM (N,M<40): ");
        scanf(" %d %d",n,m);
        printf("\n");
    }
    //Masukkan sudah valid

    for(j==0; j<m; ++j){
        for(i==0; i<n; ++i){
            layout[i][j][0] = '0';
            routing[i][j] = ' ';
            //Daerah yang dipakai oleh user
            //ditandai dengan whitespace
        }
    }

    for(j==m; j<40; ++j){
        for(i==n; i<40; ++i){
            layout[i][j][0] = '0';
            routing[i][j] = '0';
            //Daerah yang tidak dipakai oleh user
            //ditandai dengan karakter 0
        }
    }
}


void editPCB(char layout[40][40][10], char routing[40][40], int n, int m, char namaProyek[20]){
    int mode;
    FILE *fileexternal;
    printf("[Menu Utama] \nPilih Mode: \n");
    printf("1. Tampilkan Layout \n");
    printf("2. Layouting Manual \n");
    printf("3. Tampilkan Routing \n");
    printf("4. Routing Manual \n");
    printf("5. Layout Otomatis \n");
    printf("6. Routing Otomatis \n");
    printf("7. Design Rule Checker \n");
    printf("8. Simpan Proyek dan Keluar \n");
    printf("Pilih Mode:");
    scanf("%d", &mode);
    printf("\n");

    while (!(mode==8)){
        switch(mode){
            case 1:
                printLayout(layout,n,m); //infinite layout
                break;
            case 2:
                layoutManual(n,m,layout); // entah kenapa gak bisa masukin koordinat kakinya
                break;
            case 3:
                printRouting(routing,n,m); // sudah dicoba saat masih kosong dan ketika routingManual dijalankan. aman
                break;
            case 4:
                printf("bisa\n");
                routingManual(routing,n,m); // sudah  dicoba dan aman
                break;
            case 5:
                layoutOtomatis();
                break;
            case 6:
                routingOtomatis();
                break;
            case 7:
                drc();
                break;
            default:
                printf("Mode tersebut tidak ada di menu");
        }
        printf("Pilih Mode: ");
        scanf(" %d", &mode);
        printf("\n");
    }
    //User memasukkan pilihan mode == 8
    char namaProyekLayout[10];
    char namaProyekRouting [10];
    char extensionLayout [10];
    char extensionRouting [10];

    strcpy(namaProyekLayout, namaProyek);
    strcpy(namaProyekRouting, namaProyek);

    strcpy(extensionLayout, "_layout.csv");
    strcpy(extensionLayout, "_routing.csv");

    strcat(namaProyekLayout, extensionLayout);
    strcat(namaProyekRouting, extensionRouting);

    saveLayout(layout, n, m, namaProyekLayout, fileexternal);
    saveRouting(routing, n, m, namaProyekRouting, fileexternal);

    printf("Layout disimpan dalam berkas %s", namaProyekLayout);
    printf("Routing disimpan dalam berkas %s", namaProyekRouting);
}

int isSizeValid(int m, int n)
{
    if ((m<=rowMax)&&(n<=columnMax)){
        return 1;
    }
    else{
        return 0;
    }
}

void printLayout (char arr[40][40][10], int n, int m){
    int i,j;
    /*for (j=0; j<m; ++j){
        for (i=0; i<n; ++i){
            if(!(arr[i][j][0] == '0')){
                printf("%s", arr[i][j]);
            }
        }
    }*/
     for (i = 0; i<=m;i++){

    for (j = 0; j <=n;j++){

        if (i == 0 && j !=0){
            printf (" %d ",j);
        } else if (j == 0 && i!=0){
            printf (" %d ",i);
        }else if ( i == 0 && j == 0){
            printf("   ");
        } else if( j<10) {
            if(arr[i][j][0] != '0'){
            printf("%s",arr[i][j]);
        } else if (arr[i][j][0]== '0'){
            printf("   ");
        }
        }
         else if (j>=10 && i <10){ // jika ukuran array melebihi 10
            if (arr[i][j][0] != '0'){
                printf("%s",arr[i][j]);
            }
            else if (arr[i][j][0]== ' '){
                printf("    ");
            }
        }
        else if  (j>=10 && i >=10){ // jika ukuran array melebihi 10
            if (arr[i][j][0] != '0'){
            printf("%s",arr[i][j]);
        } else if (arr[i][j][0]== '0'){
            printf("    ");
        }
        }


    }
printf("\n");
}
}


void printRouting(char arr[40][40],int n, int m){
    int i,j;
    //int a;
    //printf ("%d %d ",m,n);
    //scanf("%d",&a);
    for (i = 0; i<=m;i++){

    for (j = 0; j <=n;j++){

        if (i == 0 && j !=0){
            printf (" %d ",j);
        } else if (j == 0 && i!=0){
            printf (" %d ",i);
        }else if ( i == 0 && j == 0){
            printf("   ");
        } else if( j<10) {
            if(arr[i][j] != ' '){
            printf(" %c ",arr[i][j]);
        } else if (arr[i][j]== ' '){
            printf("   ");
        }
        }
         else if (j>=10 && i <10){ // jika ukuran array melebihi 10
            if (arr[i][j] != ' '){
            printf(" %c  ",arr[i][j]);
        } else if (arr[i][j]== ' '){
            printf("    ");
        }
        } else if  (j>=10 && i >=10){ // jika ukuran array melebihi 10
            if (arr[i][j] != ' '){
            printf("%c   ",arr[i][j]);
        } else if (arr[i][j]== ' '){
            printf("    ");
        }
        }


    }
printf("\n");
}
}

void drc(){
    printf("Fungsi belum diimplementasi\n");
}

int isPlaceCmpValid(int i,int j,int N, int M, char layout [40][40][10]){
    //fungsi ini untuk mengecek apakah koordinat i,j berada dalam grid atau tidak
    //fungsi ini juga mengecek apakah koordinat tersebut sudah terisi atau tidak
    //N,M adalah batas grid yang diinput oleh user
    //i,j adalah koordinat yang akan dimasukkan komponen
    if(i>N||j>M || layout[i-1][j-1][0]!='0')
        {return 0;}
    else
        {return 1;}
}

int isJarakValid(int i1, int j1, int i2, int j2, int jrkMin){
    //fungsi ini untuk menghitung jarak antara 2 titik
    //akan mengembalikan nilai 1 apabila jarak min terpenuhi
    //dua koordinat yang akan dicek adalah (i1, j1) dan (i2, j2)
    double jarak;
        jarak=sqrt(pow(i1-i2,2)+pow(j1-j2,2));
    if(jarak<=jrkMin)
        {return 0;}
    else
        {return 1;}
}

void layoutManual(int N, int M, char layout[40][40][10]){
    int i,j;
    //prosedur untuk menaruh komponen pada layout PCB
    //N,M adalah batas grid yang diinput user
    //inisialisasi array layout
    for (i = 0;i<=M;i++){
        for (j =0;j<=N;j++){
            layout [i][j][0] = '0';
        }
    }

    char jns[2]; int i1,j1,i2,j2,i3,j3;
    printf("[Mode Layout]\n");
    printf("Isi `q` atau `Q` untuk kembali ke menu\n");
    printf("Pilih Komponen (R,C,T,J):");
    scanf("%s",&jns);
    while(jns[0]!='Q'&&jns[0]!='q'){
        switch(jns[0]){
        case 'R':
            printf("Koordinat Kaki 1:");
            scanf("%d,%d",&i1,&j1);
            //printf ("%d,%d\n",i1,j1); /* ini untuk debug. nilai berhasil masuk */
            while(isPlaceCmpValid(i1,j1,N,M,layout)==0)
            {printf("Koordinat salah atau sudah terisi, masukkan koordinat lain: ");
            scanf("%d,%d",&i1,&j1);
            }
            layout[i1-1][j1-1][0]=jns[0];
            layout[i1-1][j1-1][1]=jns[1];
            printf("Koordinat Kaki 2: ");
            scanf("%d,%d",&i2,&j2);
            while(isPlaceCmpValid(i2,j2,N,M,layout)==0)
            {printf("Koordinat salah atau sudah terisi, masukkan koordinat lain: ");
            scanf("%d,%d",&i2,&j2);
            }
            while(isJarakValid(i1,j1,i2,j2,3)==0)
            {printf("Jarak minimum tidak terpenuhi, masukkan koordinat lain: ");
            scanf("%d,%d",&i2,&j2);
            }
            layout[i2-1][j2-1][0]=jns[0];
            layout[i2-1][j2-1][1]=jns[1];
        break;
        case 'C':
            printf("Koordinat Kaki 1: ");
            scanf("%d,%d",&i1,&j1);
            while(isPlaceCmpValid(i1,j1,N,M,layout)==0)
            {printf("Koordinat salah atau sudah terisi, masukkan koordinat lain: ");
            scanf("%d,%d",&i1,&j1);
            }
            layout[i1-1][j1-1][0]=jns[0];
            layout[i1-1][j1-1][1]=jns[1];
            printf("Koordinat Kaki 2: ");
            scanf("%d,%d",&i2,&j2);
            while(isPlaceCmpValid(i2,j2,N,M,layout)==0)
            {printf("Koordinat salah atau sudah terisi, masukkan koordinat lain: ");
            scanf("%d,%d",&i2,&j2);
            }
            while(isJarakValid(i1,j1,i2,j2,1)==0)
            {printf("Jarak minimum tidak terpenuhi, masukkan koordinat lain: ");
            scanf("%d,%d",&i2,&j2);
            }
            (layout[i2-1][j2-1][0]=jns[0]);
            (layout[i2-1][j2-1][1]=jns[1]);
        break;
        case'J':
            printf("Koordinat Kaki +: ");
            scanf("%d,%d",&i1,&j1);
            while(isPlaceCmpValid(i1,j1,N,M,layout)==0)
            {printf("Koordinat salah atau sudah terisi, masukkan koordinat lain: ");
            scanf("%d,%d",&i1,&j1);
            }
            (layout[i1-1][j1-1][0]=jns[0]);
            (layout[i1-1][j1-1][1]=jns[1]);
            printf("Koordinat Kaki -: ");
            scanf("%d,%d",&i2,&j2);
            while(isPlaceCmpValid(i2,j2,N,M,layout)==0)
            {printf("Koordinat salah atau sudah terisi, masukkan koordinat lain: ");
            scanf("%d,%d",&i2,&j2);
            }
            (layout[i2-1][j2-1][0]=jns[0]);
            (layout[i2-1][j2-1][1]=jns[1]);
        break;
        case 'T':
            printf("Koordinat Kaki E: ");
            scanf("%d,%d",&i1,&j1);
            while(isPlaceCmpValid(i1,j1,N,M,layout)==0)
            {printf("Koordinat salah atau sudah terisi, masukkan koordinat lain: ");
            scanf("%d,%d",&i1,&j1);
            }
            layout[i1-1][j1-1][0]='T';
            layout[i1-1][j1-1][1]='e';
            (layout[i1-1][j1-1][2]=jns[1]);
            printf("Koordinat Kaki B: ");
            scanf("%d,%d",&i2,&j2);
            while(isPlaceCmpValid(i2,j2,N,M,layout)==0)
            {printf("Koordinat salah atau sudah terisi, masukkan koordinat lain: ");
            scanf("%d,%d",&i2,&j2);
            }
            while(isJarakValid(i1,j1,i2,j2,1)==0)
            {printf("Jarak minimum tidak terpenuhi, masukkan koordinat lain: ");
            scanf("%d,%d",&i2,&j2);
            }
            layout[i2-1][j2-1][0]='T';
            layout[i2-1][j2-1][1]='b';
            (layout[i2-1][j2-1][2]=jns[1]);
            printf("Koordinat Kaki C: ");
            scanf("%d,%d",&i3,&j3);
            while(isPlaceCmpValid(i3,j3,N,M,layout)==0)
            {printf("Koordinat salah atau sudah terisi, masukkan koordinat lain: ");
            scanf("%d,%d",&i3,&j3);
            }
            while(isJarakValid(i1,j1,i3,j3,1)==0)
            {printf("Jarak minimum tidak terpenuhi, masukkan koordinat lain: ");
            scanf("%d,%d",&i3,&j3);
            }
            while(isJarakValid(i2,j2,i3,j3,1)==0)
            {printf("Jarak minimum tidak terpenuhi, masukkan koordinat lain: ");
            scanf("%d,%d",&i3,&j3);
            }
            strcpy(&layout[i3-1][j3-1][0],jns);
            layout[i3-1][j3-1][0]='T';
            layout[i3-1][j3-1][1]='c';
            (layout[i1-1][j1-1][2]=jns[1]);
            break;
        default:
            printf("Masukkan anda salah!\n");
        }
        printf("Pilih Komponen (R,C,T,J):");
        scanf("%s",&jns);
    }
}

int IsNode (char sym, int Node_x , int Node_y, int Baris, int Kolom, char Route[40][40]){
// mengembalikan nilai 1 jika ada pada array dengan simbol yang sama atau kosong dan dalam cakupan ukuran array

    if ((Node_x > Baris) || (Node_y >Kolom)){
        return 0;
    }
    else if ((Route[Node_y][Node_x] != sym) && (Route[Node_y][Node_x] != ' ')) {
        return 0;
    }
    else {
    return 1;
    }
}

int IsSimbolValid (char p){
    if (p != '!' && p != '@'){
        if (p != '#' && p != '$'){
            if (p != '%' && p != '&'){
                if (p != '*'){
                    return 0;
                }
            }
        }
    } else { /* simbol benar */
        return 1;
    }
}

int IsKeluar (char pilih[]){
    // bernilai 1 jika pilih [0] berupa n,N,q atau Q

    if (pilih[0] == 'n' || pilih[0] == 'N' ){
        return 1;
    }
    else if (pilih[0] == 'q' || pilih[0] == 'Q'){
    return 1;
    }
    else {
        return 0;
    }

}

void routingManual(char Arr[40][40], int N,int M) {
/* m adalah ukuran baris yang terpakai */
/* n adalah ukuran kolom yang terpakai */
/* Arr adalah Array yang berisi routing PCB */
char sym; /* simbol penanda kabel penghubung */
char *ptr;
int angka1, angka2, i, j;
char pilih[5];

// mengisi array dengan whitespace
for (i = 1; i <=M;i++){
    for (j = 1; j<=N;j++){
        Arr[i][j] = ' ';
    }
}

printf ("[ Mode Routing ]\n");
printf(" Isi 'q' atau 'Q' untuk kembali ke menu awal\n");
printf (" Isi 'n' atau 'N' untuk memulai node baru dengan simbol baru\n");


// mulai mengisi rute
do{
    printf ("Pilih simbol (!,@,#,$,%,&,*) : ");
    scanf ("%c/n",&sym);
    while (!IsSimbolValid(sym)){ /* validasi agar pemilihan simbol pasti benar*/
        printf ("Pilih simbol (!,@,#,$,%,&,*) : ");
        scanf ("%c/n",&sym);
} /* di sini, simbol pasti sudah benar*/
// lakukan pengisian simbol di koordinat tertentu
    do{
        printf ("Masukkan koordinat (kolom,baris) :");
        scanf ("%s/n",&pilih);
        if (isdigit(pilih[0])){
            angka1 = strtod(pilih, &ptr);
            while (*ptr && !(isdigit(*ptr)))
                ptr++;
            strcpy(pilih, ptr);
            angka2 = strtod(pilih, &ptr);
            if (IsNode(sym,angka2,angka1,M,N,Arr)){
                Arr[angka2][angka1]=sym;
            }
            else{
                printf("Input salah. Silakan masukkan kembali");
            }

        }
        else if (!IsKeluar(pilih)) {
            printf("Input salah. Silakan masukkan kembali");
        }
    } while (!IsKeluar(pilih));

}while (pilih[0] != 'Q' && pilih[0] != 'q');


if (pilih[0]== 'q' || pilih[0]== 'Q'){
    printf ("...................\n");
    printf("kembali ke menu awal\n");
}
//printLayout(M,N,Arr);
}

//FUNGSI saveMatrix
//Fugsi untuk menyimpan array 2 dimensi ke dalam .csv
void saveLayout(char matrix[40][40][10], int Ncol, int Nrow, char fname[20], FILE *fp)
{
	//FILE *fp;
	fp = fopen(fname, "w");
	int col, row;

	col=0;
	row=0;

	for (col=0; col<Ncol; col++)
	{
		for (row=0; row<Nrow; row++)
		{
			fprintf(fp, "%s", matrix[col][row][10]);
		}
	}

	fclose (fp);
}

//FUNGSI loadMatrix
//Fugsi untuk mengakses data dari .csv dan dimasukkan ke array 2 dimensi
void loadLayout(char matrix[40][40][10], int Ncol, int Nrow, char fname[20], FILE *fp)
{
	//FILE *fp;
	fp = fopen(fname, "r");
	int col, row;

	col=0;
	row=0;

	for (col=0; col<Ncol; col++)
	{
		for (row=0; row<Nrow; row++)
		{
			fscanf(fp, "%s", matrix[col][row][10]);
		}
	}

	fclose(fp);
}

//FUNGSI saveMatrix
//Fugsi untuk menyimpan array 2 dimensi ke dalam .csv
void saveRouting(char matrix[40][40], int Ncol, int Nrow, char fname[20], FILE *fp)
{
	//FILE *fp;
	fp = fopen(fname, "w");
	int col, row;

	col=0;
	row=0;

	for (col=0; col<Ncol; col++)
	{
		for (row=0; row<Nrow; row++)
		{
			fprintf(fp, "%c", matrix[col][row]);
		}
	}

	fclose (fp);
}

//FUNGSI loadMatrix
//Fugsi untuk mengakses data dari .csv dan dimasukkan ke array 2 dimensi
void loadRouting(char matrix[40][40], int Ncol, int Nrow, char fname[20], FILE *fp)
{
	//FILE *fp;
	fp = fopen(fname, "r");
	int col, row;

	col=0;
	row=0;

	for (col=0; col<Ncol; col++)
	{
		for (row=0; row<Nrow; row++)
		{
			fscanf(fp, "%c", matrix[col][row]);
		}
	}

	fclose(fp);
}

void layoutOtomatis(){
    printf("Fungsi belum diimplementasi\n");
}

void routingOtomatis(){
    printf("Fungsi belum diimplementasi\n");
}

