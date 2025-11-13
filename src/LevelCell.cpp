#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelCell.hpp>
#include "ListManager.h"
#include "EffectsManager.h"

using namespace geode::prelude;

class $modify(LevelCell) {

    // use m_mainLayer as parent
    void loadCustomLevelCell() {
        LevelCell::loadCustomLevelCell();

        if (ListManager::demonIDList.size() == 0) {
            return;
        }

        if (m_level->m_stars != 10) {
            return;
        }

        int aredlPos = ListManager::getPositionOfID(m_level->m_levelID);
        if (aredlPos == -1 || aredlPos > 499) {
            return;
        }

        CCSprite* originalIcon = nullptr;

        auto layer = m_mainLayer->getChildByID("difficulty-container");
        if (layer) {
            originalIcon = static_cast<CCSprite*>(layer->getChildByID("difficulty-sprite"));
        }

        if (originalIcon == nullptr) {
            return;
        }

        CCSprite* newIcon = ListManager::getSpriteFromPosition(aredlPos, false);
        //CCSprite* newIcon = CCSprite::createWithSpriteFrameName("GrD_demon0.png"_spr);
        newIcon->setID("grd-difficulty");

        auto newPos = originalIcon->getPosition();
        newIcon->setPosition(originalIcon->getPosition());
        newIcon->setZOrder(originalIcon->getZOrder()+25);
        
        originalIcon->setOpacity(0);

        layer->addChild(newIcon);

        if (aredlPos <= 24) {
            EffectsManager::addInfinitySymbol(newIcon->getPosition(), layer, aredlPos);
        }
    }
};