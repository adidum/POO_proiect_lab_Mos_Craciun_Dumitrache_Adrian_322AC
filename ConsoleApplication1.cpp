/*
Moș Crăciun primește scrisori de la copii cu ce își doresc.Fiecare scrisoare conține următoarele atribute :
Nume
Prenume
Vârstă
Oraș
Wishlist(acesta este o listă de mai multe jucării pe care fiecare copil și le dorește)
Culoare plic : roz pentru fetițe și albastru pentru băieței
*/
#include <iostream>
#include<string>
using namespace std;

struct Wishlist
{
    string cadouri[10];
};


class Copiii
{
protected:
    string nume[5];
    string prenume[5];
    int varsta[5];
    string oras[5];
    Wishlist wishlist[5];
    string culoare[5];
public:
    Copiii()
    {
        cout << "5 copiii au de primit cadou\n";
    }
    Copiii(string n[5], string pn[5], int v[5], string o[5], Wishlist w[5], string c[5])
    {
        //luarea datelor principale

        int i;
        for (i = 0; i < 5; i++)
        {
            nume[i] = n[i];
            prenume[i] = pn[i];
            varsta[i] = v[i];
            oras[i] = o[i];
            wishlist[i].cadouri[0] = w[i].cadouri[0];
            wishlist[i].cadouri[1] = w[i].cadouri[1];
            culoare[i] = c[i];
        }
    }
    void setters()
    {//trimiterea datelor principale
        int i;
        for (i = 0; i < 5; i++)
        {
            cout << this->nume[i] << endl << this->prenume[i] << endl << this->varsta[i] << endl << this->oras[i] << endl << this->wishlist[i].cadouri[0] << endl << this->wishlist[i].cadouri[1] << endl << this->culoare[i] << endl << endl;
        }
    }

};
/*
Odată ce ajung scrisorile la Polul Nord, elfii se ocupă de ele.
Pentru fiecare copil se acordă un buget, în funcție dacă a fost cuminte sau nu. Pentru fiecare copil cuminte se acordă o sumă de 100$, iar pentru unul rău se acordă 10$.
Elfii au deja o listă cu statusul fiecărui copil și atribuie suma în funcție de acesta.
Elfii parcurg după lista și se uită ce au copiii pe wishlist. După care se uită pe inventar și văd dacă acele jucării există la ei în atelier.
Dacă există le pun în punga de cadouri în ordinea înșiruită.
Dacă au mai multe lucruri pe listă decât permite bugetul, se adaugă în pungă în ordinea lor până să se depășească și apoi se adaugă o acadea pentru fiecare dolar necheltuit.
Dacă nu există nimic pe inventar se va da un cadou default.
Dacă ce e pe listă depășește din start bugetul se va da un cadou default care valorează fix 100$ sau 10$ în funcție de copil. (este același cadou default)
Elfii dau mai departe lista cu cadouri trolilor.
Elfii dau mai departe numărul de acadele Doamnei Crăciun.
Elfii dau mai departe lista cu orașe lui Moș Crăciun.

*/

