#include "g_local.h"

/*
=================
Cmd_Reload_f
=================
*/
void Cmd_Reload_f(gentity_t *ent) {
    // Don't allow reloading if dead
    if (ent->health <= 0) {
        return;
    }

    // Don't allow reloading if not holding a weapon that can be reloaded
    if (ent->s.weapon == WP_NONE || 
        ent->s.weapon == WP_SABER || 
        ent->s.weapon == WP_STUN_BATON || 
        ent->s.weapon == WP_MELEE) {
        return;
    }

    // Get the weapon data
    int weaponNum = ent->s.weapon;
    int ammoIndex = weaponData[weaponNum].ammoIndex;
    int clipSize = weaponData[weaponNum].clipSize;

    // If the weapon doesn't have a clip, don't allow reloading
    if (clipSize <= 0) {
        return;
    }

    // If already reloading, don't allow another reload
    if (ent->client->ps.weaponstate == WEAPON_RELOADING) {
        return;
    }

    // Get current clip ammo and total ammo
    int currentClipAmmo = ent->client->ps.userInt2;
    int totalAmmo = ent->client->ps.ammo[ammoIndex];

    // If clip is full, don't reload
    if (currentClipAmmo >= clipSize) {
        return;
    }

    // If no ammo left, don't reload
    if (totalAmmo <= 0) {
        return;
    }

    // Start reloading
    ent->client->ps.weaponstate = WEAPON_RELOADING;
    ent->client->ps.weaponTime = weaponData[weaponNum].reloadTime;
    ent->client->ps.userInt1 = level.time + weaponData[weaponNum].reloadTime; // Time when reload will complete

    // Play reload sound
    G_Sound(ent, CHAN_WEAPON, G_SoundIndex("sound/weapons/reload.wav"));
}
