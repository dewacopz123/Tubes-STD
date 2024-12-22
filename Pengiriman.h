#ifndef PENGIRIMAN_H
#define PENGIRIMAN_H

#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <climits>

// Struktur untuk menyimpan rute
struct rute {
    std::string namaRute;
    int biaya;  // Biaya untuk rute
    int jarak;  // Jarak untuk rute
};

// Struktur untuk menyimpan gudang
struct gudang {
    std::string namaGudang;
    std::list<rute> ruteList;
    gudang* nextGudang;
};

// Struktur utama untuk menyimpan pengiriman
struct pengiriman {
    gudang* firstGudang;
};

// Fungsi untuk menambahkan gudang baru
void addGudang(pengiriman &P, std::string namaGudang);

// Fungsi untuk menambahkan rute antar gudang
void addRute(pengiriman &P, std::string gudangAsal, std::string gudangTujuan, int biaya, int jarak);

// Fungsi untuk mengecek apakah gudang valid
bool isValidGudang(pengiriman &P, std::string namaGudang);

// Fungsi Dijkstra untuk mencari rute dengan biaya termurah
void dijkstra(pengiriman &P, std::string start, std::string end);

// Fungsi untuk menampilkan menu dan menangani input dari user
void menu(pengiriman &P);
void tampilkanGudang(pengiriman &P);



#endif
