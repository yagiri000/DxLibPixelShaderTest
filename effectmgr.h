#pragma once

#include <DxLib.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

#include "effectbase.h"
#include "effects.h"

//effectbaseの配列・管理クラス
//使うときはこのクラスのみインスタンス化すればいい


class effectmgr{
public:
	
	std::vector<std::shared_ptr<effectbase>> v;
	int efGHandle[512];

	effectmgr(){
		loadimages();
	}

	void loadimages(){
	}

	//エフェクト生成 エフェクトへのスマートポインタを返す
	template <class T>
	std::shared_ptr<effectbase> add(double x, double y){
		std::shared_ptr<effectbase> p = std::make_shared<T>(x, y, efGHandle);
		v.push_back(p);
		return p;
	}


	//各エフェクトを更新・消去
	void update(){
		for(auto i : v){
			i->update();
		}
		//deleteflagがtrueなら除去
		auto rmv = std::remove_if(v.begin(), v.end(), 
			[](std::shared_ptr<effectbase> p)->bool{
				return p->deleteflag;
		}
		);
		v.erase(rmv, v.end());
	}

	//描画
	void draw(){
		for(auto i : v){
			i->draw();
		}
		//デバッグ用・現在のエフェクト数を表示
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 255 );
		//DrawFormatString(20, 60, 0xFFFFFF, "NUM : %d", v.size()) ;
	}
};