class Elfi : public Copiii
{
protected:
    bool cumintenie[5];
    double buget[5];
    string inventar_cadouri[7];
    double cost_cadouri[7];
    string punga_cadouri[5];
    double acadele[5];
public:
    Elfi(string n[5], string pn[5], int v[5], string o[5], Wishlist w[5], string c[5]) : Copiii{ nume , prenume , varsta , oras , wishlist , culoare }
    {
        cout << "Elfi se pun pe munca\n";
        int i;
        for (i = 0; i < 5; i++)
        {
            this->nume[i] = n[i];
            this->prenume[i] = pn[i];
            this->varsta[i] = v[i];
            this->oras[i] = o[i];
            this->wishlist[i].cadouri[0] = w[i].cadouri[0];
            this->wishlist[i].cadouri[1] = w[i].cadouri[1];
            this->culoare[i] = c[i];
        }
    }
    void IsCuminte(bool cumintenie[5])
    {
        //verificam daca e cuminte copilul
        //daca da ii dam 100, daca nu ii dam 10$
        int i;
        cout << endl;
        for (i = 0; i < 5; i++)
        {
            this->cumintenie[i] = cumintenie[i];
            if (this->cumintenie[i] == true)
            {
                cout << this->prenume[i] << " este cuminte";
                this->buget[i] = 100;
            }
            else
            {
                if (this->cumintenie[i] == false)
                {
                    cout << this->prenume[i] << " nu este cuminte";
                    this->buget[i] = 10;
                }
            }
            cout << endl;

        }
        cout << endl;
    }
    void Impartirea_cadourilor(string inventar_cadouri[7], double cost_cadouri[7])
    {
        int i;
        for (i = 0; i < 7; i++)
        {
            this->inventar_cadouri[i] = inventar_cadouri[i];
            this->cost_cadouri[i] = cost_cadouri[i];
        }
        int j, k, ok = 0, parcurgere_rest_buget, nr_intrari;
        for (i = 0; i < 5; i++)
        {
            //5 copiii
            nr_intrari = 0;
            ok = 0;
            for (k = 0; k < 2; k++)
            {//2 reprezinta nr de cadouri pe care si le doreste un copil
                for (j = 0; j < 7; j++)
                {
                    //7 este nr de cadouri din inventar
                    if (this->wishlist[i].cadouri[k] == this->inventar_cadouri[j])
                    {//verificare daca gasim un cadou al copilului i in inventar
                        if (this->cost_cadouri[j] <= this->buget[i])
                        {
                            //daca costul cadoului este mai mic decat bugetul intra in if
                            ok = 1;//ok vedem daca a intrat macar o data pentru default
                            nr_intrari++;
                            this->buget[i] -= this->cost_cadouri[j];
                            if (nr_intrari >= 2)
                            {
                                this->punga_cadouri[i] = this->punga_cadouri[i] + ", " + this->inventar_cadouri[j];//formam punga de cadouri
                            }
                            else
                            {
                                this->punga_cadouri[i] = this->punga_cadouri[i] + " " + this->inventar_cadouri[j];//avem cate un caz pentru a vedea daca punem virgula sau nu
                            }
                        }
                    }

                }
            }
            if (ok == 0)
            {    if(this->cumintenie[i] == true)
                {
                   this->punga_cadouri[i] = "100$";
                   ///cadou default, 0 acadele, pentru ca nu s a gasit vreun  cadou
                 }
                 else
                {
                this->punga_cadouri[i] = "10$";
                }
            this->acadele[i] = 0;
            }
            else
            {
                if (this->buget[i] != 0 && this->buget[i] != 1)
                {
                    this->punga_cadouri[i] = this->punga_cadouri[i] + " si " + to_string(this->buget[i]) + " acadele"; //adaugam acadele in punga 
                    this->acadele[i] = this->buget[i]; //nr de acadele este restul ramas din buget
                }
                else
                {
                    if (this->buget[i] == 1)
                    {
                        this->punga_cadouri[i] = this->punga_cadouri[i] + " si o acadea"; //in caz ca avem o acadea, sa apara bine
                        this->acadele[i] = 1;
                    }
                }
            }
            if (this->punga_cadouri[i] != "100$" || this->punga_cadouri[i] != "10$")
            {
                //cazul cand avem cadouri sau cel putin acadele
                if (nr_intrari > 1)
                    cout << this->prenume[i] << " are ca si cadouri" << this->punga_cadouri[i] << endl;//varianta pentru mai multe cadouri
                else
                    cout << this->prenume[i] << " are ca si cadou" << this->punga_cadouri[i] << endl;//varianta pentru un cadou

            }
            else
            {
                cout << this->prenume[i] << " are ca si cadou " << this->buget[i] << "$" << endl;//suma default
            }

        }
    }
    void set_punga_cadou_acadea(string punga_cadou[5], bool cumintenia[5], double acadea[5])
    {
        int i;
        for (i = 0; i < 5; i++)
        {
            punga_cadou[i] = this->punga_cadouri[i];
            cumintenia[i] = this->cumintenie[i];
            acadea[i] = this->acadele[i];
        }
        //trimiterea datelor precum punga de cadouri, cumintenia si acadelele
    }

};

