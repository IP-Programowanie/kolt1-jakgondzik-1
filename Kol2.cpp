#include "Wybor.h"

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczaæ pomiêdzy #ifdef a #endif.
*/

#ifdef Kol_2
class Wlasciciel
{};
enum class Stan
{
	dopuszczony,
	niedopuszczony
};
class Samochod
{
protected:
	char m_num_rej[9] = "";
	int m_licznik = 0; // do 1km
	Stan m_stan;
	Wlasciciel m_posiadacz;
	double m_war_pocz;
	static Samochod * m_wzorcowa;
public:
	Samochod(const char* num_rej, int licznik, Stan stan,Wlasciciel posiadacz ,double m_war_pocz)
	{
		strcpy_s(m_num_rej, num_rej);
		setLicznik(licznik);
		m_stan = stan;
		m_posiadacz = posiadacz;
		setWarPocz(m_war_pocz);
	}
	Samochod()
	{
		if (m_wzorcowa == nullptr) { throw runtime_error("nie ma instancji wzorcowej"); }
		strcpy_s(m_num_rej, m_wzorcowa->m_num_rej);
		m_licznik = m_wzorcowa->m_licznik;
		m_stan = m_wzorcowa->m_stan;
		m_posiadacz = m_wzorcowa->m_posiadacz;
		m_war_pocz = m_wzorcowa->m_war_pocz;

	}
	void setLicznik(int licznik)
	{
		if (licznik < 0) { throw invalid_argument("Stan licznika jest ujemny"); }
		m_licznik = lround(licznik);
	}
	int getLicznik()
	{
		return m_licznik;
	}
	virtual double countZasieg()
	{
		if(this->m_stan == Stan::niedopuszczony){ throw invalid_argument("Samochod nie jest dopuszczony do ruchu"); }
		return 800;
	}
	void setWarPocz(double val)
	{
		if(val < 0){ throw invalid_argument("Auto nie moze miec ujemnej wartosci"); }
		m_war_pocz = val;
	}

	bool operator!=(const Samochod& s) const
	{
		return (abs(this->m_licznik - s.m_licznik) > 20 || (this->m_stan != s.m_stan));
	}
	static void setWzorcowa(Samochod* wzorzec)
	{
		m_wzorcowa = wzorzec;
	}
	double valCounter() // pomocnicza do liczenia wartosci
	{
		double val = (m_war_pocz - (0.2 * m_licznik));
		if (m_stan == Stan::dopuszczony) { val = val * 1.0; }
		else if (m_stan == Stan::niedopuszczony) { val = val * 0.2; }
		if (val < 400) { return 400; }
		else { return val; }
	}
	operator double()
	{
		return valCounter();
	}
};
class Samochod_elektryczny : public Samochod
{
protected:
	int m_bateria; //0-100
public: 
	Samochod_elektryczny(const char* num_rej, int licznik, Stan stan, Wlasciciel posiadacz, double war_pocz, int bateria) : Samochod(num_rej, licznik, stan, posiadacz, war_pocz)
	{
		setBateria(bateria);
	}
	void setBateria(int bateria)
	{
		if(bateria < 0){ throw invalid_argument("Stan baterii jest ujemny"); }
		if(bateria > 100) { throw invalid_argument("Stan baterii jest zbyt wysoki"); }
		m_bateria = bateria;
	}
	double countZasieg() override
	{
		if (this->m_stan == Stan::niedopuszczony) { throw invalid_argument("Samochod nie jest dopuszczony do ruchu"); }
		return m_bateria * 2.5;
	}
	operator double()
	{
		double wynik = valCounter();
		return wynik - (wynik * 0.3);
	}
};
Samochod* Samochod::m_wzorcowa = nullptr; //Wybor przez funkcje statyczn¹
int main()
{
}

#endif
