#include "../HenigmaEngine/HenigmaEngine.h"
#include <iostream>
class Zacetna : public Scena
{
public:
    Zacetna(Scena *levelMeni)
    {
        m_levelMeni = levelMeni;
    }
    void Zacetek() override
    {
        m_theme.Predvajaj();

        m_font.NaloziFont("../Sredstva/CourierPrime.ttf", 40);

        IgrajGumb.Nastavi(Barva(0x00000000), Barva(0x000000ff), mat::vec2(Risalnik::GetVelOkno().x / 2, 500), mat::vec2(150, 150), 0, Oznaka::igralec);
        IzhodGumb.Nastavi(Barva(0x00000000), Barva(0x000000ff), mat::vec2(Risalnik::GetVelOkno().x / 2, 700), mat::vec2(150, 150), 0, Oznaka::igralec);
        Animacija tmp;
        tmp.tekID.push_back(Risalnik::NaloziTeksturo("igrajGumb.png"));

        IgrajGumb.animacija = std::vector<Animacija>{tmp};
        IgrajGumb.trenutnaAnimacija = 0;

        tmp.tekID.back() = Risalnik::NaloziTeksturo("izhodGumb.png");
        IzhodGumb.animacija = std::vector<Animacija>{tmp};
        IzhodGumb.trenutnaAnimacija = 0;
    }
    void Zanka() override
    {
        Risalnik::NarisiNiz(m_font, Barva(0x000000ff), Barva(0x00000000), mat::vec2(-40, 50), 0, 300, "Morski smetar");
        IgrajGumb.Narisi();
        IzhodGumb.Narisi();

        if (IzhodGumb.Gumb())
        {
            IzhodGumb.bobj = 0x00000055;
            if (Risalnik::GetMiskinGumb() == Gumb::levi)
            {
                Risalnik::Konec();
            }
        }
        else
        {
            IzhodGumb.bobj = 0x000000ff;
        }

        if (IgrajGumb.Gumb())
        {
            IgrajGumb.bobj = 0x00000055;
            if (Risalnik::GetMiskinGumb() == Gumb::levi)
            {
                Konec();
                m_levelMeni->Zacetek();
                Risalnik::aktivnaScena = m_levelMeni;
            }
        }
        else
        {
            IgrajGumb.bobj = 0x000000ff;
        }
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
    Scena *m_levelMeni;
};