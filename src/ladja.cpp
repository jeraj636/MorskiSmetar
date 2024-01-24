#include "../include/moji_objekti.h"

void Objekt_ladja::init()
{
    m_ladja_tek_id = Risalnik::nalozi_teksturo("ladja/ladja.png");
}

void Objekt_ladja::nastavi(CelicniAvtomat *zemljevid)
{
    velikost = mat::vec2(80, 40);
    rotacija = 180;
    barva_objekta = 0xffffffff;
    barva_odzadja = 0;
    id_teksture = m_ladja_tek_id;
    m_zemljevid = zemljevid;
    do
    {
        pozicija = mat::vec2(rand() % (int)Risalnik::get_velikost_okna().x, rand() % (int)Risalnik::get_velikost_okna().y);
    } while (m_zemljevid->Trk(pozicija.x, pozicija.y, velikost.x, pozicija.y, '0') || m_zemljevid->Trk(pozicija.x, pozicija.y, velikost.x, pozicija.y, ','));
}
