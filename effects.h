#pragma once

#include <DxLib.h>
#include <iostream>

#include "effectbase.h"
#include "effectmgr.h"
#include "Func.h"
#include "Resource.h"

//個々のエフェクトの設定ファイル

class cir : public effectbase{
public:
	double ang = Random::FRand(0, 2 * PI);
	double angspd = Random::FRand(0.003, 0.02) * Random::RandPM1();

	cir(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 256, 256, 0.0, 0.0, ang,
			16, 0.0, 0.0, 0.0, 0.0, 0.003, 0.003, 1.0,
			angspd, 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 999);
	};
};

class fire : public effectbase{
public:
	fire(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 4, 4, 0.0,
			200, 0.0, 0.0, 0.0, 0.0, -0.15, -0.15, 1.0,
			0.0, -8, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 25);
		vx = Random::FRand(-1, 1);
		vy = Random::FRand(-15, -5);
	};
};


class slash : public effectbase{
public:
	slash(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 0.5, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, 2.6, 1.0,
			0.0, -25, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 10);
		angle = Random::FRadRand();

	};
};

class dotlight : public effectbase{
public:
	dotlight(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 0.0, 0.0, Random::FRadRand(),
			255.0, 0.0, 0.0, 0.0, 0.0, 0.04, 0.04, 1.0,
			0.01, -8, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 30);
	};
};

class bomb : public effectbase{
public:
	bomb(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, Random::FRadRand(),
			255.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 1.0,
			0.01, -25, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 5);
	};
};



class dotsplash : public effectbase{
public:
	dotsplash(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.2, -0.05, -0.05, 0.93,
			0.0, 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 19);
		Random::RandInCircle(15.0, vx, vy);
	};

};


class elipsplash : public effectbase{
public:
	elipsplash(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 2.0, 1.0, Random::FRadRand(),
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, 0.93,
			0.0, 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		Random::RandInCircle(15.0, vx, vy);

	};
};

class elipsplash_rot : public effectbase{
public:
	elipsplash_rot(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 2.0, 1.0, Random::FRadRand(),
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, 0.93,
			Random::FRand(-PI, PI), 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		Random::RandInCircle(15.0, vx, vy);

	};
};

class dotsplash_curve : public effectbase{
public:
	dotsplash_curve(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, 1.0,
			0.0, 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 16);
		Random::RandOnCircle(12.0, vx, vy);
		ax = -0.10 * vx;
		ay = -0.10 * vy;
		Func::rotateonzero(ax, ay, Random::FRand(-0.5, 0.5));
	};
};


//速度変化率 1.1
class dotsplash_charge : public effectbase{
public:
	dotsplash_charge(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, 1.1,
			0.0, 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		Random::RandInCircle(3.0, vx, vy);
	};
};



//放物線
class dotsplash_fall : public effectbase{
public:
	dotsplash_fall(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.4, -0.05, -0.05, 0.93,
			0.0, 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		Random::RandInCircle(15.0, vx, vy);
	};
};

class dotsplash_rev : public effectbase{
public:
	dotsplash_rev(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, Input::mousex() / 100.0,
			0.01, -0.099, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		Random::RandInCircle(100.0, vx, vy);
	};

};

class moveonCircle : public effectbase{
public:
	int origx;
	int origy;
	moveonCircle(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		origx = (int)x;
		origy = (int)y;
		double r = 15.0 * Random::Value();
		double angle = Random::FRadRand();
		double vx = r * cos(angle);
		double vy = r * sin(angle);
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			128.0, vx, vy, 0.0, 0.0, 0.0, 0.0, 1.0,
			0.01, -3, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 120);
	};


	void move(){
		x = origx + 100 * cos(elapsedtime * 0.1);
		y = origy + 50 * sin(elapsedtime* 0.1);
	}
};




class dot_ex_inout : public effectbase{
public:
	dot_ex_inout(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 0.0, 0.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, 0.04, 0.04, 1.0,
			0.0, -8, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
	};

	void move(){

		x += vx;
		y += vy;
		vx += ax;
		vy += ay;

		exratey = exratex = 1.0 - abs(10 - elapsedtime) * 0.1;

		angle += angleplus;
		alpha += alphaplus;
	}
};




class dot_verybig : public effectbase{
public:
	dot_verybig(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 0.0, 0.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.5, 1.0,
			0.3, -8, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 30);
	};
};




class chargerotate : public effectbase{
public:
	double tx, ty;

