#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/utils/web.hpp>
#include "ListManager.h"
#include <string>
using namespace geode::prelude;

class $modify(MenuLayer) {

	struct Fields {
        EventListener<web::WebTask> m_listener;
	};

	bool init() {
		if (!MenuLayer::init()) return false;

		if (ListManager::firstTimeOpen) {
			return true;
		}

		m_fields->m_listener.bind([] (web::WebTask::Event* e) {
            if (web::WebResponse* res = e->getValue()) {
                if (!res->ok()) {
					ListManager::firstTimeOpen = true;
					ListManager::filterType = -2;
					std::string errorStr = "\n\n<cr>Could not load data from AREDL.</c>\nThe API could be down, but chances are, your internet just sucks.\n\n<cg>Restart your game to try again.</c>\n\n<cb>-Grandpa Demon</c>";
					FLAlertLayer::create("What the??", res->string().unwrapOrDefault() + errorStr, "OK")->show();
					return;
				}

				auto json = res->json().unwrapOrDefault();
				if (!json.isArray()) return;

				ListManager::parseRequest(json);
		 		ListManager::firstTimeOpen = true;
		 		ListManager::filterType = -1;
			
			}
        });

		auto req = web::WebRequest();
		m_fields->m_listener.setFilter(req.get("https://api.aredl.net/v2/api/aredl/levels"));

		// if (!ListManager::firstTimeOpen) {
		// 	web::AsyncWebRequest()
		// 	.fetch("https://api.aredl.net/api/aredl/list")
		// 	.text()
		// 	.then([](std::string const& str) {
		// 		ListManager::parseRequestString(str);
		// 		ListManager::firstTimeOpen = true;
		// 		ListManager::filterType = -1;
		// 	})
		// 	.expect([](std::string const& error) {
		// 		ListManager::firstTimeOpen = true;
		// 		ListManager::filterType = -2;
		// 		std::string errorStr = "\n\n<cr>Could not load data from AREDL.</c>\nThe API could be down, but chances are, your internet just sucks.\n\n<cg>Restart your game to try again.</c>\n\n<cb>-Grandpa Demon</c>";
		// 		FLAlertLayer::create("What the??", error + errorStr, "OK")->show();
		// 	});
		// }
		

		return true;
	}
};


