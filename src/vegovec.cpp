#include "../include/moji_objekti.h"

void Objekt_vegovec::init()
{
    m_idle_tek_id[0] = Risalnik::nalozi_teksturo("vegovec/idle/idle1.png");
    m_idle_tek_id[1] = Risalnik::nalozi_teksturo("vegovec/idle/idle2.png");

    m_hoja_tek_id[0] = Risalnik::nalozi_teksturo("vegovec/hoja/hoja1.png");
    m_hoja_tek_id[1] = Risalnik::nalozi_teksturo("vegovec/hoja/hoja2.png");
    m_hoja_tek_id[2] = Risalnik::nalozi_teksturo("vegovec/hoja/hoja3.png");
    m_hoja_tek_id[3] = Risalnik::nalozi_teksturo("vegovec/hoja/hoja4.png");

    m_udarec_tek_id[0] = Risalnik::nalozi_teksturo("vegovec/udarec/udarec1.png");
    m_udarec_tek_id[1] = Risalnik::nalozi_teksturo("vegovec/udarec/udarec2.png");
    m_udarec_tek_id[2] = Risalnik::nalozi_teksturo("vegovec/udarec/udarec3.png");
    m_udarec_tek_id[3] = Risalnik::nalozi_teksturo("vegovec/udarec/udarec4.png");
    m_udarec_tek_id[4] = Risalnik::nalozi_teksturo("vegovec/udarec/udarec5.png");
    m_udarec_tek_id[5] = Risalnik::nalozi_teksturo("vegovec/udarec/udarec6.png");
    m_udarec_tek_id[6] = Risalnik::nalozi_teksturo("vegovec/udarec/udarec7.png");
    m_udarec_tek_id[7] = Risalnik::nalozi_teksturo("vegovec/udarec/udarec8.png");
    m_udarec_tek_id[8] = Risalnik::nalozi_teksturo("vegovec/udarec/udarec9.png");
    m_udarec_tek_id[9] = Risalnik::nalozi_teksturo("vegovec/udarec/udarec10.png");
}
void Objekt_vegovec::nastavi()
{
    pozicija = mat::vec2(rand() % (int)Risalnik::get_velikost_okna().x, rand() % (int)Risalnik::get_velikost_okna().y);
    velikost = mat::vec2(32, 64);
    rotacija = 180;
    aktiven = false;
    barva_objekta = 0xffffffff;
    barva_odzadja = 0;

    trenutna_animacija = 0;

    Animacija tmp;
    tmp.tekstura_id = std::vector<uint32_t>{m_idle_tek_id[0], m_idle_tek_id[1]};
    tmp.perioda = .5f;
    tmp.naslednja_animacija = 0;

    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_hoja_tek_id[0], m_hoja_tek_id[1], m_hoja_tek_id[2], m_hoja_tek_id[3]};
    tmp.perioda = .5f;
    tmp.naslednja_animacija = 1;

    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_udarec_tek_id[0], m_udarec_tek_id[1], m_udarec_tek_id[2], m_udarec_tek_id[3], m_udarec_tek_id[4], m_udarec_tek_id[5], m_udarec_tek_id[6], m_udarec_tek_id[7], m_udarec_tek_id[8], m_udarec_tek_id[9]};
    tmp.perioda = 0.5f;
    tmp.naslednja_animacija = 0;

    animacije.push_back(tmp);
}