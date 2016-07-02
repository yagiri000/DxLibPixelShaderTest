#pragma once

#include <DxLib.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

#include "effectbase.h"
#include "effects.h"

//effectbase�̔z��E�Ǘ��N���X
//�g���Ƃ��͂��̃N���X�̂݃C���X�^���X������΂���


class effectmgr{
public:
	
	std::vector<std::shared_ptr<effectbase>> v;
	int efGHandle[512];

	effectmgr(){
		loadimages();
	}

	void loadimages(){
	}

	//�G�t�F�N�g���� �G�t�F�N�g�ւ̃X�}�[�g�|�C���^��Ԃ�
	template <class T>
	std::shared_ptr<effectbase> add(double x, double y){
		std::shared_ptr<effectbase> p = std::make_shared<T>(x, y, efGHandle);
		v.push_back(p);
		return p;
	}


	//�e�G�t�F�N�g���X�V�E����
	void update(){
		for(auto i : v){
			i->update();
		}
		//deleteflag��true�Ȃ珜��
		auto rmv = std::remove_if(v.begin(), v.end(), 
			[](std::shared_ptr<effectbase> p)->bool{
				return p->deleteflag;
		}
		);
		v.erase(rmv, v.end());
	}

	//�`��
	void draw(){
		for(auto i : v){
			i->draw();
		}
		//�f�o�b�O�p�E���݂̃G�t�F�N�g����\��
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 255 );
		//DrawFormatString(20, 60, 0xFFFFFF, "NUM : %d", v.size()) ;
	}
};