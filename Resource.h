#pragma once

#include "DxLib.h"
#include <string>
#include <unordered_map>


class Graph{
public:

	//シングルトン
	static Graph& get(){
		static Graph inst;
		return inst;
	}

	static int handle(std::string name){
		return get().handlemap.at(name);
	}

private:
	std::unordered_map<std::string, int> handlemap;

	Graph()
	{
		init();
	}

	void init(){
		LoadToMap("dot100");
		LoadToMap("dot32");
		LoadToMap("rect100");
		LoadToMap("rect32");
	}

	void LoadToMap(std::string name){
		int gh;
		std::string loadname = "Images/" + name;
		gh = LoadGraph((loadname + ".png").c_str());
		if (gh != -1){
			handlemap.emplace(name, gh);
			return;
		}
		gh = LoadGraph((loadname + ".jpg").c_str());
		if (gh != -1){
			handlemap.emplace(name, gh);
			return;
		}
	}

	Graph& operator=(const Graph& a) = delete;
	Graph(const Graph& a) = delete;
};


class GraphDiv{
public:

	//シングルトン
	static GraphDiv& get(){
		static GraphDiv inst;
		return inst;
	}

	static int handle(std::string name, int num){
		return get().handlemap.at(name).arr[num];
	}

	class gh_array{
	public:
		int arr[128];
	};

private:
	std::unordered_map<std::string, gh_array> handlemap;

	GraphDiv()
	{
		init();
	}

	//pngのみ読み込み
	void init(){
	}

	//pngのみ読み込み
	void LoadToMap(std::string name, int AllNum, int XNum, int YNum, int XSize, int YSize){
		std::string loadname = "Images_div/" + name;
		gh_array gh_array_;
		LoadDivGraph((loadname + ".png").c_str(), AllNum, XNum, YNum, XSize, YSize, &gh_array_.arr[0]);
		handlemap.emplace(name, gh_array_);
	}

	GraphDiv& operator=(const GraphDiv& a) = delete;
	GraphDiv(const GraphDiv& a) = delete;
};


class Sound{
public:

	//シングルトン
	static Sound& get(){
		static Sound inst;
		return inst;
	}

	static int handle(std::string name){
		return get().handlemap.at(name);
	}

private:
	std::unordered_map<std::string, int> handlemap;

	Sound()
	{
		init();
	}

	void init(){

	}

	void LoadToMap(std::string name){
		int sh;
		std::string loadname = "Sounds/" + name;
		sh = LoadSoundMem((loadname + ".wav").c_str());
		if (sh != -1){
			handlemap.emplace(name, sh);
			return;
		}
		sh = LoadSoundMem((loadname + ".ogg").c_str());
		if (sh != -1){
			handlemap.emplace(name, sh);
			return;
		}
		sh = LoadSoundMem((loadname + ".mp3").c_str());
		if (sh != -1){
			handlemap.emplace(name, sh);
			return;
		}
	}

	Sound& operator=(const Sound& a) = delete;
	Sound(const Sound& a) = delete;

};



class Font{
public:

	//シングルトン
	static Font& get(){
		static Font inst;
		return inst;
	}

	static int handle(std::string name){
		return get().handlemap.at(name);
	}

private:
	std::unordered_map<std::string, int> handlemap;

	Font()
	{
		init();
	}

	void init(){
		handlemap.emplace("SegoeUI20", CreateFontToHandle("Segoe UI", 20, 5, DX_FONTTYPE_ANTIALIASING_4X4));
		handlemap.emplace("SegoeUI40", CreateFontToHandle("Segoe UI", 40, 5, DX_FONTTYPE_ANTIALIASING_4X4));
	}

	void LoadToMap(std::string name, int Size, int Thick, int FontType){
		int fh = CreateFontToHandle(name.c_str(), Size, Thick, FontType);
		handlemap.emplace(name.c_str(), fh);
	}

	Font& operator=(const Font& a) = delete;
	Font(const Font& a) = delete;

};


