#pragma once

#include <DxLib.h>
#include <iostream>

//-------------------------------------------
//
//                 n.i.a.
//
//                         effect draw system
//-------------------------------------------


//effectsの個々のエフェクトの基底クラス

class effectbase{
public:
	double x, y;
	double centerx, centery;
	double exratex, exratey;
	double angle;

	double alpha;
	double vx, vy;
	double ax, ay;
	double exratexplus, exrateyplus;
	double sppedrate;

	double angleplus;
	double alphaplus;
	int turnflag;
	int blendmode;

	int ghandle;
	int *efGHandle;
	
	int elapsedtime;
	int deleteframe;

	bool deleteflag;

	double PI;

	effectbase(int *p_gh) :
		efGHandle(p_gh),
		PI(3.141592653589793),
		x(0),  y(0),
		centerx(0),  centery(0),
		exratex(1.0), exratey(1.0),
		angle(0.0),

		alpha(255.0),
		vx(0.0), vy(0.0),
		ax(0.0), ay(0.0),
		exratexplus(1.0), exrateyplus(1.0),
		sppedrate(1.0),

		angleplus(0.0),
		alphaplus(0.0),
		turnflag(0),
		blendmode(DX_BLENDMODE_NOBLEND),

		elapsedtime(0),
		deleteframe(999),
		deleteflag(false)
	{

	}


	virtual void set(double xx, double yy, 
		double centerx,double centery,
		double exratex,double exratey,
		double angle,

		double alpha,
		double vx,double vy,
		double ax,double ay,
		double exratexplus,double exrateyplus,
		double sppedrate,

		double angleplus,
		double alphaplus,

		int turnflag,
		int blendmode,
		int ghandle,

		int deleteframe
		)
	{
			this->x = xx;
			this->y = yy;
			this->centerx = centerx;
			this->centery = centery;
			this->exratex = exratex;
			this->exratey = exratey;
			this->angle = angle;

			this->alpha = alpha;
			this->vx = vx;
			this->vy = vy;
			this->ax = ax;
			this->ay = ay;
			this->exratexplus = exratexplus;
			this->exrateyplus = exrateyplus;
			this->sppedrate = sppedrate;

			this->angleplus = angleplus;
			this->alphaplus = alphaplus;
			this->turnflag = turnflag;
			this->blendmode = blendmode;

			this->ghandle = ghandle;
			
			this->elapsedtime = 0;
			this->deleteframe = deleteframe;
			this->deleteflag = false;
	}

	virtual void move(){
		x += vx;
		y += vy;

		vx += ax;
		vy += ay;

		vx *= sppedrate;
		vy *= sppedrate;

		exratex += exratexplus;
		exratey += exrateyplus;

		angle += angleplus;
		alpha += alphaplus;
	}

	virtual void update(){
		if(elapsedtime > -1){
			move();
		}

		elapsedtime++;

		if(elapsedtime > deleteframe){
			deleteflag = true;
		}
	}

	virtual void draw(){
		if(elapsedtime > -1){
			Draw::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, turnflag, blendmode);
		}
	}

	void wait(int f){
		elapsedtime = -f;
	}

};
