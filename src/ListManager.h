#ifndef LISTMANAGER_H
#define LISTMANAGER_H
#include <vector>

using namespace geode::prelude;

class ListManager {
    public:
        inline static std::vector<int> demonIDList;
        inline static bool firstTimeOpen;
        inline static int filterType;
        inline static bool isSupremeSearching;

        inline static void parseRequest(matjson::Value const& value) {
            for (auto& item : value) {
                if (auto levelID = item.get<int>("level_id")) {
                    demonIDList.push_back(levelID.unwrap());
                }
            }
        }

        inline static int getPositionOfID(int id) {
            for (unsigned int i = 0; i < demonIDList.size(); i++) {
                if (demonIDList[i] == id) return i;
            }

            return -1;
        }

        inline static CCSprite* getSpriteFromPosition(int pos, bool hasText) {
            if (pos <= 499 &&
                pos > 249) {
                    if (hasText) {
                        return CCSprite::createWithSpriteFrameName("GrD_demon0_text.png"_spr);
                    } else {
                        return CCSprite::createWithSpriteFrameName("GrD_demon0.png"_spr);
                    }
                }

            if (pos <= 249 &&
                pos > 149) {
                    if (hasText) {
                        return CCSprite::createWithSpriteFrameName("GrD_demon1_text.png"_spr);
                    } else {
                        return CCSprite::createWithSpriteFrameName("GrD_demon1.png"_spr);
                    }
                }

            if (pos <= 149 &&
                pos > 74) {
                    if (hasText) {
                        return CCSprite::createWithSpriteFrameName("GrD_demon2_text.png"_spr);
                    } else {
                        return CCSprite::createWithSpriteFrameName("GrD_demon2.png"_spr);
                    }
                }
            if (pos <= 74 &&
                pos > 24) {
                    if (hasText) {
                        return CCSprite::createWithSpriteFrameName("GrD_demon3_text.png"_spr);
                    } else {
                        return CCSprite::createWithSpriteFrameName("GrD_demon3.png"_spr);
                    }
                }
            if (pos <= 24 &&
                pos > 0) {
                    if (hasText) {
                        return CCSprite::createWithSpriteFrameName("GrD_demon4_text.png"_spr);
                    } else {
                        return CCSprite::createWithSpriteFrameName("GrD_demon4.png"_spr);
                    }
                }
            if (pos == 0) {
                if ((Mod::get()->getSettingValue<bool>("grandpa-demon-disable"))) {
                    if (hasText) {
                        return CCSprite::createWithSpriteFrameName("GrD_demon4_text.png"_spr);
                    } else {
                        return CCSprite::createWithSpriteFrameName("GrD_demon4.png"_spr);
                    }
                } else {
                    if (hasText) {
                        return CCSprite::createWithSpriteFrameName("GrD_demon5_text.png"_spr);
                    } else {
                        return CCSprite::createWithSpriteFrameName("GrD_demon5.png"_spr);
                    }
                }
            } 
            return CCSprite::create();
        }

        inline static GJSearchObject* getSearchObject(int upper, int lower) {
            fmt::memory_buffer download;
            bool first = true;
            if (!(upper == 0 && lower == 0)) {
                for (unsigned int i = upper; i > lower; i--) {
                    if (!first) {
                        download.push_back(',');
                    }
                    fmt::format_to(std::back_inserter(download), "{}", ListManager::demonIDList[i]);
                    first = false;
                }
            } else {
                fmt::format_to(std::back_inserter(download), "{}", ListManager::demonIDList[0]);
            }
            
            GJSearchObject* searchObj = GJSearchObject::create(SearchType::Type19, fmt::to_string(download));
            return searchObj;
        }   

        
};

#endif