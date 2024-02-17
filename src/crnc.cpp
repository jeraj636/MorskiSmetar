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
    m_plavanje_tek_id[1] = Risalnik::nalozi_teksturo("zapecenec/plavanje/plavanje2.png");

    m_grob_tekstura = Risalnik::nalozi_teksturo("nagrobnik.png");
    m_duh_tekstura = Risalnik::nalozi_teksturo("duh.png");
}

void Objekt_crnc::nastavi(CelicniAvtomat *zemljevid)
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
    ali_zivim = true;
    tmp.tekstura_id = std::vector<uint32_t>{m_idle_tek_id[0], m_idle_tek_id[1]};
    tmp.perioda = .5f;
    tmp.naslednja_animacija = 0;
    animacije.push_back(tmp);
    sem_mocan = false;
    sem_pokopan = false;
    ali_zivim = true;
    tmp.tekstura_id = std::vector<uint32_t>{m_hoja_tek_id[0], m_hoja_tek_id[1], m_hoja_tek_id[2], m_hoja_tek_id[3]};
    tmp.perioda = .1f;
    tmp.naslednja_animacija = 1;
    animacije.push_back(tmp);
	rand_smer();
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
}

void Objekt_crnc::update(std::vector<Objekt_smeti *> &smece)
{
    if (sem_mocan && m_mocni_ucinek_time <= Cas::get_time())
    {
        sem_mocan = false;
    }
    if (!ali_zivim && sem_pokopan)
        return;

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

    if (pozicija.x < 20 || pozicija.x > Risalnik::get_velikost_okna().x - 20 || pozicija.y < 20 || pozicija.y > Risalnik::get_velikost_okna().y - 20 || m_naslednji_cas <= Cas::get_time())
    {
        pozicija = mat::vec2(pozicija.x + -m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + -m_hitrost * m_smer.y * Cas::get_delta_time());
        pozicija = mat::vec2(pozicija.x + -m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + -m_hitrost * m_smer.y * Cas::get_delta_time());
        rand_smer();
        m_naslednji_cas = Cas::get_time() + rand() % 10;
        if (ali_zivim)
        {
            smece.push_back(new Objekt_smeti);
            smece.back()->nastavi(m_zemljevid, pozicija);
            smece.back()->update();
        }
    }
    pozicija = mat::vec2(pozicija.x + m_hitrost * m_smer.x * Cas::get_delta_time(), pozicija.y + m_hitrost * m_smer.y * Cas::get_delta_time());

    if ((velikost.x > 0 && m_smer.x > 0) || (velikost.x < 0 && m_smer.x < 0))
        velikost.x *= -1;
}
void Objekt_crnc::smrt()
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
void Objekt_crnc::rand_smer()
{
    float val = rand();
    m_smer = mat::vec2(cos(val), sin(val));
}
void Objekt_crnc::trk_s_crnim()
{
    m_mocni_ucinek_time = Cas::get_time() + 5;
    sem_mocan = true;
}
