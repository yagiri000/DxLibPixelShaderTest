#pragma once

#include <DxLib.h>
#include <iostream>
#include <iterator>

#include "myglobal.h"

#include "Resource.h"
#include "Func.h"
#include "Screen.h"

#include "effectbase.h"
#include "effects.h"
#include "effectmgr.h"


int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	ChangeWindowMode( TRUE );
	SetGraphMode( 800 , 600 , 32 );
	SetOutApplicationLogValidFlag( FALSE ) ;//logを生成しないように設定
	if(DxLib_Init() == 1){return -1;}//初期化に失敗時にエラーを吐かせて終了
	SetDrawScreen( DX_SCREEN_BACK ) ;
	
	Input::get();
	Screen::get();

	int ef_mode = 0;
	auto scr_iter = Screen::get().handlemap.begin();

	effectmgr ef;


	Mgr<IButton> Button_;

#pragma region button
	int buttony = 100;
	Button_.v.emplace_back(std::make_shared<CrickButton>(20, buttony, 50, 30, "<SH",
		[&scr_iter](){
		if (scr_iter != Screen::get().handlemap.begin()){
			scr_iter--;
		}
	}
	));

	Button_.v.emplace_back(std::make_shared<CrickButton>(100, buttony, 50, 30, "SH>",
		[&scr_iter](){
		scr_iter++;
		if (scr_iter == Screen::get().handlemap.end()){
			scr_iter--;
		}
	}
	));
	buttony += 40;


	Button_.v.emplace_back(std::make_shared<CrickButton>(20, buttony, 50, 30, "<EF",
		[&ef_mode](){
		ef_mode--;
		if (ef_mode < 0){
			ef_mode = 0;
		}
	}
	));

	Button_.v.emplace_back(std::make_shared<CrickButton>(100, buttony, 50, 30, "EF>",
		[&ef_mode](){
		ef_mode++;
	}
	));
	buttony += 40;


	Button_.v.emplace_back(std::make_shared<OnOffButton>(20, buttony, 200, 30, "色相変更",
		[](){
		Screen::get().rot_hue(2);
	}
	));
	buttony += 40;
	Button_.v.emplace_back(std::make_shared<OnOffButton>(20, buttony, 200, 30, "ガウスぼかし",
		[](){
		Screen::get().gauss(50);
	}
	));


#pragma endregion make_button




	while( ProcessMessage() == 0)
	{
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();//裏画面消す
		Input::update();

		//DrawBox(0, 0, 800, 800, 0x888888, 1);

		int mousex = Input::mousex(), mousey = Input::mousey();
		Screen &scr = Screen::get();


#pragma region hoge

		if(Input::keynow(KEY_INPUT_Z)){
			switch (ef_mode)
			{
			case 0: ef.add<fire>(mousex, mousey); break;
			case 1: ef.add<slash>(mousex, mousey); break;
			case 2: ef.add<dotsplash>(mousex, mousey); break;
			case 3: ef.add<moveonCircle>(mousex, mousey); break;
			case 4: ef.add<dot_ex_inout>(mousex, mousey); break;
			case 5: ef.add<dot_verybig>(mousex, mousey); break;
			case 6: ef.add<chargerotate>(mousex, mousey); break;
			case 7: ef.add<dot_charge>(mousex, mousey); break;
			case 8: ef.add<reaf_move>(mousex, mousey); break;
			case 9: ef.add<firework>(mousex, mousey); break;
			case 10: ef.add<out_in_dot>(mousex, mousey); break;
			case 11: ef.add<floting_dot>(mousex, mousey); break;
			case 12: ef.add<fire_dot>(mousex, mousey); break;
			case 13: ef.add<splash_gravity>(mousex, mousey); break;
			case 14: ef.add<splash_thin>(mousex, mousey); break;
			case 15: ef.add<smoke>(mousex, mousey); break;
			}
		}

		if (Input::keydown(KEY_INPUT_X)){
			for (int i = 0; i < 30; i++){
				double gx, gy;
				Random::RandOnCircle(30, gx, gy);
				auto p = ef.add<slash>(mousex + gx, mousey + gy);
				p->angle = i * DegToRad * 6;
			}
		}

		//エフェクトじゃなくて弾幕
		if (Input::keydown(KEY_INPUT_C)){
			for (int i = 0; i < 30; i++){
				auto p = ef.add<dotmove>(mousex, mousey);
				double ang = (Input::eframe() + i) * 0.05 + (i % 3) * PI * 2 / 3.0;
				double r = 2.0;
				p->vx = r * cos(ang);
				p->vy = r * sin(ang);
				p->ax = 0.02*r * cos(ang + PI);
				p->ay = 0.02*r * sin(ang + PI);
				p->elapsedtime = -i * 4;
			}
		}


#pragma endregion make_ef
		
#pragma region hoge
		if (Input::keydown(KEY_INPUT_RIGHT)){
			scr_iter++;
			if (scr_iter == scr.handlemap.end()){
				scr_iter--;
			}
		}
		if (Input::keydown(KEY_INPUT_LEFT)){
			if (scr_iter != scr.handlemap.begin()){
				scr_iter--;
			}
		}
		if (Input::keydown(KEY_INPUT_UP)){
			ef_mode++;
		}
		if (Input::keydown(KEY_INPUT_DOWN)){
			ef_mode--;
		}

#pragma endregion keydown


		ef.update();
		Button_.update();

		//サブスクリーンに描画開始
		scr.SetDrawScreenSub();
		ef.draw(); 
		if (Input::keydown(KEY_INPUT_V)){ DrawCircle(400, 300, 100, 0xFFFFFF, 1); }
		if (Input::keynow(KEY_INPUT_B)){ DrawCircle(512, (Input::eframe() * 32) % 2048 - 512, 100, 0xFF8800, 0, 8); }
		if (Input::keynow(KEY_INPUT_B)){ DrawCircle(512, (Input::eframe() * 32 + 1024) % 2048 - 512, 100, 0xFF8800, 0, 8); }


		//シェーダーでサブスクリーンを更新
		scr.update(scr_iter->first);
		


		//裏画面に描画開始
		scr.SetDrawScreenBack();
		scr.draw();
		Button_.draw();
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 250 );	SetDrawBright(255,255,255);
		int stry = 0;
		DrawFormatStringToHandle(20, stry += 20, 0xFFFFFF, Font::handle("SegoeUI20"), "シェーダー(←→) %d/%d", std::distance(scr.handlemap.begin(), scr_iter) + 1, scr.handlemap.size());
		DrawFormatStringToHandle(20, stry += 20, 0xFFFFFF, Font::handle("SegoeUI20"), ("シェーダー名 : " + scr_iter->first).c_str());
		DrawFormatStringToHandle(20, stry += 20, 0xFFFFFF, Font::handle("SegoeUI20"), "エフェクト(↓↑) %3d", ef_mode);

		ScreenFlip();//裏画面を表画面にコピー
	}


	DxLib_End();
	return 0;
}

