#include "../include/level.h"
#include <chrono>
#include <thread>
Level::Level()
{
    Objekt_vegovec::init();
    Objekt_crnc::init();
    Objekt_smeti::init();
    Objekt_greta::init();
    Objekt_jasek::init();
    m_pisava = Risalnik::nalozi_font("FixedDays.ttf", 40);
    m_ploscice_tekstura = Risalnik::nalozi_teksturo("ploscica.png");

    m_muzika = Risalnik::nalozi_zvok("zvok/theme.mp3");

    m_tocke_tek = Risalnik::nalozi_teksturo("tocke.png");
    m_ura_tek = Risalnik::nalozi_teksturo("ura.png");
}
void Level::zacetek()
{
    m_izhod_gumb_tek = Risalnik::nalozi_teksturo("ui/izhod_gumb.png");
    m_zemljevid.Naredi(Risalnik::get_velikost_okna().x / 8, Risalnik::get_velikost_okna().y / 8, rand() % 0xffffffff);

    m_ura.nastavi(mat::vec2(32, 32), mat::vec2(32, 50), 180, 0xffffffff, 0);
    m_ura.id_teksture = m_ura_tek;
    m_tocke_obj.nastavi(mat::vec2(32, 100), mat::vec2(32, 32), 180, 0xffffffff, 0);
    m_tocke_obj.id_teksture = m_tocke_tek;

    m_izhod_gumb.nastavi(mat::vec2(Risalnik::get_velikost_okna().x / 2, 600), mat::vec2(100, 100), 180, 0xffffffff, 0);
    m_izhod_gumb.id_teksture = m_izhod_gumb_tek;

    m_obala.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '.', m_ploscice_tekstura, 0xfbe790ff);
    m_otoki.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '0', m_ploscice_tekstura, 0x03ac13ff);

    m_tocke = 0;
    m_vegovec.nastavi(&m_zemljevid);

    m_muzika.zacetek();
    m_muzika.nastavi_loop(true);
    m_muzika.predvajaj();

    int n = rand() % 3 + 5;
    for (int i = 0; i < n; i++)
    {
        m_crnci.push_back(new Objekt_crnc);
        m_crnci.back()->nastavi(&m_zemljevid);
    }
    n = rand() % 3 + 5;
    for (int i = 0; i < n; i++)
    {
        m_smeti.push_back(new Objekt_smeti);
        m_smeti.back()->nastavi(&m_zemljevid, mat::vec2(rand() % ((int)Risalnik::get_velikost_okna().x + 40) - 20, rand() % ((int)Risalnik::get_velikost_okna().y + 40) - 20));
    }
    n = rand() % 3 + 5;

    for (int i = 0; i < n; i++)
    {
        m_grete.push_back(new Objekt_greta);
        m_grete.back()->nastavi(&m_zemljevid, m_smeti);
    }
    m_next_tocke_odboj = Cas::get_time() + 5;

    n = rand() % 2 + 3;
    for (int i = 0; i < n; i++)
    {
        m_jaski.push_back(new Objekt_jasek);
        m_jaski.back()->nastavi();
    }
}

void Level::zanka()
{
    m_obala.narisi_me();
    m_otoki.narisi_me();

    m_ura.narisi_me();
    m_tocke_obj.narisi_me();

    for (int i = 0; i < m_jaski.size(); i++)
    {
        m_jaski[i]->narisi_me();
    }

    bool je_se_kaksen_crn = false;
    for (int i = 0; i < m_crnci.size(); i++)
    {
        m_crnci[i]->update(m_smeti, m_jaski);
        m_crnci[i]->narisi_me();

        if (m_crnci[i]->ali_zivim)
            je_se_kaksen_crn = true;
        if (m_vegovec.trk(*m_crnci[i]))
        {
            if (Risalnik::get_tipko_tipkovnice(' ') && m_crnci[i]->ali_zivim)
            {
                m_crnci[i]->smrt();
                m_tocke += 10;
            }
            if (m_crnci[i]->sem_mocan && m_vegovec.sem_lahko_udarjen())
            {
                m_tocke -= 30;
                m_crnci[i]->sem_mocan = false;
                m_vegovec.udarjen();
                log::war("au");
            }
        }
        for (int j = 0; j < m_crnci.size(); j++)
        {
            if (m_crnci[i]->ali_zivim && m_crnci[j]->ali_zivim && j != i && m_crnci[i]->trk(*m_crnci[j]))
            {
                m_crnci[j]->trk_s_crnim();
            }
        }
    }
    for (int i = 0; i < m_grete.size(); i++)
    {
        m_grete[i]->update(m_smeti, m_tocke, m_jaski);
        m_grete[i]->narisi_me();
        if (m_vegovec.trk(*m_grete[i]) && Risalnik::get_tipko_tipkovnice(' ') && m_grete[i]->ali_zivim)
        {
            m_grete[i]->smrt();
            m_tocke -= 10;
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

    //! Jaz sem zabit!!!!
    m_vegovec.update(m_jaski);
    m_vegovec.narisi_me();
    // Risalnik::narisi_niz(m_pisava, Barva(0xffffffff), Barva(0), 20, 400, std::to_string(m_tocke));
    Risalnik::narisi_niz(m_pisava, 0x000000ff, 0, mat::vec2(70, Risalnik::get_velikost_okna().y - 115), 500, std::to_string(m_tocke));
    if (Risalnik::get_tipko_tipkovnice('R'))
    {
        konec();
        zacetna->zacetek();
        Risalnik::aktivna_scena = zacetna;
    }
    // std::cout << m_next_tocke_odboj << "  " << Cas::get_time() << "\n";
    if (!je_se_kaksen_crn && m_smeti.size() == 0)
    {
        Risalnik::narisi_niz(m_pisava, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y / 2, 400, "BRAVO!");
        m_izhod_gumb.narisi_me();
        if (m_izhod_gumb.je_miska_gor())
        {
            m_izhod_gumb.barva_objekta.set_a(0xaa);
            if (Risalnik::get_miskin_gumb() == Gumb::levi)
            {
                konec();
                zacetna->zacetek();
                Risalnik::aktivna_scena = zacetna;
            }
        }
        else
        {
            m_izhod_gumb.barva_objekta.set_a(0xff);
        }
    }
    else
    {
        // Risalnik::narisi_niz(m_pisava, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 200, 400, std::to_string((int)floor(m_next_tocke_odboj - Cas::get_time())));
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
}

void Level::konec()
{

    m_vegovec.animacije = std::vector<Animacija>{};
    m_izhod_gumb.unici();
    m_zemljevid.Unici();
    m_muzika.stop();
    for (int i = 0; i < m_jaski.size(); i++)
    {
        delete m_jaski.back();
        m_jaski.pop_back();
    }

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

    m_smeti = std::vector<Objekt_smeti *>{};
    m_crnci = std::vector<Objekt_crnc *>{};
    m_grete = std::vector<Objekt_greta *>{};
    m_jaski = std::vector<Objekt_jasek *>{};
    // std::cout << "konec2" << std::endl;
}