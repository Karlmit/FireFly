#include "Map.h"
using namespace tinyxml2;

int stringToInt(string str)
{
    istringstream temp(str);
    int ret;
    temp >> ret;

    return ret;
}

Map::Map(string source)
{
	loadMap(source);
}

Map::~Map()
{
}

void Map::loadMap(string source)
{
	XMLDocument xmlmap;

    if (xmlmap.LoadFile(source.data()) != XMLError::XML_NO_ERROR)
		throw runtime_error("Map::loadMap - Error loading the xml map file.\n");

    XMLElement* map_info = xmlmap.FirstChildElement("map");

    mVersion = map_info->Attribute("version");
    mOrientation = map_info->Attribute("orientation");

    mWidth = stringToInt(map_info->Attribute("width"));
    mHeight = stringToInt(map_info->Attribute("height"));
    mTilewidth = stringToInt(map_info->Attribute("tilewidth"));
    mTileheight = stringToInt(map_info->Attribute("tileheight"));

    loadTilesets(&xmlmap);
    loadObjectGroups(&xmlmap);

}

void Map::loadTilesets(XMLDocument *xmlmap)
{
    XMLElement* tileset;
    if((tileset = xmlmap->FirstChildElement("map")->FirstChildElement("tileset")) != NULL)
    {
        MapTileset temp;// = new TiledMapTileset();
        temp.setFirstgid(stringToInt(tileset->Attribute("firstgid")));
        temp.setName(tileset->Attribute("name"));
        temp.setTilewidth(stringToInt(tileset->Attribute("tilewidth")));
        temp.setTileheight(stringToInt(tileset->Attribute("tileheight")));
        temp.setImageSource(tileset->FirstChildElement("image")->Attribute("source"));
        //temp->setImageTrans(tileset->FirstChildElement("image")->Attribute("trans"));
        //temp->setImageWidth(stringToInt(tileset->FirstChildElement("image")->Attribute("width")));
        //temp->setImageHeight(stringToInt(tileset->FirstChildElement("image")->Attribute("height")));

		mTilesets.push_back(temp);
        //this->insertTileset(temp);
    }

    while(tileset != NULL && (tileset = tileset->NextSiblingElement("tileset")) != NULL)
    {
        MapTileset temp;
        temp.setFirstgid(stringToInt(tileset->Attribute("firstgid")));
        temp.setName(tileset->Attribute("name"));
        temp.setTilewidth(stringToInt(tileset->Attribute("tilewidth")));
        temp.setTileheight(stringToInt(tileset->Attribute("tileheight")));
        temp.setImageSource(tileset->FirstChildElement("image")->Attribute("source"));
        //temp.setImageTrans(tileset->FirstChildElement("image")->Attribute("trans"));
        //temp.setImageWidth(stringToInt(tileset->FirstChildElement("image")->Attribute("width")));
        //temp.setImageHeight(stringToInt(tileset->FirstChildElement("image")->Attribute("height")));

		mTilesets.push_back(temp);
        //this->insertTileset(temp);
    }
}

