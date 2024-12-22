#include "pengiriman.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <climits>

// Fungsi untuk mencari gudang berdasarkan nama
gudang* findGudang(pengiriman &P, std::string namaGudang) {
    gudang* g = P.firstGudang;
    while (g != NULL) {
        if (g->namaGudang == namaGudang) return g;
        g = g->nextGudang;
    }
    return NULL;
}

// Fungsi untuk menambahkan gudang baru
void addGudang(pengiriman &P, std::string namaGudang) {
    gudang* g = new gudang;
    g->namaGudang = namaGudang;
    g->nextGudang = P.firstGudang;
    P.firstGudang = g;
}

// Fungsi untuk menambahkan rute antar gudang
void addRute(pengiriman &P, std::string gudangAsal, std::string gudangTujuan, int biaya, int jarak) {
    gudang* g = P.firstGudang;
    while (g != NULL && g->namaGudang != gudangAsal) {
        g = g->nextGudang;
    }
    if (g != NULL) {
        rute newRute;
        newRute.namaRute = gudangTujuan;
        newRute.biaya = biaya;  // Menyimpan biaya untuk rute
        newRute.jarak = jarak;  // Menyimpan jarak untuk rute
        g->ruteList.push_back(newRute);
    }
}

// Fungsi untuk mengecek apakah gudang valid
bool isValidGudang(pengiriman &P, std::string namaGudang) {
    return findGudang(P, namaGudang) != NULL;
}

// Fungsi Dijkstra untuk mencari rute dengan biaya termurah
void dijkstra(pengiriman &P, std::string start, std::string end) {
    std::unordered_map<std::string, int> dist;
    std::unordered_map<std::string, std::string> previous;
    std::unordered_map<std::string, int> distanceTravelled;  // Menyimpan jarak yang ditempuh
    std::unordered_set<std::string> processed;

    // Set initial distance untuk setiap gudang
    gudang* g = P.firstGudang;
    while (g != NULL) {
        dist[g->namaGudang] = INT_MAX;
        distanceTravelled[g->namaGudang] = 0;  // Set jarak yang ditempuh ke 0
        g = g->nextGudang;
    }

    dist[start] = 0;  // Biaya ke gudang start adalah 0

    while (true) {
        std::string minCity = "";
        int minCost = INT_MAX;

        // Mencari gudang yang belum diproses dengan biaya terkecil
        g = P.firstGudang;
        while (g != NULL) {
            if (processed.find(g->namaGudang) == processed.end()) {
                if (dist[g->namaGudang] < minCost) {
                    minCost = dist[g->namaGudang];
                    minCity = g->namaGudang;
                }
            }
            g = g->nextGudang;
        }

        if (minCity == "") break; // Tidak ada lagi kota untuk diproses

        processed.insert(minCity);

        g = findGudang(P, minCity);
        for (const auto& route : g->ruteList) {
            std::string nextCity = route.namaRute;
            int newCost = dist[minCity] + route.biaya;

            // Update biaya jika ditemukan rute yang lebih murah
            if (newCost < dist[nextCity]) {
                dist[nextCity] = newCost;
                previous[nextCity] = minCity;
                // Menyimpan total jarak yang ditempuh sampai kota tujuan
                distanceTravelled[nextCity] = distanceTravelled[minCity] + route.jarak;
            }
        }
    }

    if (dist[end] == INT_MAX) {
        std::cout << "Tidak ada rute dari " << start << " ke " << end << std::endl;
        return;
    }

    std::cout << "Biaya termurah dari " << start << " ke " << end << " adalah IDR " << dist[end] << std::endl;

    // Menampilkan rute yang dilewati dan jarak yang ditempuh
    std::list<std::string> path;
    int totalJarak = distanceTravelled[end];  // Mengambil total jarak dari map distanceTravelled
    std::string currentCity = end;
    while (currentCity != start) {
        path.push_front(currentCity);
        currentCity = previous[currentCity];
    }
    path.push_front(start);

    std::cout << "Rute yang dilewati: ";
    for (const auto& city : path) {
        std::cout << city << " ";
    }
    std::cout << std::endl;

    std::cout << "Total jarak yang ditempuh: " << totalJarak << " km" << std::endl;
}

// Fungsi untuk menampilkan menu dan menangani input dari user
void menu(pengiriman &P) {
    std::string pilihan;
    std::string gudangAsal, gudangTujuan;

    do {
        std::cout << "Menu:\n";
        std::cout << "1. Lakukan Pengiriman Barang\n";
        std::cout << "2. Tampilkan Kota/Gudang yang Tersedia\n";
        std::cout << "3. Keluar\n";
        std::cout << "Pilih opsi: ";
        std::cin >> pilihan;

        if (pilihan == "1") {
            std::cout << "Masukkan lokasi asal barang: ";
            std::cin >> gudangAsal;
            std::cout << "Masukkan lokasi tujuan barang: ";
            std::cin >> gudangTujuan;

            if (!isValidGudang(P, gudangAsal)) {
                std::cout << "Lokasi asal tidak valid. Silakan coba lagi.\n";
            } else if (!isValidGudang(P, gudangTujuan)) {
                std::cout << "Lokasi tujuan tidak valid. Silakan coba lagi.\n";
            } else {
                dijkstra(P, gudangAsal, gudangTujuan);
            }
        } else if (pilihan == "2") {
            tampilkanGudang(P);
        } else if (pilihan == "3") {
            std::cout << "Keluar dari program.\n";
        } else {
            std::cout << "Opsi tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != "3");
}

// Fungsi untuk menampilkan daftar gudang
void tampilkanGudang(pengiriman &P) {
    gudang* g = P.firstGudang;
    if (g == NULL) {
        std::cout << "Belum ada gudang yang terdaftar.\n";
        return;
    }

    std::cout << "Kota/Gudang yang tersedia untuk pengiriman:\n";
    while (g != NULL) {
        std::cout << "- " << g->namaGudang << std::endl;
        g = g->nextGudang;
    }
}
