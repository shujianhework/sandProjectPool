#ifndef GIFBASE_H
#define GIFBASE_H
#include "cocos2d.h"
#include "Bitmap.h"

class GifBase : public cocos2d::Sprite
{
public:
	virtual void updateGif(uint32_t delta) = 0;
	virtual cocos2d::Texture2D* createTexture(Bitmap* bm, int index, bool getCache);
	GifBase() :m_PlayMax(0), m_PlayStart(0) {}
	virtual void update(float delta)
	{
        //if delta>1, generally speaking  the reason is the device is stuck
        if(delta > 1)
        {
            return;
        }
		uint32_t ldelta = (uint32_t)(delta * 1000);
		updateGif(ldelta);
	};
	virtual void setPosition(const cocos2d::Vec2& position) {
		Node::setPosition(position);
	}
	virtual void setPosition(float x, float y) {
		Node::setPosition(x, y);
	}
	virtual std::string getGifFrameName(int index)
	{
		return m_gif_fullpath;
	};
	
	bool fileEndWithGif( const char* filename )
	{
		int nLen = strlen(filename);
		if (nLen < 4) return false;
		if (filename[nLen - 4] != '.') return false;
		if (filename[nLen - 3] != 'g' && filename[nLen - 3] != 'G') return false;
		if (filename[nLen - 2] != 'i' && filename[nLen - 3] != 'I') return false;
		if (filename[nLen - 1] != 'f' && filename[nLen - 3] != 'F') return false;
		return true;
	}
	//播放到第多少帧
	virtual bool setPlayCount(int idx) {
		return false;
	}
	//从多少帧开始播
	virtual bool setPlayBegin(int idx) {
		return false;
	}
	virtual cocos2d::Size getSize() {
		return { 0,0 };
	}
protected:
	std::string m_gif_fullpath;;
	int m_PlayMax;
	int m_PlayStart;
};
#endif//GIFBASE_H