/*
Trolii primesc de la elfi lista cu cadouri și împachetează fiecare cadou cu un ambalaj specific pentru fete
 și unul specific pentru băieți.
De asemenea, trolii pun și un cărbune în punga fiecărui copil rău.
*/
class Troli : public Elfi
{
protected:
    string impachetare[5];
public:
    Troli(string n[5], string pn[5], int v[5], string o[5], Wishlist w[5], string c[5]) : Elfi{ nume , prenume , varsta , oras , wishlist , culoare }
    {
        cout << "Troli se pun pe munca\n";
        int i;
        for (i = 0; i < 5; i++)
        {
            this->nume[i] = n[i];
            this->prenume[i] = pn[i];
            this->varsta[i] = v[i];
            this->oras[i] = o[i];
            this->wishlist[i].cadouri[0] = w[i].cadouri[0];
            this->wishlist[i].cadouri[1] = w[i].cadouri[1];
            this->culoare[i] = c[i];
        }
    }
    void set_punga_cadorui_si_cumintenie(string pc[5], bool c[5])
    {
        int i;
        for (i = 0; i < 5; i++)
        {
            this->punga_cadouri[i] = pc[i];
            this->cumintenie[i] = c[i];
            cout << this->punga_cadouri[i] << " " << this->cumintenie[i] << " ";
            //luam date precum punga de cadouri si cumintenia
        }
    }
    void ambalare()
    {
        int i, spatiere_cadou, spatiere_cadou_1;
        string impachetare_model_initial[2] = { "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"  , "__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __" };
        //modelul de impachatere. Primul este pentru baietei, al doilea este pentru fetite
        int lungime_model_initial[2]{ impachetare_model_initial[0].length() , impachetare_model_initial[1].length() };
        //lungimea impachterii initiale atat pentru baieti, cat si pentru fete
        for (i = 0; i < 5; i++)
        {
            if (this->culoare[i] == "albastru")
            {//intram la baieti
                this->impachetare[i] = impachetare_model_initial[0] + "\n|";

                if (this->cumintenie[i] == true)
                {
                    //este cuminte
                    for (spatiere_cadou = 0; spatiere_cadou < ((lungime_model_initial[0] - this->punga_cadouri[i].length()) / 2); spatiere_cadou++)
                    {
                        this->impachetare[i] += " ";
                        //adaugam spatii in prima parte din lugimea initiala - lungimea in text a cadourilor impartit la 2
                        //scopul acestuia este de a centra cadoul
                    }
                    this->impachetare[i] += this->punga_cadouri[i];
                    spatiere_cadou_1 = spatiere_cadou;
                    for (spatiere_cadou = spatiere_cadou_1; spatiere_cadou < lungime_model_initial[0] - 1 - this->punga_cadouri[i].length(); spatiere_cadou++)
                    {
                        this->impachetare[i] += " ";
                        //restul de spatieri pana la final
                    }
                    this->impachetare[i] += "|\n";
                }
                else
                {
                    if (this->cumintenie[i] == false)
                    {//nu este cuminte
                        this->punga_cadouri[i] += "+ carbune";//adaugam carbune
                        for (spatiere_cadou = 0; spatiere_cadou < ((lungime_model_initial[0] - this->punga_cadouri[i].length()) / 2); spatiere_cadou++)
                        {//acelasi concept
                            this->impachetare[i] += " ";
                        }
                        this->impachetare[i] += this->punga_cadouri[i];
                        spatiere_cadou_1 = spatiere_cadou;
                        for (spatiere_cadou = spatiere_cadou_1; spatiere_cadou < lungime_model_initial[0] - 1 - this->punga_cadouri[i].length(); spatiere_cadou++)
                        {
                            this->impachetare[i] += " ";
                        }
                        this->impachetare[i] += "|\n";
                    }
                }
                this->impachetare[i] += impachetare_model_initial[0];

            }
            else
            {
                if (this->culoare[i] == "roz")
                {//daca este fata
                    //mai jos se repeta aceleasi conceptii ca la baieti, diferind impachetarea
                    this->impachetare[i] = impachetare_model_initial[1] + "\n|";

                    if (this->cumintenie[i] == true)
                    {
                        for (spatiere_cadou = 0; spatiere_cadou < ((lungime_model_initial[1] - this->punga_cadouri[i].length()) / 2); spatiere_cadou++)
                        {
                            this->impachetare[i] += " ";
                        }
                        this->impachetare[i] += this->punga_cadouri[i];
                        spatiere_cadou_1 = spatiere_cadou;
                        for (spatiere_cadou = spatiere_cadou_1; spatiere_cadou < lungime_model_initial[1] - 1 - this->punga_cadouri[i].length(); spatiere_cadou++)
                        {
                            this->impachetare[i] += " ";
                        }
                        this->impachetare[i] += "|\n";
                    }
                    else
                    {
                        if (this->cumintenie[i] == false)
                        {
                            for (spatiere_cadou = 0; spatiere_cadou < ((lungime_model_initial[1] - this->punga_cadouri[i].length()) / 2); spatiere_cadou++)
                            {
                                this->impachetare[i] += " ";
                            }
                            this->impachetare[i] += this->punga_cadouri[i];
                            spatiere_cadou_1 = spatiere_cadou;
                            for (spatiere_cadou = spatiere_cadou_1; spatiere_cadou < lungime_model_initial[1] - 1 - this->punga_cadouri[i].length(); spatiere_cadou++)
                            {
                                this->impachetare[i] += " ";
                            }
                            this->impachetare[i] += "|\n";
                        }
                    }
                    this->impachetare[i] += impachetare_model_initial[1];
                    cout << this->impachetare[i] << endl;
                }
            }
            cout << "\n" << this->prenume[i] << " are impachetat cadoul astfel:\n" << this->impachetare[i] << "\n";
        }
    }
};
/*
Doamna Crăciun primește lista cu numărul de acadele pe care trebuie să le facă, de la elfi, iar de la troli numărul de cărbuni folosiți.
Fiecare cărbune valorează 0.5$.
La final doamna Crăciun calculează bugetul extra(acadele plus cărbuni).

Să se afișeze suma totală.
*/

