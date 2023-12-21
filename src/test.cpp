#include "HenigmaEngine/HenigmaEngine.h"
#include "Scene/Zacetna.h"
int main()
{
    Risalnik::Init("Morski smetar");
    Risalnik::odzadje = 0xffff00ff;
    Risalnik::sredstvaPath = "../Sredstva";

    Zacetna sc;
    Risalnik::aktivnaScena = &sc;
    Risalnik::aktivnaScena->Zacetek();
    std::cout << "tukaj sem4" << std::endl;
    while (!Risalnik::AliSeMoramZapreti())
    {
        Risalnik::ZacetekFrame();
        Risalnik::aktivnaScena->Zanka();
        Risalnik::KonecFrame();
    }
    Risalnik::Konec();
}