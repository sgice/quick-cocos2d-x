#include "CCGameCenter.h"
#include "GameCenterIos.h"


void CCGameCenter::login()
{
    [[GameCenterIos shared] login];
}

#pragma mark -
#pragma mark Achievements

bool CCGameCenter::showAchievements()
{
    return [[GameCenterIos shared] showAchievements];
}

void CCGameCenter::postAchievement(const char* idName, int percentComplete)
{
    [[GameCenterIos shared] postAchievement:idName percent:[NSNumber numberWithInt:percentComplete]];
}

void CCGameCenter::clearAllAchievements()
{
    [[GameCenterIos shared] clearAllAchivements];
}

#pragma mark -
#pragma mark Leaderboard

bool CCGameCenter::showScores()
{
    return [[GameCenterIos shared] showScores];
}

void CCGameCenter::postScore(const char* idName, int score)
{
    [[GameCenterIos shared] postScore:idName score:[NSNumber numberWithInt:score]];
}

void CCGameCenter::clearAllScores()
{
    [[GameCenterIos shared] clearAllScores];
}

