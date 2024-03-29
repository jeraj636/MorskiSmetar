#include "../include/moji_objekti.h"
void Objekt_greta::init()
{
    m_idle_tek_id[0] = Risalnik::nalozi_teksturo("greta/idle/idle1.png");
    m_idle_tek_id[1] = Risalnik::nalozi_teksturo("greta/idle/idle2.png");

    m_hoja_tek_id[0] = Risalnik::nalozi_teksturo("greta/hoja/hoja1.png");
    m_hoja_tek_id[1] = Risalnik::nalozi_teksturo("greta/hoja/hoja2.png");
    m_hoja_tek_id[2] = Risalnik::nalozi_teksturo("greta/hoja/hoja3.png");
    m_hoja_tek_id[3] = Risalnik::nalozi_teksturo("greta/hoja/hoja4.png");

    m_plavanje_tek_id[0] = Risalnik::nalozi_teksturo("greta/plavanje/plavanje1.png");
    m_plavanje_tek_id[1] = Risalnik::nalozi_teksturo("greta/plavanje/plavanje2.png");

    m_grob_tekstura = Risalnik::nalozi_teksturo("nagrobnik.png");
    m_duh_tekstura = Risalnik::nalozi_teksturo("duh.png");
}

void Objekt_greta::nastavi(CelicniAvtomat *zemljevid, std::vector<Objekt_smeti *> &smece)
{
    m_zemljevid = zemljevid;
    velikost = mat::vec2(32, 64);
    pozicija = mat::vec2(rand() % ((int)Risalnik::get_velikost_okna().x - 40) + 20, rand() % ((int)Risalnik::get_velikost_okna().y - 40) + 20);
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
    ali_zivim = true;
    tmp.tekstura_id = std::vector<uint32_t>{m_hoja_tek_id[0], m_hoja_tek_id[1], m_hoja_tek_id[2], m_hoja_tek_id[3]};
    tmp.perioda = .1f;
    tmp.naslednja_animacija = 1;
    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_plavanje_tek_id[0], m_plavanje_tek_id[1]};
    tmp.perioda = .1f;
    tmp.naslednja_animacija = 2;
    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_grob_tekstura};
    tmp.perioda = .1f;
    tmp.naslednja_animacija = 3;
    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_duh_tekstura};
    tmp.perioda = .1f;
    tmp.naslednja_animacija = 4;
    animacije.push_back(tmp);

    m_trenutna_smet = rand() % smece.size();
    if (smece.size() != 0)
        nastavi_smer(smece[m_trenutna_smet]);
    m_smer = mat::vec2(0, 0);
}

