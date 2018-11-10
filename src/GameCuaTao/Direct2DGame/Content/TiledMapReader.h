#pragma once

#include "AbstractReader.h"
#include "../Extensions/Tiled/TiledMap.h"

class TiledMapReader : public AbstractReader<TiledMap>
{
public:
	std::shared_ptr<TiledMap> Read(std::string filePath, ContentManager &contentManager) override;

private:
	TiledMapObjects ReadTiledMapObjects(pugi::xml_node mapNode);
};