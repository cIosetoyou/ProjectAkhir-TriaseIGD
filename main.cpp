#include <iostream>
#include <iomanip>
using namespace std;

struct Pasien{
    string nama;
    int kategori;
    Pasien* next;
};
Pasien* head = NULL;


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
			case 2:  
			case 3: 
			case 4:  
		}
	} while (n!=5);
}