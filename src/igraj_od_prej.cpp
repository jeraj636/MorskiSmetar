#include "../include/igraj_od_prej.h"
// #include "../include/level.h"
#include "../include/zacetna.h"
#include <chrono>
#include <thread>
#include <fstream>
Igraj_od_prej_level::Igraj_od_prej_level()
{
    m_pisava = Risalnik::nalozi_font("FixedDays.ttf", 40);
    m_ploscice_tekstura = Risalnik::nalozi_teksturo("ploscica.png");

    m_muzika = Risalnik::nalozi_zvok("zvok/theme.mp3");

    m_tocke_tek = Risalnik::nalozi_teksturo("tocke.png");
    m_ura_tek = Risalnik::nalozi_teksturo("ura.png");
}

void Igraj_od_prej_level::zacetek()
{
    std::ifstream i_dat("../sredstva/tt.bin", std::ios::binary);
    Risalnik::aktivna_scena = this;
    m_izhod_gumb_tek = Risalnik::nalozi_teksturo("ui/izhod_gumb.png");
    o_dat.open("../sredstva/replay.ms", std::ios::binary);
    seme = rand() % 0xffffffff;
    i_dat.read((char *)&seme, sizeof(uint32_t));
    o_dat.write((char *)&seme, sizeof(uint32_t));
    // std::cout << seme << "\n";
    m_zemljevid.Naredi(Risalnik::get_velikost_okna().x / 8, Risalnik::get_velikost_okna().y / 8, seme);
    m_jasek.nastavi();

    m_ura.nastavi(mat::vec2(32, 32), mat::vec2(32, 50), 180, 0xffffffff, 0);
    m_ura.id_teksture = m_ura_tek;
    m_tocke_obj.nastavi(mat::vec2(32, 100), mat::vec2(32, 32), 180, 0xffffffff, 0);
    m_tocke_obj.id_teksture = m_tocke_tek;

    m_izhod_gumb.nastavi(mat::vec2(Risalnik::get_velikost_okna().x / 2, 600), mat::vec2(100, 100), 180, 0xffffffff, 0);
    m_izhod_gumb.id_teksture = m_izhod_gumb_tek;

    m_obala.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '.', m_ploscice_tekstura, 0xfbe790ff);
    m_otoki.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '0', m_ploscice_tekstura, 0x03ac13ff);

    m_tocke = 0;
    double t;
    i_dat.read((char *)&t, sizeof(double));
    Cas::sin_cas = Cas::get_time() - t;

    i_dat.read((char *)&m_tocke, sizeof(m_tocke));
    m_vegovec.nastavi(&m_zemljevid);
    i_dat.read((char *)&m_vegovec.pozicija, sizeof(mat::vec2));

    m_muzika.zacetek();
    m_muzika.nastavi_loop(true);
    m_muzika.predvajaj();

    Objekt_crnc::multiplay = false;
    int n;
    n = rand() % 2 + 3;
    i_dat.read((char *)&n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        m_crnci.push_back(new Objekt_crnc);
        m_crnci.back()->nastavi(&m_zemljevid);
        i_dat.read((char *)&m_crnci.back()->pozicija, sizeof(mat::vec2));
        i_dat.read((char *)&m_crnci.back()->sem_mocan, sizeof(bool));
        i_dat.read((char *)&m_crnci.back()->sem_pokopan, sizeof(bool));
        i_dat.read((char *)&m_crnci.back()->ali_zivim, sizeof(bool));
    }
    n = rand() % 2 + 3;
    i_dat.read((char *)&n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        m_smeti.push_back(new Objekt_smeti);
        m_smeti.back()->nastavi(&m_zemljevid, mat::vec2(rand() % ((int)Risalnik::get_velikost_okna().x + 40) - 20, rand() % ((int)Risalnik::get_velikost_okna().y + 40) - 20));
        i_dat.read((char *)&m_smeti.back()->pozicija, sizeof(mat::vec2));
    }
    n = rand() % 2 + 3;
    i_dat.read((char *)&n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        m_grete.push_back(new Objekt_greta);
        m_grete.back()->nastavi(&m_zemljevid, m_smeti);
        i_dat.read((char *)&m_grete.back()->pozicija, sizeof(mat::vec2));
        i_dat.read((char *)&m_grete.back()->ali_zivim, sizeof(bool));
        i_dat.read((char *)&m_grete.back()->sem_pokopan, sizeof(bool));
    }
    m_next_tocke_odboj = Cas::get_time() + 5;

    n = rand() % 2 + 3;
    i_dat.read((char *)&n, sizeof(int));
    m_st_judov_const = m_st_judov = n;

    for (int i = 0; i < n; i++)
    {
        m_judi.push_back(new Objekt_jud);
        m_judi.back()->nastavi(&m_zemljevid, mat::vec2(rand() % ((int)Risalnik::get_velikost_okna().x - 64) + 32, rand() % ((int)Risalnik::get_velikost_okna().y - 64) + 32));
        i_dat.read((char *)&m_judi.back()->pozicija, sizeof(mat::vec2));
        i_dat.read((char *)&m_judi.back()->ali_zivim, sizeof(bool));
        i_dat.read((char *)&m_judi.back()->sem_pokopan, sizeof(bool));
    }
    m_naslednj_okvir_cas = Cas::get_time() + 0.05;
    log::msg("tuka");
    std::cout << std::endl;
}

