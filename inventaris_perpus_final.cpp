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
    cout << "            ======================****======================" << endl;
    cout << "            |         Program Inventaris Perpustakaan      |" << endl;
    cout << "            ======================****======================" << endl;
}

void menu_login() {
    cout << "            =================**MENU LOGIN**=================" << endl;
    cout << "            |                 1.Login Akun                 |" << endl;
    cout << "            |                 2.Buat akun                  |" << endl;
    cout << "            |                 3.Exit/Keluar                |" << endl;
    cout << "            ======================****======================" << endl;
    cout << "                         Masukan Pilihan anda  :";
    cin >> pilihan1;
    system ("cls");
}

void menu_inventaris() {
    cout << "            ==========**Inventaris Perpustakaan**===========" << endl;
    cout << "            |               1.Input Buku                   |" << endl;
    cout << "            |               2.buku yang tersedia           |" << endl;
    cout << "            |               3.Mencari buku                 |" << endl;
    cout << "            |               4.Pinjam Buku                  |" << endl;
    cout << "            |               5.Kembalikan Buku              |" << endl;
    cout << "            |               6.Logout/Keluar                |" << endl;
    cout << "            ======================****======================" << endl;
    cout << "                          Masukan pilihan anda : ";
    cin >> pilihan2;
        system ("cls");
}

int main () {
//DATA BUKU
    string databuku[100][3];
    int stok[100];
    int jml_buku = 0;
    jml_buku = muatBuku(databuku, stok);

//TYPE DATA CARI BUKU
    string caribuku;
    string judul_buku;
    bool cekbuku = false;

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
            cout << "            ================ Login Berhasil ================" << endl;
            cout << "                         Selamat datang, " << users[i].username << "!" << endl;
            cout << "            ================================================" << endl;
            break;
        }  
    }   
    //CEK LOGIN GAGAL
        if (!login) {
            cout << "           =================**Login Gagal**=================" << endl;
            cout << "           |          username atau password salah         |" << endl; 
            cout << "           |          tekan enter untuk coba lagi!         |" << endl;
            cout << "           =================================================";
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
                cout <<"      ==================**Buat Akun baru**==================" << endl;
                cin.ignore();
                cout << "                         username : "; 
                getline(cin, newuser);
                cout << "                         Password : "; 
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
                    cout << "\t\t----- Maaf akun sudah terdaftar -----" << endl;
                } 
                //AKUN BERHASIL TERDAFTAR
                else {
                    users[jml_akun].username = newuser;
                    users[jml_akun].password = newpass;
                    jml_akun++;

                    cout <<"\t\t----- Akun Berhasil Terdaftar -----\n";
                }
                cout << "      =========================****=========================" << endl; 
            } 
                cout << "                tekan enter untuk kembali ke menu";
                cin.get();
                system ("cls");
                goto menu1;
    break;

    case '3' :
    return 0;

    default:
        cout << "            ======================****======================" << endl;
        cin.ignore ();
        cout << "            |  pilihan salah, tekan enter untuk coba lagi  |" << endl;
        cout << "            ======================****======================";
        cin.get ();
        system ("cls");
        goto menu1;
    break;
    }

    menu2 :
    judul_program();
    menu_inventaris();
   
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
                cout << "      =========================****=========================" << endl;
                cout << "      |              Maaf, penyimpanan penuh!              |" << endl;
                cout << "      |          tekan enter untuk kembali ke menu         |" << endl;
                cout << "      =========================****=========================";
            cin.ignore();
            cin.get();
            system("cls");
            goto menu2;
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
        cout << "\n      Masukkan judul buku yang ingin dicari: ";
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
                    cout << "\n\t\t       Buku " << databuku[i][0] << " berhasil dikeluarkan\n";
                    //BUKU TIDAK DITEMUKA
                    cout << "\n\t\t   Tekan enter untuk kembali ke menu";
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
                cout << "\n\t\t\t   Buku tidak ditemukan dalam inventaris.\n";
                cout << "\n\t\t\t   Tekan enter untuk kembali ke menu";
                cout << "\n\t==================================****====================================";
                cin.get(); 
                system("cls");
                goto menu2;
            }
        }
    break;
        //PILIHAN 5 DATA PEMINJAM
    case '5' :
    cin.ignore();
    cout << "\n\t============================*PENGEMBALIAN BUKU*=============================";  
    cout << "\n\t\t     Masukan Buku Yang ingin dikembalikan : ";
    getline(cin, judul_buku);
    cekbuku = false;
    for (int i = 0; i < jml_buku; i++) {
            if (databuku[i][0] == judul_buku) {
               //CEK STOK BUKU TERSEDIA
                    stok[i]++;
                    simpanbuku(databuku,stok,jml_buku);
                    cout << "\n\t\t\t   Buku " << databuku[i][0] << " berhasil dikembalikan\n";
                    cout<<"\t\t             Tekan Enter Untuk Kembali Ke Menu!";
                    cout << "\n\t==================================****======================================";
                    cin.get();
                    system("cls");
                    cekbuku = true;
                    goto menu2; 
                } 
        }
         if (!cekbuku) {
                cout << "\n\t\t         Buku tidak ditemukan dalam inventaris.\n";
                cout << "\n\t\t\t   Tekan enter untuk kembali ke menu";
                cout << "\n\t==================================****======================================";
                cin.get(); 
                system("cls");
                goto menu2;
            }
    break;
        //PILIHAN 6 LOGOUT/KELUAR
    case '6' :
        cout << "            ======================****======================" << endl;
        cout << "            |                  Logout...                   |" << endl;
        cin.ignore();
        cout << "            |    Tekan enter untuk kembali ke menu login   |" << endl;
        cout << "            ======================****======================";
        cin.get();
        system("cls");
        goto menu1;
    break;
        //PILIHAN SALAH
    default:
        cout << "            ======================****======================" << endl;
        cin.ignore ();
        cout << "            |  pilihan salah, tekan enter untuk coba lagi  |" << endl;
        cout << "            ======================****======================";
        cin.get ();
        system ("cls");
        goto menu2;
    break;
    }
}