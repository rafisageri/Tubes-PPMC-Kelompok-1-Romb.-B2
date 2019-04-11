//***********************************************************//
// [ Source Code ]
//
// Institution : Institut Teknologi Bandung
// Name : Afif Hanidar M. 18317003
//        Syifa Hasanah 18317002
//        R. Rafi Sageri 13217081
//        Marcel DFP 13217082
// File Name : problem1.c
// Dependency : stdio.h, math.h, stdlib.h, ctype.h,string.h
//
// Description:
// Penyelesaian masalah pertama, yaitu pembuatan sebuah desain rangkaian
//
// Status:
// 1. Rafi Sageri - 13217081 : Interface
// 2. Afif Hanidar M. - 18317003 : Routing dan debugging layout dan interface
// 3. Syifa Hasanag - 18317002 : File eksternal sekaligus debugging
// 4. Marcel DFP - 13217082 : Layouting komponen
//***********************************************************//
#include "lib_final.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define columnMax 40
#define rowMax 40

int main (){
    //Kamus
    char layout[40][40][10], routing[40][40];
    char namaProyek[20];
    int pilihan,n,m;
    FILE *fileexternal;

    // inisialisasi array layout

    printf("Menu: \n1. Buat Proyek Baru 2. Muat Proyek dari Berkas 3. Keluar \nMasukan: ");
    scanf(" %d", &pilihan);
    printf("\n");

    while(!(pilihan==3)){
        if (pilihan==1){
        //Menu membuat proyek baru
            buatProyekBaru(layout,routing,&n,&m, namaProyek);
            editPCB(layout,routing,n,m, namaProyek);
        }
        else if (pilihan==2){
        //Menu memuat proyek dari file eksternal
            printf("Masukkan nama proyek yang ingin dimuat:");
            scanf("%s", namaProyek);
            loadLayout(layout, n, m, namaProyek, fileexternal);
            loadRouting(routing, n, m, namaProyek, fileexternal);
            editPCB(layout, routing, n,m, namaProyek);
        }
        else{
        //User memasukkan pilihan selain 1,2,3
            printf("Pilihan tidak ada di menu\n");
        }
        printf("Masukan: ");
        scanf(" %d", &pilihan);
        printf("\n");
    }
    //User memasukkan pilihan 3, program berhenti
    return 0;
}