void Igraj_od_prej_level::zanka()
{
    log::msg("zanka");
    m_obala.narisi_me();
    m_otoki.narisi_me();
    m_ura.narisi_me();
    m_tocke_obj.narisi_me();
    m_jasek.narisi_me();

    m_je_se_kaksen_crn = false;
    std::cout << m_crnci.size() << std::endl;

    m_crnci[0]->narisi_me();

    for (int i = 0; i < m_crnci.size(); i++)
    {
        m_crnci[i]->update(m_smeti, m_jasek, m_vegovec);
        m_crnci[i]->narisi_me();

        if (m_crnci[i]->ali_zivim)
            m_je_se_kaksen_crn = true;
        if (m_vegovec.trk(*m_crnci[i]))
        {
            if (Risalnik::get_tipko_tipkovnice(' ') && m_crnci[i]->ali_zivim && !m_crnci[i]->sem_mocan)
            {
                m_crnci[i]->smrt();
                m_tocke += 10;
            }
            if (m_crnci[i]->sem_mocan && m_vegovec.sem_lahko_udarjen())
            {
                m_tocke -= 30;
                m_vegovec.udarjen();
            }
        }
        for (int j = 0; j < m_crnci.size(); j++) // ce se dva crnca zadaneta
        {
            if (m_crnci[i]->ali_zivim && m_crnci[j]->ali_zivim && j != i && m_crnci[i]->trk(*m_crnci[j]))
            {
                m_crnci[j]->trk_s_crnim();
            }
        }
    }

    for (int i = 0; i < m_grete.size(); i++)
    {
        int t = m_grete[i]->update(m_smeti, m_tocke, m_jasek);
        if (t != -1)
        {
            std::swap(m_smeti[t], m_smeti.back());
            delete m_smeti.back();
            m_smeti.pop_back();
            m_tocke++;
        }
        m_grete[i]->narisi_me();
        if (m_vegovec.trk(*m_grete[i]) && Risalnik::get_tipko_tipkovnice(' ') && m_grete[i]->ali_zivim)
        {
            m_grete[i]->smrt();
            m_tocke -= 10;
        }
    }

    for (int i = 0; i < m_judi.size(); i++)
    {
        m_judi[i]->update(m_jasek, m_cekini);
        m_judi[i]->narisi_me();
        if (m_judi[i]->ali_zivim)
        {
            if (m_judi[i]->sem_lahko_ubit())
            {

                for (int j = 0; j < m_crnci.size(); j++)
                    if (m_crnci[j]->trk(*m_judi[i]) && m_crnci[j]->ali_zivim)
                    {
                        m_judi[i]->smrt();
                        m_st_judov--;
                    }
                if (m_judi[i]->trk(m_vegovec) && Risalnik::get_tipko_tipkovnice(' '))
                {

                    m_judi[i]->smrt();
                    m_st_judov--;
                    m_tocke -= 30;
                }
            }
        }
    }

    for (int i = 0; i < m_smeti.size(); i++)
    {
        m_smeti[i]->update();
        m_smeti[i]->narisi_me();
        if (m_vegovec.trk(*m_smeti[i]))
        {
            std::swap(m_smeti[i], m_smeti.back());
            delete m_smeti.back();
            m_smeti.pop_back();
            m_tocke += 5;
        }
    }

    for (int i = 0; i < m_cekini.size(); i++)
    {
        m_cekini[i]->narisi_me();
        if (m_vegovec.trk(*m_cekini[i]))
        {
            if (!konec_igre())
                m_tocke += 20;
            std::swap(m_cekini[i], m_cekini.back());
            delete m_cekini.back();
            m_cekini.pop_back();
            break;
        }

        if (m_cekini[i]->ttl <= Cas::get_time())
        {
            std::swap(m_cekini[i], m_cekini.back());
            delete m_cekini.back();
            m_cekini.pop_back();
            // break;
        }
    }

    //! Jaz sem zabit!!!!
    m_vegovec.update(m_jasek);
    m_vegovec.narisi_me();

    Risalnik::narisi_niz(m_pisava, 0x000000ff, 0, mat::vec2(70, Risalnik::get_velikost_okna().y - 115), 500, std::to_string(m_tocke));

    if (Risalnik::get_tipko_tipkovnice('R'))
    {
        konec();
    }
    if (Risalnik::get_tipko_tipkovnice('U'))
    {
        izhod_v_sili();
        konec();
        std::exit(0);
    }
    if (konec_igre()) // konec igre
    {
        Risalnik::narisi_niz(m_pisava, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y / 2, 400, "BRAVO!");
        m_izhod_gumb.narisi_me();
        if (m_izhod_gumb.je_miska_gor())
        {
            m_izhod_gumb.barva_objekta.set_a(0xaa);
            if (Risalnik::get_miskin_gumb() == Gumb::levi)
            {
                konec();
            }
        }
        else
        {
            m_izhod_gumb.barva_objekta.set_a(0xff);
        }
    }
    else
    {
        Risalnik::narisi_niz(m_pisava, 0x000000ff, Barva(0), mat::vec2(70, Risalnik::get_velikost_okna().y - 55), 500, std::to_string((int)floor(m_next_tocke_odboj - Cas::get_time())));
        if (m_next_tocke_odboj <= Cas::get_time())
        {
            if (m_tocke <= 0)
                m_tocke -= rand() % 10;
            else
            {
                m_tocke -= rand() % m_tocke / 2 + m_tocke / 6;
            }
            m_next_tocke_odboj = Cas::get_time() + rand() % 10;
        }
    }

    if (m_st_judov < m_st_judov_const) // preverjanje števeila judov
    {
        m_jasek.naredi_juda(m_judi, &m_zemljevid);
        m_st_judov++;
    }

    if (!konec_igre() && m_naslednj_okvir_cas <= Cas::get_time())
    {
        o_dat.write((char *)&m_vegovec.pozicija, sizeof(mat::vec2));
    }
    log::msg("zanka konec");
}

