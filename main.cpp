#include <iostream>
#include <iomanip>
using namespace std;

struct Pasien{
    string nama;
    int kategori;
    Pasien* next;
};
Pasien* head = NULL;
int totalPasien = 0;

void insertAntrean(string nama, int kat){
    Pasien* baru = new Pasien;
    baru->nama = nama;
    baru->kategori = kat;
    baru->next = NULL;
    if (head == NULL || head->kategori > baru->kategori) {
        baru->next = head;
        head = baru;
    } else {
        Pasien* temp = head;
        while (temp->next != NULL && temp->next->kategori <= baru->kategori) {
            temp = temp->next;
        }
        baru->next = temp->next;
        temp->next = baru;
    }
    totalPasien++;
}
void bacaFile(){
    FILE *berkas;
    berkas=fopen("data_pasien.txt","r");
    if(berkas==NULL) cout<<"Error\n";
    else{
        char buf_name[100]; string nama; int kat;
        while(fscanf(berkas, " %[^,],%d\n", buf_name, &kat) != EOF){
            nama = buf_name;
            insertAntrean(nama,kat);
        }
    }
    fclose(berkas);
}
void tulisUlangFile(){
    FILE *berkas;
    berkas = fopen("data_pasien.txt","w");
    Pasien* temp = head;
    while (temp != NULL) {
        fprintf(berkas, "%s,%d\n", temp->nama.c_str(), temp->kategori);
        temp = temp->next;
    }
    fclose(berkas);
}
void kategoriInfo(int kat, string &prioritas, string &status, string &zona, string &kategoriFull, string &tindakan){
    switch(kat){
        case 1: prioritas = "P1 (MERAH)"; status = "Resusitasi"; zona = "MERAH"; kategoriFull = "P1 - MERAH (RESUSITASI)"; tindakan = "Menuju Ruang Resusitasi SEGERA!"; break;
        case 2: prioritas = "P2 (MERAH)"; status = "Emergency"; zona = "MERAH"; kategoriFull = "P2 - MERAH (EMERGENCY)"; tindakan = "Menuju Ruang Tindakan Darurat!"; break;
        case 3: prioritas = "P3 (KUNING)"; status = "Urgent"; zona = "KUNING"; kategoriFull = "P3 - KUNING (URGENT)"; tindakan = "Menuju Ruang Observasi."; break;
        case 4: prioritas = "P4 (HIJAU)"; status = "Non-Urgent"; zona = "HIJAU"; kategoriFull = "P4 - HIJAU (NON-URGENT)"; tindakan = "Menuju Ruang Rawat Jalan."; break;
        case 5: prioritas = "P5 (BIRU)"; status = "False Emerg."; zona = "BIRU"; kategoriFull = "P5 - BIRU (FALSE EMERGENCY)"; tindakan = "Diarahkan ke Poliklinik."; break;
        default: prioritas = "-"; status = "-"; zona = "-"; kategoriFull = "-"; tindakan = "-"; break;
    }
}
void registrasiPasien(){
    string nama;
    int kat;
    
    cout << "\n>> REGISTRASI PASIEN\n";
    cout << "Nama Pasien\t: ";
    getline(cin, nama);
    cout << "Kategori Triase\t:\n";
    cout << "\t[1] P1 - MERAH (Resusitasi)\n\t[2] P2 - MERAH (Emergency)\n\t[3] P3 - KUNING (Urgent)\n\t[4] P4 - HIJAU (Non-Urgent)\n\t[5] P5 - BIRU (False Emergency)\n";
    cout << "Pilihan Kategori : ";
    cin >> kat;
    cin.ignore(1000, '\n');

    insertAntrean(nama, kat);
    tulisUlangFile(); 

    string p, s, z, kf, t;
    kategoriInfo(kat, p, s, z, kf, t);
    cout << "\n[SISTEM]: Pasien '" << nama << "' berhasil masuk ke zona " << z << " dan tersimpan di database.\n";
    cout << "Tekan ENTER untuk kembali ke menu...";
    cin.get();
}
void panggilPasien() {
    if (head == NULL) {
        cout << "\n[SISTEM]: Tidak ada pasien dalam antrean.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    Pasien* panggil = head;
    head = head->next; 

    string p, s, z, kf, t;
    kategoriInfo(panggil->kategori, p, s, z, kf, t);

    cout << "\n>> TINDAKAN MEDIS SEGERA\n";
    cout << "-----------------------------------------------------\n";
    cout << "SEDANG DIPROSES:\n";
    cout << "Nama Pasien : " << panggil->nama << "\n";
    cout << "Kategori    : " << kf << "\n";
    cout << "Status      : " << t << "\n";
    cout << "-----------------------------------------------------\n";
    delete panggil;
    totalPasien--;
    tulisUlangFile(); 

    cout << "\n[SISTEM]: Pasien telah dipindahkan dari antrean. Database diperbarui.\n";
    cout << "Tekan ENTER untuk kembali ke menu...";
    cin.get();
}

void lihatAntrean() {
	if (head == NULL){
		cout << "Tidak ada antrean!\n";
		cout << "Tekan enter untuk kembali...";
		cin.get();
		return;
		}
		
		Pasien* temp = head;
		int no = 1;
			
		cout << "\n==================== DATA SELURUH ANTREAN IGD ====================\n";
		cout << left << setw(5) << "NO" << setw(20) << "NAMA PASIEN" << setw(20) << "PRIORITAS" << setw(20) << "STATUS" << endl;
		cout << "---------------------------------------------------------------------\n";
		
		while (temp != NULL){
			
			string prioritas, status, zona, kategoriFull, tindakan;
			kategoriInfo(temp->kategori, prioritas, status, zona, kategoriFull, tindakan);
			
			cout << left << setw(5) << no << setw(20) << temp->nama << setw(20) << prioritas << setw(20) << status << endl;
			
			temp = temp->next;
			no++;
		}
			
        cout << "=========================================================================\n";
        cout << "Total Data : " << totalPasien << endl;
        
        cout << "\nTekan Enter Untuk Kembali...";
        cin.get();
	}

void cariPasien() {
    if (head == NULL) {
        cout << "\n[SISTEM]: Antrean saat ini kosong!\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }
    string nama;
    cout << "\n==========================================\n";
    cout << "          PENCARIAN DATA PASIEN\n";
    cout << "==========================================\n";
    cout << "Masukkan Nama Pasien yang dicari: ";
    getline(cin, nama);

    Pasien* temp = head;
    bool ketemu = false;

    while (temp != NULL) {
        if (temp->nama == nama) {
            string p, s, z, kf, t;
            kategoriInfo(temp->kategori, p, s, z, kf, t);
            
            cout << "\nDATA DITEMUKAN:\n";
            cout << "------------------------------------------\n";
            cout << "Nama Pasien  : " << temp->nama << "\n";
            cout << "Prioritas    : " << kf << "\n";
            cout << "Status       : Menunggu di Zona " << z << "\n";
            cout << "------------------------------------------\n";
            ketemu = true;
            break;
        }
        temp = temp->next;
    }
    if (!ketemu) cout << "\n[SISTEM]: Data Pasien dengan nama'" << nama << "' tidak ditemukan dalam antrean.\n";
    cout << "\nTekan ENTER untuk kembali...";
    cin.get();
}

int main(){
	bacaFile();
	int n;
	do{
	    cout<<"=====================================================\n          SISTEM MANAJEMEN TRIASE IGD v1.0          \n=====================================================\n\n";
		cout<<"-----------------------------------------------------\nMENU UTAMA:\n1. Registrasi Pasien Baru\n2. Panggil Pasien (Proses Penanganan)\n3. Lihat Detail Antrean\n4. Cari Data Pasien\n5. Keluar Program\n-----------------------------------------------------\nPilih menu [1-5]: ";
		cin>>n;
		cin.ignore();
		switch(n){
			case 1: registrasiPasien(); break;  
			case 2: panggilPasien(); break;
			case 3: lihatAntrean(); break;
			case 4: cariPasien(); break;
            case 5: 
            cout << "\nTerima kasih, semoga petugas sehat selalu"; break;
            default:
            cout << "Pilihan tidak valid! Pilih menu [1-4]\n"<< endl;
		}
	} while (n!=5);
}