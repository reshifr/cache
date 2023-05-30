# Mind [![integration](https://github.com/reshifr/mind/actions/workflows/integration.yml/badge.svg)](https://github.com/reshifr/mind/actions/workflows/integration.yml)

## Pencatat memo berbasis CLI

Alat pencatat memo serba guna yang dapat menyimpan berbagai data dalam format kunci-nilai.
Alat ini dapat menyimpan format data berupa catatan teks, skrip shell dan berkas.
Dilengkapi dengan fitur keamanan dan kemampuan untuk mengeksekusi skrip shell.

### Fitur

* Menyimpan catatan dalam bentuk teks, skrip shell dan berkas
* Mengeksekusi skrip shell secara langsung tanpa perlu diekstrak terlebih dahulu
* Menggunakan standar keamanan terbaik saat ini dalam menyimpan catatan:
  * Cipher simetrik **ChaCha20-Poly1305** ([RFC 8439](https://datatracker.ietf.org/doc/html/rfc8439)) untuk melindungi catatan
  * Generator kunci dan hash **scrypt** ([RFC 7914](https://datatracker.ietf.org/doc/html/rfc7914)) untuk penghasil kunci enkripsi
  * Generator acak aman **Intel® Secure Key Technology** (`RDRAND`)
