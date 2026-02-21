# 📝 Dynamic To-Do List Manager in C

Un manager de sarcini, dezvoltat în limbajul C, care pune accent pe **gestionarea dinamică a memoriei** 
---

## 📖 Despre Proiect
Timp de lucru: 4h

Acest proiect a fost creat pentru a simula comportamentul unei liste dinamice. Resursele sistemului fiind utilizate într-un mod strict proporțional cu datele procesate:
### 🧠 Concepte Tehnice Utilizate
* **Pointeri Dubli (`Task **`)**: Utilizați pentru a permite modificarea adresei vectorului din `main` atunci când acesta este realocat în alte funcții.
* **Alocare pe Heap**: Controlul manual al memoriei prin care „rezervăm” loc în RAM exact cât ocupă fiecare text și „eliberăm” locul imediat ce ștergem task-ul.
* **Algoritm de Shifting**: La ștergerea unui task, elementele sunt mutate pentru a menține continuitatea datelor.

---

## ✨ Funcționalități Detaliate

### 1. ➕ Gestiune Dinamică
Programul verifică dacă există spațiu disponibil. Când lista se umple, programul rezervă automat spațiu pentru încă 3 task-uri noi, pentru a nu cere permisiunea sistemului la fiecare pas.

### 2. 🔍 Validarea Datelor
Funcția `ver_str` asigură integritatea datelor:
- Previne introducerea de task-uri goale.
- Limitează lungimea la 150 de caractere pentru a preveni buffer overflow.

### 3. 📝 Editare în Timp Real
Permite actualizarea descrierii unui task. Memoria pentru vechea descriere este eliberată/realocată pentru a se potrivi noii lungimi a textului.

### 4. 🗑️ Gestiune Eficientă la Ștergere
După eliminarea unui task programul folosește `realloc` pentru a elibera memoria neutilizată.

---

## 🛠️ Ghid de Utilizare

### Cerințe de Sistem
* Compilator `gcc` (GNU Compiler Collection)
* Utilitarul `make`