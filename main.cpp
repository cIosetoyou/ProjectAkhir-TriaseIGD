#include <iostream>
#include <iomanip>
using namespace std;


int main(){
	bacaFile();
	int n;
	do{
	    cout<<"=====================================================\n          SISTEM MANAJEMEN TRIASE IGD v1.0          \n=====================================================\n\n";
		cout<<"-----------------------------------------------------\nMENU UTAMA:\n1. Registrasi Pasien Baru\n2. Panggil Pasien (Proses Penanganan)\n3. Lihat Detail Antrean\n4. Cari Data Pasien\n5. Keluar Program\n-----------------------------------------------------\nPilih menu [1-5]: ";
		cin>>n;
		cin.ignore();
		switch(n){
			case 1:  
			case 2:  
			case 3: 
			case 4:  
		}
	} while (n!=5);
}