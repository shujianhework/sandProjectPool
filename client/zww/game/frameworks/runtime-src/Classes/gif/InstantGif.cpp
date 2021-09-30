#include "InstantGif.h"
#include "platform/CCFileUtils.h"
static uint32_t InstantGifId = 0;

bool InstantGif::init(const char* fileName)
{
	std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(fileName);
	FILE* f = GifUtils::openFile(fullPath.c_str());
	return init(f, fullPath.c_str());
}

bool InstantGif::init(FILE* f,const char* fileName)
{
	m_gif_fullpath = fileName;
	if(GifUtils::isGifFile(f) == false)
	{
        GifUtils::closeFile(f);
		return false;
	}

	m_movie = GIFMovie::create(f);
	if(m_movie == NULL || m_movie->getGifCount() <= 0)
	{
		return false;
	}

	if(m_movie->getGifCount()>1)
	{
		scheduleUpdate();
	}
	m_PlayMax = m_movie->getGifCount();
	m_PlayStart = 0;
	m_movie->setTime(0);
	cocos2d::Texture2D* texture = createTexture(m_movie->bitmap(),0,false);

	return initWithTexture(texture);
}

InstantGif::InstantGif()
{
	m_movie = NULL;

	InstantGifId++;
	if(InstantGifId == UNINITIALIZED_UINT)
	{
		InstantGifId = 0;
	}
	m_instantGifId = InstantGifId;// gif id.
}

std::string InstantGif::getGifFrameName(int index)
{
    // Use id to create framename or texturename, to ensure multiple gifs created under the same path, not confusion in the texture cache
	return cocos2d::CCString::createWithFormat("%s_instant_%u",m_gif_fullpath.c_str(),m_instantGifId)->getCString();
}

bool InstantGif::setPlayCount(int idx)
{
	if(idx < 1 || (m_movie->getGifCount()) >= idx )
		return false;
	this->m_PlayMax = idx;
	if (m_PlayStart <= m_PlayMax)
		m_PlayStart = 0;
	m_movie->getCurrentIndex();
}

bool InstantGif::setPlayBegin(int idx)
{
	if (idx < 0 || idx >= (m_movie->getGifCount() - 4)) {
		return false;
	}
	this->m_PlayStart = idx;
	if (m_PlayStart <= m_PlayMax)
		m_PlayStart = m_movie->getGifCount();
	return true;
}

InstantGif::~InstantGif()
{
	CC_SAFE_DELETE(m_movie);
	std::string texture = getGifFrameName(0);
    cocos2d::Director::getInstance()->getTextureCache()->removeTextureForKey(texture.c_str());
}

void InstantGif::updateGif(uint32_t delta)
{
	if(m_movie->appendTime(delta))
	{
		cocos2d::Texture2D* texture = createTexture(m_movie->bitmap(),0,false);
		this->setTexture(texture);
	}
}

