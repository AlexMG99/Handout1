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
	std::list<tileset_info>::const_iterator iterator;
	for (iterator = tilesetList.begin(); iterator != tilesetList.end(); ++iterator) {
		App->render->Blit(iterator->imageTileset, 0, 0);
	}

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
		LOG("Successfully parsed map XML file : %s", map_file.name());
		LOG("width : %u height : %u", map.width, map.height);
		LOG("tile_width : %u tile_height : %u", map.tilewidth, map.tileheight);

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
	map.width = map_node.attribute("width").as_uint();
	map.height = map_node.attribute("height").as_uint();
	map.tilewidth = map_node.attribute("tilewidth").as_uint();
	map.tileheight = map_node.attribute("tileheight").as_uint();

	return true;
}

bool j1Map::LoadTileset(const pugi::xml_node& tileset_node) {

	for (pugi::xml_node tileset = tileset_node; tileset; tileset = tileset.next_sibling("tileset")) {
		tileset_info newTileset;
		newTileset.imageTileset = App->tex->Load(tileset.parent().child("image").attribute("source").as_string());
		newTileset.firstgid = tileset.attribute("firstgid").as_uint();
		newTileset.name = tileset.attribute("name").value();
		newTileset.tilewidth = tileset.attribute("tilewidth").as_uint();
		newTileset.tileheight = tileset.attribute("tileheight").as_uint();
		newTileset.spacing = tileset.attribute("spacing").as_uint();
		newTileset.margin = tileset.attribute("margin").as_uint();
		tilesetList.push_back(newTileset);

		LOG("Tileset----");
		LOG("name : %s firstgid : %u", newTileset.name, newTileset.firstgid);
		LOG("tile_width : %u tile_height : %u", newTileset.tilewidth, newTileset.tileheight);
		LOG("spacing : %u margin : %u", newTileset.spacing, newTileset.margin);
	}

	return true;
}

