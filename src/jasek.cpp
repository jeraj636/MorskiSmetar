#include "../include/moji_objekti.h"

void Objekt_jasek::init()
{
    m_tek_id = Risalnik::nalozi_teksturo("jasek.png");
}

void Objekt_jasek::nastavi()
{
    id_teksture = m_tek_id;
    pozicija = mat::vec2(rand() % ((int)Risalnik::get_velikost_okna().x - 128) + 64, rand() % ((int)Risalnik::get_velikost_okna().y - 128) + 64);
    velikost = mat::vec2(64, 64);
    aktiven = true;
    barva_objekta = 0xffffffff;
    barva_odzadja = 0;
}

void Objekt_jasek::rand_time()
{
    m_nex_time = rand() % 10;
}

/*shabat shalom*/
void Objekt_jasek::naredi_juda(std::vector<Objekt_jud *> &judi, CelicniAvtomat *zemljevid)
{
    judi.push_back(new Objekt_jud);
    judi.back()->nastavi(zemljevid, pozicija);
}
void Objekt_jasek::unici()
{
    Risalnik::skenslaj_teksturo(&m_tek_id);
}