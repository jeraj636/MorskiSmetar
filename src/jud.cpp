#include "../include/moji_objekti.h"

void Objekt_jud::init()
{
    m_idle_tek_id[0] = Risalnik::nalozi_teksturo("zidek/idle/idle1.png");
    m_idle_tek_id[1] = Risalnik::nalozi_teksturo("zidek/idle/idle2.png");

    m_hoja_tek_id[0] = Risalnik::nalozi_teksturo("zidek/hoja/hoja1.png");
    m_hoja_tek_id[1] = Risalnik::nalozi_teksturo("zidek/hoja/hoja2.png");
    m_hoja_tek_id[2] = Risalnik::nalozi_teksturo("zidek/hoja/hoja3.png");
    m_hoja_tek_id[3] = Risalnik::nalozi_teksturo("zidek/hoja/hoja4.png");

    m_plavanje_tek_id[0] = Risalnik::nalozi_teksturo("zidek/plavanje/plavanje1.png");
    m_plavanje_tek_id[1] = Risalnik::nalozi_teksturo("zidek/plavanje/plavanje2.png");

    m_grob_tekstura = Risalnik::nalozi_teksturo("nagrobnik.png");
    m_duh_tekstura = Risalnik::nalozi_teksturo("duh_jud.png");
}
// Re di denari
void Objekt_jud::nastavi(CelicniAvtomat *zemljevid, const mat::vec2 &poz)
{
    m_zemljevid = zemljevid;
    velikost = mat::vec2(32, 64);
    pozicija = poz;
    rotacija = 180;
    aktiven = true;
    barva_objekta = 0xffffffff;
    barva_odzadja = 0;
    trenutna_animacija = 0;
    ali_zivim = true;
    sem_pokopan = false;
    rand_smer();
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

    tmp.tekstura_id = std::vector<uint32_t>{m_grob_tekstura};
    tmp.perioda = .1f;
    tmp.naslednja_animacija = 3;
    animacije.push_back(tmp);

    tmp.tekstura_id = std::vector<uint32_t>{m_duh_tekstura};
    tmp.perioda = .1f;
    tmp.naslednja_animacija = 4;
    animacije.push_back(tmp);

    m_naslednji_cas = Cas::get_time() + rand() % 5;
    kdaj_sem_lahko_ubit = Cas::get_time() + 5;
}
void Objekt_jud::update(Objekt_jasek &jasek, std::vector<Objekt_cekin *> &cekini)
{
    // shema izrael
    if (!ali_zivim && sem_pokopan)
        return;

    mat::vec2 trkalnik_vel(32, 10);
    mat::vec2 trkalnik_poz(pozicija.x, pozicija.y + velikost.y / 2 + 5);
    mat::vec2 prava_vel = velikost;
    mat::vec2 prava_poz = pozicija;
    if (m_zemljevid->Trk(trkalnik_poz.x, trkalnik_poz.y, trkalnik_vel.x, trkalnik_vel.y, ',', Risalnik::get_velikost_okna().x, Risalnik::get_velikost_okna().y) || m_zemljevid->Trk(trkalnik_poz.x, trkalnik_poz.y, trkalnik_vel.x, trkalnik_vel.y, '0', Risalnik::get_velikost_okna().x, Risalnik::get_velikost_okna().y))
    {
        m_sem_v_vodi = false;
    }
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
    if (ali_zivim && m_naslednji_cas <= Cas::get_time())
    {
        cekini.push_back(new Objekt_cekin);
        cekini.back()->nastavi(pozicija);
        // m_naslednji_cas = rand() % 10 + Cas::get_time();
    }
    if (pozicija.x < 20 || pozicija.x > Risalnik::get_velikost_okna().x - 20 || pozicija.y < 20 || pozicija.y > Risalnik::get_velikost_okna().y - 20 || m_naslednji_cas <= Cas::get_time())
    {
        pozicija = mat::vec2(pozicija.x + -m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + -m_hitrost * m_smer.y * Cas::get_delta_time());
        pozicija = mat::vec2(pozicija.x + -m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + -m_hitrost * m_smer.y * Cas::get_delta_time());
        rand_smer();
        if (m_naslednji_cas <= Cas::get_time())
            m_naslednji_cas = Cas::get_time() + rand() % 10 + 2;
    }
    pozicija = mat::vec2(pozicija.x + m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + m_hitrost * m_smer.y * Cas::get_delta_time());

    if ((velikost.x > 0 && m_smer.x > 0) || (velikost.x < 0 && m_smer.x < 0))
        velikost.x *= -1;
}
void Objekt_jud::rand_smer()
{
    float val = rand();
    m_smer = mat::vec2(cos(val), sin(val));
}
void Objekt_jud::smrt()
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
        velikost = mat::vec2(24, 48);
    }
}

bool Objekt_jud::sem_lahko_ubit()
{
    return kdaj_sem_lahko_ubit <= Cas::get_time();
}
void Objekt_jud::unici()
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