void Map::loadObjectGroups(XMLDocument *xmlmap)
{
    XMLElement* objectgroup;
    XMLElement* object;
    XMLElement* property;

    if((objectgroup = xmlmap->FirstChildElement("map")->FirstChildElement("objectgroup")) != NULL)
    {
        MapObjectGroup temp;// = new TiledMapObjectGroup();
        temp.setName(objectgroup->Attribute("name"));
        temp.setWidth(stringToInt(objectgroup->Attribute("width")));
        temp.setHeight(stringToInt(objectgroup->Attribute("height")));

        if((object = objectgroup->FirstChildElement("object")) != NULL)
        {
            MapObject obj;// = new TiledMapObject();

            obj.setName(object->Attribute("name"));
            obj.setType(object->Attribute("type"));
            obj.setX(stringToInt(object->Attribute("x")));
            obj.setY(stringToInt(object->Attribute("y")));
            obj.setWidth(stringToInt(object->Attribute("width")));
            obj.setHeight(stringToInt(object->Attribute("height")));

            if((property = object->FirstChildElement("properties")->FirstChildElement("property")) != NULL)
            {
                MapObjectProperty prop;// = new TiledMapObjectProperty();

                prop.setName(property->Attribute("name"));
                prop.setValue(property->Attribute("value"));

                obj.insertProperty(prop);
            }

            while((property = object->NextSiblingElement("property")) != NULL)
            {
                MapObjectProperty prop;// = new TiledMapObjectProperty();

                prop.setName(property->Attribute("name"));
                prop.setValue(property->Attribute("value"));

                obj.insertProperty(prop);
            }

            temp.insertObject(obj);
        }

        while((object = object->NextSiblingElement("object")) != NULL)
        {
            MapObject obj;// = new TiledMapObject();

            obj.setName(object->Attribute("name"));
            obj.setType(object->Attribute("type"));
            obj.setX(stringToInt(object->Attribute("x")));
            obj.setY(stringToInt(object->Attribute("y")));
            obj.setWidth(stringToInt(object->Attribute("width")));
            obj.setHeight(stringToInt(object->Attribute("height")));

            if((property = object->FirstChildElement("properties")->FirstChildElement("property")) != NULL)
            {
                MapObjectProperty prop;// = new TiledMapObjectProperty();

                prop.setName(property->Attribute("name"));
                prop.setValue(property->Attribute("value"));

                obj.insertProperty(prop);
            }

            while((property = object->NextSiblingElement("property")) != NULL)
            {
                MapObjectProperty prop;// = new TiledMapObjectProperty();

                prop.setName(property->Attribute("name"));
                prop.setValue(property->Attribute("value"));

                obj.insertProperty(prop);
            }

            temp.insertObject(obj);
        }

        //insertObjectGroup(temp);
		mObjectGroups.push_back(temp);
    }

    while((objectgroup = objectgroup->NextSiblingElement("objectgroup")) != NULL)
    {
        MapObjectGroup temp;// = new TiledMapObjectGroup();
        temp.setName(objectgroup->Attribute("name"));
        temp.setWidth(stringToInt(objectgroup->Attribute("width")));
        temp.setHeight(stringToInt(objectgroup->Attribute("height")));

        if((object = objectgroup->FirstChildElement("object")) != NULL)
        {
            MapObject obj;// = new TiledMapObject();

            obj.setName(object->Attribute("name"));
            obj.setType(object->Attribute("type"));
            obj.setX(stringToInt(object->Attribute("x")));
            obj.setY(stringToInt(object->Attribute("y")));
            obj.setWidth(stringToInt(object->Attribute("width")));
            obj.setHeight(stringToInt(object->Attribute("height")));

            if((property = object->FirstChildElement("properties")->FirstChildElement("property")) != NULL)
            {
                MapObjectProperty prop;// = new TiledMapObjectProperty();

                prop.setName(property->Attribute("name"));
                prop.setValue(property->Attribute("value"));

                obj.insertProperty(prop);
            }

            while((property = object->NextSiblingElement("property")) != NULL)
            {
                MapObjectProperty prop;// = new TiledMapObjectProperty();

                prop.setName(property->Attribute("name"));
                prop.setValue(property->Attribute("value"));

                obj.insertProperty(prop);
            }

            temp.insertObject(obj);
        }

        while(object != NULL && (object = object->NextSiblingElement("object")) != NULL)
        {
            MapObject obj;// = new TiledMapObject();

            obj.setName(object->Attribute("name"));
            obj.setType(object->Attribute("type"));
            obj.setX(stringToInt(object->Attribute("x")));
            obj.setY(stringToInt(object->Attribute("y")));
            obj.setWidth(stringToInt(object->Attribute("width")));
            obj.setHeight(stringToInt(object->Attribute("height")));

            if((property = object->FirstChildElement("properties")->FirstChildElement("property")) != NULL)
            {
                MapObjectProperty prop;// = new TiledMapObjectProperty();

                prop.setName(property->Attribute("name"));
                prop.setValue(property->Attribute("value"));

                obj.insertProperty(prop);
            }

            while((property = object->NextSiblingElement("property")) != NULL)
            {
                MapObjectProperty prop;// = new TiledMapObjectProperty();

                prop.setName(property->Attribute("name"));
                prop.setValue(property->Attribute("value"));

                obj.insertProperty(prop);
            }

            temp.insertObject(obj);
        }

        //this->insertObjectGroup(temp);
		mObjectGroups.push_back(temp);
    }
}