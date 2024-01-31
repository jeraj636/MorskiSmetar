#include "../include/level.h"
#include <chrono>
#include <thread>
Level::Level()
{
    Objekt_vegovec::init();
    Objekt_crnc::init();
    Objekt_smeti::init();
    Objekt_greta::init();
    m_pisava = Risalnik::nalozi_font("FixedDays.ttf", 40);
    m_ploscice_tekstura = Risalnik::nalozi_teksturo("ploscica.png");
}
void Level::zacetek()
{
    m_zemljevid.Naredi(240, 135, rand() % 0xffffffff);

    m_obala.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '.', m_ploscice_tekstura, 0xfbe790ff);
    m_otoki.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '0', m_ploscice_tekstura, 0x03ac13ff);

    m_tocke = 0;

    m_vegovec.nastavi(&m_zemljevid);
    /*
        m_muzika.nastavi("../../sredstva/zvok/theme.mp3");
        m_muzika.nastavi_loop(true);
        m_muzika.predvajaj();

    double next = Cas::get_time() + 0.05;
    while (next > Cas::get_time())
        ;
        */
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
    m_next_tocek_odboj = Cas::get_time() + 5;
}

void Level::zanka()
{
    m_obala.narisi_me();
    m_otoki.narisi_me();

    m_vegovec.update();
    m_vegovec.narisi_me();

    bool je_se_kaksen_crn = false;
    for (int i = 0; i < m_crnci.size(); i++)
    {
        m_crnci[i]->update(m_smeti);
        m_crnci[i]->narisi_me();

        if (m_crnci[i]->ali_zivim)
            je_se_kaksen_crn = true;
        if (m_vegovec.trk(*m_crnci[i]) && Risalnik::get_tipko_tipkovnice(' ') && m_crnci[i]->ali_zivim)
        {

            m_crnci[i]->smrt();
            m_tocke += 10;
        }
    }

    for (int i = 0; i < m_smeti.size(); i++)
    {
        m_smeti[i]->update();
        m_smeti[i]->narisi_me();
    }

    for (int i = 0; i < m_grete.size(); i++)
    {
        m_grete[i]->update(m_smeti, m_tocke);
        m_grete[i]->narisi_me();
        if (m_vegovec.trk(*m_grete[i]) && Risalnik::get_tipko_tipkovnice(' ') && m_grete[i]->ali_zivim)
        {
            m_grete[i]->smrt();
            m_tocke -= 10;
        }
    }

    //! Jaz sem zabit!!!!

    for (int i = 0; i < m_smeti.size(); i++)
    {
        if (m_vegovec.trk(*m_smeti[i]))
        {
            std::swap(m_smeti[i], m_smeti.back());
            delete m_smeti.back();
            m_smeti.pop_back();
            m_tocke++;
        }
    }

    Risalnik::narisi_niz(m_pisava, Barva(0xffffffff), Barva(0), 20, 400, std::to_string(m_tocke));

    if (Risalnik::get_tipko_tipkovnice('R'))
    {
        konec();
        zacetna->zacetek();
        Risalnik::aktivna_scena = zacetna;
    }
    // std::cout << m_next_tocek_odboj << "  " << Cas::get_time() << "\n";
    if (!je_se_kaksen_crn && m_smeti.size() == 0)
    {
        Risalnik::narisi_niz(m_pisava, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y / 2, 400, "BRAVO!");
    }
    else
    {
        Risalnik::narisi_niz(m_pisava, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 200, 400, std::to_string((int)floor(m_next_tocek_odboj - Cas::get_time())));
        if (m_next_tocek_odboj <= Cas::get_time())
        {
            m_tocke -= rand() % 10;
            m_next_tocek_odboj = Cas::get_time() + rand() % 10;
        }
    }
}

void Level::konec()
{
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    m_vegovec.animacije = std::vector<Animacija>{};
    m_zemljevid.Unici();

    for (int i = 0; i < m_smeti.size(); i++)
    {
        delete m_smeti.back();
        m_smeti.pop_back();
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
    m_smeti = std::vector<Objekt_smeti *>{};
    m_crnci = std::vector<Objekt_crnc *>{};
    m_grete = std::vector<Objekt_greta *>{};
    std::cout << "konec2" << std::endl;
}