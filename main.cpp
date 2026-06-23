#include <nds.h>
#include <nf_lib2d.h>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

struct Player {
    int x;
    int y;
    int speed;
    int color;
};

int main(int argc, char **argv) {
    NF_Set2D(0, 0);
    NF_Set2D(1, 0);
    
    nitroFSInit();
    NF_SetRootFolder("NITROFS");

    NF_InitTiledBgBuffers();
    NF_InitSpriteBuffers();
    NF_InitTiledBgSys(1); 

    NF_LoadTiledBg("bg/grid_map", "map_bg", 256, 256);
    NF_LoadSpriteGfx("sprite/inkling", 0, 32, 32);
    NF_LoadSpritePal("sprite/inkling", 0);

    NF_CreateTiledBg(1, 3, "map_bg");
    NF_VramSpriteGfx(1, 0, 0, false);
    NF_VramSpritePal(1, 0, 0);

    Player player;
    player.x = 112;
    player.y = 80;
    player.speed = 2;
    player.color = 1;

    NF_CreateSprite(1, 0, 0, 0, player.x, player.y);

    while(1) {
        scanKeys();
        uint32 keys = keysHeld();

        if (keys & KEY_UP)    player.y -= player.speed;
        if (keys & KEY_DOWN)  player.y += player.speed;
        if (keys & KEY_LEFT)  player.x -= player.speed;
        if (keys & KEY_RIGHT) player.x += player.speed;

        if (player.x < 0) player.x = 0;
        if (player.x > SCREEN_WIDTH - 32) player.x = SCREEN_WIDTH - 32;
        if (player.y < 0) player.y = 0;
        if (player.y > SCREEN_HEIGHT - 32) player.y = SCREEN_HEIGHT - 32;

        NF_MoveSprite(1, 0, player.x, player.y);

        int tileX = (player.x + 16) / 8;
        int tileY = (player.y + 16) / 8;

        NF_SetTileOfMap(1, 3, tileX, tileY, 5); 

        NF_SpriteOamUpdate(1);
        swiWaitForVBlank();
        bgUpdate();
    }

    return 0;
}
