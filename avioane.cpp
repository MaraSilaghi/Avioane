#include <iostream>
#include <string>
using namespace std;

const int LUNG_TABLA= 10;
const int LAT_TABLA = 10;
const int NR_AVION = 3;

const char AER = 247; // "*" in cod ASCII
const char LOVIT = 'X';
const char LOVIT_CABINA= 'A';
const char e_avion = 'S';
const char nu_e_avion = '0';
const char e_cabina='O';

struct PUNCT {
             // un punct de coordonate x(abscisa) si y(ordonata) pe tabla
             int X;
             int Y;
             };

struct AVION {
             PUNCT punct[10]; //coordonatele fiecarui punct de pe tabla (10 puncte intr-o avion)
             bool e_lovit[10];//daca punctele au fost lovite sau nu
             bool cabina[10];
             }avion[NR_AVION];

struct JUCATOR {
                char tabla[LUNG_TABLA][LAT_TABLA];//fiecare jucator are tabla sa
               }jucator[3]; //ignoram jucatorul 0, folosim doar jucatorii 1 si 2

enum DIRECTIE {STANGA=1,DREAPTA=2,SUS=3,JOS=4};
struct PLASEAZA_AVION {
                       DIRECTIE directie;
                       AVION nr_avion;
                      };

bool joc_inceput = false;

//Functii (explicate la finalul codului)
void Incarca_avion();
void Resetare_tabla();
void Desen_tabla(int);
PLASEAZA_AVION Plasare_avion(int);
bool Atac(int&,int&,int);
bool joc_sfarsit(int);