class Doamna_Craciunita : public Troli
{
protected:
    double buget_extra_total;
    int harta[5];
public:
    Doamna_Craciunita(string n[5], string pn[5], int v[5], string o[5], Wishlist w[5], string c[5]) : Troli{ nume , prenume , varsta , oras , wishlist , culoare }
    {
        cout << "Domna Craciunita se pune pe munca\n";
        int i;
        for (i = 0; i < 5; i++)
        {
            this->nume[i] = n[i];
            this->prenume[i] = pn[i];
            this->varsta[i] = v[i];
            this->oras[i] = o[i];
            this->wishlist[i].cadouri[0] = w[i].cadouri[0];
            this->wishlist[i].cadouri[1] = w[i].cadouri[1];
            this->culoare[i] = c[i];
        }
    }
    void get_acadea_cumintenia(double acadea[5], bool cumintenia[5])
    {//luam datele pentru acadele si cumintenie
        int i;
        for (i = 0; i < 5; i++)
        {
            this->acadele[i] = acadea[i];
            this->cumintenie[i] = cumintenia[i];
        }
    }
    void buget_extr()
    {
        //bugetul extra pentru acadele si carbuni
        int i;
        double nr_carbuni = 0;
        buget_extra_total = 0;
        for (i = 0; i < 5; i++)
        {
            if (this->cumintenie[i] == false)
            {
                nr_carbuni++;
            }
            buget_extra_total += this->acadele[i];
        }
        buget_extra_total += nr_carbuni * 0.5;
        cout << "\nBuget extra total este " << buget_extra_total << "$\n";
    }
    void get_harta(int harta[5])
    {
        //luam harta de la mos craciun
        int i;
        for (i = 0; i < 5; i++)
        {
            this->harta[i] = harta[i];
            if (i != 4)
                cout << this->oras[this->harta[i] - 1] << "->";
            else
                cout << this->oras[this->harta[i] - 1];//finalul hartii
        }
    }
};


/*Moș Crăciun primește lista cu orașe de la elfi și calculează drumul critic în număr de kilometrii și
ordinea destinațiilor având în vedere că el pleacă cu sania din aeroportul Rovaniemi din Laponia(Finlanda). (nu se ia în calcul și drumul de întoarcere)
Useful: https://www.distancecalculator.net/
Minim 4 orașe la fiecare țară.

Înainte să plece, Doamna Crăciun vrea și ea să afle traseul lui Moș Crăciun, așa că îl împărtășește și cu ea.
*/
class Mos_Craciun : public Elfi
{
public:
    Mos_Craciun(string n[5], string pn[5], int v[5], string o[5], Wishlist w[5], string c[5]) : Elfi{ nume , prenume , varsta , oras , wishlist , culoare }
    {
        cout << "Mos Craciun se pune pe treaba\n";
        int i;
        for (i = 0; i < 5; i++)
        {
            this->nume[i] = n[i];
            this->prenume[i] = pn[i];
            this->varsta[i] = v[i];
            this->oras[i] = o[i];
            this->wishlist[i].cadouri[0] = w[i].cadouri[0];
            this->wishlist[i].cadouri[1] = w[i].cadouri[1];
            this->culoare[i] = c[i];
        }
    }

