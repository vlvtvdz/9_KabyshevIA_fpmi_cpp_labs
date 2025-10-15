#include <iostream>
#include <cstring>

//  Дата рождения 
struct date {
    char daymon[6];
    int  year;
};

//  class Student 
class Student {
    char fam[30];
    char imya[30];
    char otch[30];
    date t;
    char adr[40];
    char tel[20];
    char fac[20];
    int  kurs;

public:
    Student();

    void set(const char* s_fam, const char* s_imya, const char* s_otch,
             const char* s_daymon, int s_year,
             const char* s_adr, const char* s_tel,
             const char* s_fac, int s_kurs);

    char* getfac();
    int   getkurs();
    int   getyear();

    void show();
};

//  Реализация студентов 
Student::Student() {
    std::cout << "Input Surname (fam): ";  std::cin >> fam;
    std::cout << "Input Name (imya): ";    std::cin >> imya;
    std::cout << "Input Отчетво: ";     std::cin >> otch;

    std::cout << "Input date of born\n";
    std::cout << "Day.mon: ";  std::cin >> t.daymon;
    std::cout << "Year: ";     std::cin >> t.year;

    std::cout << "Input address: ";  std::cin >> adr;
    std::cout << "Input phone: ";    std::cin >> tel;
    std::cout << "Input faculty: ";  std::cin >> fac;
    std::cout << "Input kurs: ";     std::cin >> kurs;
}

void Student::set(const char* s_fam, const char* s_imya, const char* s_otch,
                  const char* s_daymon, int s_year,
                  const char* s_adr, const char* s_tel,
                  const char* s_fac, int s_kurs) {
    std::strcpy(fam,  s_fam);
    std::strcpy(imya, s_imya);
    std::strcpy(otch, s_otch);
    std::strcpy(t.daymon, s_daymon);
    t.year = s_year;
    std::strcpy(adr,  s_adr);
    std::strcpy(tel,  s_tel);
    std::strcpy(fac,  s_fac);
    kurs = s_kurs;
}

char* Student::getfac()  { return fac; }
int   Student::getkurs() { return kurs; }
int   Student::getyear() { return t.year; }

void Student::show() {
    std::cout << "---------------------------------\n";
    std::cout << "FIO        : " << fam << ' ' << imya << ' ' << otch << '\n';
    std::cout << "Was born   : " << t.daymon << '.' << t.year << '\n';
    std::cout << "Address    : " << adr << '\n';
    std::cout << "Phone      : " << tel << '\n';
    std::cout << "Faculty    : " << fac << '\n';
    std::cout << "Kurs       : " << kurs << '\n';
}

//  Список студентов заданного факультета 
void spisfac(Student spis[], int n) {
    char qfac[20];
    std::cout << "\nInput faculty: ";
    std::cin >> qfac;

    std::cout << "\n=== Students of faculty \"" << qfac << "\" ===\n";
    int found = 0;
    for (int i = 0; i < n; ++i) {
        if (std::strcmp(spis[i].getfac(), qfac) == 0) {
            spis[i].show();
            found = 1;
        }
    }
    if (!found) std::cout << "(no entries)\n";
}

//  Списки студентов для КАЖДОГО факультета и курса 
void spisfackurs_all(Student spis[], int n) {
    std::cout << "\n=== Lists for each (faculty, course) ===\n";

    char seenFac[100][20];
    int  seenKurs[100];
    int  seenCount = 0;

    for (int i = 0; i < n; ++i) {
        char* fac_i = spis[i].getfac();
        int   k_i   = spis[i].getkurs();

        int already = 0;
        for (int s = 0; s < seenCount; ++s) {
            if (std::strcmp(seenFac[s], fac_i) == 0 && seenKurs[s] == k_i) {
                already = 1;
                break;
            }
        }
        if (already) continue;

        std::strcpy(seenFac[seenCount], fac_i);
        seenKurs[seenCount] = k_i;
        ++seenCount;

        std::cout << "\n-- Faculty: " << fac_i << " | Kurs: " << k_i << " --\n";
        for (int j = 0; j < n; ++j) {
            if (std::strcmp(spis[j].getfac(), fac_i) == 0 && spis[j].getkurs() == k_i) {
                spis[j].show();
            }
        }
    }
}

// Список студентов, родившихся после заданного года 
void spis_born_after(Student spis[], int n) {
    int y;
    std::cout << "\nInput year (born AFTER this year): ";
    std::cin >> y;
    std::cout << "\n=== Students born after " << y << " ===\n";
    int any = 0;
    for (int i = 0; i < n; ++i) {
        if (spis[i].getyear() > y) {
            spis[i].show();
            any = 1;
        }
    }
    if (!any) std::cout << "(no entries)\n";
}

//  main 
int main() {
    Student* spis = nullptr;
    int n;

    std::cout << "Input a number of students: ";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Wrong number!\n";
        return 0;
    }

    spis = new Student[n]; // каждый челик заполнится в конструкторе

    std::cout << "\n=========== Full list ==========\n";
    for (int i = 0; i < n; ++i) spis[i].show();

    spisfac(spis, n);
    spisfackurs_all(spis, n);
    spis_born_after(spis, n);

    delete [] spis;

    std::cout << "\nPress any key to exit...\n";

    // ожидание нажатия enter
#ifdef _WIN32
    system("pause"); // Windows
#else
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); 
#endif

    return 0;
}