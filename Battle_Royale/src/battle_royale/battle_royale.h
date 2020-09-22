#ifndef AZEROTHCORE_BATTLE_ROYALE_H
#define AZEROTHCORE_BATTLE_ROYALE_H

#include "ScriptMgr.h"
#include "Player.h"
#include "OutdoorPvP.h"
#include <map>
#include <deque>

using namespace std;
using GuidDeque = deque<uint64>;
using GuidSet = set<uint64>;

class BattleRoyale : public OutdoorPvP {
public:
    BattleRoyale();

    bool SetupOutdoorPvP() override;

    void HandlePlayerEnterZone(Player *player, uint32 zone) override;

    void HandlePlayerLeaveZone(Player *player, uint32 zone) override;

    bool Update(uint32 diff) override;

    void HandleKill(Player* player, Unit* killed) override;

private:
    void startRoyale();

    void resetRoyale();

    bool checkShouldStart();

    void RemovePlayerFromRoyale(Player *player);

    bool IsPlayerInQueue(Player *player);

    void RemovePlayerFromQueue(Player *player);

    void RemovePlayerFromRoyaleTracker(Player *player);

    void TurnPlayersAggressive();

    void setNewRelic();

    void infectPlayers();

    bool IsPlayerInRoyale(Player *player);

    static void setPlayerFFAFlags(Player *player);

    static void removePlayerFFAFlags(Player *player);

    void NotifyPlayerEnteredQueue(Player *player);

    void NotifyPlayerGameInProgress(Player *player);

    static void TeleportPlayerToHS(Player *player);

    void RemoveExtraPlayers();

    void NotifyPlayerMissedQueue(Player *player);

    void SelectQueuedPlayers();

    void AwardWinner();

    void NotifyNewRelic();

    void spawnNewRelic();

    void setGracePeriod();

    void clearExistingRelicBuffs();

    int getRelicBuffSpellID();

    void HandleInfectionKill(Player* player);

    static void SelectRandomRelic();

    GameObject *SpawnGameObject(uint32 entry, Position const &pos);

    int m_zoneId;
    GuidDeque queue;
    GuidSet playersInRoyale;
    bool royaleEnabled = true;
    bool gameStarted = false;
    bool aggressivePlayers = false;
    bool startInfecting = false;
    int playerLimit = 40;
    int requiredPlayers = 2;
    int currentIteration = 1;
    int startTimer = 60000;
    int relicSwitchTimer = 60000;
    int gracePeriod = 2000;
    Position spawnPointNighthaven;
    Position spawnPointShrine;
    Position spawnPointDens;
    GameObject* currentRelic = nullptr;

};
#endif //AZEROTHCORE_BATTLE_ROYALE_H