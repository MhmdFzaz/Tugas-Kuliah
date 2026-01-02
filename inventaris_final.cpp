#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
using namespace std;

void simpanbuku(string databuku[][3], int stok[], int jml_buku) {
    ofstream file ("database_buku.txt");
    if (!file)  {
        cout << "Gagal Membuka file untuk menyimpan!\n";
        return;
    }
    for (int i = 0; i < jml_buku; i++) {
        file << databuku[i][0] << "|";
        file << databuku[i][1] << "|";
        file << databuku[i][2] << "|";
        file << stok[i] << endl;
    }
    file.close();
}

int muatBuku(string databuku[][3], int stok[]) {
    ifstream file("database_buku.txt");
    if (!file) {
        cout << ">> Database belum ada, mulai dengan data default.\n";
        return 0;
    }
    int jml_buku = 0;
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1+1);
        size_t pos3 = line.find("|", pos2+1);

        databuku[jml_buku][0] = line.substr(0, pos1);
        databuku[jml_buku][1] = line.substr(pos1+1, pos2-pos1-1);
        databuku[jml_buku][2] = line.substr(pos2+1, pos3-pos2-1);
        stok[jml_buku] = atoi(line.substr(pos3+1).c_str());
        jml_buku++;
    }
    file.close();
    return jml_buku;
}

//TYPE DATA LOGIN ADMIN
struct user {
    string username;
    string password;
};

//pilihan menu
char pilihan1,pilihan2;

//HEADER
void judul_program() {
    cout << "\t======================****======================";
    cout << "\n\t\t Program Inventaris Perpustakaan";
    cout << "\n\t======================****======================\n";
}

void menu_login() {
    cout << "\t=================**MENU LOGIN**=================";
    cout << "\n\t\t\t 1.Login Akun";
    cout << "\n\t\t\t 2.Buat akun";
    cout << "\n\t\t\t 3.Exit/Keluar";
    cout << "\n\t======================****======================";
    cout << "\n\t\t     Masukan Pilihan anda  :";
    cin >> pilihan1;
    system ("cls");
}

void menu_inventaris() {
    cout << "\n\t==========**Inventaris Perpustakaan**===========";
    cout << "\n\t\t\t1.Input Buku";
    cout << "\n\t\t\t2.buku yang tersedia";
    cout << "\n\t\t\t3.Mencari buku";
    cout << "\n\t\t\t4.Pinjam Buku";
    cout << "\n\t\t\t5.Kembalikan Buku";
    cout << "\n\t\t\t6.Logout/Keluar";
    cout << "\n\t======================****======================";
    cout << "\n\t\t     Masukan pilihan anda : ";
    cin >> pilihan2;
        system ("cls");
}

