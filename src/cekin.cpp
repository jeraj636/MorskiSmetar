#include "../include/moji_objekti.h"

void Objekt_cekin::init()
{
    m_tek_id = Risalnik::nalozi_teksturo("cekincek.png");
}

void Objekt_cekin::nastavi(const mat::vec2 &poz)
{
    pozicija = poz;
    velikost = mat::vec2(16, 16);
    id_teksture = m_tek_id;
    aktiven = true;
    barva_objekta = 0xffffffff;
    barva_odzadja = 0;
    ttl = Cas::get_time() + rand() % 10;
}
