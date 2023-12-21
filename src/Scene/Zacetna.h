#include "../HenigmaEngine/HenigmaEngine.h"

class Zacetna : public Scena
{
    void Zacetek() override
    {
        theme.Predvajaj();
    }
    void Zanka() override
    {
    }
    void Konec() override
    {
    }

private:
    Muzika theme = Risalnik::UstvariMuziko("theme.mp3", 1);
};