#include <henigma_engine.h>

int main()
{
    Risalnik::init("Morski smetar", mat::vec2(1920, 1080));
    Risalnik::barva_odzadja = 0x0000ffff;
    while (!Risalnik::ali_se_moram_zapreti())
    {
        Risalnik::zacetek_okvir();
        Risalnik::konec_okvir();
    }
    Risalnik::konec();
}