int main () {
//TYPE DATA PENCARIAN BUKU
    string cari;
    int ditemukan = 0;

//TYPE DATA INPUT BUKU
    string index,bukubaru;

//DATA BUKU
    string databuku[100][3];
    int stok[100];
    int jml_buku = 0;
    jml_buku = muatBuku(databuku, stok);

//TYPE DATA AKUN BARU
    string newuser;
    string newpass;
    bool duplikat;

//DATA LOGIN
    bool login;
    int jml_akun = 5;
    user users[100] = {
        {"admin","123"},
        {"mipta","111"},
        {"faiz","222"},
        {"febri","333"},
        {"glen", "444"},
    };
    string user1,pass;
    
    menu1:
    //HEADER
    judul_program();
    //MENU LOGIN
    menu_login();

    switch (pilihan1){
    case '1':
    inputlogin:
    cout << "\t=================**Silahkan Login**=================";
    login = false;
    cout << "\n\t\t\tusername : ";
    cin >> user1;
    cout << "\t\t\tPassword : ";
    cin >> pass;
    system ("cls");

    for (int i = 0; i < jml_akun; i++){
        
    //CEK LOGIN BERHASIL
        if (user1 == users[i].username && pass == users[i].password) {
            login = true;
            cout << "\t================ Login Berhasil ================";
            cout << "\n\t\t     Selamat datang, " << users[i].username << "!" << endl;
            cout << "\t================================================\n";
            break;
        }  
    }   
    //CEK LOGIN GAGAL
        if (!login) {
            cout << "\t=================**Login Gagal**=================";
            cout << "\n\t\t username atau password salah"; 
            cout << "\n\t\t tekan enter untuk coba lagi!";
            cout << "\n\t=================================================";
            cin.ignore();
            cin.get();
            system("cls");
            goto inputlogin;
            break;
        } 
        break;
  
        //SIGNUP AKUN BARU
    case '2' :
     if (jml_akun < 100) {
                cout <<"\n\t==================**Buat Akun baru**==================\n";
                cin.ignore();
                cout << "\t\t\t  username : "; 
                getline(cin, newuser);
                cout << "\t\t\t  Password : "; 
                getline(cin, newpass);
            
            //CEK DUPLIKAT AKUN
                duplikat = false;
                for (int i = 0; i < 5 + jml_akun; i++) {
                    if (users[i].username == newuser && users[i].password == newpass) {
                        duplikat = true;
                        break; }
                }
                //AKUN SUDAH TERDAFTAR
                if (duplikat) {
                    cout << "\t\t----- Maaf akun sudah terdaftar -----\n";
                } 
                //AKUN BERHASIL TERDAFTAR
                else {
                    users[jml_akun].username = newuser;
                    users[jml_akun].password = newpass;
                    jml_akun++;

                    cout <<"\t\t  ----- Akun Berhasil Terdaftar -----\n";
                }
                cout << "\t=========================****=========================\n"; 
            } 
                cout << "\t\t  tekan enter untuk kembali ke menu";
                cin.get();
                system ("cls");
                goto menu1;
    break;

    case '3' :
    return 0;

    default:
        cout << "\t============================****=============================";
        cin.ignore ();
        cout << "\n\t\t  pilihan salah, tekan enter untuk coba lagi";
        cout << "\n\t============================****=============================";
        cin.get ();
        system ("cls");
        goto menu1;
    break;
    }

    menu2 :
    judul_program();
    menu_inventaris();
   
    //TYPE DATA BAGIAN INVENTARIS
    string caribuku;
    string judul_buku;
    bool cekbuku = false;

    switch (pilihan2){
        //PILIHAN 1 INPUT BUKU
        case '1' :
        if (jml_buku < 100) {
                cout << "\n\t==================**Input Buku Baru**==================\n";

                cin.ignore();
                
                cout << "\t\t\t  Judul   : "; 
                getline(cin, databuku[jml_buku][0]);
                
                cout << "\t\t\t  Penulis : "; 
                getline(cin, databuku[jml_buku][1]);
                
                cout << "\t\t\t  Tahun   : "; 
                getline(cin, databuku[jml_buku][2]);
                
                cout << "\t\t\t  Stok    : "; 
                cin >> stok[jml_buku];
                
                jml_buku++;
                simpanbuku(databuku,stok,jml_buku);
                cout << "\t\t  ----- Buku berhasil disimpan! -----\n";
                cout << "\t=======================================================\n";
                cin.ignore();
                cout << "\t\t   tekan enter untuk kembali ke menu";
                cin.get();
                system("cls");
                goto menu2;
            } else {
                cout << "\t=========================****=========================\n";
                cout << "\t\t\tMaaf, penyimpanan penuh!\n";
                cout << "\t\t   tekan enter untuk kembali ke menu\n";
                cout << "\t=========================****=========================";
            cin.ignore();
            cin.get();
            system("cls");
            goto menu2;
            break;
            }
            break;

    //PILIHAN 2 CEK DAFTAR BUKU
    case '2':
        cout << "=========================================**DAFTAR BUKU**========================================";
        cout << left << setw(5)<< "\n| NO |"
             << setw(33) << "    Judul Buku  "
             << setw(25) << "    | Tahun |"
             << setw(23) << " Pengarang "
             << setw(5) << " | Stok |";
        cout << "\n=========================================**===*****===**========================================" << endl;;
        for (int i = 0; i < jml_buku; i++) {
            cout << "| " << right << setw(2) << (i + 1) << "." 
                 << "| " << left <<setw(36)<<databuku[i][0]
                 << "| " << databuku[i][2] << setw(15) << "  |" 
                 << setw(24)<< databuku[i][1] 
                 << "| " << setw(5) << stok[i] 
                 <<"|\n";
        }
        cout << "===========================================***********=========================================="<< endl;
        cin.ignore();
        cout << "\t\t\t\tTekan enter untuk kembali ke menu";
        cin.get();
        system("cls");
        goto menu2;
    break;
    
    //PILIHAN 3 MENCARI BUKU
    case '3' :
        cout << "========================**Cari Buku**========================";
        cin.ignore();
        cout << "\n\t Masukkan judul buku yang ingin dicari: ";
        getline(cin, caribuku);
        cekbuku = false;
        //CEK JUDUL BUKU DITEMUKAN
        for (int i = 0; i < jml_buku; i++) {
            if (databuku[i][0] == caribuku) {
                cout << "\n\t\t       Buku ditemukan!";
                cout << "\n\t\t       Judul   : " << databuku[i][0];
                cout << "\n\t\t       Penulis : " << databuku[i][1];
                cout << "\n\t\t       Tahun   : " << databuku[i][2];
                cout << "\n\t\t       Stok    : " << stok[i] << endl;
                cout << "=============================================================";
                cekbuku = true;
                break;
            }
        //CEK JUDUL BUKU TIDAK DITEMUKAN
        } if (!cekbuku) {
            cout << "\t\t    Buku tidak ditemukan!";
            cout << "\n============================****=============================";
        }
        cout << "\n\t     Tekan enter untuk kembali ke menu";
        cin.get();
        system("cls");
        goto menu2;
        break;
    
    //PILIHAN 4 BUKU YANG DIPINJAM
    case '4':{
        cout << "\n\t============================*PEMINJAMAN BUKU*=============================";
        cout << "\n\t\t  Masukan buku yang ingin di keluarkan : ";
        cin.ignore();
        getline (cin, judul_buku);

    //CEK BUKU TERSEDIA ATAU TIDAK
         for (int i = 0; i < jml_buku; i++) {
            if (databuku[i][0] == judul_buku) {
               //CEK STOK BUKU TERSEDIA
                if (stok[i] > 0) {
                    stok[i]--;
                    simpanbuku(databuku,stok,jml_buku);
                    cout << "\n\t\t        Buku " << databuku[i][0] << " berhasil dikeluarkan\n";
                    //BUKU TIDAK DITEMUKA
                    cout << "\n\t\t\t   Tekan enter untuk kembali ke menu";
                    cout << "\n\t==================================****====================================";
                    cin.get(); 
                    system("cls");
                    goto menu2;
                } 
                //CEK STOK BUKU HABIS
                else {
                    cout << "\n\t\t       Maaf, stok buku " << databuku[i][0] << " sedang habis.\n";
                    cout << "\n\t\t\t   Tekan enter untuk kembali ke menu";
                    cout << "\n\t==================================****====================================";
                    cin.get(); 
                    system("cls");
                    goto menu2;
                }
                cekbuku = true;
            } 
        }
            if (!cekbuku){
                cout << "\n\t\t         Buku tidak ditemukan dalam inventaris.\n";
                cout << "\n\t\t\t   Tekan enter untuk kembali ke menu";
                cout << "\n\t==================================****====================================";
                cin.get(); 
                system("cls");
                goto menu2;
            }
    break;
        }
        //PILIHAN 5 DATA PEMINJAM
    case '5' :
    cout << "\n\t============================*PENGEMBALIAN BUKU*=============================";  
    cout << "\n\t\t    Masukan Buku Yang ingin dikembalikan : ";
    cin.ignore();
    getline(cin, judul_buku);
    for (int i = 0; i < jml_buku; i++) {
            if (databuku[i][0] == judul_buku) {
               //CEK STOK BUKU TERSEDIA
                    stok[i]++;
                    simpanbuku(databuku,stok,jml_buku);
                    cout << "\n\t\t         Buku " << databuku[i][0] << " berhasil dikembalikan\n";
                    cout<<"\t\t             Tekan Enter Untuk Kembali Ke Menu!\n";
                    cout << "\n\t==================================****====================================";
                    cin.get();
                    goto menu2;
                    system("cls");
            }
        }
        if (!cekbuku) {
                cout << "\n\t\t         Buku tidak ditemukan dalam inventaris.\n";
                cout << "\n\t\t\t   Tekan enter untuk kembali ke menu";
                cout << "\n\t==================================****====================================";
                cin.get(); 
                system("cls");
                goto menu2;
            }
    break;
        //PILIHAN 6 LOGOUT/KELUAR
    case '6' :
        cout << "\t======================****======================\n";
        cout << "\t\t\t     Logout..." << endl;
        cin.ignore();
        cout << "\t     Tekan enter untuk kembali ke menu login";
        cout << "\n\t======================****======================";
        cin.get();
        system("cls");
        goto menu1;
        return 0;
    break;
        //PILIHAN SALAH
    default:
        cout << "\t============================****=============================";
        cin.ignore ();
        cout << "\n\t\t  pilihan salah, tekan enter untuk coba lagi";
        cout << "\n\t============================****=============================";
        cin.get ();
        system ("cls");
        goto menu2;
    break;
    }
}