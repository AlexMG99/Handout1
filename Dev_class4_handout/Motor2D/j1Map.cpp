#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map


	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());



	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		map_node = map_file.child("map");
		LOG("Node map name is: %s", map_node.name());
		LoadMap(map_node);
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	tileset_node = map_node.child("tileset");
	LOG("Node tilset name is: %s", tileset_node.name());
	LoadTileset(tileset_node);

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}

	map_loaded = ret;

	return ret;
}

bool j1Map::LoadMap(const pugi::xml_node& map_node) {

	//Define render order
	const char* renderorder = map_node.attribute("renderorder").as_string();
	if (renderorder[0] == 'r')
	{
		if (renderorder[6] == 'd')
		{
			map.renderorder = map_renderorder::right_down;
		}
		else
		{
			map.renderorder = map_renderorder::right_up;
		}
	}
	else if (renderorder[0] == 'l')
	{
		if (renderorder[5] == 'd')
		{
			map.renderorder = map_renderorder::left_down;
		}
		else
		{
			map.renderorder = map_renderorder::left_up;
		}
	}

	LOG("Map render order: %i", map.renderorder);

	//Define render order
	const char* orientation = map_node.attribute("orientation").as_string();
	if (renderorder[0] == 'o')
	{
		map.orientation = map_orientation::orthogonal;
	}
	else if (renderorder[0] == 'i')
	{
		map.orientation = map_orientation::isometric;
	}

	LOG("Map orientation: %i", map.orientation);

	map.version = map_node.attribute("version").as_float();
	LOG("La version es: %f papito", map.version);
	map.width = map_node.attribute("width").as_uint();
	LOG("Width: %u", map.width);
	map.height = map_node.attribute("height").as_uint();
	LOG("Height: %u", map.height);
	map.tilewidth = map_node.attribute("tilewidth").as_uint();
	LOG("Tile Width: %u", map.tilewidth);
	map.tileheight = map_node.attribute("tileheight").as_uint();
	LOG("Tile Height: %u", map.tileheight);

	return true;
}

bool j1Map::LoadTileset(const pugi::xml_node& tileset_node) {

	for (pugi::xml_node tileset = tileset_node; tileset; tileset = tileset.next_sibling("tileset")) {
		tileset_info newTileset;
		newTileset.firstgid = tileset_node.attribute("firstgid").as_uint();
		LOG("Firstgid: %u", newTileset.firstgid);
		newTileset.name = tileset_node.attribute("name").value();
		LOG("Name: %s", newTileset.name);
		newTileset.tilewidth = tileset_node.attribute("tilewidth").as_uint();
		LOG("Tileswidth: %u", newTileset.tilewidth);
		newTileset.tileheight = tileset_node.attribute("tileheight").as_uint();
		LOG("Tileheight: %u", newTileset.tileheight);
		newTileset.spacing = tileset_node.attribute("spacing").as_uint();
		LOG("Spacing: %u", newTileset.spacing);
		newTileset.margin = tileset_node.attribute("margin").as_uint();
		LOG("Margin: %u", newTileset.margin);
		tilesetList.push_back(newTileset);
	}

	return true;
}

