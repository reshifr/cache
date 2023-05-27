# Mind

## Pencatat memo berbasis CLI

Alat pencatat memo serba guna yang dapat menyimpan berbagai data dalam format kunci-nilai.
Alat ini dapat menyimpan format data berupa catatan teks, skrip shell dan berkas.
Dilengkapi dengan fitur keamanan dan kemampuan untuk mengeksekusi skrip shell.

### Fitur

1. Menyimpan catatan dalam bentuk teks, skrip shell dan berkas
2. Mengeksekusi skrip shell secara langsung tanpa perlu diekstrak terlebih dahulu
3. Menggunakan standar keamanan terbaik saat ini dalam menyimpan catatan:
   - Cipher simetrik **ChaCha20-Poly1305** ([RFC 8439](https://datatracker.ietf.org/doc/html/rfc8439)) untuk melindungi catatan
   - Generator kunci dan hash **scrypt** ([RFC 7914](https://datatracker.ietf.org/doc/html/rfc7914)) untuk penghasil kunci enkripsi
   - Generator acak aman **Intel® Secure Key Technology** (`RDRAND`)
