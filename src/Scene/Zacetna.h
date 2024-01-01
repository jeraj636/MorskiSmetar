#include "../HenigmaEngine/HenigmaEngine.h"
#include "CelicniAvtomat/CelicniAvtomat.h"
#include <iostream>
enum class Maska
{
    otoki,
    plaza
};
class Zacetna : public Scena
{
public:
    Zacetna(Scena *levelMeni)
    {
        m_levelMeni = levelMeni;
    }
    void Zacetek() override
    {
        // m_theme.Predvajaj();
        // m_zemljevid.Naredi(192, 108, time(NULL));
        m_font.NaloziFont("../Sredstva/CourierPrime.ttf", 40);
        belaTek = Risalnik::NaloziTeksturo("bela.png");
        IgrajGumb.Nastavi(Barva(0x00000000), Barva(0xb6d4e0ff), mat::vec2(Risalnik::GetVelOkno().x / 2, 500), mat::vec2(150, 150), 0, Oznaka::igralec);
        IzhodGumb.Nastavi(Barva(0x00000000), Barva(0xb6d4e0ff), mat::vec2(Risalnik::GetVelOkno().x / 2, 700), mat::vec2(150, 150), 0, Oznaka::igralec);
        Animacija tmp;
        tmp.tekID.push_back(Risalnik::NaloziTeksturo("igrajGumb.png"));

        IgrajGumb.animacija = std::vector<Animacija>{tmp};
        IgrajGumb.trenutnaAnimacija = 0;

        tmp.tekID.back() = Risalnik::NaloziTeksturo("izhodGumb.png");
        IzhodGumb.animacija = std::vector<Animacija>{tmp};
        IzhodGumb.trenutnaAnimacija = 0;

        CelicniAvtomat zemljevid;
        zemljevid.Naredi(192, 108, 69);
        m_otoki.Nastavi(zemljevid.GetTab(), zemljevid.GetX(), zemljevid.GetY(), '0', belaTek, Barva(0x80ff72ff), Maska::otoki);
        m_plaze.Nastavi(zemljevid.GetTab(), zemljevid.GetX(), zemljevid.GetY(), '.', belaTek, Barva(0xfff07cff), Maska::plaza);
    }
    void Zanka() override
    {

        m_otoki.NarisiMe();
        m_plaze.NarisiMe();
        IgrajGumb.Narisi();
        IzhodGumb.Narisi();

        if (IzhodGumb.Gumb())
        {
            IzhodGumb.bobj = 0xb6d4e0aa;
            if (Risalnik::GetMiskinGumb() == Gumb::levi)
            {
                Risalnik::Konec();
            }
        }
        else
        {
            IzhodGumb.bobj = 0xb6d4e0ff;
        }

        if (IgrajGumb.Gumb())
        {
            IgrajGumb.bobj = 0xb6d4e0aa;
            if (Risalnik::GetMiskinGumb() == Gumb::levi)
            {
            }
        }
        else
        {
            IgrajGumb.bobj = 0xb6d4e0ff;
        }
        Risalnik::NarisiNiz(m_font, Barva(0xb6d4e0ff), Barva(0x00000000), mat::vec2(-40, 50), 300, "Morski smetar");
        Risalnik::NarisiNiz(m_font, Barva(0xb6d4e0ff), Barva(0), mat::vec2(-30, -60), 300, std::to_string(m_seme));
        // std::cout << IgrajGumb.Trk(m_otoki) << "\n";
        IgrajGumb.Trk(m_otoki);
    }
    void Konec() override
    {
        m_theme.Ustavi();
    }

private:
    Muzika m_theme = Risalnik::UstvariMuziko("theme.mp3", 1);
    Font m_font;
    Objekt IgrajGumb;
    Objekt IzhodGumb;
    uint32_t belaTek;
    Scena *m_levelMeni;
    unsigned int m_seme;
    double nT;
    Ploscice m_otoki;
    Ploscice m_plaze;
};