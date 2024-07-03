#include "Wybor.h"

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczaæ pomiêdzy #ifdef a #endif.
*/

#ifdef Kol_2
class Wlasciciel
{

};
enum class Stan
{
	dopuszczony,
	niedopuszczony
};
class Samochod
{
protected:
	char m_num_rej[8];
	int m_licznik; // do 1km
	Stan m_stan;
	Wlasciciel m_posiadacz;
	double m_war_pocz;
	static Samochod* m_wzorcowa;
public:
	Samochod()
	{
		if (m_wzorcowa == nullptr) { throw runtime_error("nie ma instancji wzorcowej"); }
		strcpy_s(m_num_rej, m_wzorcowa->m_num_rej);	
		m_licznik = m_wzorcowa->m_licznik;
		m_stan = m_wzorcowa->m_stan;

	}
	Samochod(const char* num_rej, int licznik, Stan stan)
	{
		strcpy_s(m_num_rej, num_rej);
		setLicznik(licznik);
		m_stan = stan;
	}
	void setLicznik(int licznik)
	{
		if (licznik < 0) { throw invalid_argument("Stan licznika jest ujemny"); }
		m_licznik = licznik; // zaokr¹glenie dodaj
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
	operator double()
	{
		double wsp_sparw;
		if (m_stan == Stan::dopuszczony) { wsp_sparw = 1.0; }
		else if (m_stan == Stan::niedopuszczony) { wsp_sparw = 0.2; }
	}
};
class Samochod_elektryczny : public Samochod
{
protected:
	int m_bateria; //0-100
public: 
	Samochod_elektryczny(const char* num_rej, int licznik, Stan stan, int bateria) : Samochod(num_rej, licznik, stan)
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
};
int main()
{

}

#endif
