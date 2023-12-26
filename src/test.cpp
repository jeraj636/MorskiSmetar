#include "HenigmaEngine/HenigmaEngine.h"
#include "Scene/Zacetna.h"
#include "Scene/IzbiraSlota.h"

int main()
{
    Risalnik::Init("Morski smetar");
    Risalnik::odzadje = 0x5b6ee1ff;
    Risalnik::sredstvaPath = "../Sredstva";

    IzbiraSlota izbiraSlota;
    Zacetna sc(&izbiraSlota);
    Risalnik::aktivnaScena = &sc;
    Risalnik::aktivnaScena->Zacetek();
    while (!Risalnik::AliSeMoramZapreti())
    {
        Risalnik::ZacetekFrame();
        Risalnik::KonecFrame();
    }
    Risalnik::Konec();
}