#pragma once

#include<string>
#include<DirectXMath.h>
#include<DirectXTex.h>
#include<Windows.h>
#include<wrl.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<vector>
#include<fbxsdk.h>

//ノード
struct Node
{
	//名前
	std::string name;
	//ローカルスケール
	DirectX::XMVECTOR scaling = { 1,1,1,0 };
	//ローカル回転角
	DirectX::XMVECTOR rotation = { 0,0,0,0 };
	//ローカル移動
	DirectX::XMVECTOR translation = { 0,0,0,1 };
	//ローカル変形行列
	DirectX::XMMATRIX transform;
	//グローバル変形行列
	DirectX::XMMATRIX globalTransform;
	//親ノード
	Node* parent = nullptr;
};

class Model
{
public:
	//フレンドクラス
	friend class FbxLoader;
private:
	//モデル名
	std::string name;
	//ノード配列
	std::vector<Node> nodes;

private:
	//メッシュを持つノード
	Node* meshNode = nullptr;
	
	//頂点インデックス配列
	std::vector<unsigned short>indices;

	//アンビエント係数
	DirectX::XMFLOAT3 ambient = { 1,1,1 };
	//ディフューズ係数
	DirectX::XMFLOAT3 diffuse = { 1,1,1 };
	//テクスチャメタデータ
	DirectX::TexMetadata metadata = {};
	//スクラッチイメージ
	DirectX::ScratchImage scratchImg = {};



	
public:
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//バッファの生成
	void CreateBuffers(ID3D12Device* device);
	

private: //エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr =
		Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetadata = DirectX::TexMetadata;
	using ScratchImage = DirectX::ScratchImage;
	//std::を省略
	using string = std::string;
	template<class T>using Vector =
		std::vector<T>;

private:
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//インデクスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	//インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap>descHeapSRV;



	// 頂点バッファビューの作成
	//D3D12_VERTEX_BUFFER_VIEW vbView{};

public:
	//モデルの変形行列取得
	const XMMATRIX& GetModelTransform()
	{
		return meshNode->globalTransform;
	}


	//ボーン構造体
	struct Bone
	{
		//名前
		std::string name;
		//初期姿勢の進行列
		DirectX::XMMATRIX invIntialPose;
		//クラスタ(FBX側のボーン情報)
		FbxCluster* fbxCluster;
		//コンストラクタ
		Bone(const std::string& name) {
			this->name = name;
		}
	};
private:
	//ボーン配列
	std::vector<Bone> bones;


public:
	//getter
	std::vector<Bone>& GetBones() { return bones; }
	
public://定数

	//ボーンインデックスの最大数
	static const int MAX_BONE_INDICES = 4;

public: //サブクラス
		//頂点データ構造体
		struct VertexPosNormalUvskin
		{
			DirectX::XMFLOAT3 pos; //x,y,z座標
			DirectX::XMFLOAT3 normal; //法線ベクトル
			DirectX::XMFLOAT2 uv; //uv座標
			UINT boneIndex[MAX_BONE_INDICES]; //ボーン　番号
			float boneWeight[MAX_BONE_INDICES]; //ボーン　重み
		};

private:
	std::vector<VertexPosNormalUvskin> vertices;

	FbxScene* fbxScene = nullptr;

public:
	//getter
	FbxScene* GetFbxScene() { return fbxScene; }
	//デストラクタ
	~Model();
};
