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

    m_plavanje_tek_id[0] = Risalnik::nalozi_teksturo("vegovec/plavanje/plavanje1.png");
    m_plavanje_tek_id[1] = Risalnik::nalozi_teksturo("vegovec/plavanje/plavanje2.png");

    m_plavanje_udraec_tek_id[0] = Risalnik::nalozi_teksturo("vegovec/morskiUdarec/udarec1.png");
    m_plavanje_udraec_tek_id[1] = Risalnik::nalozi_teksturo("vegovec/morskiUdarec/udarec2.png");
    m_plavanje_udraec_tek_id[2] = Risalnik::nalozi_teksturo("vegovec/morskiUdarec/udarec3.png");
    m_plavanje_udraec_tek_id[3] = Risalnik::nalozi_teksturo("vegovec/morskiUdarec/udarec4.png");
    m_plavanje_udraec_tek_id[4] = Risalnik::nalozi_teksturo("vegovec/morskiUdarec/udarec5.png");
    m_plavanje_udraec_tek_id[5] = Risalnik::nalozi_teksturo("vegovec/morskiUdarec/udarec6.png");
    m_plavanje_udraec_tek_id[6] = Risalnik::nalozi_teksturo("vegovec/morskiUdarec/udarec7.png");
    m_plavanje_udraec_tek_id[7] = Risalnik::nalozi_teksturo("vegovec/morskiUdarec/udarec8.png");
    m_plavanje_udraec_tek_id[8] = Risalnik::nalozi_teksturo("vegovec/morskiUdarec/udarec9.png");
    m_plavanje_udraec_tek_id[9] = Risalnik::nalozi_teksturo("vegovec/morskiUdarec/udarec10.png");
}
void Objekt_vegovec::nastavi(CelicniAvtomat *zemljeveid)
{
    pozicija = mat::vec2(rand() % ((int)Risalnik::get_velikost_okna().x - 40) + 20, rand() % ((int)Risalnik::get_velikost_okna().y - 40) + 20);

    velikost = mat::vec2(32, 64);
    rotacija = 180;
    aktiven = true;
    barva_objekta = 0xffffffff;
    barva_odzadja = 0;
    trenutna_animacija = 0;

    m_zemljevid = zemljeveid;
    m_nazadnje_udarjen = Cas::get_time();
    Animacija tmp;
    tmp.tekstura_id = std::vector<uint32_t>{m_idle_tek_id[0], m_idle_tek_id[1]};
    tmp.perioda = .5f;
    tmp.naslednja_animacija = 0;
    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_hoja_tek_id[0], m_hoja_tek_id[1], m_hoja_tek_id[2], m_hoja_tek_id[3]};
    tmp.perioda = .1f;
    tmp.naslednja_animacija = 1;
    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_udarec_tek_id[0], m_udarec_tek_id[1], m_udarec_tek_id[2], m_udarec_tek_id[3], m_udarec_tek_id[4], m_udarec_tek_id[5], m_udarec_tek_id[6], m_udarec_tek_id[7], m_udarec_tek_id[8], m_udarec_tek_id[9]};
    tmp.perioda = 0.04f;
    tmp.naslednja_animacija = 0;
    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_plavanje_tek_id[0], m_plavanje_tek_id[1]};
    tmp.perioda = 0.2f;
    tmp.naslednja_animacija = 3;
    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_plavanje_udraec_tek_id[0], m_plavanje_udraec_tek_id[1], m_plavanje_udraec_tek_id[2], m_plavanje_udraec_tek_id[3], m_plavanje_udraec_tek_id[4], m_plavanje_udraec_tek_id[5], m_plavanje_udraec_tek_id[6], m_plavanje_udraec_tek_id[7], m_plavanje_udraec_tek_id[8], m_plavanje_udraec_tek_id[9]};
    tmp.perioda = 0.04f;
    tmp.naslednja_animacija = 3;
    animacije.push_back(tmp);
    id_teksture = animacije[0].tekstura_id[0];
}