void Igraj_od_prej_level::konec()
{
    o_dat.close();
    m_vegovec.animacije = std::vector<Animacija>{};
    m_izhod_gumb.unici();
    m_zemljevid.Unici();
    m_muzika.stop();
    // m_pisava.unici();
    for (int i = 0; i < m_crnci.size(); i++)
    {

        delete m_crnci.back();
        m_crnci.pop_back();
    }

    for (int i = 0; i < m_grete.size(); i++)
    {
        delete m_grete.back();
        m_grete.pop_back();
    }

    for (int i = 0; i < m_smeti.size(); i++)
    {
        delete m_smeti.back();
        m_smeti.pop_back();
    }

    for (int i = 0; i < m_judi.size(); i++)
    {
        delete m_judi.back();
        m_judi.pop_back();
    }

    for (int i = 0; i < m_cekini.size(); i++)
    {
        delete m_cekini.back();
        m_cekini.pop_back();
    }

    m_smeti = std::vector<Objekt_smeti *>{};
    m_crnci = std::vector<Objekt_crnc *>{};
    m_grete = std::vector<Objekt_greta *>{};
    m_judi = std::vector<Objekt_jud *>{};
    zacetna->posodobi_igralca(m_tocke);
    zacetna->zacetek();
}
bool Igraj_od_prej_level::konec_igre()
{
    return (!m_je_se_kaksen_crn && m_smeti.size() == 0);
}

void Igraj_od_prej_level::izhod_v_sili()
{
    std::ofstream o_dat("../sredstva/tt.bin", std::ios::binary);
    o_dat.write((char *)&seme, sizeof(uint32_t));
    double cas = Cas::get_time();

    o_dat.write((char *)&cas, sizeof(double));
    o_dat.write((char *)&m_tocke, sizeof(m_tocke));
    o_dat.write((char *)&m_vegovec.pozicija, sizeof(mat::vec2));

    int vel = m_crnci.size();
    o_dat.write((char *)&vel, sizeof(vel));
    for (int i = 0; i < vel; i++)
    {
        o_dat.write((char *)&m_crnci[i]->pozicija, sizeof(mat::vec2));
        o_dat.write((char *)&m_crnci[i]->sem_mocan, sizeof(bool));
        o_dat.write((char *)&m_crnci[i]->sem_pokopan, sizeof(bool));
        o_dat.write((char *)&m_crnci[i]->ali_zivim, sizeof(bool));
    }

    vel = m_smeti.size();
    o_dat.write((char *)&vel, sizeof(vel));
    for (int i = 0; i < vel; i++)
    {
        o_dat.write((char *)&m_smeti[i]->pozicija, sizeof(mat::vec2));
    }
    vel = m_grete.size();
    o_dat.write((char *)&vel, sizeof(vel));
    for (int i = 0; i < vel; i++)
    {
        o_dat.write((char *)&m_grete[i]->pozicija, sizeof(mat::vec2));
        o_dat.write((char *)&m_grete[i]->ali_zivim, sizeof(bool));
        o_dat.write((char *)&m_grete[i]->sem_pokopan, sizeof(bool));
    }
    vel = m_judi.size();
    o_dat.write((char *)&vel, sizeof(vel));
    for (int i = 0; i < vel; i++)
    {
        o_dat.write((char *)&m_judi[i]->pozicija, sizeof(mat::vec2));
        o_dat.write((char *)&m_judi[i]->ali_zivim, sizeof(bool));
        o_dat.write((char *)&m_judi[i]->sem_pokopan, sizeof(bool));
    }
    /*
    vel = m_cekini.size();
    o_dat.write((char *)&vel, sizeof(vel));
    for (int i = 0; i < vel; i++)
    {
        o_dat.write((char *)m_judi[i], sizeof(Objekt_jud));
    }
    o_dat.close();*/
}