int main()
{
	Resetare_tabla();
    //*********************PLASAM AVIOANELE***************************
	for (int un_jucator=1; un_jucator<3; ++un_jucator)
	{
		//fiecare jucător își plasează avioanele
		for (int avion_curent=0; avion_curent<NR_AVION; ++avion_curent)
		{
			system("cls");
			Desen_tabla(un_jucator);//se afiseaza tabla pentru un jucator
			//INSTRUCTIUNI
			cout << endl << endl;
			cout << "INSTRUCTIUNI (Jucatorul " << un_jucator <<")"<< endl << endl;
			cout << "Acum iti vei plasa cele 3 avioane. Coordonatele necesare sunt:" << endl;
			cout << "Directia cabinei (1:stanga, 2:dreapta, 3:sus, 4:jos), X (linia pe care se afla cabina), Y (coloana pe care se afla cabina)"<<endl;
			cout << "Exemplu: 1 7 2 plaseaza un avion orizontal, cu punctul din extrema stanga pe linia 7 si coloana 2"<<endl;
			cout << endl <<"Unde doresti sa plasezi avionul? ";

			//Verificam datele introduse si, daca sunt valide, continuam
			PLASEAZA_AVION un_avion;
			un_avion.nr_avion.punct[0].X = -1;
			while (un_avion.nr_avion.punct[0].X == -1)
			{
				un_avion = Plasare_avion(un_jucator);
			}

			//Adaugam punctul mentionat de jucator pe tabla
			jucator[un_jucator].tabla[un_avion.nr_avion.punct[0].Y][un_avion.nr_avion.punct[0].X] = e_cabina;

			//Determinam TOATE punctele avionului in functie de directie
			if (un_avion.directie == STANGA)
      {
				 un_avion.nr_avion.punct[1].X = un_avion.nr_avion.punct[0].X-2;
				 un_avion.nr_avion.punct[1].Y = un_avion.nr_avion.punct[0].Y+1;
				 un_avion.nr_avion.punct[2].X = un_avion.nr_avion.punct[0].X-1;
				 un_avion.nr_avion.punct[2].Y = un_avion.nr_avion.punct[0].Y+1;
				 un_avion.nr_avion.punct[3].X = un_avion.nr_avion.punct[0].X;
				 un_avion.nr_avion.punct[3].Y = un_avion.nr_avion.punct[0].Y+1;
				 un_avion.nr_avion.punct[4].X = un_avion.nr_avion.punct[0].X+1;
				 un_avion.nr_avion.punct[4].Y = un_avion.nr_avion.punct[0].Y+1;
				 un_avion.nr_avion.punct[5].X = un_avion.nr_avion.punct[0].X+2;
				 un_avion.nr_avion.punct[5].Y = un_avion.nr_avion.punct[0].Y+1;
				 un_avion.nr_avion.punct[6].X = un_avion.nr_avion.punct[0].X;
				 un_avion.nr_avion.punct[6].Y = un_avion.nr_avion.punct[0].Y+2;
				 un_avion.nr_avion.punct[7].X = un_avion.nr_avion.punct[0].X-1;
				 un_avion.nr_avion.punct[7].Y = un_avion.nr_avion.punct[0].Y+3;
				 un_avion.nr_avion.punct[8].X = un_avion.nr_avion.punct[0].X;
				 un_avion.nr_avion.punct[8].Y = un_avion.nr_avion.punct[0].Y+3;
				 un_avion.nr_avion.punct[9].X = un_avion.nr_avion.punct[0].X+1;
				 un_avion.nr_avion.punct[9].Y = un_avion.nr_avion.punct[0].Y+3;
   }
 if (un_avion.directie == DREAPTA)
   {
				 un_avion.nr_avion.punct[1].X = un_avion.nr_avion.punct[0].X-2;
				 un_avion.nr_avion.punct[1].Y = un_avion.nr_avion.punct[0].Y-1;
				 un_avion.nr_avion.punct[2].X = un_avion.nr_avion.punct[0].X-1;
				 un_avion.nr_avion.punct[2].Y = un_avion.nr_avion.punct[0].Y-1;
				 un_avion.nr_avion.punct[3].X = un_avion.nr_avion.punct[0].X;
				 un_avion.nr_avion.punct[3].Y = un_avion.nr_avion.punct[0].Y-1;
				 un_avion.nr_avion.punct[4].X = un_avion.nr_avion.punct[0].X+1;
				 un_avion.nr_avion.punct[4].Y = un_avion.nr_avion.punct[0].Y-1;
				 un_avion.nr_avion.punct[5].X = un_avion.nr_avion.punct[0].X+2;
				 un_avion.nr_avion.punct[5].Y = un_avion.nr_avion.punct[0].Y-1;
				 un_avion.nr_avion.punct[6].X = un_avion.nr_avion.punct[0].X;
				 un_avion.nr_avion.punct[6].Y = un_avion.nr_avion.punct[0].Y-2;
				 un_avion.nr_avion.punct[7].X = un_avion.nr_avion.punct[0].X-1;
				 un_avion.nr_avion.punct[7].Y = un_avion.nr_avion.punct[0].Y-3;
				 un_avion.nr_avion.punct[8].X = un_avion.nr_avion.punct[0].X;
				 un_avion.nr_avion.punct[8].Y = un_avion.nr_avion.punct[0].Y-3;
				 un_avion.nr_avion.punct[9].X = un_avion.nr_avion.punct[0].X+1;
				 un_avion.nr_avion.punct[9].Y = un_avion.nr_avion.punct[0].Y-3;
    }
 if (un_avion.directie == SUS)
    {
				 un_avion.nr_avion.punct[1].X = un_avion.nr_avion.punct[0].X+1;
				 un_avion.nr_avion.punct[1].Y = un_avion.nr_avion.punct[0].Y-2;
				 un_avion.nr_avion.punct[2].X = un_avion.nr_avion.punct[0].X+1;
				 un_avion.nr_avion.punct[2].Y = un_avion.nr_avion.punct[0].Y-1;
				 un_avion.nr_avion.punct[3].X = un_avion.nr_avion.punct[0].X+1;
				 un_avion.nr_avion.punct[3].Y = un_avion.nr_avion.punct[0].Y;
				 un_avion.nr_avion.punct[4].X = un_avion.nr_avion.punct[0].X+1;
				 un_avion.nr_avion.punct[4].Y = un_avion.nr_avion.punct[0].Y+1;
				 un_avion.nr_avion.punct[5].X = un_avion.nr_avion.punct[0].X+1;
				 un_avion.nr_avion.punct[5].Y = un_avion.nr_avion.punct[0].Y+2;
		     	 un_avion.nr_avion.punct[6].X = un_avion.nr_avion.punct[0].X+2;
				 un_avion.nr_avion.punct[6].Y = un_avion.nr_avion.punct[0].Y;
				 un_avion.nr_avion.punct[7].X = un_avion.nr_avion.punct[0].X+3;
				 un_avion.nr_avion.punct[7].Y = un_avion.nr_avion.punct[0].Y-1;
				 un_avion.nr_avion.punct[8].X = un_avion.nr_avion.punct[0].X+3;
				 un_avion.nr_avion.punct[8].Y = un_avion.nr_avion.punct[0].Y;
				 un_avion.nr_avion.punct[9].X = un_avion.nr_avion.punct[0].X+3;
				 un_avion.nr_avion.punct[9].Y = un_avion.nr_avion.punct[0].Y+1;
    }
if (un_avion.directie == JOS)
    {
				 un_avion.nr_avion.punct[1].X = un_avion.nr_avion.punct[0].X-1;
				 un_avion.nr_avion.punct[1].Y = un_avion.nr_avion.punct[0].Y-2;
				 un_avion.nr_avion.punct[2].X = un_avion.nr_avion.punct[0].X-1;
				 un_avion.nr_avion.punct[2].Y = un_avion.nr_avion.punct[0].Y-1;
				 un_avion.nr_avion.punct[3].X = un_avion.nr_avion.punct[0].X-1;
			     un_avion.nr_avion.punct[3].Y = un_avion.nr_avion.punct[0].Y;
				 un_avion.nr_avion.punct[4].X = un_avion.nr_avion.punct[0].X-1;
				 un_avion.nr_avion.punct[4].Y = un_avion.nr_avion.punct[0].Y+1;
				 un_avion.nr_avion.punct[5].X = un_avion.nr_avion.punct[0].X-1;
				 un_avion.nr_avion.punct[5].Y = un_avion.nr_avion.punct[0].Y+2;
				 un_avion.nr_avion.punct[6].X = un_avion.nr_avion.punct[0].X-2;
				 un_avion.nr_avion.punct[6].Y = un_avion.nr_avion.punct[0].Y;
				 un_avion.nr_avion.punct[7].X = un_avion.nr_avion.punct[0].X-3;
				 un_avion.nr_avion.punct[7].Y = un_avion.nr_avion.punct[0].Y-1;
				 un_avion.nr_avion.punct[8].X = un_avion.nr_avion.punct[0].X-3;
				 un_avion.nr_avion.punct[8].Y = un_avion.nr_avion.punct[0].Y;
				 un_avion.nr_avion.punct[9].X = un_avion.nr_avion.punct[0].X-3;
				 un_avion.nr_avion.punct[9].Y = un_avion.nr_avion.punct[0].Y+1;
    }

				for(int i=1;i<10;i++)
				jucator[un_jucator].tabla[un_avion.nr_avion.punct[i].Y][un_avion.nr_avion.punct[i].X] = e_avion;

				//Adaugam punctele rezultate mai sus pe tabla jucatorului

		}
		system("cls");
        Desen_tabla(un_jucator);
        system("pause");

	}

	//********* AM TERMINAT PLASAREA AVIOANELOR *********************************
	//*****************************************************************************

	//Suntem gata sa incepem jocul
	joc_inceput = true;
	int jucator_curent = 1;
	do {
      //pentru ca atacam acum, se afiseaza tabla oponentului
		  int oponent;
		  if (jucator_curent == 1) oponent = 2;
		  if (jucator_curent == 2) oponent = 1;
		  system("cls");//se sterge ecranul
		  Desen_tabla(oponent);//se afiseaza tabla oponentului
		  //preluam coordonatele punctului atacat
		  bool coord_OK = false;
		  int x,y;
		  while (coord_OK == false) coord_OK = Atac(x,y,jucator_curent);

      //Verificam daca punctul atacat face sau nu parte din avion
		  if (jucator[oponent].tabla[x][y] == e_avion) jucator[oponent].tabla[x][y] = LOVIT;
		  if (jucator[oponent].tabla[x][y] == AER) jucator[oponent].tabla[x][y] = nu_e_avion;
      if (jucator[oponent].tabla[x][y] == e_cabina) jucator[oponent].tabla[x][y] = LOVIT_CABINA;

		  //Verificam daca jocul a luat sfarsit
		  int castig = joc_sfarsit(oponent);
		  if (castig != 0) {
			                 joc_inceput = false;
			                 break;
		                   }
		  //Interschimbam jucatorii
		  jucator_curent = (jucator_curent == 1) ? 2 : 1;

	} while (joc_inceput);

	system("cls");
	cout << endl <<"FELICITARI! JUCATORUL " << jucator_curent << " A CASTIGAT JOCUL!";

	system("pause");
	return 0;
}