    class drum_scurt
    {
    protected:
        int harta[5];
    public:
        //cele 2 subprograme pentru drumul minim
        int poz_minimum(int linie_orase[6]) {
            int min = 999999;
            int pozitie;
            for (int i = 0; i < 6; i++) {
                if (linie_orase[i] < min && linie_orase[i] != 0) {
                    min = linie_orase[i];//vedem care e minimul si apoi ii luam pozitia
                    pozitie = i;
                }
            }
            return pozitie;
        }
        void drum_minim(int graph[6][6]) {
            int poz,  distanta = 0, j, i, drum[6];
            for (i = 0; i < 6; i++)
                drum[i] = 0;//initializam la inceput cu 0
            int k = 0;
            for (i = 0; i < 5; i++) {
                this->harta[i] = poz_minimum(graph[drum[i]]);//apelam poz_minimum pentru a gasi pozitia minima
                
                drum[i + 1] = this->harta[i];//drum[i+1] ii dam pozitia minima pentru a continua
                distanta += graph[drum[i]][this->harta[i]];
                for (j = 0; j < 6; j++)
                    graph[j][this->harta[i]] = 0;
            }
            cout << "\nDistanta minima: " << endl;
            cout << distanta<<" km\n";
        }
        void set_harta(int harta[5])
        {
            int i;
            for (i = 0; i < 5; i++)
                harta[i] = this->harta[i];
            //trimitem mai departe harta
        }
    };
};
int main()
{
    //avem datele cu apelarile
    string nume[5] = { "Toba" , "Filoteanu" , "Pruna" , "Dima" , "Cazacu" };
    string prenume[5] = { "Bogdan" , "Ilinca" , "Orlando" , "Alexandru" , "Stefan" };
    int varsta[5] = { 21 , 20 , 20 , 20 , 20 };
    string oras[5] = { "Santiago" , "Valparaiso" , "Vina del Mar" , "Arica" , "La Serena" };
    int i = 0, j = 0;
    Wishlist wishlist[5];

    wishlist[0].cadouri[0] = { "un PS5" };
    wishlist[1].cadouri[0] = { "un make-up" };
    wishlist[2].cadouri[0] = { "o masinuta" };
    wishlist[3].cadouri[0] = { "o figurina" };
    wishlist[4].cadouri[0] = { "un caine" };
    wishlist[0].cadouri[1] = { "o masinuta" };
    wishlist[1].cadouri[1] = { "o pensula" };
    wishlist[2].cadouri[1] = { "un mouse" };
    wishlist[3].cadouri[1] = { "casti" };
    wishlist[4].cadouri[1] = { "o pisica" };
    string culoare[5] = { "albastru" , "roz" , "albastru" , "albastru" , "albastru" };
    Copiii copiii;
    Elfi elfi(nume, prenume, varsta, oras, wishlist, culoare);
    bool cumintenie[5] = { false , true , true , false , true };
    elfi.IsCuminte(cumintenie);
    string inventar_cadouri[7] = { "o figurina" , "un PS3" , "un make-up" , "o pisica" , "o pensula" , "casti" , "un caine" };
    double cost_cadouri[7] = { 23 , 98 , 84 , 50 , 15 , 34 , 60 };
    elfi.Impartirea_cadourilor(inventar_cadouri, cost_cadouri);
    string punga_cadou[5];
    bool cumintenie_troli[5];
    double acadea[5];
    elfi.set_punga_cadou_acadea(punga_cadou, cumintenie_troli, acadea);
    Troli troli(nume, prenume, varsta, oras, wishlist, culoare);
    troli.set_punga_cadorui_si_cumintenie(punga_cadou, cumintenie);
    troli.ambalare();
    Doamna_Craciunita doamna_craciunita(nume, prenume, varsta, oras, wishlist, culoare);

    doamna_craciunita.get_acadea_cumintenia(acadea, cumintenie_troli);
    doamna_craciunita.buget_extr();
    Mos_Craciun mos_craciun(nume, prenume, varsta, oras, wishlist, culoare);
    Mos_Craciun::drum_scurt reni;
    int graph[6][6] = { { 0,    13664,  13663, 13658, 12138, 13334   },
                        { 13664, 0,     99,  94,    1663,  397},
                        { 13663, 99,    0,    6,    1624, 350},
                        { 13658, 94,    6,   0,    1621, 347 },
                        { 12138, 1663, 1624, 1621,  0,    1273 },
                        { 13334, 397,  350  , 347,  1273,  0} };
    reni.drum_minim(graph);
    int harta[5];
    reni.set_harta(harta);
    doamna_craciunita.get_harta(harta);

}