int Objekt_greta::update(std::vector<Objekt_smeti *> &smece, int &tocke, Objekt_jasek &jasek)
{
    if (!ali_zivim && sem_pokopan)
    {
        trenutna_animacija = 3;
        return -1;
    }
    /*
    if (!ali_zivim && !sem_pokopan)
    {
        trenutna_animacija = 4;
    }
    */
    mat::vec2 trkalnik_vel(32, 10);
    mat::vec2 trkalnik_poz(pozicija.x, pozicija.y + velikost.y / 2 + 5);
    mat::vec2 prava_vel = velikost;
    mat::vec2 prava_poz = pozicija;
    if (m_zemljevid->Trk(trkalnik_poz.x, trkalnik_poz.y, trkalnik_vel.x, trkalnik_vel.y, ',', Risalnik::get_velikost_okna().x, Risalnik::get_velikost_okna().y) || m_zemljevid->Trk(trkalnik_poz.x, trkalnik_poz.y, trkalnik_vel.x, trkalnik_vel.y, '0', Risalnik::get_velikost_okna().x, Risalnik::get_velikost_okna().y))
        m_sem_v_vodi = false;
    else
    {
        pozicija = trkalnik_poz;
        velikost = trkalnik_vel;
        m_sem_v_vodi = true;
        if (trk(jasek) || jasek.trk(*this))
        {
            m_sem_v_vodi = false;
        }
        velikost = prava_vel;
        pozicija = prava_poz;
    }

    if (ali_zivim)
    {

        if (m_sem_v_vodi)
        {
            trenutna_animacija = 2;
        }
        else
        {
            trenutna_animacija = 1;
        }
    }

    if (m_trenutna_smet >= smece.size() && smece.size() != 0)
    {
        m_trenutna_smet = rand() % smece.size();
    }

    if (smece.size() != 0 && ali_zivim)
    {
        nastavi_smer(smece[m_trenutna_smet]);
        // m_next_time = Cas::get_time() + rand() % 10;
    }
    if ((smece.size() == 0 || !ali_zivim) && (sem_zunaj() || m_next_time <= Cas::get_time()))
    {
        if (sem_zunaj())
        {
            pozicija = mat::vec2(pozicija.x + m_hitrost * -m_smer.x * Cas::get_delta_time(), pozicija.y + m_hitrost * -m_smer.y * Cas::get_delta_time());
            pozicija = mat::vec2(pozicija.x + m_hitrost * -m_smer.x * Cas::get_delta_time(), pozicija.y + m_hitrost * -m_smer.y * Cas::get_delta_time());
            pozicija = mat::vec2(pozicija.x + m_hitrost * -m_smer.x * Cas::get_delta_time(), pozicija.y + m_hitrost * -m_smer.y * Cas::get_delta_time());
        }
        rand_smer();
        m_next_time = Cas::get_time() + rand() % 10;
    }
    pozicija = mat::vec2(pozicija.x + m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + m_hitrost * m_smer.y * Cas::get_delta_time());
    if ((velikost.x > 0 && m_smer.x > 0) || (velikost.x < 0 && m_smer.x < 0))
        velikost.x *= -1;
    if (ali_zivim)
        for (int i = 0; i < smece.size(); i++)
        {
            if (trk(*smece[i]))
            {
                return i;
                if (smece.size() != 0)
                    m_trenutna_smet = rand() % smece.size();
            }
        }
    return -1;
}

void Objekt_greta::nastavi_smer(Objekt_smeti *t)
{
    m_smer = t->pozicija;
    m_smer.x -= pozicija.x;
    m_smer.y -= pozicija.y;
    float dol = sqrt(m_smer.x * m_smer.x + m_smer.y * m_smer.y);
    m_smer.x /= dol;
    m_smer.y /= dol;
}
bool Objekt_greta::sem_zunaj()
{
    return (pozicija.x < 0 || pozicija.x >= Risalnik::get_velikost_okna().x || pozicija.y < 0 || pozicija.y > Risalnik::get_velikost_okna().y - 20);
}

void Objekt_greta::rand_smer()
{
    float val = rand();
    m_smer = mat::vec2(cos(val), sin(val));
}
// Requiem æternam dona ei, Domine
void Objekt_greta::smrt()
{
    ali_zivim = false;
    mat::vec2 trkalnik_vel(32, 10);
    mat::vec2 trkalnik_poz(pozicija.x, pozicija.y + velikost.y / 2 + 5);
    if (m_zemljevid->Trk(trkalnik_poz.x, trkalnik_poz.y, trkalnik_vel.x, trkalnik_vel.y, ',', Risalnik::get_velikost_okna().x, Risalnik::get_velikost_okna().y) || m_zemljevid->Trk(trkalnik_poz.x, trkalnik_poz.y, trkalnik_vel.x, trkalnik_vel.y, '0', Risalnik::get_velikost_okna().x, Risalnik::get_velikost_okna().y))
    {
        sem_pokopan = true;
        trenutna_animacija = 3;
    }
    else
    {
        barva_objekta.set_a(0x55);
        sem_pokopan = false;
        trenutna_animacija = 4;
        velikost = mat::vec2(24, 48); //*Mea maxima culpa
    }
}
void Objekt_greta::unici()
{
    for (int i = 0; i < 2; i++)
    {
        Risalnik::skenslaj_teksturo(&m_idle_tek_id[i]);
        Risalnik::skenslaj_teksturo(&m_plavanje_tek_id[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        Risalnik::skenslaj_teksturo(&m_hoja_tek_id[i]);
    }
}