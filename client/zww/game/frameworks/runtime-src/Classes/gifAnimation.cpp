#include "gifAnimation.h"
#include <bullet/BulletMultiThreaded/TrbStateVec.h>
NS_CC_BEGIN

namespace ui {
	gifAnimation::gifAnimation(std::string filepath, bool isCache):
		path(filepath), 
		isCache(isCache),
		frameCount(-1),
		gifBase(NULL),
		cacheGif(NULL)
	{

	}

	gifAnimation::~gifAnimation()
	{
	}

	gifAnimation* gifAnimation::create(std::string path, bool isCache)
	{
		gifAnimation* gif = new (std::nothrow) gifAnimation(path,isCache);
		if (gif && gif->init() == true) {
			gif->autorelease();
			return gif;
		}
		CC_SAFE_DELETE(gif);
		return NULL;
	}
	void gifAnimation::setPosition(float x, float y) {
		const Vec2 v2 = { x,y };
		setPosition(v2);
	}
	void gifAnimation::setPosition(const Vec2& position) {

		Sprite* sprite = getNode();
		if (sprite == NULL) {
			return;
		}
		sprite->setPosition(position);

	}
	
	bool gifAnimation::init() {
		bool ret = true;
		do
		{
			if (!Widget::init())
			{
				ret = false;
				break;
			}
			if (isCache == false) {
				gifBase = InstantGif::create(this->path.c_str());

			}
			else {
				cacheGif = CacheGif::create(path.c_str());
			}
			if (gifBase == NULL && cacheGif == NULL)
				return false;

		} while (0);
		return ret;
	}
}
NS_CC_END