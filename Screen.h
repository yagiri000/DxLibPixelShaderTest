#pragma once

#include "DxLib.h"
#include <string>
#include <unordered_map>
#include <map>
#include <functional>

class Handle_Update{
public:
	int handle;
	std::function<void(std::string)> func;
	Handle_Update(){

	}
	Handle_Update(int h, std::function<void(std::string)> f){
		handle = h;
		func = f;
	}
};

class Screen{
public:
	const int ScrSize = 1024;

	//頂点の設定
	VERTEX2DSHADER vertex[4];

	//シングルトン
	static Screen& get(){
		static Screen inst;
		return inst;
	}

	static int handle(std::string name){
		return get().handlemap.at(name).handle;
	}

	//スクリーン
	int tmpscreen;
	int subscreen;


	//スクリーンを描画
	void draw(int scrhandle, int blendmode, int pal = 255){
		SetDrawBlendMode(blendmode, pal);
		DrawGraph(0, 0, scrhandle, 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	//スクリーンを描画
	void draw(){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawGraph(0, 0, subscreen, 1);
	}

	//スクリーンにシェーダーを適用してtmpに出力
	void DrawScrToTmpShader(int targetscr, int shaderh){
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawScreen(tmpscreen);
		ClearDrawScreen();
		SetUseTextureToShader(0, targetscr);
		SetUsePixelShader(shaderh);
		DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);
	}


	//シェーダーのみで更新
	void update(std::string str){
		handlemap[str].func(str);
	}

	void rot_hue(int num){
		GraphFilter(subscreen, DX_GRAPH_FILTER_HSB, 0, num, 0, 0);
	}

	void gauss(int num){
		GraphFilter(subscreen, DX_GRAPH_FILTER_GAUSS, 8, num);
	}


	static void SetDrawScreenSub(){
		SetDrawScreen(get().subscreen);
	}

	static void SetDrawScreenBack(){
		SetDrawScreen(DX_SCREEN_BACK);
	}


	std::unordered_map<std::string, Handle_Update> handlemap;

private:

	Screen()
	{
		init();
	}

	void init(){
		//新たにスクリーンを作成
		tmpscreen = MakeScreen(ScrSize, ScrSize, 1);
		subscreen = MakeScreen(ScrSize, ScrSize, 1);


		//斜め線上がランダムにa=0になる
		//乱数を渡さなければいけない(0~2PI)
		LoadToMap("randalpha0",
			[](std::string str){
			//スクリーンにシェーダーを適用してtmpに出力
			SetPSConstSF(0, (float)(Random::FRadRand()));
			get().DrawScrToTmpShader(get().subscreen, handle(str));
			//結果をコピー
			GraphFilterBlt(get().tmpscreen, get().subscreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
		}
		);

		LoadToMap("distr_angg",
			[](std::string str){
			//スクリーンにシェーダーを適用してtmpに出力
			get().DrawScrToTmpShader(get().subscreen, handle(str));
			//結果をコピー
			GraphFilterBlt(get().tmpscreen, get().subscreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
			GraphFilter(get().subscreen, DX_GRAPH_FILTER_GAUSS, 8, 50);
		}
		);

		LoadToMap("sinalpha",
			[](std::string str){
			//スクリーンにシェーダーを適用してtmpに出力
			get().DrawScrToTmpShader(get().subscreen, handle(str));
			//結果をコピー
			GraphFilterBlt(get().tmpscreen, get().subscreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
			GraphFilter(get().subscreen, DX_GRAPH_FILTER_GAUSS, 8, 50);
		}
		);

		//
		//マウス座標を渡す
		LoadToMap("mouserotcolor",
			[](std::string str){
			//スクリーンにシェーダーを適用してtmpに出力
			SetPSConstSF(0, (float)(Input::mousex() / 1024.0));
			SetPSConstSF(1, (float)(Input::mousex() / 1024.0));
			get().DrawScrToTmpShader(get().subscreen, handle(str));
			//結果をコピー
			GraphFilterBlt(get().tmpscreen, get().subscreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
		}
		);

		//マウス座標を渡す
		LoadToMap("rotdistcos",
			[](std::string str){
			//スクリーンにシェーダーを適用してtmpに出力
			SetPSConstSF(0, (float)(Input::mousex() / 1024.0));
			SetPSConstSF(1, (float)(Input::mousex() / 1024.0));
			get().DrawScrToTmpShader(get().subscreen, handle(str));
			//結果をコピー
			GraphFilterBlt(get().tmpscreen, get().subscreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
		}
		);

		//マウス座標を渡す
		LoadToMap("cosmoddydy",
			[](std::string str){
			//スクリーンにシェーダーを適用してtmpに出力
			SetPSConstSF(0, (float)(Input::mousex() / 1024.0));
			SetPSConstSF(1, (float)(Input::mousex() / 1024.0));
			get().DrawScrToTmpShader(get().subscreen, handle(str));
			//結果をコピー
			GraphFilterBlt(get().tmpscreen, get().subscreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
		}
		);
		//マウス座標を渡す
		LoadToMap("cosdistrotcolor",
			[](std::string str){
			//スクリーンにシェーダーを適用してtmpに出力
			SetPSConstSF(0, (float)(Input::mousex() / 1024.0));
			SetPSConstSF(1, (float)(Input::mousex() / 1024.0));
			get().DrawScrToTmpShader(get().subscreen, handle(str));
			//結果をコピー
			GraphFilterBlt(get().tmpscreen, get().subscreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
		}
		);
		//マウス座標を渡す
		LoadToMap("cosmoddist",
			[](std::string str){
			//スクリーンにシェーダーを適用してtmpに出力
			SetPSConstSF(0, (float)(Input::mousex() / 1024.0));
			SetPSConstSF(1, (float)(Input::mousex() / 1024.0));
			get().DrawScrToTmpShader(get().subscreen, handle(str));
			//結果をコピー
			GraphFilterBlt(get().tmpscreen, get().subscreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
		}
		);
		//マウス座標を渡す
		LoadToMap("distsand",
			[](std::string str){
			//スクリーンにシェーダーを適用してtmpに出力
			SetPSConstSF(0, (float)(Input::mousex() / 1024.0));
			SetPSConstSF(1, (float)(Input::mousex() / 1024.0));
			get().DrawScrToTmpShader(get().subscreen, handle(str));
			//結果をコピー
			GraphFilterBlt(get().tmpscreen, get().subscreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
		}
		);


		LoadToMap("modpos");
		LoadToMap("rotcolor");
		LoadToMap("sinbox");
		LoadToMap("sinpos");
		LoadToMap("cosysinx");
		LoadToMap("coscosx");
		LoadToMap("coscosy");
		LoadToMap("exrate_plus");
		LoadToMap("rotpos");
		LoadToMap("cosmod");
		LoadToMap("cosmod");


		//頂点の設定
		for (int i = 0; i < 4; i++)
		{
			vertex[i].pos = VGet((i % 2)*(float)ScrSize, (i / 2)*(float)ScrSize, 0);
			vertex[i].rhw = 1.0f;
			vertex[i].dif = GetColorU8(255, 255, 255, 255);
			vertex[i].spc = GetColorU8(0, 0, 0, 0);
			vertex[i].u = vertex[i].su = (float)(i % 2);
			vertex[i].v = vertex[i].sv = (float)(i / 2);
		}
	}

	//シェーダー適用後、任意の処理セットを適用（ラムダ式で指定）
	void LoadToMap(std::string name, std::function<void(std::string)> f){
		int sh;
		sh = LoadPixelShader(("Shader/" + name + ".pso").c_str());
		if (sh != -1){
			handlemap.emplace(name, Handle_Update(sh, f));
			return;
		}
	}

	//シェーダーだけを適用
	void LoadToMap(std::string name){
		int sh;
		sh = LoadPixelShader(("Shader/" + name + ".pso").c_str());
		if (sh != -1){
			handlemap.emplace(name, Handle_Update(sh,
				[](std::string str){
				//スクリーンにシェーダーを適用してtmpに出力
				get().DrawScrToTmpShader(get().subscreen, handle(str));
				//結果をコピー
				GraphFilterBlt(get().tmpscreen, get().subscreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
			}));
			return;
		}
	}
	
	Screen& operator=(const Screen& a) = delete;
	Screen(const Screen& a) = delete;
};


