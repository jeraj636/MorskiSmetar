#include "../include/moji_objekti.h"

void Objekt_crnc::init()
{
    m_idle_tek_id[0] = Risalnik::nalozi_teksturo("zapecenec/idle/idle1.png");
    m_idle_tek_id[1] = Risalnik::nalozi_teksturo("zapecenec/idle/idle2.png");

    m_hoja_tek_id[0] = Risalnik::nalozi_teksturo("zapecenec/hoja/hoja1.png");
    m_hoja_tek_id[1] = Risalnik::nalozi_teksturo("zapecenec/hoja/hoja2.png");
    m_hoja_tek_id[2] = Risalnik::nalozi_teksturo("zapecenec/hoja/hoja3.png");
    m_hoja_tek_id[3] = Risalnik::nalozi_teksturo("zapecenec/hoja/hoja4.png");

    m_plavanje_tek_id[0] = Risalnik::nalozi_teksturo("zapecenec/plavanje/plavanje1.png");
    m_plavanje_tek_id[1] = Risalnik::nalozi_teksturo("zapecenec/plavanje/plavanje1.png");
}

void Objekt_crnc::nastavi(CelicniAvtomat *zemljevid)
{
    m_zemljevid = zemljevid;
    velikost = mat::vec2(32, 64);
    pozicija = mat::vec2(rand() % (int)Risalnik::get_velikost_okna().x, rand() % (int)Risalnik::get_velikost_okna().y);
    rotacija = 180;
    aktiven = true;
    barva_objekta = 0xffffffff;
    barva_odzadja = 0;
    trenutna_animacija = 0;
    Animacija tmp;
    tmp.tekstura_id = std::vector<uint32_t>{m_idle_tek_id[0], m_idle_tek_id[1]};
    tmp.perioda = .5f;
    tmp.naslednja_animacija = 0;
    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_hoja_tek_id[0], m_hoja_tek_id[1], m_hoja_tek_id[2], m_hoja_tek_id[3]};
    tmp.perioda = .1f;
    tmp.naslednja_animacija = 1;
    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_plavanje_tek_id[0], m_plavanje_tek_id[1]};
    tmp.perioda = .1f;
    tmp.naslednja_animacija = 2;
    animacije.push_back(tmp);
}

void Objekt_crnc::update()
{
    if (pozicija.x < 0 || pozicija.x > Risalnik::get_velikost_okna().x || pozicija.y < 0 || pozicija.y > Risalnik::get_velikost_okna().y || m_naslednji_cas <= Cas::get_time())
    {
        pozicija = mat::vec2(pozicija.x + -m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + -m_hitrost * m_smer.y * Cas::get_delta_time());
        pozicija = mat::vec2(pozicija.x + -m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + -m_hitrost * m_smer.y * Cas::get_delta_time());
        rand_smer();
        m_naslednji_cas = Cas::get_time() + rand() % 10;
    }
    pozicija = mat::vec2(pozicija.x + m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + m_hitrost * m_smer.y * Cas::get_delta_time());
}

void Objekt_crnc::rand_smer()
{
    float val = rand();
    m_smer = mat::vec2(cos(val), sin(val));
}