bool joc_sfarsit(int inamic)
{
	bool castigator = true;
	//verificam tabla inamica
	for (int i=0; i<LUNG_TABLA; ++i)
  {
			for (int j=0; j<LAT_TABLA; ++j)
      {
				//daca au mai ramas avioane, jocul NU a luat sfarsit
				if (jucator[inamic].tabla[i][j] = e_avion)
					{
						castigator = false;
						return castigator;
					}
	  	}
  }
  //Daca am ajuns aici, cineva a castigat
	return castigator;
}

bool Atac(int& y, int& x, int jucatorul)
{
    cout<<endl;
    cout<<"Punctele atacate sunt notate cu:"<<endl;
    cout<<"*0, daca niciun avion nu a fost atacat"<<endl;
    cout<<"*X, daca un avion a fost lovit"<<endl;
    cout<<"*A, daca a fost lovita cabina unui avion"<<endl;
    cout<<endl;
	cout << "JUCATOR " << jucatorul << ", SCRIE COORDONATELE PUNCTULUI PE CARE IL ATACI: ";
	bool coord_OK = false;
	cin >> x >> y;
	if (x<0 || x>=LUNG_TABLA) return coord_OK;
	if (y<0 || y>=LAT_TABLA) return coord_OK;
	coord_OK = true;
	return coord_OK;
}

