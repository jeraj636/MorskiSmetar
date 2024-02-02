#include <henigma_engine.h>

#include "../include/zacetna.h"
#include "../include/level.h"
int main()
{
    Risalnik::init("Morski smetar");

    Risalnik::barva_odzadja = 0x0000ffff;
    Risalnik::sredstva_pot = "../../sredstva";

    Muzika::init();

    Level level;

    Zacetna zacetna(&level);
    zacetna.zacetek();

    level.zacetna = &zacetna;

    Risalnik::aktivna_scena = &zacetna;

    while (!Risalnik::ali_se_moram_zapreti())
    {
        Risalnik::zacetek_okvir();
        Risalnik::aktivna_scena->zanka();
        Risalnik::konec_okvir();
    }
    Risalnik::konec();
}