void Objekt_vegovec::update()
{
    mat::vec2 trkalnik_vel(32, 10);
    mat::vec2 trkalnik_poz(pozicija.x, pozicija.y + velikost.y / 2 + 5);
    if (m_zemljevid->Trk(trkalnik_poz.x, trkalnik_poz.y, trkalnik_vel.x, trkalnik_vel.y, ',', Risalnik::get_velikost_okna().x, Risalnik::get_velikost_okna().y) || m_zemljevid->Trk(trkalnik_poz.x, trkalnik_poz.y, trkalnik_vel.x, trkalnik_vel.y, '0', Risalnik::get_velikost_okna().x, Risalnik::get_velikost_okna().y))
    {
        m_sem_v_vodi = false;
    }
    else
    {
        m_sem_v_vodi = true;
    }

    if (trenutna_animacija != 2 && trenutna_animacija != 4)
    {
        if (Risalnik::get_tipko_tipkovnice(' '))
        {
            if (m_sem_v_vodi)
            {
                trenutna_animacija = 4;
            }
            else
            {

                trenutna_animacija = 2;
            }
        }
        else
        {
            premakni();

            if (m_sem_v_vodi)
            {
                trenutna_animacija = 3;
            }
            else
            {
                if (m_smer.x == 0 && m_smer.y == 0)
                    trenutna_animacija = 0;
                else
                    trenutna_animacija = 1;
            }
            if (pozicija.x < 0 || pozicija.x >= Risalnik::get_velikost_okna().x || pozicija.y < 0 || pozicija.y > Risalnik::get_velikost_okna().y - 20)
            {

                pozicija = mat::vec2(pozicija.x + m_hitrost * -m_smer.x * Cas::get_delta_time(), pozicija.y + -m_hitrost * m_smer.y * Cas::get_delta_time());
                pozicija = mat::vec2(pozicija.x + m_hitrost * -m_smer.x * Cas::get_delta_time(), pozicija.y + -m_hitrost * m_smer.y * Cas::get_delta_time());
            }
        }
    }
}

void Objekt_vegovec::premakni()
{
    if (Risalnik::get_tipko_tipkovnice('W') && Risalnik::get_tipko_tipkovnice('D'))
        m_smer = mat::vec2(sin(45), -sin(45));
    else if (Risalnik::get_tipko_tipkovnice('S') && Risalnik::get_tipko_tipkovnice('D'))
        m_smer = mat::vec2(sin(45), sin(45));
    else if (Risalnik::get_tipko_tipkovnice('A') && Risalnik::get_tipko_tipkovnice('S'))
        m_smer = mat::vec2(-sin(45), sin(45));
    else if (Risalnik::get_tipko_tipkovnice('A') && Risalnik::get_tipko_tipkovnice('W'))
        m_smer = mat::vec2(-sin(45), -sin(45));
    else if (Risalnik::get_tipko_tipkovnice('W'))
        m_smer = mat::vec2(0, -1);
    else if (Risalnik::get_tipko_tipkovnice('A'))
        m_smer = mat::vec2(-1, 0);
    else if (Risalnik::get_tipko_tipkovnice('S'))
        m_smer = mat::vec2(0, 1);
    else if (Risalnik::get_tipko_tipkovnice('D'))
        m_smer = mat::vec2(1, 0);
    else
        m_smer = mat::vec2(0, 0);

    if (m_smer.x < 0 && velikost.x < 0)
        velikost.x *= -1;
    if (m_smer.x > 0 && velikost.x > 0)
        velikost.x *= -1;

    pozicija = mat::vec2(pozicija.x + m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + m_hitrost * m_smer.y * Cas::get_delta_time());
}
void Objekt_vegovec::udarjen()
{
    m_nazadnje_udarjen = Cas::get_time();
}
bool Objekt_vegovec::sem_lahko_udarjen()
{
    return (m_nazadnje_udarjen + 3 <= Cas::get_time());
}