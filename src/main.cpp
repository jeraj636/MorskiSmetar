#include <henigma_engine.h>

#include "../include/zacetna.h"
#include "../include/level.h"
#include "../include/level_streznik.h"
#include "../include/level_client.h"
int main()
{
    Risalnik::init("Morski smetar");

    Risalnik::barva_odzadja = 0x0000ffff;
    Risalnik::sredstva_pot = "../../sredstva";

    Muzika::init();

    Level level;
    Level_streznik s_level;
    Level_client c_level;

    Zacetna zacetna(&level, &c_level, &s_level);
    zacetna.zacetek();

    level.zacetna = &zacetna;
    s_level.zacetna = &zacetna;
    c_level.zacetna = &zacetna;

    Risalnik::aktivna_scena = &zacetna;

    while (!Risalnik::ali_se_moram_zapreti())
    {
        Risalnik::zacetek_okvir();
        Risalnik::aktivna_scena->zanka();
        Risalnik::konec_okvir();
    }
    Risalnik::konec();
}
