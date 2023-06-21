#pragma once

#include"Model.h"
#include"Camera.h"

#include<Windows.h>
#include<wrl.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<DirectXMath.h>
#include<string>

class Object3d
{
protected: //エイリアス
	//Microsoft::WRL::を省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: //静的メンバー関数
	//Setter
	static void SetDevice(ID3D12Device* device) { Object3d::device = device; }
	static void SetCamera(Camera* camera) { Object3d::camera = camera; }

	///<summay>
	///毎フレーム処理
	///<summay>
	void Update();

	///<summay>
	///モデルのセット
	///<summay>
	void SetModel(Model* model) { this->model = model; }
	
private: //静的メンバー変数
	//デバイス
	static ID3D12Device* device;
	//カメラ
	static Camera* camera;

public: //サブクラス
	//定数バッファ用データ構造体
	struct  ConstBufferDataTransform
	{
		XMMATRIX viewproj; //ビュープロダクション行列
		XMMATRIX world;    //ワールド行列
		XMFLOAT3 cameraPos; //カメラ座標(ワールド座標)
	};
public: //メンバ関数
	///<summary>
	///初期化
	///</summary>
	void Initialize();

	///<summary>
	///グラフィックパイプラインの生成
	///</summary>
	static void CreateGraphicsPipeline();

	///<summary>
	///描画
	///</summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

protected: //メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource>constBuffTransform;

	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;

	//ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	//X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	//ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	//ローカルワールド変換行列
	XMMATRIX matWorld;
    //モデル
	Model* model = nullptr;

};