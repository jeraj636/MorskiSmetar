#include "../include/moji_objekti.h"

void Objekt_smeti::init()
{
    m_smeti_tek = Risalnik::nalozi_teksturo("smet.png");
}

void Objekt_smeti::nastavi(CelicniAvtomat *zemljeveid, mat::vec2 poz)
{
    velikost = mat::vec2(20, 20);
    rotacija = 180;
    pozicija = poz;
    id_teksture = m_smeti_tek;
    barva_objekta = 0xffffffff;
    barva_odzadja = 0;
    m_zemljevid = zemljeveid;
    m_sem_v_vodi = !(trk('.') || trk('0'));
    aktiven = true;
    rand_smer();
}
bool Objekt_smeti::trk(char c)
{
    return m_zemljevid->Trk(pozicija.x, pozicija.y, velikost.x, velikost.y, c, Risalnik::get_velikost_okna().x, Risalnik::get_velikost_okna().y);
}
void Objekt_smeti::update()
{
    if (!m_sem_v_vodi)
        return;
    if (trk('0'))
    {
        m_sem_v_vodi = false;
        return;
    }
    if (trk('.') || sem_zunaj())
    {
        pozicija = mat::vec2(pozicija.x + -m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + -m_hitrost * m_smer.y * Cas::get_delta_time());
        pozicija = mat::vec2(pozicija.x + -m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + -m_hitrost * m_smer.y * Cas::get_delta_time());
        pozicija = mat::vec2(pozicija.x + -m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + -m_hitrost * m_smer.y * Cas::get_delta_time());
        rand_smer();
    }
    pozicija = mat::vec2(pozicija.x + m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + m_hitrost * m_smer.y * Cas::get_delta_time());
}
void Objekt_smeti::rand_smer()
{
    float val = rand();
    m_smer = mat::vec2(cos(val), sin(val));
}
bool Objekt_smeti::sem_zunaj()
{
    return (pozicija.x <= 0 || pozicija.x >= Risalnik::get_velikost_okna().x || pozicija.y <= 0 || pozicija.y >= Risalnik::get_velikost_okna().y);
}