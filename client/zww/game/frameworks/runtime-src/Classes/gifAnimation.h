#ifndef __IEXT_GIFANIMATION_H__
#define __IEXT_GIFANIMATION_H__

#include "cocos2d.h"
#include "ui/UIWidget.h"
#include "gif/InstantGif.h"
#include "gif/GifBase.h"
#include "gif/CacheGif.h"
#include "base/CCRef.h"

NS_CC_BEGIN
namespace ui {
	class gifAnimation :public Widget {
		std::string path;
		int frameCount;
		bool isCache;
		GifBase* gifBase;
		CacheGif* cacheGif;

	public:
		gifAnimation(std::string filepath,bool isCache);
		virtual ~gifAnimation();
		static gifAnimation* create(std::string path, bool isCache = false);
		void setPosition(const Vec2& position);
		void setPosition(float x, float y);
		inline Sprite* getNode() {
			if (isCache)
				return (Sprite*)cacheGif;
			return (Sprite*)gifBase;
		}
		bool init();

	};
}
NS_CC_END
#endif  // __IEXT_GIFANIMATION_H__

