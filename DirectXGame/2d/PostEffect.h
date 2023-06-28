#pragma once
#include "Sprite.h"
class PostEffect :
    public Sprite
{

private: // エイリアス
    // Microsoft::WRL::を省略
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    // DirectX::を省略
    using XMFLOAT2 = DirectX::XMFLOAT2;
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMFLOAT4 = DirectX::XMFLOAT4;
    using XMVECTOR = DirectX::XMVECTOR;
    using XMMATRIX = DirectX::XMMATRIX;

public:
    ///<summary>
    ///コンストラクタ
    ///</summary>
    PostEffect(); 
    
    ///<summary>
    ///初期化
    ///</summary>
    void Initialize();

    ///<summary>
    ///描画コマンドの発行
    ///</summary>
    /// <param name="cmdList">コマンドリスト</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);
    
   //テクスチャバッファ
    ComPtr<ID3D12Resource> texBuff;
    //SRVデスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
};