	chargerotate(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		tx = x; ty = y;
		double sx, sy;
		Random::RandOnCircle(100, sx, sy);
		set(x + sx, y + sy, 16, 16, 1.0, 1.0, 0.0,
			60, vx, vy, 0.0, 0.0, 0.0, 0.0, 0.92,
			0.0, -1, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
	};

	void move(){

		Func::normalizedVector(vx, vy, x, y, tx, ty);
		Func::rotateonzero(vx, vy, 0.9);
		x += 8 * vx;
		y += 8 * vy;

		exratex += exratexplus;
		exratey += exrateyplus;

		angle += angleplus;
		alpha += alphaplus;
	}
};


class chargerotate_rev : public effectbase{
public:
	double tx, ty ;
	chargerotate_rev(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		tx = x; ty = y;
		double sx, sy;
		Random::RandOnCircle(150, sx, sy);
		set(x + sx, y + sy, 16, 16, 0.5, 0.5, 0.0,
			255, vx, vy, 0.0, 0.0, 0.0, 0.0, 0.92,
			0.0, 0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		angleplus = 0.9 * Random::RandPM1();
	};

	void move(){
		Func::normalizedVector(vx, vy, x, y, tx, ty);
		Func::rotateonzero(vx, vy, angleplus);
		x += 12 * vx;
		y += 12 * vy;

		exratex += exratexplus;
		exratey += exrateyplus;

		angle += angleplus;
		alpha += alphaplus;
	}
};


class dot_charge : public effectbase{
public:
	dot_charge(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double sx, sy, ang;
		Random::RandOnCircle(100, sx, sy, ang);
		double vx = -7 * cos(ang);
		double vy = -7 * sin(ang);
		set(x + sx, y + sy, 16, 16, 1.0, 1.0, 0.0,
			60, vx, vy, 0.0, 0.0, 0.0, 0.0, 0.92,
			0.0, -1, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 60);
	};
};


class reaf_move : public effectbase{
public:
	reaf_move(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double ang_v = Random::FRand(0.05, 0.1);
		double vx, vy;
		Random::RandOnCircle(1.4, vx, vy);
		set(x, y, 16, 16, 1.0, 2, 0.0,
			120, vx, vy, 0.0, 0.0, 0.0, 0.0, 1.0,
			ang_v, -1, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 120);
	};
};


class firework : public effectbase{
public:
	firework(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double vx, vy, ang;
		Random::RandOnCircle(Random::FRand(5, 15), vx, vy, ang);
		set(x, y, 16, 16, 1.0, 0.2, ang,
			150, vx, vy, 0.0, 0.0, 0, 0, 0.97,
			0.0, -10, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 15);
	};
};

class out_in_dot : public effectbase{
public:
	out_in_dot(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double ang = Random::FRadRand();
		double spd = Random::FRand(0.6, 1.3);
		double vx = 6 * spd * cos(ang);
		double vy = 6 * spd * sin(ang);
		double ax = 0.2 * spd * cos(ang - PI);
		double ay = 0.2 * spd * sin(ang - PI);
		set(x, y, 16, 16, 1.0, 1.0, ang,
			100, vx, vy, ax, ay, 0.0, 0.0, 1.0,
			0.0, -1.66, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 60);
	};
};


class floting_dot : public effectbase{
public:
	floting_dot(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double v_rate = Random::FRand(0.6, 1.3);
		double ang = Random::FRadRand();
		vx = 6 * v_rate * cos(ang);
		vy = 6 * v_rate * sin(ang);
		double ang_a = Random::FRadRand();
		ax = 0.2 * v_rate * cos(ang_a);
		ay = 0.2 * v_rate * sin(ang_a);
		set(x, y, 16, 16, 1.0, 1.0, ang,
			100, vx, vy, ax, ay, 0.0, 0.0, 0.9,
			0.0, -1.66, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 60);
	};
};

class fire_dot : public effectbase{
public:
	fire_dot(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double spd = Random::FRand(0.6, 1.3);
		double ang = Random::FRadRand(-100, -80);
		double vx = 8 * spd * cos(ang);
		double vy = 8 * spd * sin(ang);
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			80, vx, vy, 0.0, 0.0, -0.05, -0.05, 0.95,
			0.0, -4, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
	};
	void move(){
		x += vx;
		y += vy;

		vx += ax;
		vy += ay;

		vx *= sppedrate;
		vy *= sppedrate;

		exratex += exratexplus;
		exratey += exrateyplus;

		angle += angleplus;
		alpha = Func::linef(0, 100, elapsedtime, 20);
	}
};

class splash_gravity : public effectbase{
public:
	splash_gravity(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double spd = Random::FRand(0.6, 1.3);
		double ang = Random::FRadRand() * 0.2 - PI * 0.5;
		double vvx = 6 * spd * cos(ang);
		double vvy = 4 * spd * sin(ang);
		set(x, y, 16, 16, 1.0, 1.0, 0,
			100, vvx, vvy, 0.0, 0.5, 0.0, 0.0, 1.0,
			0.0, -1, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 60);
	};
};


class splash_thin : public effectbase{
public:
	splash_thin(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double ang = Random::FRadRand();
		double spd = Random::FRand(0.6, 1.3) * 7;
		double vx = spd * cos(ang);
		double vy = spd * sin(ang);

		set(x, y, 16, 16, 1.0, 0.5, ang,
			220, vx, vy, 0.0, 0.0, 0, -0.033, 0.99,
			0.0, -10, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 15);
	};
};

class smoke : public effectbase{
public:
	smoke(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, -3, 0.0, 0.0, -0.05, -0.05, 0.99,
			0.0, -10, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
	};
};


class dotmove : public effectbase{
public:
	dotmove(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 0.5, 0.5, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
			0.0, 0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 300);

	};

};