PLASEAZA_AVION Plasare_avion(int juc_curent)
{
	int d, x, y;
	PLASEAZA_AVION tmp;
	//Verificam daca datele introduse sunt corecte
	tmp.nr_avion.punct[0].X = -1;
	//Se citesc directia, abscisa si ordonata punctului
	cin >> d >> x >> y;
	//returnam -1 daca datele introduse nu convin
	if (d!=1 && d!=2 && d!=3&& d!=4) {cout<<"Datele introduse nu sunt corecte!";
                                     return tmp;
                                     }
	if (x<0 || x>=LUNG_TABLA){cout<<"Datele introduse nu sunt corecte!";
                              return tmp;
                             }
	if (y<0 || y>=LAT_TABLA) {cout<<"Datele introduse nu sunt corecte!";
                              return tmp;
                             }
	if(d==1&&(y>LAT_TABLA-4||x<=1||x>LUNG_TABLA-3)){cout<<"Datele introduse nu sunt corecte!";
                                                    return tmp;
                                                   }
	if(d==2&&(y<=2||x<=1||x>LUNG_TABLA-3)){cout<<"Datele introduse nu sunt corecte!";
                                           return tmp;
                                          }
	if(d==3&&(x>LUNG_TABLA-4||y<=1||y>LAT_TABLA-3)) {cout<<"Datele introduse nu sunt corecte!";
                                                     return tmp;
                                                    }
	if(d==4&&(x<=2||y<=1||y>LAT_TABLA-3)) {cout<<"Datele introduse nu sunt corecte!";
                                           return tmp;
                                          }
	if(jucator[juc_curent].tabla[y][x]=='S'||jucator[juc_curent].tabla[y][x]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                    return tmp;
                                                                                    }
	if(d==1)
    {
        if(jucator[juc_curent].tabla[y+1][x-2]=='S'||jucator[juc_curent].tabla[y+1][x-2]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                                return tmp;
                                                                                               }
        if(jucator[juc_curent].tabla[y+1][x-1]=='S'||jucator[juc_curent].tabla[y+1][x-1]=='O'){cout<<"Datele introduse nu sunt corecte!";
                                                                                               return tmp;
                                                                                               }
        if(jucator[juc_curent].tabla[y+1][x]=='S'||jucator[juc_curent].tabla[y+1][x]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                            return tmp;
                                                                                           }
        if(jucator[juc_curent].tabla[y+1][x+1]=='S'||jucator[juc_curent].tabla[y+1][x+1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                                return tmp;
                                                                                               }
        if(jucator[juc_curent].tabla[y+1][x+2]=='S'||jucator[juc_curent].tabla[y+1][x+2]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                                return tmp;
                                                                                               }
        if(jucator[juc_curent].tabla[y+2][x]=='S'||jucator[juc_curent].tabla[y+2][x]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                            return tmp;
                                                                                           }
        if(jucator[juc_curent].tabla[y+3][x-1]=='S'||jucator[juc_curent].tabla[y+3][x-1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                                return tmp;
                                                                                               }
        if(jucator[juc_curent].tabla[y+3][x]=='S'||jucator[juc_curent].tabla[y+3][x]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                            return tmp;
                                                                                           }
        if(jucator[juc_curent].tabla[y+3][x+1]=='S'||jucator[juc_curent].tabla[y+3][x+1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                                return tmp;
                                                                                               }
    }
	else if(d==2)
    {
        if(jucator[juc_curent].tabla[y-1][x-2]=='S'||jucator[juc_curent].tabla[y-1][x-2]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                                return tmp;
                                                                                               }
        if(jucator[juc_curent].tabla[y-1][x-1]=='S'||jucator[juc_curent].tabla[y-1][x-1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                                return tmp;
                                                                                               }
        if(jucator[juc_curent].tabla[y-1][x]=='S'||jucator[juc_curent].tabla[y-1][x]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                            return tmp;
                                                                                            }
        if(jucator[juc_curent].tabla[y-1][x+1]=='S'||jucator[juc_curent].tabla[y-1][x+1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                                return tmp;
                                                                                               }
        if(jucator[juc_curent].tabla[y-1][x+2]=='S'||jucator[juc_curent].tabla[y-1][x+2]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                                return tmp;
                                                                                               }
        if(jucator[juc_curent].tabla[y-2][x]=='S'||jucator[juc_curent].tabla[y-2][x]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                            return tmp;
                                                                                            }
        if(jucator[juc_curent].tabla[y-3][x-1]=='S'||jucator[juc_curent].tabla[y-3][x-1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                                return tmp;
                                                                                               }
        if(jucator[juc_curent].tabla[y-3][x]=='S'||jucator[juc_curent].tabla[y-3][x]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                            return tmp;
                                                                                               }
        if(jucator[juc_curent].tabla[y-3][x+1]=='S'||jucator[juc_curent].tabla[y-3][x+1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                                return tmp;
                                                                                               }
    }
    else if(d==3)
    {
      if(jucator[juc_curent].tabla[y-2][x+1]=='S'||jucator[juc_curent].tabla[y-2][x+1]=='O'){cout<<"Datele introduse nu sunt corecte!";
                                                                                             return tmp;
                                                                                            }
      if(jucator[juc_curent].tabla[y-1][x+1]=='S'||jucator[juc_curent].tabla[y-1][x+1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                              return tmp;
                                                                                             }
      if(jucator[juc_curent].tabla[y][x+1]=='S'||jucator[juc_curent].tabla[y][x+1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                          return tmp;
                                                                                         }
      if(jucator[juc_curent].tabla[y+1][x+1]=='S'||jucator[juc_curent].tabla[y+1][x+1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                              return tmp;
                                                                                             }
      if(jucator[juc_curent].tabla[y+2][x+1]=='S'||jucator[juc_curent].tabla[y+2][x+1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                              return tmp;
                                                                                               }
      if(jucator[juc_curent].tabla[y][x+2]=='S'||jucator[juc_curent].tabla[y][x+2]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                          return tmp;
                                                                                         }
      if(jucator[juc_curent].tabla[y-1][x+3]=='S'||jucator[juc_curent].tabla[y-1][x+3]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                              return tmp;
                                                                                               }
      if(jucator[juc_curent].tabla[y][x+3]=='S'||jucator[juc_curent].tabla[y][x+3]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                          return tmp;
                                                                                         }
      if(jucator[juc_curent].tabla[y+1][x+3]=='S'||jucator[juc_curent].tabla[y+1][x+3]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                              return tmp;
                                                                                             }
    }
    else if(d==4)
    {
      if(jucator[juc_curent].tabla[y-2][x-1]=='S'||jucator[juc_curent].tabla[y-2][x-1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                              return tmp;
                                                                                               }
      if(jucator[juc_curent].tabla[y-1][x-1]=='S'||jucator[juc_curent].tabla[y-1][x-1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                              return tmp;
                                                                                               }
      if(jucator[juc_curent].tabla[y][x-1]=='S'||jucator[juc_curent].tabla[y][x-1]=='O'){cout<<"Datele introduse nu sunt corecte!";
                                                                                         return tmp;
                                                                                        }
      if(jucator[juc_curent].tabla[y+1][x-1]=='S'||jucator[juc_curent].tabla[y+1][x-1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                              return tmp;
                                                                                               }
      if(jucator[juc_curent].tabla[y+2][x-1]=='S'||jucator[juc_curent].tabla[y+2][x-1]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                              return tmp;
                                                                                               }
      if(jucator[juc_curent].tabla[y][x-2]=='S'||jucator[juc_curent].tabla[y][x-2]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                          return tmp;
                                                                                         }
      if(jucator[juc_curent].tabla[y-1][x-3]=='S'||jucator[juc_curent].tabla[y-1][x-3]=='O'){cout<<"Datele introduse nu sunt corecte!";
                                                                                            return tmp;
                                                                                            }
      if(jucator[juc_curent].tabla[y][x-3]=='S'||jucator[juc_curent].tabla[y][x-3]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                          return tmp;
                                                                                         }
      if(jucator[juc_curent].tabla[y+1][x-3]=='S'||jucator[juc_curent].tabla[y+1][x-3]=='O') {cout<<"Datele introduse nu sunt corecte!";
                                                                                              return tmp;
                                                                                             }
    }

	//Daca am ajuns aici, datele sunt corecte
	tmp.directie = (DIRECTIE)d;
	tmp.nr_avion.punct[0].X = x;
	tmp.nr_avion.punct[0].Y = y;
	return tmp;
}

void Resetare_tabla()
{
	for (int juc=1; juc<3; ++juc)
	{
		//Fiecare punct e initializat cu "*"
		for (int i=0; i<LUNG_TABLA; ++i)
			for (int j=0; j<LAT_TABLA; ++j)
				jucator[juc].tabla[i][j] = AER;
		//Trecem la urmatorul jucator
	}
}

void Desen_tabla(int jucator_curent)
{
	  //Desenam tabla jucatorului curent
	  cout << "TABLA JUCATORULUI " << jucator_curent<<endl;
	  cout << "----------------------"<<endl;

  	//Numerotam liniile si coloanele
	  cout << "   ";
	  for (int i=0; i<LUNG_TABLA; ++i)
		    if (i < 10) cout << i << "  ";
	     	else if (i >= 10) cout << i << " ";
    cout << endl;

	  //Trecem prin fiecare punct al tablei si afisam simbolul corespunzator
	  for (int j=0; j<LAT_TABLA; ++j)
    {
	  	for (int i=0; i<LUNG_TABLA; ++i)
        {
			  if (i==0) cout << j << " ";
			  if (i<10 && i==0) cout << " ";
			  //Daca jocul nu a inceput, afisam avioanele
			  if (joc_inceput == false) cout << jucator[jucator_curent].tabla[i][j] << "  ";
			  //Daca jocul a inceput, nu afisam barcile dar afisam punctele atacate
			  if (joc_inceput == true && (jucator[jucator_curent].tabla[i][j] != e_avion&&jucator[jucator_curent].tabla[i][j] != e_cabina))
				  cout << jucator[jucator_curent].tabla[i][j] << "  ";
			  else if (joc_inceput == true && jucator[jucator_curent].tabla[i][j] == e_avion)
				  cout << AER << "  ";
			  else if (joc_inceput == true && jucator[jucator_curent].tabla[i][j] == e_cabina)
				  cout << AER << "  ";
			  if (i == LUNG_TABLA-1) cout << endl;
		  }
	}
}