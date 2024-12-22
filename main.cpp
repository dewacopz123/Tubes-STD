#include <iostream>
#include "pengiriman.h"

int main() {
    pengiriman PengirimanBarang;
    PengirimanBarang.firstGudang = NULL;

    // Menambahkan gudang
    addGudang(PengirimanBarang, "Jakarta");
    addGudang(PengirimanBarang, "Surabaya");
    addGudang(PengirimanBarang, "Yogyakarta");
    addGudang(PengirimanBarang, "Bandung");
    addGudang(PengirimanBarang, "Bali");
    addGudang(PengirimanBarang, "Medan");
    addGudang(PengirimanBarang, "Makassar");
    addGudang(PengirimanBarang, "Semarang");

    // Menambahkan rute antar gudang beserta biaya dan jarak
    addRute(PengirimanBarang, "Jakarta", "Surabaya", 10000, 700);
    addRute(PengirimanBarang, "Surabaya", "Yogyakarta", 50000, 200);
    addRute(PengirimanBarang, "Yogyakarta", "Bandung", 80000, 350);
    addRute(PengirimanBarang, "Bandung", "Bali", 15000, 100);
    addRute(PengirimanBarang, "Bali", "Medan", 20000, 120);
    addRute(PengirimanBarang, "Medan", "Makassar", 25000, 150);
    addRute(PengirimanBarang, "Makassar", "Semarang", 22000, 200);
    addRute(PengirimanBarang, "Semarang", "Jakarta", 70000, 100);
    addRute(PengirimanBarang, "Surabaya", "Bandung", 40000, 250);
    addRute(PengirimanBarang, "Yogyakarta", "Semarang", 10000, 200);
    addRute(PengirimanBarang, "Medan", "Jakarta", 21000, 100);

    // Memanggil Function menu
    menu(PengirimanBarang);

    return 0;
}
